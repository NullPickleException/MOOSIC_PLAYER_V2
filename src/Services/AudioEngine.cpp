#include "AudioEngine.h"

#include <bass.h>
#include <bass_aac.h>
#include <bassflac.h>
#include <bassopus.h>
#include <basswma.h>

#include <iostream>
#include <algorithm>

// BASS defines HSTREAM as DWORD, so we can use it directly

namespace moosic
{

//==============================================================================
// Constructor / Destructor
//==============================================================================

AudioEngine::AudioEngine()
{
    // Initialize BASS
    if (!BASS_Init(-1, 44100, 0, nullptr, nullptr))
    {
        std::cout << "[AudioEngine] Failed to initialize BASS. Error: " 
                  << BASS_ErrorGetCode() << '\n';
        return;
    }

    // Load plugins
#ifdef _WIN32
    BASS_PluginLoad("bass_aac.dll", 0);
    BASS_PluginLoad("bassflac.dll", 0);
    BASS_PluginLoad("bassopus.dll", 0);
    BASS_PluginLoad("basswma.dll", 0);
#endif

    m_bassInitialized = true;
    std::cout << "[AudioEngine] BASS initialized successfully\n";
}

AudioEngine::~AudioEngine()
{
    CloseStream();
    
    if (m_bassInitialized)
    {
        BASS_Free();
        m_bassInitialized = false;
    }
}

//==============================================================================
// Playback Control
//==============================================================================

bool AudioEngine::Open(const MusicTrack& track)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_bassInitialized)
    {
        std::cout << "[AudioEngine] BASS not initialized\n";
        return false;
    }

    CloseStream();

    std::string path = track.GetPath().string();
    std::string ext = track.GetExtension();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    HSTREAM stream = 0;

    // Try appropriate decoder based on extension
    if (ext == "m4a" || ext == "mp4" || ext == "m4b")
    {
        stream = BASS_AAC_StreamCreateFile(FALSE, path.c_str(), 0, 0, 
                                           BASS_STREAM_AUTOFREE);  // REMOVED BASS_STREAM_DECODE
    }

    if (!stream)
    {
        // Generic stream creation - REMOVED BASS_STREAM_DECODE
        stream = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, 
                                       BASS_STREAM_AUTOFREE | BASS_STREAM_PRESCAN);
    }

    if (!stream)
    {
        std::cout << "[AudioEngine] Failed to open: " << track.GetTitle() 
                  << " (Error: " << BASS_ErrorGetCode() << ")\n";
        return false;
    }

    BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, m_volume);

    m_stream = stream;
    m_currentTrack = &track;
    m_state = State::Stopped;

    std::cout << "[AudioEngine] Opened: " << track.GetTitle() 
              << " (" << track.GetDuration() << "s)\n";

    return true;
}

void AudioEngine::Start()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stream == 0)
    {
        std::cout << "[AudioEngine] No track loaded\n";
        return;
    }

    if (m_state == State::Paused)
    {
        // Resume from pause
        BASS_ChannelPlay(m_stream, FALSE);
        m_state = State::Playing;
        std::cout << "[AudioEngine] Resumed\n";
    }
    else if (m_state == State::Stopped)
    {
        // Start from beginning
        BASS_ChannelSetPosition(m_stream, 0, BASS_POS_BYTE);
        BASS_ChannelPlay(m_stream, FALSE);
        m_state = State::Playing;
        std::cout << "[AudioEngine] Started\n";
    }
}

void AudioEngine::Pause()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stream != 0 && m_state == State::Playing)
    {
        BASS_ChannelPause(m_stream);
        m_state = State::Paused;
        std::cout << "[AudioEngine] Paused\n";
    }
}

void AudioEngine::Resume()
{
    Start();
}

void AudioEngine::Stop()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stream != 0)
    {
        BASS_ChannelStop(m_stream);
        BASS_ChannelSetPosition(m_stream, 0, BASS_POS_BYTE);
        m_state = State::Stopped;
        std::cout << "[AudioEngine] Stopped\n";
    }
}

void AudioEngine::TogglePlayPause()
{
    if (m_state == State::Playing)
        Pause();
    else
        Start();
}

//==============================================================================
// Seeking & Volume
//==============================================================================

void AudioEngine::SetPosition(float seconds)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stream == 0)
        return;

    QWORD position = BASS_ChannelSeconds2Bytes(m_stream, seconds);
    BASS_ChannelSetPosition(m_stream, position, BASS_POS_BYTE);
}

void AudioEngine::SetVolume(float volume)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_volume = std::clamp(volume, 0.0f, 1.0f);

    if (m_stream != 0)
    {
        BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, m_volume);
    }
}

//==============================================================================
// Status
//==============================================================================

bool AudioEngine::IsPlaying() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    // Also check BASS state directly
    if (m_stream != 0)
        return BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PLAYING;
    
    return m_state == State::Playing;
}

bool AudioEngine::IsPaused() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    if (m_stream != 0)
        return BASS_ChannelIsActive(m_stream) == BASS_ACTIVE_PAUSED;
    
    return m_state == State::Paused;
}

bool AudioEngine::IsStopped() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_state == State::Stopped;
}

bool AudioEngine::HasTrack() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_stream != 0 && m_currentTrack != nullptr;
}

float AudioEngine::GetPosition() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stream == 0)
        return 0.0f;

    QWORD position = BASS_ChannelGetPosition(m_stream, BASS_POS_BYTE);
    return static_cast<float>(BASS_ChannelBytes2Seconds(m_stream, position));
}

float AudioEngine::GetDuration() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_stream == 0 || !m_currentTrack)
        return 0.0f;

    return static_cast<float>(m_currentTrack->GetDuration());
}

float AudioEngine::GetVolume() const
{
    return m_volume;
}

const MusicTrack* AudioEngine::GetCurrentTrack() const
{
    return m_currentTrack;
}

//==============================================================================
// Internal
//==============================================================================

void AudioEngine::CloseStream()
{
    if (m_stream != 0)
    {
        BASS_StreamFree(m_stream);
        m_stream = 0;
    }

    m_currentTrack = nullptr;
    m_state = State::Stopped;
}

void AudioEngine::UpdatePlaybackState()
{
    // Check if playback finished naturally
    if (m_stream != 0 && m_state == State::Playing)
    {
        if (BASS_ChannelIsActive(m_stream) != BASS_ACTIVE_PLAYING)
        {
            m_state = State::Stopped;
            std::cout << "[AudioEngine] Playback finished\n";
        }
    }
}

} // namespace moosic