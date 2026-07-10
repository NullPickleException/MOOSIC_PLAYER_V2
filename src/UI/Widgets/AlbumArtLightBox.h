#pragma once
#include <imgui.h>
#include <SDL.h>

namespace moosic
{

struct LightboxTheme
{
    ImVec4 BackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
    ImVec4 BorderColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    ImVec4 CloseButtonColor = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
    ImVec4 CloseButtonHovered = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 TitleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 ArtistColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    
    float MaxWidth = 600.0f;
    float MaxHeight = 600.0f;
    float BorderRounding = 12.0f;
    float CloseButtonSize = 30.0f;
    float Padding = 20.0f;
};

class AlbumArtLightbox
{
public:
    AlbumArtLightbox() = default;
    
    void SetTexture(void* texture, int width, int height);
    void SetInfo(const char* title, const char* artist);
    void SetTheme(const LightboxTheme& theme);
    
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












