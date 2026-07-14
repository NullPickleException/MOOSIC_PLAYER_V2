//==============================================================================
// AlbumArtBox.cpp
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

void AlbumArtBox::SetStyle(const AlbumArtBoxStyle& style)
{
    m_style = style;
}

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

    // Apply rounding: use provided rounding or style's border rounding
    float r = (rounding > 0.0f) ? rounding : m_style.BorderRounding;

    // Draw shadow
    if (m_style.ShowShadow)
        DrawShadow(pos, boxSize, r);

    // Draw background
    if (showBackground)
        DrawBackground(pos, boxSize, r);

    // Draw image or placeholder
    if (m_texture && m_textureWidth > 0 && m_textureHeight > 0)
        DrawImage(pos, boxSize, r);  // Pass rounding for clipping
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
        float blur = t * m_style.ShadowBlur;
        float offsetX = t * m_style.ShadowOffsetX;
        float offsetY = t * m_style.ShadowOffsetY;

        ImVec2 shadowPos = ImVec2(
            pos.x + offsetX - blur * 0.5f,
            pos.y + offsetY - blur * 0.5f
        );
        ImVec2 shadowSize = ImVec2(
            size.x + blur,
            size.y + blur
        );

        float alpha = 0.5f * (1.0f - t) * m_style.ShadowColor.w;
        ImVec4 color = m_style.ShadowColor;
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
        ImGui::GetColorU32(m_style.BackgroundColor),
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
        ImGui::GetColorU32(m_style.BorderColor),
        rounding,
        ImDrawFlags_RoundCornersAll,
        m_style.BorderThickness
    );
}

//==============================================================================
// FIXED: DrawImage with proper clipping using AddImageRounded
//==============================================================================

void AlbumArtBox::DrawImage(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

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

    const char* text = m_style.PlaceholderText ? m_style.PlaceholderText : "No Art";
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 textPos = ImVec2(
        pos.x + (size.x - textSize.x) * 0.5f,
        pos.y + (size.y - textSize.y) * 0.5f
    );

    drawList->AddText(
        textPos,
        ImGui::GetColorU32(m_style.PlaceholderTextColor),
        text
    );
}

} // namespace moosic