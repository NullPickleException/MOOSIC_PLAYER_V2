//==============================================================================
// Services/SystemMediaTransport.h
// Cross-platform system media transport controls
//==============================================================================

#pragma once

#include <string>
#include <functional>

namespace moosic
{

    enum class SystemMediaButton
    {
        Play,
        Pause,
        PlayPause,
        Next,
        Previous,
        Stop
    };

    struct SystemMediaInfo
    {
        std::string title;
        std::string artist;
        std::string album;
        std::string albumArtPath; // Path to album art file (optional)
        double durationSeconds = 0.0;
        double positionSeconds = 0.0;
        bool isPlaying = false;
        bool canPlay = true;
        bool canPause = true;
        bool canNext = true;
        bool canPrevious = true;
        bool canSeek = true;
    };

    // Callback types
    using SystemMediaButtonCallback = std::function<void(SystemMediaButton)>;
    using SystemMediaSeekCallback = std::function<void(double positionSeconds)>;

    class SystemMediaTransport
    {
    public:
        SystemMediaTransport();
        ~SystemMediaTransport();

        // Initialize with the native window handle (HWND on Windows)
        // Pass the SDL window so we can extract the real HWND
        bool Initialize(void* nativeWindowHandle);

        // Update the displayed media info (call when track or state changes)
        void UpdateInfo(const SystemMediaInfo& info);

        // Set callbacks for when the user presses system media buttons
        void SetButtonCallback(SystemMediaButtonCallback callback);
        void SetSeekCallback(SystemMediaSeekCallback callback);

        // Call this periodically (e.g. once per frame)
        void Update();

        // Cleanup
        void Shutdown();

    private:
        class Impl;
        Impl* m_impl = nullptr;
        bool m_initialized = false;
    };

} // namespace moosic