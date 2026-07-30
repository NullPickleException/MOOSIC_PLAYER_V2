#pragma once
#include <imgui.h>
#include <SDL.h>

namespace moosic
{
    
struct LightboxTheme
{
    // Colors
    ImVec4 BackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
    ImVec4 BorderColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    ImVec4 CloseButtonColor = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
    ImVec4 CloseButtonHovered = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 TitleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 ArtistColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    
    // Sizing
    float MaxWidth = 400.0f;
    float MaxHeight = 400.0f;
    float BorderRounding = 4.0f;
    float BorderThickness = 1.0f;
    float CloseButtonSize = 24.0f;
    float Padding = 30.0f;
    float TitleSpacing = 12.0f;
    float ArtistSpacing = 8.0f;

    //--------------------------------------------------------------------------
    // Classic 2000s Lightbox Effects
    //--------------------------------------------------------------------------
    
    bool UseLightboxGloss = false;
    float LightboxGlossIntensity = 0.0f;
    ImVec4 LightboxGlossColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    
    bool UseLightboxGradient = false;
    ImVec4 LightboxGradientTop = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
    ImVec4 LightboxGradientBottom = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
    
    bool UseGlossyCloseButton = false;
    float CloseButtonGlossIntensity = 0.0f;
};

class AlbumArtLightbox
{
public:
    AlbumArtLightbox() = default;
    
    void SetTexture(void* texture, int width, int height);
    void SetInfo(const char* title, const char* artist);
    
    void ApplyTheme(const LightboxTheme& theme) { m_theme = theme; }
    
    void Toggle();
    void Show();
    void Hide();
    bool IsVisible() const { return m_visible; }
    
    void Draw();

private:
    void* m_texture = nullptr;
    int m_width = 0;
    int m_height = 0;
    const char* m_title = "";
    const char* m_artist = "";
    LightboxTheme m_theme;
    bool m_visible = false;
};

} // namespace moosic