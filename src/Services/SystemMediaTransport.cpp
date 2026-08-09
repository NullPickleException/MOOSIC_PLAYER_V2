//==============================================================================
// Services/SystemMediaTransport.cpp
//==============================================================================

#include "SystemMediaTransport.h"
#include <iostream>
#include <string>
#include <cstring>

//==============================================================================
// Windows – System Media Transport Controls
//==============================================================================
#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <wrl.h>
#include <wrl/client.h>
#include <wrl/event.h>
#include <windows.media.h>
#include <windows.storage.streams.h>
#include <systemmediatransportcontrolsinterop.h>

#pragma comment(lib, "runtimeobject.lib")
#pragma comment(lib, "windowsapp.lib")

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Media;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Storage::Streams;

namespace moosic
{

    static std::wstring Utf8ToWide(const std::string &str)
    {
        if (str.empty())
            return std::wstring();

        int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), nullptr, 0);
        std::wstring result(size, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &result[0], size);
        return result;
    }

    class SystemMediaTransport::Impl
    {
    public:
        Impl() = default;
        ~Impl() { Shutdown(); }

        bool Initialize(void *nativeWindowHandle)
        {
            HWND hwnd = static_cast<HWND>(nativeWindowHandle);
            if (!hwnd)
            {
                std::cerr << "[SMTC] Invalid window handle\n";
                return false;
            }

            HRESULT hr = RoInitialize(RO_INIT_MULTITHREADED);
            if (FAILED(hr) && hr != RPC_E_CHANGED_MODE)
            {
                std::cerr << "[SMTC] RoInitialize failed: 0x" << std::hex << hr << std::endl;
                return false;
            }
            m_roInitialized = true;

            ComPtr<ISystemMediaTransportControlsInterop> interop;
            hr = RoGetActivationFactory(
                HStringReference(RuntimeClass_Windows_Media_SystemMediaTransportControls).Get(),
                IID_PPV_ARGS(&interop));

            if (FAILED(hr))
            {
                std::cerr << "[SMTC] Failed to get SMTC interop: 0x" << std::hex << hr << std::endl;
                return false;
            }

            hr = interop->GetForWindow(hwnd, IID_PPV_ARGS(&m_controls));
            if (FAILED(hr))
            {
                std::cerr << "[SMTC] GetForWindow failed: 0x" << std::hex << hr << std::endl;
                return false;
            }

            m_controls->put_IsEnabled(true);
            m_controls->put_IsPlayEnabled(true);
            m_controls->put_IsPauseEnabled(true);
            m_controls->put_IsNextEnabled(true);
            m_controls->put_IsPreviousEnabled(true);
            m_controls->put_IsStopEnabled(true);

            auto buttonHandler = Callback<ITypedEventHandler<
                SystemMediaTransportControls *,
                SystemMediaTransportControlsButtonPressedEventArgs *>>(
                [this](ISystemMediaTransportControls *,
                       ISystemMediaTransportControlsButtonPressedEventArgs *args) -> HRESULT
                {
                    SystemMediaTransportControlsButton button;
                    args->get_Button(&button);

                    if (!m_buttonCallback)
                        return S_OK;

                    switch (button)
                    {
                    case SystemMediaTransportControlsButton_Play:
                        m_buttonCallback(SystemMediaButton::Play);
                        break;
                    case SystemMediaTransportControlsButton_Pause:
                        m_buttonCallback(SystemMediaButton::Pause);
                        break;
                    case SystemMediaTransportControlsButton_Next:
                        m_buttonCallback(SystemMediaButton::Next);
                        break;
                    case SystemMediaTransportControlsButton_Previous:
                        m_buttonCallback(SystemMediaButton::Previous);
                        break;
                    case SystemMediaTransportControlsButton_Stop:
                        m_buttonCallback(SystemMediaButton::Stop);
                        break;
                    default:
                        break;
                    }
                    return S_OK;
                });

            hr = m_controls->add_ButtonPressed(buttonHandler.Get(), &m_buttonToken);
            if (FAILED(hr))
                std::cerr << "[SMTC] Failed to add ButtonPressed handler\n";

            m_controls->put_PlaybackStatus(MediaPlaybackStatus_Closed);
            std::cout << "[SMTC] Initialized successfully\n";
            return true;
        }

        void UpdateInfo(const SystemMediaInfo &info)
        {
            if (!m_controls)
                return;

            ComPtr<ISystemMediaTransportControlsDisplayUpdater> updater;
            m_controls->get_DisplayUpdater(&updater);
            if (!updater)
                return;

            updater->put_Type(MediaPlaybackType_Music);

            ComPtr<IMusicDisplayProperties> musicProps;
            updater->get_MusicProperties(&musicProps);
            if (musicProps)
            {
                std::wstring wTitle  = Utf8ToWide(info.title);
                std::wstring wArtist = Utf8ToWide(info.artist);

                musicProps->put_Title(HStringReference(wTitle.c_str()).Get());
                musicProps->put_Artist(HStringReference(wArtist.c_str()).Get());
            }

            updater->Update();

            if (info.isPlaying)
                m_controls->put_PlaybackStatus(MediaPlaybackStatus_Playing);
            else
                m_controls->put_PlaybackStatus(MediaPlaybackStatus_Paused);

            m_controls->put_IsPlayEnabled(info.canPlay);
            m_controls->put_IsPauseEnabled(info.canPause);
            m_controls->put_IsNextEnabled(info.canNext);
            m_controls->put_IsPreviousEnabled(info.canPrevious);
            m_controls->put_IsStopEnabled(true);
        }

        void Update() {}

        void Shutdown()
        {
            if (m_controls && m_buttonToken.value != 0)
            {
                m_controls->remove_ButtonPressed(m_buttonToken);
                m_buttonToken.value = 0;
            }
            m_controls.Reset();

            if (m_roInitialized)
            {
                RoUninitialize();
                m_roInitialized = false;
            }
        }

        SystemMediaButtonCallback m_buttonCallback;
        SystemMediaSeekCallback   m_seekCallback;

    private:
        ComPtr<ISystemMediaTransportControls> m_controls;
        EventRegistrationToken m_buttonToken{};
        bool m_roInitialized = false;
    };

} // namespace moosic

//==============================================================================
// Linux – MPRIS (D-Bus) when available, otherwise silent stub
//==============================================================================
#elif defined(__linux__) && defined(MOOSIC_HAVE_DBUS)

#include <dbus/dbus.h>
#include <map>
#include <vector>

namespace moosic
{

    class SystemMediaTransport::Impl
    {
    public:
        Impl() = default;
        ~Impl() { Shutdown(); }

        bool Initialize(void *)
        {
            DBusError err;
            dbus_error_init(&err);

            m_conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
            if (dbus_error_is_set(&err) || !m_conn)
            {
                std::cerr << "[MPRIS] Failed to connect to session bus: "
                          << (err.message ? err.message : "unknown") << std::endl;
                dbus_error_free(&err);
                return false;
            }

            // Request well-known name
            int ret = dbus_bus_request_name(m_conn, "org.mpris.MediaPlayer2.moosic",
                                            DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
            if (dbus_error_is_set(&err) || ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
            {
                std::cerr << "[MPRIS] Failed to request name: "
                          << (err.message ? err.message : "unknown") << std::endl;
                dbus_error_free(&err);
                // Non-fatal – continue without name ownership if possible
            }

            // Match method calls on our object path
            dbus_bus_add_match(m_conn,
                "type='method_call',interface='org.mpris.MediaPlayer2.Player',"
                "path='/org/mpris/MediaPlayer2'",
                &err);
            dbus_bus_add_match(m_conn,
                "type='method_call',interface='org.freedesktop.DBus.Properties',"
                "path='/org/mpris/MediaPlayer2'",
                &err);
            dbus_connection_flush(m_conn);

            if (dbus_error_is_set(&err))
            {
                std::cerr << "[MPRIS] add_match failed: " << err.message << std::endl;
                dbus_error_free(&err);
            }

            std::cout << "[MPRIS] Initialized successfully\n";
            return true;
        }

        void UpdateInfo(const SystemMediaInfo &info)
        {
            m_info = info;
            // PropertiesChanged signal is optional for basic functionality
            // Many desktops poll GetAll periodically
        }

        void Update()
        {
            if (!m_conn)
                return;

            dbus_connection_read_write(m_conn, 0);

            DBusMessage *msg;
            while ((msg = dbus_connection_pop_message(m_conn)) != nullptr)
            {
                HandleMessage(msg);
                dbus_message_unref(msg);
            }
        }

        void Shutdown()
        {
            if (m_conn)
            {
                dbus_connection_unref(m_conn);
                m_conn = nullptr;
            }
        }

        SystemMediaButtonCallback m_buttonCallback;
        SystemMediaSeekCallback   m_seekCallback;

    private:
        void HandleMessage(DBusMessage *msg)
        {
            const char *iface = dbus_message_get_interface(msg);
            const char *member = dbus_message_get_member(msg);
            if (!iface || !member)
                return;

            // ---- org.mpris.MediaPlayer2.Player methods ----
            if (strcmp(iface, "org.mpris.MediaPlayer2.Player") == 0)
            {
                if (strcmp(member, "Play") == 0)
                {
                    if (m_buttonCallback) m_buttonCallback(SystemMediaButton::Play);
                    SendEmptyReply(msg);
                }
                else if (strcmp(member, "Pause") == 0)
                {
                    if (m_buttonCallback) m_buttonCallback(SystemMediaButton::Pause);
                    SendEmptyReply(msg);
                }
                else if (strcmp(member, "PlayPause") == 0)
                {
                    if (m_buttonCallback) m_buttonCallback(SystemMediaButton::PlayPause);
                    SendEmptyReply(msg);
                }
                else if (strcmp(member, "Stop") == 0)
                {
                    if (m_buttonCallback) m_buttonCallback(SystemMediaButton::Stop);
                    SendEmptyReply(msg);
                }
                else if (strcmp(member, "Next") == 0)
                {
                    if (m_buttonCallback) m_buttonCallback(SystemMediaButton::Next);
                    SendEmptyReply(msg);
                }
                else if (strcmp(member, "Previous") == 0)
                {
                    if (m_buttonCallback) m_buttonCallback(SystemMediaButton::Previous);
                    SendEmptyReply(msg);
                }
            }
            // ---- org.freedesktop.DBus.Properties ----
            else if (strcmp(iface, "org.freedesktop.DBus.Properties") == 0)
            {
                if (strcmp(member, "Get") == 0)
                    HandlePropertiesGet(msg);
                else if (strcmp(member, "GetAll") == 0)
                    HandlePropertiesGetAll(msg);
            }
        }

        void SendEmptyReply(DBusMessage *call)
        {
            DBusMessage *reply = dbus_message_new_method_return(call);
            if (reply)
            {
                dbus_connection_send(m_conn, reply, nullptr);
                dbus_message_unref(reply);
            }
        }

        void HandlePropertiesGet(DBusMessage *msg)
        {
            const char *iface = nullptr;
            const char *prop  = nullptr;
            DBusError err;
            dbus_error_init(&err);

            if (!dbus_message_get_args(msg, &err,
                                       DBUS_TYPE_STRING, &iface,
                                       DBUS_TYPE_STRING, &prop,
                                       DBUS_TYPE_INVALID))
            {
                dbus_error_free(&err);
                return;
            }

            DBusMessage *reply = dbus_message_new_method_return(msg);
            if (!reply)
                return;

            DBusMessageIter iter, variant;
            dbus_message_iter_init_append(reply, &iter);

            if (strcmp(prop, "PlaybackStatus") == 0)
            {
                const char *status = m_info.isPlaying ? "Playing" : "Paused";
                dbus_message_iter_open_container(&iter, DBUS_TYPE_VARIANT, "s", &variant);
                dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &status);
                dbus_message_iter_close_container(&iter, &variant);
            }
            else if (strcmp(prop, "CanPlay") == 0 ||
                     strcmp(prop, "CanPause") == 0 ||
                     strcmp(prop, "CanGoNext") == 0 ||
                     strcmp(prop, "CanGoPrevious") == 0 ||
                     strcmp(prop, "CanControl") == 0)
            {
                dbus_bool_t v = TRUE;
                dbus_message_iter_open_container(&iter, DBUS_TYPE_VARIANT, "b", &variant);
                dbus_message_iter_append_basic(&variant, DBUS_TYPE_BOOLEAN, &v);
                dbus_message_iter_close_container(&iter, &variant);
            }
            else if (strcmp(prop, "Metadata") == 0)
            {
                AppendMetadataVariant(&iter);
            }
            else
            {
                // Unknown property – return empty string variant
                const char *empty = "";
                dbus_message_iter_open_container(&iter, DBUS_TYPE_VARIANT, "s", &variant);
                dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &empty);
                dbus_message_iter_close_container(&iter, &variant);
            }

            dbus_connection_send(m_conn, reply, nullptr);
            dbus_message_unref(reply);
        }

        void HandlePropertiesGetAll(DBusMessage *msg)
        {
            DBusMessage *reply = dbus_message_new_method_return(msg);
            if (!reply)
                return;

            DBusMessageIter iter, array, entry, variant;
            dbus_message_iter_init_append(reply, &iter);
            dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "{sv}", &array);

            // PlaybackStatus
            {
                const char *key = "PlaybackStatus";
                const char *status = m_info.isPlaying ? "Playing" : "Paused";
                dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, nullptr, &entry);
                dbus_message_iter_append_basic(&entry, DBUS_TYPE_STRING, &key);
                dbus_message_iter_open_container(&entry, DBUS_TYPE_VARIANT, "s", &variant);
                dbus_message_iter_append_basic(&variant, DBUS_TYPE_STRING, &status);
                dbus_message_iter_close_container(&entry, &variant);
                dbus_message_iter_close_container(&array, &entry);
            }

            // CanPlay / CanPause / CanGoNext / CanGoPrevious / CanControl
            auto appendBool = [&](const char *key, dbus_bool_t value)
            {
                DBusMessageIter e, v;
                dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, nullptr, &e);
                dbus_message_iter_append_basic(&e, DBUS_TYPE_STRING, &key);
                dbus_message_iter_open_container(&e, DBUS_TYPE_VARIANT, "b", &v);
                dbus_message_iter_append_basic(&v, DBUS_TYPE_BOOLEAN, &value);
                dbus_message_iter_close_container(&e, &v);
                dbus_message_iter_close_container(&array, &e);
            };
            appendBool("CanPlay", TRUE);
            appendBool("CanPause", TRUE);
            appendBool("CanGoNext", TRUE);
            appendBool("CanGoPrevious", TRUE);
            appendBool("CanControl", TRUE);

            // Metadata
            {
                const char *key = "Metadata";
                dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, nullptr, &entry);
                dbus_message_iter_append_basic(&entry, DBUS_TYPE_STRING, &key);
                AppendMetadataVariant(&entry);
                dbus_message_iter_close_container(&array, &entry);
            }

            dbus_message_iter_close_container(&iter, &array);
            dbus_connection_send(m_conn, reply, nullptr);
            dbus_message_unref(reply);
        }

        void AppendMetadataVariant(DBusMessageIter *parent)
        {
            DBusMessageIter variant, array, entry, var;
            dbus_message_iter_open_container(parent, DBUS_TYPE_VARIANT, "a{sv}", &variant);
            dbus_message_iter_open_container(&variant, DBUS_TYPE_ARRAY, "{sv}", &array);

            auto appendString = [&](const char *key, const std::string &value)
            {
                const char *v = value.c_str();
                dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, nullptr, &entry);
                dbus_message_iter_append_basic(&entry, DBUS_TYPE_STRING, &key);
                dbus_message_iter_open_container(&entry, DBUS_TYPE_VARIANT, "s", &var);
                dbus_message_iter_append_basic(&var, DBUS_TYPE_STRING, &v);
                dbus_message_iter_close_container(&entry, &var);
                dbus_message_iter_close_container(&array, &entry);
            };

            appendString("xesam:title",  m_info.title.empty()  ? "Unknown" : m_info.title);
            appendString("xesam:artist", m_info.artist.empty() ? "Unknown" : m_info.artist);
            appendString("xesam:album",  m_info.album.empty()  ? ""        : m_info.album);

            // Length in microseconds
            {
                const char *key = "mpris:length";
                int64_t lengthUs = static_cast<int64_t>(m_info.durationSeconds * 1000000.0);
                dbus_message_iter_open_container(&array, DBUS_TYPE_DICT_ENTRY, nullptr, &entry);
                dbus_message_iter_append_basic(&entry, DBUS_TYPE_STRING, &key);
                dbus_message_iter_open_container(&entry, DBUS_TYPE_VARIANT, "x", &var);
                dbus_message_iter_append_basic(&var, DBUS_TYPE_INT64, &lengthUs);
                dbus_message_iter_close_container(&entry, &var);
                dbus_message_iter_close_container(&array, &entry);
            }

            dbus_message_iter_close_container(&variant, &array);
            dbus_message_iter_close_container(parent, &variant);
        }

        DBusConnection *m_conn = nullptr;
        SystemMediaInfo m_info;
    };

} // namespace moosic

//==============================================================================
// Linux without D-Bus / macOS / other – silent no-op stub
//==============================================================================
#else

namespace moosic
{
    class SystemMediaTransport::Impl
    {
    public:
        bool Initialize(void *)
        {
            // Platform has no system media transport implementation.
            // This is intentional – the rest of the player still works.
            return true;
        }
        void UpdateInfo(const SystemMediaInfo &) {}
        void Update() {}
        void Shutdown() {}

        SystemMediaButtonCallback m_buttonCallback;
        SystemMediaSeekCallback   m_seekCallback;
    };
}

#endif

//==============================================================================
// Common implementation (all platforms)
//==============================================================================

namespace moosic
{

    SystemMediaTransport::SystemMediaTransport()
    {
        m_impl = new Impl();
    }

    SystemMediaTransport::~SystemMediaTransport()
    {
        Shutdown();
        delete m_impl;
        m_impl = nullptr;
    }

    bool SystemMediaTransport::Initialize(void *nativeWindowHandle)
    {
        if (!m_impl)
            return false;

        m_initialized = m_impl->Initialize(nativeWindowHandle);
        return m_initialized;
    }

    void SystemMediaTransport::UpdateInfo(const SystemMediaInfo &info)
    {
        if (m_impl && m_initialized)
            m_impl->UpdateInfo(info);
    }

    void SystemMediaTransport::SetButtonCallback(SystemMediaButtonCallback callback)
    {
        if (m_impl)
            m_impl->m_buttonCallback = std::move(callback);
    }

    void SystemMediaTransport::SetSeekCallback(SystemMediaSeekCallback callback)
    {
        if (m_impl)
            m_impl->m_seekCallback = std::move(callback);
    }

    void SystemMediaTransport::Update()
    {
        if (m_impl && m_initialized)
            m_impl->Update();
    }

    void SystemMediaTransport::Shutdown()
    {
        if (m_impl)
            m_impl->Shutdown();
        m_initialized = false;
    }

} // namespace moosic