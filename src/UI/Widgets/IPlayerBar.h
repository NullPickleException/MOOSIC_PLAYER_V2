#pragma once
#include <imgui.h>
#include "../../Services/PlaybackController.h"

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
};

class IPlayerBar
{
public:
    virtual ~IPlayerBar() = default;
    virtual void Draw() = 0;

    void ApplyTheme(const PlayerBarTheme& theme);
    void SetPlaybackController(PlaybackController* controller);
    void UpdatePlaybackState();

protected:
    void PushNormalButtonStyle();
    void PushPrimaryButtonStyle();
    void PushSliderStyle();
    void PushAlbumArtStyle();
    void PopStyle();
    void PopStyleVarOnly();

    void DrawAlbumArt();
    void DrawSongTitle();
    void DrawArtistName();
    void DrawElapsedTime();
    void DrawTotalTime();
    void DrawPlaybackSlider();

    void DrawPreviousButton();
    void DrawPlayPauseButton();
    void DrawNextButton();
    void DrawPlayModeButton();

    void DrawVolumeIcon();
    void DrawVolumeSlider();

    virtual void OnPreviousButtonPressed();
    virtual void OnPlayPauseButtonPressed();
    virtual void OnNextButtonPressed();
    virtual void OnPlaybackSliderChanged(float value);
    virtual void OnVolumeIconPressed();
    virtual void OnVolumeSliderChanged(float value);
    virtual void OnPlayModeButtonPressed();

protected:
    PlayerBarTheme m_theme;
    PlaybackController* m_playbackController = nullptr;
    PlaybackMode m_playbackMode = PlaybackMode::Normal;

    bool m_isPlaying = false;
    float m_playbackProgress = 0.0f;
    float m_volume = 0.80f;
    float m_elapsedTime = 0.0f;
    float m_songDuration = 0.0f;
    const char* m_songTitle = "No Song Playing";
    const char* m_artistName = "Unknown Artist";
    void* m_albumArt = nullptr;
    
    bool m_isSeeking = false;
    std::size_t m_lastTrackId = 0;  // ADDED: Track when track changes
};

} // namespace moosic