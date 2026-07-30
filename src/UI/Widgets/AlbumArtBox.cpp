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
    m_isMouseDown = false;

    ImVec2 boxSize(size, size);
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // Reserve space
    ImGui::Dummy(boxSize);

    // Apply rounding: use provided rounding or theme's border rounding
    float r = (rounding > 0.0f) ? rounding : m_theme.BorderRounding;

    // Draw shadow
    if (m_theme.ShowShadow)
        DrawShadow(pos, boxSize, r);

    // Draw background (use hovered color if hovered)
    if (showBackground)
        DrawBackground(pos, boxSize, r);

    // Draw image or placeholder
    if (m_texture && m_textureWidth > 0 && m_textureHeight > 0)
        DrawImage(pos, boxSize, r);
    else
        DrawPlaceholder(pos, boxSize);

    // Click detection (placed before border so border draws on top)
    ImGui::SetCursorScreenPos(pos);
    ImGui::InvisibleButton("##AlbumArtBoxHitbox", boxSize, ImGuiButtonFlags_None);

    m_isHovered = ImGui::IsItemHovered();
    m_isMouseDown = ImGui::IsItemActive();
    m_wasClicked = ImGui::IsItemClicked();

    // Hover overlay (tinted overlay for feedback)
    if (m_isHovered && m_theme.ShowHoverOverlay)
        DrawHoverOverlay(pos, boxSize, r);

    // Play button on hover
    if (m_isHovered && m_theme.ShowPlayButtonOnHover && m_texture)
        DrawPlayButton(pos, boxSize);

    // Draw border (changes color/thickness on hover/click)
    if (showBorder)
        DrawBorder(pos, boxSize, r);
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
    ImVec4 bgColor = m_isHovered ? m_theme.BackgroundColorHovered : m_theme.BackgroundColor;

    drawList->AddRectFilled(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(bgColor),
        rounding,
        ImDrawFlags_RoundCornersAll
    );

    // Glossy overlay on background
    if (m_theme.UseGlossyOverlay && m_theme.GlossyIntensity > 0.0f)
    {
        float glossHeight = size.y * 0.40f;
        ImVec4 glossCol = m_theme.GlossyHighlightColor;
        glossCol.w *= m_theme.GlossyIntensity;
        ImVec4 fadeOut = ImVec4(glossCol.x, glossCol.y, glossCol.z, 0.0f);
        
        drawList->AddRectFilledMultiColor(
            ImVec2(pos.x + 2.0f, pos.y + 2.0f),
            ImVec2(pos.x + size.x - 2.0f, pos.y + glossHeight),
            ImGui::GetColorU32(glossCol),
            ImGui::GetColorU32(glossCol),
            ImGui::GetColorU32(fadeOut),
            ImGui::GetColorU32(fadeOut));
    }

    // Inner shadow
    if (m_theme.UseInnerShadow && m_theme.InnerShadowSize > 0.0f)
    {
        float is = m_theme.InnerShadowSize;
        ImVec4 shadowCol = m_theme.InnerShadowColor;
        for (float i = 0; i < is; i += 0.5f)
        {
            float alpha = shadowCol.w * (1.0f - i / is);
            ImU32 col = ImGui::GetColorU32(ImVec4(shadowCol.x, shadowCol.y, shadowCol.z, alpha));
            drawList->AddRect(
                ImVec2(pos.x + i, pos.y + i),
                ImVec2(pos.x + size.x - i, pos.y + size.y - i),
                col, rounding, ImDrawFlags_RoundCornersAll, 1.0f);
        }
    }
}

void AlbumArtBox::DrawBorder(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Select border color and thickness based on state
    ImVec4 borderColor = m_theme.BorderColor;
    float borderThickness = m_theme.BorderThickness;

    if (m_isMouseDown)
    {
        borderColor = m_theme.BorderColorClicked;
        borderThickness = m_theme.BorderThicknessHovered;
    }
    else if (m_isHovered)
    {
        borderColor = m_theme.BorderColorHovered;
        borderThickness = m_theme.BorderThicknessHovered;
    }

    drawList->AddRect(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(borderColor),
        rounding,
        ImDrawFlags_RoundCornersAll,
        borderThickness
    );
}

void AlbumArtBox::DrawHoverOverlay(const ImVec2& pos, const ImVec2& size, float rounding)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec4 overlayColor = m_isMouseDown ? m_theme.ClickOverlayColor : m_theme.HoverOverlayColor;

    drawList->AddRectFilled(
        pos,
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(overlayColor),
        rounding,
        ImDrawFlags_RoundCornersAll
    );

    // Reflection effect at bottom
    if (m_theme.UseReflection && m_theme.ReflectionOpacity > 0.0f && m_texture)
    {
        float reflectHeight = size.y * m_theme.ReflectionHeight;
        ImVec4 reflectCol = ImVec4(1.0f, 1.0f, 1.0f, m_theme.ReflectionOpacity);
        ImVec4 fadeOut = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
        
        drawList->AddRectFilledMultiColor(
            ImVec2(pos.x, pos.y + size.y - reflectHeight),
            ImVec2(pos.x + size.x, pos.y + size.y),
            ImGui::GetColorU32(fadeOut),
            ImGui::GetColorU32(fadeOut),
            ImGui::GetColorU32(reflectCol),
            ImGui::GetColorU32(reflectCol));
    }
}

void AlbumArtBox::DrawPlayButton(const ImVec2& pos, const ImVec2& size)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    float playSize = size.x * m_theme.PlayButtonSize;
    float centerX = pos.x + size.x * 0.5f;
    float centerY = pos.y + size.y * 0.5f;
    float radius = playSize * 0.5f;

    // Background circle
    drawList->AddCircleFilled(
        ImVec2(centerX, centerY),
        radius,
        ImGui::GetColorU32(m_theme.PlayButtonBackgroundColor)
    );

    // Play triangle (slightly offset right for visual center)
    float triOffset = radius * 0.1f;
    ImVec2 triP1(centerX - radius * 0.35f + triOffset, centerY - radius * 0.55f);
    ImVec2 triP2(centerX - radius * 0.35f + triOffset, centerY + radius * 0.55f);
    ImVec2 triP3(centerX + radius * 0.55f + triOffset, centerY);

    drawList->AddTriangleFilled(
        triP1, triP2, triP3,
        ImGui::GetColorU32(m_theme.PlayButtonColor)
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

} // namespace moosic