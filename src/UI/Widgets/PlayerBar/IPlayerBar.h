#pragma once
#include "../../../Services/PlaybackController.h"
#include "../../../Services/ImageLoader.h"
#include "../AlbumArtLightbox.h"
#include "../AlbumArtBox.h"
#include "../WaveVisualizer.h"
#include <imgui.h>
#include <SDL.h>

namespace moosic
{

    struct PlayerBarTheme
    {
        ImVec4 TextPrimary = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        ImVec4 TextSecondary = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);

        ImVec4 ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        ImVec4 ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        ImVec4 ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

        ImVec4 ButtonPrimary = ImVec4(0.00f, 0.60f, 1.00f, 1.00f);
        ImVec4 ButtonPrimaryHovered = ImVec4(0.20f, 0.70f, 1.00f, 1.00f);
        ImVec4 ButtonPrimaryActive = ImVec4(0.00f, 0.50f, 0.90f, 1.00f);

        ImVec4 SliderTrack = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        ImVec4 SliderGrab = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
        ImVec4 SliderGrabActive = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        float ButtonRounding = 6.0f;
        float SliderRounding = 6.0f;
        float AlbumArtRounding = 4.0f;
        float AlbumArtSize = 60.0f;

        float NormalButtonExtraWidth = 15.0f;
        float PrimaryButtonExtraWidth = 22.0f;
        float ButtonHeightExtra = 3.0f;

        LightboxTheme Lightbox;
        AlbumArtBoxStyle AlbumArtBox;
        WaveVisualizerStyle Visualizer;  // Add this
    };

    class IPlayerBar
    {
    public:
        virtual ~IPlayerBar() = default;
        virtual void Draw() = 0;

        void ApplyTheme(const PlayerBarTheme &theme);
        void SetPlaybackController(PlaybackController *controller);
        void SetRenderer(SDL_Renderer *renderer);
        void UpdatePlaybackState();

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
        void DrawSongInfo();           // Title + Artist in a group
        void DrawPlaybackTimeline();   // Elapsed | Slider | Total
        void DrawControls();           // Prev | Play | Next | Mode | Volume
        void DrawVisualizer();         // Waveform/Spectrum visualizer
        
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
        // Internal
        //--------------------------------------------------------------------------

        void LoadAlbumArt(const MusicTrack *track);
        void UpdateAlbumArtTexture();

    protected:
        PlayerBarTheme m_theme;
        PlaybackController *m_playbackController = nullptr;
        PlaybackMode m_playbackMode = PlaybackMode::Normal;

        bool m_isPlaying = false;
        float m_playbackProgress = 0.0f;
        float m_volume = 0.80f;
        float m_elapsedTime = 0.0f;
        float m_songDuration = 0.0f;
        const char *m_songTitle = "No Song Playing";
        const char *m_artistName = "Unknown Artist";

        bool m_isSeeking = false;
        std::size_t m_lastTrackId = 0;

        SDL_Renderer *m_renderer = nullptr;
        ImageLoader m_imageLoader;
        void *m_albumArtTexture = nullptr;
        std::size_t m_lastAlbumArtTrackId = 0;
        int m_albumArtWidth = 0;
        int m_albumArtHeight = 0;

        AlbumArtLightbox m_lightbox;
        AlbumArtBox m_albumArtBox;
        WaveVisualizer m_visualizer;  // Add this
    };

} // namespace moosic