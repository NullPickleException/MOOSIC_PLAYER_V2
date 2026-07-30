//==============================================================================
// AlbumArtBox.h
//==============================================================================

#pragma once

#include <imgui.h>
#include <SDL.h>

namespace moosic
{

struct AlbumArtBoxTheme
{
    //--------------------------------------------------------------------------
    // Border
    //--------------------------------------------------------------------------

    ImVec4 BorderColor         = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    ImVec4 BorderColorHovered  = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    ImVec4 BorderColorClicked  = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    float BorderThickness      = 1.0f;
    float BorderThicknessHovered = 2.0f;
    float BorderRounding       = 0.0f;

    //--------------------------------------------------------------------------
    // Background
    //--------------------------------------------------------------------------

    ImVec4 BackgroundColor       = ImVec4(0.08f, 0.08f, 0.10f, 1.0f);
    ImVec4 BackgroundColorHovered = ImVec4(0.12f, 0.12f, 0.15f, 1.0f);

    //--------------------------------------------------------------------------
    // Overlay
    //--------------------------------------------------------------------------

    bool ShowHoverOverlay         = true;
    ImVec4 HoverOverlayColor      = ImVec4(1.0f, 1.0f, 1.0f, 0.08f);
    ImVec4 ClickOverlayColor      = ImVec4(1.0f, 1.0f, 1.0f, 0.15f);

    //--------------------------------------------------------------------------
    // Shadow
    //--------------------------------------------------------------------------

    bool ShowShadow       = false;
    ImVec4 ShadowColor    = ImVec4(0.0f, 0.0f, 0.0f, 0.3f);
    float ShadowOffsetX   = 2.0f;
    float ShadowOffsetY   = 2.0f;
    float ShadowBlur      = 4.0f;

    //--------------------------------------------------------------------------
    // Placeholder
    //--------------------------------------------------------------------------

    ImVec4 PlaceholderTextColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    const char* PlaceholderText = "No Art";

    //--------------------------------------------------------------------------
    // Play Button Overlay
    //--------------------------------------------------------------------------

    bool ShowPlayButtonOnHover      = false;
    ImVec4 PlayButtonColor          = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
    ImVec4 PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
    float PlayButtonSize            = 0.35f;

    //--------------------------------------------------------------------------
    // Classic 2000s Album Art Effects
    //--------------------------------------------------------------------------
    
    bool UseGlossyOverlay = false;
    float GlossyIntensity = 0.0f;
    ImVec4 GlossyHighlightColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    
    bool UseInnerShadow = false;
    ImVec4 InnerShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    float InnerShadowSize = 0.0f;
    
    bool UseReflection = false;
    float ReflectionHeight = 0.0f;
    float ReflectionOpacity = 0.0f;
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
    void DrawHoverOverlay(const ImVec2& pos, const ImVec2& size, float rounding);
    void DrawPlayButton(const ImVec2& pos, const ImVec2& size);

    AlbumArtBoxTheme m_theme;
    void* m_texture = nullptr;
    int m_textureWidth = 0;
    int m_textureHeight = 0;
    bool m_wasClicked = false;
    bool m_isHovered = false;
    bool m_isMouseDown = false;
};

} // namespace moosic