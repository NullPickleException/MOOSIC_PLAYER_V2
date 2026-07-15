//==============================================================================
// AlbumArtBox.cpp
//==============================================================================
// Implementation of a flexible album art widget that adapts to any layout size
//==============================================================================

#include "AlbumArtBox.h"
#include <imgui.h>
#include <cmath>

namespace moosic
{

AlbumArtBox::AlbumArtBox() = default;
AlbumArtBox::~AlbumArtBox() = default;

//==============================================================================
// Configuration
//==============================================================================

// REMOVED: AlbumArtBox::ApplyTheme - Now defined inline in header

void AlbumArtBox::SetTexture(void* texture, int width, int height)
{
    m_texture = texture;
    m_textureWidth = width;
    m_textureHeight = height;
}

void AlbumArtBox::ClearTexture()
{
    m_texture = nullptr;
    m_textureWidth = 0;
    m_textureHeight = 0;
}

//==============================================================================
// Main Draw
//==============================================================================

void AlbumArtBox::Draw(float size, float rounding, bool showBorder, bool showBackground)
{
    m_wasClicked = false;
    m_isHovered = false;

    ImVec2 boxSize(size, size);
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // Reserve space
    ImGui::Dummy(boxSize);

    // Apply rounding: use provided rounding or theme's border rounding
    float r = (rounding > 0.0f) ? rounding : m_theme.BorderRounding;

    // Draw shadow
    if (m_theme.ShowShadow)
        DrawShadow(pos, boxSize, r);

    // Draw background
    if (showBackground)
        DrawBackground(pos, boxSize, r);

    // Draw image or placeholder
    if (m_texture && m_textureWidth > 0 && m_textureHeight > 0)
        DrawImage(pos, boxSize, r);
    else
        DrawPlaceholder(pos, boxSize);

    // Draw border
    if (showBorder)
        DrawBorder(pos, boxSize, r);

    // Click detection
    ImGui::SetCursorScreenPos(pos);
    ImGui::InvisibleButton("##AlbumArtBoxHitbox", boxSize, ImGuiButtonFlags_None);

    m_isHovered = ImGui::IsItemHovered();
    m_wasClicked = ImGui::IsItemClicked();
}

//==============================================================================
// Internal Drawing Helpers
//==============================================================================

void AlbumArtBox::DrawShadow(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    const int steps = 8;
    for (int i = steps; i > 0; --i)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps);
        float blur = t * m_theme.ShadowBlur;
        float offsetX = t * m_theme.ShadowOffsetX;
        float offsetY = t * m_theme.ShadowOffsetY;

        ImVec2 shadowPos = ImVec2(
            pos.x + offsetX - blur * 0.5f,
            pos.y + offsetY - blur * 0.5f
        );
        ImVec2 shadowSize = ImVec2(
            size.x + blur,
            size.y + blur
        );

        float alpha = 0.5f * (1.0f - t) * m_theme.ShadowColor.w;
        ImVec4 color = m_theme.ShadowColor;
        color.w = alpha;

        drawList->AddRectFilled(
            shadowPos,
            ImVec2(shadowPos.x + shadowSize.x, shadowPos.y + shadowSize.y),
            ImGui::GetColorU32(color),
            rounding,
            ImDrawFlags_RoundCornersAll
        );
    }
}

void AlbumArtBox::DrawBackground(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    drawList->AddRectFilled(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(m_theme.BackgroundColor),
        rounding,
        ImDrawFlags_RoundCornersAll
    );
}

void AlbumArtBox::DrawBorder(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    drawList->AddRect(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(m_theme.BorderColor),
        rounding,
        ImDrawFlags_RoundCornersAll,
        m_theme.BorderThickness
    );
}

//==============================================================================
// DrawImage - Uses AddImageRounded for proper clipping
//==============================================================================

void AlbumArtBox::DrawImage(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Calculate aspect ratio preserving fit
    float imgAspect = static_cast<float>(m_textureWidth) / static_cast<float>(m_textureHeight);
    float containerWidth = size.x;
    float containerHeight = size.y;

    ImVec2 imageSize;
    float containerAspect = containerWidth / containerHeight;

    if (imgAspect > containerAspect)
    {
        imageSize.x = containerWidth;
        imageSize.y = containerWidth / imgAspect;
    }
    else
    {
        imageSize.y = containerHeight;
        imageSize.x = containerHeight * imgAspect;
    }

    // Center the image
    ImVec2 imagePos = ImVec2(
        pos.x + (containerWidth - imageSize.x) * 0.5f,
        pos.y + (containerHeight - imageSize.y) * 0.5f
    );

    // Use AddImageRounded to clip the image to the rounded rectangle
    drawList->AddImageRounded(
        (ImTextureID)(uintptr_t)m_texture,
        imagePos,
        ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y),
        ImVec2(0, 0),
        ImVec2(1, 1),
        IM_COL32(255, 255, 255, 255),
        rounding
    );
}

void AlbumArtBox::DrawPlaceholder(const ImVec2& pos, const ImVec2& size)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    const char* text = m_theme.PlaceholderText ? m_theme.PlaceholderText : "No Art";
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 textPos = ImVec2(
        pos.x + (size.x - textSize.x) * 0.5f,
        pos.y + (size.y - textSize.y) * 0.5f
    );

    drawList->AddText(
        textPos,
        ImGui::GetColorU32(m_theme.PlaceholderTextColor),
        text
    );
}

} // namespace moosic  // <-- Make sure this closing brace exists!