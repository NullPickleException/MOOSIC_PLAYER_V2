//==============================================================================
// UI/Widgets/PlayerBar/IPlayerBar.h
//==============================================================================
// Base interface for player bar implementations with theme support.
// Reads all playback state from PlayerBarData (owned by PlaybackController).
// Owns only: theme, renderer reference, album art texture, scroll state,
// and child widgets.
//==============================================================================

#pragma once

#include "../../Data/PlayerBarData.h"
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

class PlaybackController;

//==============================================================================
// PlayerBarTheme
//==============================================================================
struct PlayerBarTheme
{
    //--------------------------------------------------------------------------
    // Text
    //--------------------------------------------------------------------------
    ImVec4 TextPrimary = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    ImVec4 TextSecondary = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);

    //--------------------------------------------------------------------------
    // Buttons
    //--------------------------------------------------------------------------
    ImVec4 ButtonNormal = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    ImVec4 ButtonHovered = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
    ImVec4 ButtonActive = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);

    ImVec4 ButtonPrimary = ButtonNormal;
    ImVec4 ButtonPrimaryHovered = ButtonHovered;
    ImVec4 ButtonPrimaryActive = ButtonActive;

    //--------------------------------------------------------------------------
    // Sliders
    //--------------------------------------------------------------------------
    ImVec4 SliderTrack = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    ImVec4 SliderGrab = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    ImVec4 SliderGrabActive = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);

    //--------------------------------------------------------------------------
    // Sizing
    //--------------------------------------------------------------------------
    float ButtonRounding = 5.0f;
    float SliderRounding = 3.0f;
    float AlbumArtRounding = 0.0f;

    float AlbumArtSize = 56.0f;

    float NormalButtonExtraWidth = 6.0f;
    float PrimaryButtonExtraWidth = 5.0f;
    float ButtonHeightExtra = 0.0f;

    //--------------------------------------------------------------------------
    // Scrolling text
    //--------------------------------------------------------------------------
    float ScrollSpeed = 30.0f;
    float ScrollDelay = 1.5f;

    //--------------------------------------------------------------------------
    // Child Widget Themes
    //--------------------------------------------------------------------------
    LightboxTheme Lightbox;
    AlbumArtBoxTheme AlbumArtBox;
    WaveVisualizerStyle Visualizer;
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

    // Theme application
    void ApplyTheme(const PlayerBarTheme& theme);

    // External dependencies
    void SetPlaybackController(PlaybackController* controller);
    void SetRenderer(SDL_Renderer* renderer);

    //--------------------------------------------------------------------------
    // Album Art Cache - Clears all cached textures (call on library refresh)
    //--------------------------------------------------------------------------
    void ClearAlbumArtCache();

protected:
    //--------------------------------------------------------------------------
    // Data Access (bars read from data, never write to it)
    //--------------------------------------------------------------------------

    const PlayerBarData& Data() const { return *m_data; }
    PlaybackController* Controller() const { return m_playbackController; }

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
    // Drawing Methods - Modular (subclasses override Draw() to arrange)
    //--------------------------------------------------------------------------

    void DrawAlbumArt();
    void DrawSongInfo();
    void DrawPlaybackTimeline();
    void DrawControls();
    void DrawVisualizer();

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
    void DrawScrollingText(const char* text, const ImVec4& color, float maxWidth,
                           float& scrollOffset, float& lastTrackChangeTime, bool trackChanged);
    void DrawElapsedTime();
    void DrawTotalTime();
    void DrawPlaybackSlider();

    //--------------------------------------------------------------------------
    // Event Handlers (subclasses can override)
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
    // Album Art Helpers
    //--------------------------------------------------------------------------

    void LoadAlbumArtForCurrentTrack();
    bool HasAlbumArtTexture() const { return m_albumArtTexture != nullptr; }

    //--------------------------------------------------------------------------
    // Theme (read by drawing methods)
    //--------------------------------------------------------------------------

    PlayerBarTheme m_theme;

    //--------------------------------------------------------------------------
    // Seeking State (only UI mutable state that's not in PlayerBarData)
    //--------------------------------------------------------------------------

    bool m_isSeeking = false;

    //--------------------------------------------------------------------------
    // Child Widgets (protected so subclasses can access for custom layouts)
    //--------------------------------------------------------------------------

    AlbumArtLightbox m_lightbox;
    AlbumArtBox m_albumArtBox;
    WaveVisualizer m_visualizer;

    //--------------------------------------------------------------------------
    // Album Art Texture (protected so subclasses can check for clicks)
    //--------------------------------------------------------------------------

    void* m_albumArtTexture = nullptr;

    //--------------------------------------------------------------------------
    // Album Art Load State (protected so subclasses can reset on track change)
    //--------------------------------------------------------------------------

    bool m_artLoadAttempted = false;

    //--------------------------------------------------------------------------
    // Scrolling text animation state (protected for subclass Draw() methods)
    //--------------------------------------------------------------------------

    float m_titleScrollOffset = 0.0f;
    float m_artistScrollOffset = 0.0f;
    float m_lastTrackChangeTime = 0.0f;

    bool m_wasSeeking = false; 

private:
    //--------------------------------------------------------------------------
    // Internal Helpers
    //--------------------------------------------------------------------------

    void LoadAlbumArtFromData();
    void DestroyAlbumArtTexture();
    void SyncChildWidgets();

    //--------------------------------------------------------------------------
    // Members
    //--------------------------------------------------------------------------

    // External dependencies (set once)
    PlaybackController* m_playbackController = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    // Pointer to controller's PlayerBarData (set from controller)
    const PlayerBarData* m_data = nullptr;

    // Rendering
    ImageLoader m_imageLoader;

    // Album Art Texture tracking
    std::size_t m_lastAlbumArtTrackId = 0;
    int m_albumArtWidth = 0;
    int m_albumArtHeight = 0;

    int m_lastVisualizerMode = 0;
};

} // namespace moosic