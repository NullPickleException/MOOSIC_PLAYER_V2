//==============================================================================
// UI/Widgets/PlayerBar/IPlayerBar.h
//==============================================================================
// Base interface for player bar implementations with theme support.
// Reads all playback state from PlayerBarData (owned by PlaybackController).
// Owns only: theme, renderer reference, album art texture, scroll state,
// child widgets, and track options dropdown.
//==============================================================================

#pragma once

#include "../../Data/PlayerBarData.h"
#include "../../../Services/ImageLoader.h"
#include "../AlbumArtLightBox.h"
#include "../AlbumArtBox.h"
#include "../WaveVisualizer.h"
#include "../PopupMenu.h"
#include "../EditTrackDialog.h"

#include <imgui.h>
#include <SDL.h>

#include <string>
#include <unordered_map>
#include <functional>

namespace moosic
{

    class PlaybackController;

    //==========================================================================
    // PlayerBarTheme
    //==========================================================================
    struct PlayerBarTheme
    {
        //----------------------------------------------------------------------
        // Text
        //----------------------------------------------------------------------
        ImVec4 TextPrimary = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        ImVec4 TextSecondary = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);

        //----------------------------------------------------------------------
        // Buttons
        //----------------------------------------------------------------------
        ImVec4 ButtonNormal = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        ImVec4 ButtonHovered = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        ImVec4 ButtonActive = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);

        ImVec4 ButtonPrimary = ButtonNormal;
        ImVec4 ButtonPrimaryHovered = ButtonHovered;
        ImVec4 ButtonPrimaryActive = ButtonActive;

        //----------------------------------------------------------------------
        // Sliders
        //----------------------------------------------------------------------
        ImVec4 SliderTrack = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
        ImVec4 SliderGrab = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
        ImVec4 SliderGrabActive = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

        //----------------------------------------------------------------------
        // Classic 2000s Slider Effects (default: off)
        //----------------------------------------------------------------------
        bool UseSliderTrackGradient = false;
        ImVec4 SliderTrackGradientTop = ImVec4(0.28f, 0.28f, 0.30f, 1.00f);
        ImVec4 SliderTrackGradientBottom = ImVec4(0.18f, 0.18f, 0.20f, 1.00f);

        bool UseSliderGrabGloss = false;
        float SliderGrabGlossIntensity = 0.0f;
        ImVec4 SliderGrabGlossHighlight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);

        bool UseSliderGrabBevel = false;
        float SliderGrabBevelThickness = 0.0f;
        ImVec4 SliderGrabBevelLight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
        ImVec4 SliderGrabBevelDark = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        ImVec4 SliderGrabBevelBorderColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        //----------------------------------------------------------------------
        // Sizing
        //----------------------------------------------------------------------
        float ButtonRounding = 5.0f;
        float SliderRounding = 3.0f;
        float AlbumArtRounding = 0.0f;

        float AlbumArtSize = 56.0f;

        float NormalButtonExtraWidth = 6.0f;
        float PrimaryButtonExtraWidth = 5.0f;
        float ButtonHeightExtra = 0.0f;

        float OptionsButtonWidth = 28.0f;

        //----------------------------------------------------------------------
        // Scrolling text
        //----------------------------------------------------------------------
        float ScrollSpeed = 30.0f;
        float ScrollDelay = 1.5f;

        //----------------------------------------------------------------------
        // Child Widget Themes
        //----------------------------------------------------------------------
        LightboxTheme Lightbox;
        AlbumArtBoxTheme AlbumArtBox;
        WaveVisualizerStyle Visualizer;

        //----------------------------------------------------------------------
        // Classic 2000s Progress Bar Effects (default: off)
        //----------------------------------------------------------------------
        ImVec4 ProgressTrackColor = ImVec4(0.24f, 0.24f, 0.24f, 1.0f);
        ImVec4 ProgressFillColor = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
        ImVec4 ProgressFillTop = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
        ImVec4 ProgressFillBottom = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
        bool UseProgressGradient = false;
        bool ShowProgressGloss = false;
        float ProgressGlossOpacity = 0.0f;
        float ProgressHeight = 8.0f;
        float ProgressRounding = 4.0f;

        //----------------------------------------------------------------------
        // Classic 2000s Button Effects (default: off)
        //----------------------------------------------------------------------
        bool UseButtonGloss = false;
        float ButtonGlossIntensity = 0.0f;
        ImVec4 ButtonGlossHighlight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);

        bool UseButtonBevel = false;
        float ButtonBevelThickness = 0.0f;
        ImVec4 ButtonBevelLight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
        ImVec4 ButtonBevelDark = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        ImVec4 ButtonBevelBorderColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

        //----------------------------------------------------------------------
        // Classic 2000s Player Bar Background (default: off)
        //----------------------------------------------------------------------
        bool UsePlayerBarGradient = false;
        ImVec4 PlayerBarGradientTop = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);
        ImVec4 PlayerBarGradientBottom = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);
        float PlayerBarGradientRounding = 0.0f;
        float PlayerBarOpacity = 1.0f;

        bool UsePlayerBarBevel = false;
        float PlayerBarBevelThickness = 0.0f;
        ImVec4 PlayerBarBevelLight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
        ImVec4 PlayerBarBevelDark = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        ImVec4 PlayerBarBevelBorderColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    };

    //==========================================================================
    // IPlayerBar - Base Interface
    //==========================================================================

    class IPlayerBar
    {
    public:
        IPlayerBar();
        virtual ~IPlayerBar() { delete m_editTrackDialog; }

        //----------------------------------------------------------------------
        // Core Interface
        //----------------------------------------------------------------------

        virtual void Draw() = 0;

        void ApplyTheme(const PlayerBarTheme &theme);
        void SetPlaybackController(PlaybackController *controller);
        void SetRenderer(SDL_Renderer *renderer);

        // Track options callbacks
        void SetOnEditTrackInfo(std::function<void()> callback) { m_onEditTrackInfo = std::move(callback); }
        void SetOnOpenTrackFolder(std::function<void()> callback) { m_onOpenTrackFolder = std::move(callback); }
        void SetEditTrackDialog(EditTrackDialog *dialog) { m_editTrackDialog = dialog; }

        void ClearAlbumArtCache();

    protected:
        //----------------------------------------------------------------------
        // Data Access
        //----------------------------------------------------------------------

        const PlayerBarData &Data() const { return *m_data; }
        PlaybackController *Controller() const { return m_playbackController; }

        //----------------------------------------------------------------------
        // Style Helpers
        //----------------------------------------------------------------------

        void PushNormalButtonStyle();
        void PushPrimaryButtonStyle();
        void PushSliderStyle();
        void PushAlbumArtStyle();
        void PopStyle();
        void PopStyleVarOnly();
        void PopSliderStyle();

        //----------------------------------------------------------------------
        // Classic 2000s Rendering Helpers
        //----------------------------------------------------------------------

        void DrawGlossOverlay(const ImVec2 &min, const ImVec2 &max, float rounding);
        void DrawBevelEdges(const ImVec2 &min, const ImVec2 &max, float rounding);
        void DrawButtonGradientBg(const ImVec2 &min, const ImVec2 &max, float rounding,
                                  const ImVec4 &colorTop, const ImVec4 &colorBottom);
        void DrawClassicButtonDecorations(const ImVec2 &min, const ImVec2 &max);
        void DrawPlayerBarBackground(const ImVec2 &pos, const ImVec2 &size);
        void DrawSliderGradientBg(const ImVec2 &min, const ImVec2 &max, float rounding);
        void DrawClassicSliderDecorations(const ImVec2 &min, const ImVec2 &max);

        //----------------------------------------------------------------------
        // Drawing Methods
        //----------------------------------------------------------------------

        void DrawAlbumArt();
        void DrawSongInfo();
        void DrawPlaybackTimeline();
        void DrawControls();
        void DrawVisualizer();
        void DrawTrackOptionsButton();

        void DrawPreviousButton();
        void DrawPlayPauseButton();
        void DrawNextButton();
        void DrawPlayModeButton();
        void DrawVolumeIcon();
        void DrawVolumeSlider();

        void DrawSongTitle();
        void DrawArtistName();
        void DrawScrollingText(const char *text, const ImVec4 &color, float maxWidth,
                               float &scrollOffset, float &lastTrackChangeTime, bool trackChanged);
        void DrawElapsedTime();
        void DrawTotalTime();
        void DrawPlaybackSlider();

        //----------------------------------------------------------------------
        // Event Handlers
        //----------------------------------------------------------------------

        virtual void OnPreviousButtonPressed();
        virtual void OnPlayPauseButtonPressed();
        virtual void OnNextButtonPressed();
        virtual void OnPlaybackSliderChanged(float value);
        virtual void OnVolumeIconPressed();
        virtual void OnVolumeSliderChanged(float value);
        virtual void OnPlayModeButtonPressed();
        virtual void OnAlbumArtClicked();
        virtual void OnTrackOptionsClicked();
        void OnEditTrackInfoDefault();
        void OnOpenTrackFolderDefault();
        //----------------------------------------------------------------------
        // Album Art
        //----------------------------------------------------------------------

        void LoadAlbumArtForCurrentTrack();
        bool HasAlbumArtTexture() const { return m_albumArtTexture != nullptr; }

        //----------------------------------------------------------------------
        // Theme & State
        //----------------------------------------------------------------------

        PlayerBarTheme m_theme;
        bool m_isSeeking = false;

        AlbumArtLightbox m_lightbox;
        AlbumArtBox m_albumArtBox;
        WaveVisualizer m_visualizer;

        void *m_albumArtTexture = nullptr;
        bool m_artLoadAttempted = false;

        float m_titleScrollOffset = 0.0f;
        float m_artistScrollOffset = 0.0f;
        float m_lastTrackChangeTime = 0.0f;
        bool m_wasSeeking = false;

        // Track options dropdown
        ContextMenu m_trackOptionsMenu;

        EditTrackDialog *m_editTrackDialog = nullptr;

        bool m_showTrackOptions = false;
        std::function<void()> m_onEditTrackInfo;
        std::function<void()> m_onOpenTrackFolder;

    private:
        //----------------------------------------------------------------------
        // Internal Helpers
        //----------------------------------------------------------------------

        void LoadAlbumArtFromData();
        void DestroyAlbumArtTexture();
        void SyncChildWidgets();

        //----------------------------------------------------------------------
        // Members
        //----------------------------------------------------------------------

        PlaybackController *m_playbackController = nullptr;
        SDL_Renderer *m_renderer = nullptr;
        const PlayerBarData *m_data = nullptr;

        ImageLoader m_imageLoader;

        std::size_t m_lastAlbumArtTrackId = 0;
        int m_albumArtWidth = 0;
        int m_albumArtHeight = 0;
        int m_lastVisualizerMode = 0;
    };

} // namespace moosic