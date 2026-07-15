#include "AlbumArtLightbox.h"

#include <imgui.h>

#include <iostream>
#include <cmath>
#include <algorithm>

namespace moosic
{

void AlbumArtLightbox::SetTexture(void* texture, int width, int height)
{
    m_texture = texture;
    m_width = width;
    m_height = height;
}

void AlbumArtLightbox::SetInfo(const char* title, const char* artist)
{
    m_title = title ? title : "";
    m_artist = artist ? artist : "";
}

// REMOVED: SetTheme implementation - now inline in header

void AlbumArtLightbox::Toggle()
{
    if (m_texture && m_width > 0 && m_height > 0)
        m_visible = !m_visible;
}

void AlbumArtLightbox::Show()
{
    if (m_texture && m_width > 0 && m_height > 0)
        m_visible = true;
}

void AlbumArtLightbox::Hide()
{
    m_visible = false;
}

void AlbumArtLightbox::Draw()
{
    if (!m_visible || !m_texture)
        return;

    auto& lb = m_theme;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImVec2 viewportSize = viewport->Size;
    ImVec2 center = viewport->GetCenter();

    // Calculate display size maintaining aspect ratio
    float aspect = (float)m_width / m_height;
    float displayW, displayH;

    if (aspect > 1.0f) {
        displayW = std::min(lb.MaxWidth, viewportSize.x * 0.8f);
        displayH = displayW / aspect;
        if (displayH > lb.MaxHeight) {
            displayH = std::min(lb.MaxHeight, viewportSize.y * 0.8f);
            displayW = displayH * aspect;
        }
    } else {
        displayH = std::min(lb.MaxHeight, viewportSize.y * 0.8f);
        displayW = displayH * aspect;
        if (displayW > lb.MaxWidth) {
            displayW = std::min(lb.MaxWidth, viewportSize.x * 0.8f);
            displayH = displayW / aspect;
        }
    }

    displayW = std::min(displayW, viewportSize.x * 0.9f);
    displayH = std::min(displayH, viewportSize.y * 0.9f);

    ImVec2 popupSize(displayW + lb.Padding * 2, displayH + lb.Padding * 2 + 80.0f);
    ImVec2 popupPos(center.x - popupSize.x * 0.5f, center.y - popupSize.y * 0.5f);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                             ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
                             ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

    ImGui::SetNextWindowPos(popupPos);
    ImGui::SetNextWindowSize(popupSize);
    ImGui::SetNextWindowBgAlpha(lb.BackgroundColor.w);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, lb.BorderRounding);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, lb.BackgroundColor);
    ImGui::PushStyleColor(ImGuiCol_Border, lb.BorderColor);

    if (ImGui::Begin("##Lightbox", nullptr, flags)) {
        // Close button
        ImVec2 closePos(popupSize.x - lb.CloseButtonSize - 10.0f, 10.0f);
        ImGui::SetCursorPos(closePos);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, lb.CloseButtonHovered);
        ImGui::PushStyleColor(ImGuiCol_Text, lb.CloseButtonColor);
        if (ImGui::Button("×", ImVec2(lb.CloseButtonSize, lb.CloseButtonSize)))
            m_visible = false;
        ImGui::PopStyleColor(3);

        // Image
        ImVec2 imagePos((popupSize.x - displayW) * 0.5f, 40.0f);
        ImGui::SetCursorPos(imagePos);
        ImGui::Image(m_texture, ImVec2(displayW, displayH));

        // Title
        if (m_title && *m_title) {
            float textY = imagePos.y + displayH + 20.0f;
            ImGui::SetCursorPos(ImVec2(popupSize.x * 0.5f - ImGui::CalcTextSize(m_title).x * 0.5f, textY));
            ImGui::PushStyleColor(ImGuiCol_Text, lb.TitleColor);
            ImGui::TextUnformatted(m_title);
            ImGui::PopStyleColor();
        }

        // Artist
        if (m_artist && *m_artist) {
            float textY = imagePos.y + displayH + 45.0f;
            ImGui::SetCursorPos(ImVec2(popupSize.x * 0.5f - ImGui::CalcTextSize(m_artist).x * 0.5f, textY));
            ImGui::PushStyleColor(ImGuiCol_Text, lb.ArtistColor);
            ImGui::TextUnformatted(m_artist);
            ImGui::PopStyleColor();
        }

        // Click outside to close
        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            ImVec2 mp = ImGui::GetMousePos();
            ImVec2 wp = ImGui::GetWindowPos();
            ImVec2 ws = ImGui::GetWindowSize();
            if (mp.x < wp.x + 20 || mp.x > wp.x + ws.x - 20 ||
                mp.y < wp.y + 20 || mp.y > wp.y + ws.y - 20)
                m_visible = false;
        }

        ImGui::End();
    }

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);

    if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        m_visible = false;
}

} // namespace moosic