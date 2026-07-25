//==============================================================================
// IPlayerBar.h
//==============================================================================
// Base interface for player bar implementations with theme support
// Provides common functionality for audio playback controls, album art,
// and visualizers
//==============================================================================

#pragma once

#include "../../../Services/PlaybackController.h"
#include "../../../Services/ImageLoader.h"
#include "../AlbumArtLightBox.h"
#include "../AlbumArtBox.h"
#include "../WaveVisualizer.h"
#include <imgui.h>
#include <SDL.h>
#include <string>
#include <unordered_map>

namespace moosic
{

    //==============================================================================
    // PlayerBarTheme
    //==============================================================================
    struct PlayerBarTheme
    {
        //==========================================================================
        // Text
        //==========================================================================
        ImVec4 TextPrimary = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        ImVec4 TextSecondary = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);

        //==========================================================================
        // Buttons
        //==========================================================================
        ImVec4 ButtonNormal = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        ImVec4 ButtonHovered = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        ImVec4 ButtonActive = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);

        ImVec4 ButtonPrimary = ButtonNormal;
        ImVec4 ButtonPrimaryHovered = ButtonHovered;
        ImVec4 ButtonPrimaryActive = ButtonActive;

        //==========================================================================
        // Sliders
        //==========================================================================
        ImVec4 SliderTrack = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
        ImVec4 SliderGrab = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
        ImVec4 SliderGrabActive = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

        //==========================================================================
        // Classic Dear ImGui sizing
        //==========================================================================
        float ButtonRounding = 5.0f;
        float SliderRounding = 3.0f;
        float AlbumArtRounding = 0.0f;

        float AlbumArtSize = 56.0f;

        float NormalButtonExtraWidth = 6.0f;
        float PrimaryButtonExtraWidth = 5.0f;
        float ButtonHeightExtra = 0.0f;

        //==========================================================================
        // Scrolling text
        //==========================================================================
        float ScrollSpeed = 30.0f;       // Pixels per second
        float ScrollDelay = 1.5f;        // Seconds before scrolling starts

        //==========================================================================
        // Child Widget Themes
        //==========================================================================
        LightboxTheme Lightbox;
        AlbumArtBoxTheme AlbumArtBox;
        WaveVisualizerStyle Visualizer;
    };

    //==============================================================================
    // Album Art Cache Entry
    //==============================================================================
    struct CachedAlbumArt
    {
        void* texture = nullptr;
        int width = 0;
        int height = 0;
    };

    //==============================================================================
    // IPlayerBar - Base Interface
    //==============================================================================

    class IPlayerBar
    {
    public:
        virtual ~IPlayerBar() = default;

        //--------------------------------------------------------------------------
        // Core Interface
        //--------------------------------------------------------------------------

        virtual void Draw() = 0;

        // Theme application - implemented inline
        void ApplyTheme(const PlayerBarTheme &theme);

        // External dependencies
        void SetPlaybackController(PlaybackController *controller);
        void SetRenderer(SDL_Renderer *renderer);
        void UpdatePlaybackState();
        
        //--------------------------------------------------------------------------
        // Album Art Cache - Clears all cached textures (call on library refresh)
        //--------------------------------------------------------------------------
        void ClearAlbumArtCache();

    protected:
        //--------------------------------------------------------------------------
        // Style Helpers
        //--------------------------------------------------------------------------

        void PushNormalButtonStyle();
        void PushPrimaryButtonStyle();
        void PushSliderStyle();
        void PushAlbumArtStyle();
        void PopStyle();
        void PopStyleVarOnly();

        //--------------------------------------------------------------------------
        // Drawing Methods - Modular
        //--------------------------------------------------------------------------

        void DrawAlbumArt();
        void DrawSongInfo();         // Title + Artist in a group
        void DrawPlaybackTimeline(); // Elapsed | Slider | Total
        void DrawControls();         // Prev | Play | Next | Mode | Volume
        void DrawVisualizer();       // Waveform/Spectrum visualizer

        // Individual control drawers
        void DrawPreviousButton();
        void DrawPlayPauseButton();
        void DrawNextButton();
        void DrawPlayModeButton();
        void DrawVolumeIcon();
        void DrawVolumeSlider();

        //--------------------------------------------------------------------------
        // Drawing - Song Info Helpers
        //--------------------------------------------------------------------------

        void DrawSongTitle();
        void DrawArtistName();
        void DrawScrollingText(const char* text, const ImVec4& color, float maxWidth, float& scrollOffset, float& lastTrackChangeTime, bool trackChanged);
        void DrawElapsedTime();
        void DrawTotalTime();
        void DrawPlaybackSlider();

        //--------------------------------------------------------------------------
        // Event Handlers
        //--------------------------------------------------------------------------

        virtual void OnPreviousButtonPressed();
        virtual void OnPlayPauseButtonPressed();
        virtual void OnNextButtonPressed();
        virtual void OnPlaybackSliderChanged(float value);
        virtual void OnVolumeIconPressed();
        virtual void OnVolumeSliderChanged(float value);
        virtual void OnPlayModeButtonPressed();
        virtual void OnAlbumArtClicked();

        //--------------------------------------------------------------------------
        // Internal Helpers
        //--------------------------------------------------------------------------

        void LoadAlbumArt(const MusicTrack *track);
        void UpdateAlbumArtTexture();
        
        // Album art cache lookup
        CachedAlbumArt* GetCachedArt(std::size_t trackId);
        void CacheArt(std::size_t trackId, void* texture, int width, int height);

        //--------------------------------------------------------------------------
        // Member Variables
        //--------------------------------------------------------------------------

        // Theme
        PlayerBarTheme m_theme;

        // Playback
        PlaybackController *m_playbackController = nullptr;
        PlaybackMode m_playbackMode = PlaybackMode::Normal;

        // Playback State
        bool m_isPlaying = false;
        float m_playbackProgress = 0.0f;
        float m_volume = 0.80f;
        float m_elapsedTime = 0.0f;
        float m_songDuration = 0.0f;
        const char *m_songTitle = "No Song Playing";
        const char *m_artistName = "Unknown Artist";

        // Seeking
        bool m_isSeeking = false;
        std::size_t m_lastTrackId = 0;

        // Rendering
        SDL_Renderer *m_renderer = nullptr;
        ImageLoader m_imageLoader;

        // Album Art
        void *m_albumArtTexture = nullptr;
        std::size_t m_lastAlbumArtTrackId = 0;
        int m_albumArtWidth = 0;
        int m_albumArtHeight = 0;
        
        // Album Art Cache - persists across track changes during session
        std::unordered_map<std::size_t, CachedAlbumArt> m_albumArtCache;

        // Scrolling text state
        float m_titleScrollOffset = 0.0f;
        float m_artistScrollOffset = 0.0f;
        float m_lastTrackChangeTime = 0.0f;

        // Child Widgets
        AlbumArtLightbox m_lightbox;
        AlbumArtBox m_albumArtBox;
        WaveVisualizer m_visualizer;

        int m_lastVisualizerMode = 0;

        bool m_artLoadAttempted = false;
    };

} // namespace moosic