//==============================================================================
// AlbumArtBox.h
//==============================================================================
// A flexible album art widget that adapts to any layout size
//==============================================================================

#pragma once

#include <imgui.h>
#include <SDL.h>

namespace moosic
{

//==============================================================================
// AlbumArtBoxTheme
//==============================================================================

struct AlbumArtBoxTheme
{
    // Border
    ImVec4 BorderColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    float BorderThickness = 2.0f;
    float BorderRounding = 6.0f;

    // Background
    ImVec4 BackgroundColor = ImVec4(0.08f, 0.08f, 0.10f, 1.0f);

    // Shadow
    bool ShowShadow = true;
    ImVec4 ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.3f);
    float ShadowOffsetX = 2.0f;
    float ShadowOffsetY = 2.0f;
    float ShadowBlur = 4.0f;

    // Placeholder
    ImVec4 PlaceholderTextColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    const char* PlaceholderText = "No Art";
};

//==============================================================================
// AlbumArtBox
//==============================================================================

class AlbumArtBox
{
public:
    AlbumArtBox();
    ~AlbumArtBox();

    // Theme application - inline
    void ApplyTheme(const AlbumArtBoxTheme& theme) { m_theme = theme; }
    
    void SetTexture(void* texture, int width, int height);
    void ClearTexture();

    // Main drawing function - call with your desired size
    void Draw(float size, float rounding = 0.0f, bool showBorder = true, bool showBackground = true);

    // Click handling
    bool IsClicked() const { return m_wasClicked; }
    bool IsHovered() const { return m_isHovered; }
    void ResetClick() { m_wasClicked = false; }

private:
    void DrawShadow(const ImVec2& pos, const ImVec2& size, float rounding);
    void DrawBackground(const ImVec2& pos, const ImVec2& size, float rounding);
    void DrawBorder(const ImVec2& pos, const ImVec2& size, float rounding);
    void DrawImage(const ImVec2& pos, const ImVec2& size, float rounding);
    void DrawPlaceholder(const ImVec2& pos, const ImVec2& size);

    AlbumArtBoxTheme m_theme;
    void* m_texture = nullptr;
    int m_textureWidth = 0;
    int m_textureHeight = 0;
    bool m_wasClicked = false;
    bool m_isHovered = false;
};

} // namespace moosic