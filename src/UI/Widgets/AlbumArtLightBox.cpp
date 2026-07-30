#include "AlbumArtLightBox.h"
#include <imgui.h>
#include <algorithm>

namespace moosic
{

    void AlbumArtLightbox::SetTexture(void *texture, int width, int height)
    {
        m_texture = texture;
        m_width = width;
        m_height = height;
    }

    void AlbumArtLightbox::SetInfo(const char *title, const char *artist)
    {
        m_title = title ? title : "";
        m_artist = artist ? artist : "";
    }

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

        auto &lb = m_theme;
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImVec2 viewportSize = viewport->Size;
        ImVec2 center = viewport->GetCenter();

        // Calculate display size maintaining aspect ratio
        float aspect = (float)m_width / m_height;
        float displayW, displayH;

        if (aspect > 1.0f)
        {
            displayW = std::min(lb.MaxWidth, viewportSize.x * 0.6f);
            displayH = displayW / aspect;
            if (displayH > lb.MaxHeight)
            {
                displayH = std::min(lb.MaxHeight, viewportSize.y * 0.6f);
                displayW = displayH * aspect;
            }
        }
        else
        {
            displayH = std::min(lb.MaxHeight, viewportSize.y * 0.6f);
            displayW = displayH * aspect;
            if (displayW > lb.MaxWidth)
            {
                displayW = std::min(lb.MaxWidth, viewportSize.x * 0.6f);
                displayH = displayW / aspect;
            }
        }

        // Ensure it's not too large
        displayW = std::min(displayW, viewportSize.x * 0.7f);
        displayH = std::min(displayH, viewportSize.y * 0.7f);

        // Calculate popup size with minimal extra space for title/artist
        float textAreaHeight = 0.0f;
        if (m_title && *m_title)
            textAreaHeight += ImGui::GetTextLineHeight() + lb.TitleSpacing;
        if (m_artist && *m_artist)
            textAreaHeight += ImGui::GetTextLineHeight() + lb.ArtistSpacing;

        // Add space for close button at top
        float topBarHeight = lb.CloseButtonSize + 12.0f;
        
        ImVec2 popupSize(displayW + lb.Padding * 2,
                         displayH + lb.Padding * 2 + textAreaHeight + topBarHeight + 10.0f);

        ImVec2 popupPos(center.x - popupSize.x * 0.5f, center.y - popupSize.y * 0.5f);

        // Window flags
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                 ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::SetNextWindowPos(popupPos);
        ImGui::SetNextWindowSize(popupSize);
        ImGui::SetNextWindowBgAlpha(lb.BackgroundColor.w);

        // Apply border styling matching your theme
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, lb.BorderRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, lb.BorderThickness);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, lb.BackgroundColor);
        ImGui::PushStyleColor(ImGuiCol_Border, lb.BorderColor);

        if (ImGui::Begin("##Lightbox", nullptr, flags))
        {
            // Draw gradient background if enabled
            if (lb.UseLightboxGradient)
            {
                ImVec2 wp = ImGui::GetWindowPos();
                ImVec2 ws = ImGui::GetWindowSize();
                ImDrawList* dl = ImGui::GetWindowDrawList();
                dl->AddRectFilledMultiColor(
                    wp, ImVec2(wp.x + ws.x, wp.y + ws.y),
                    ImGui::GetColorU32(lb.LightboxGradientTop),
                    ImGui::GetColorU32(lb.LightboxGradientTop),
                    ImGui::GetColorU32(lb.LightboxGradientBottom),
                    ImGui::GetColorU32(lb.LightboxGradientBottom));
            }

            // Draw lightbox gloss overlay if enabled
            if (lb.UseLightboxGloss && lb.LightboxGlossIntensity > 0.0f)
            {
                ImVec2 wp = ImGui::GetWindowPos();
                ImVec2 ws = ImGui::GetWindowSize();
                ImDrawList* dl = ImGui::GetWindowDrawList();
                float glossH = ws.y * 0.30f;
                ImVec4 glossCol = lb.LightboxGlossColor;
                glossCol.w *= lb.LightboxGlossIntensity;
                ImVec4 fadeOut = ImVec4(glossCol.x, glossCol.y, glossCol.z, 0.0f);
                dl->AddRectFilledMultiColor(
                    ImVec2(wp.x + 2.0f, wp.y + 2.0f),
                    ImVec2(wp.x + ws.x - 2.0f, wp.y + glossH),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(fadeOut),
                    ImGui::GetColorU32(fadeOut));
            }

            // Close button in top-right corner
            ImVec2 closePos(popupSize.x - lb.CloseButtonSize - 12.0f, 10.0f);
            ImGui::SetCursorPos(closePos);
            
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(lb.CloseButtonHovered.x,
                                                                  lb.CloseButtonHovered.y,
                                                                  lb.CloseButtonHovered.z, 0.15f));
            ImGui::PushStyleColor(ImGuiCol_Text, lb.CloseButtonColor);
            
            if (ImGui::Button("×", ImVec2(lb.CloseButtonSize, lb.CloseButtonSize)))
                m_visible = false;

            // Close button gloss if enabled
            if (lb.UseGlossyCloseButton && lb.CloseButtonGlossIntensity > 0.0f)
            {
                ImVec2 btnMin = ImGui::GetItemRectMin();
                ImVec2 btnMax = ImGui::GetItemRectMax();
                ImDrawList* dl = ImGui::GetWindowDrawList();
                float glossH = (btnMax.y - btnMin.y) * 0.35f;
                ImVec4 glossCol = ImVec4(1.0f, 1.0f, 1.0f, lb.CloseButtonGlossIntensity * 0.5f);
                ImVec4 fadeOut = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
                dl->AddRectFilledMultiColor(
                    ImVec2(btnMin.x + 2.0f, btnMin.y + 1.0f),
                    ImVec2(btnMax.x - 2.0f, btnMin.y + glossH),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(fadeOut),
                    ImGui::GetColorU32(fadeOut));
            }
            
            ImGui::PopStyleColor(3);

            // Image centered - starts after close button area
            float imageY = topBarHeight;
            ImVec2 imagePos((popupSize.x - displayW) * 0.5f, imageY);
            ImGui::SetCursorPos(imagePos);
            ImGui::Image(m_texture, ImVec2(displayW, displayH));

            // Title centered below image
            float currentY = imageY + displayH + lb.TitleSpacing;
            if (m_title && *m_title)
            {
                float textWidth = ImGui::CalcTextSize(m_title).x;
                ImGui::SetCursorPos(ImVec2((popupSize.x - textWidth) * 0.5f, currentY));
                ImGui::PushStyleColor(ImGuiCol_Text, lb.TitleColor);
                ImGui::TextUnformatted(m_title);
                ImGui::PopStyleColor();
                currentY += ImGui::GetTextLineHeight() + lb.ArtistSpacing;
            }

            // Artist centered below title
            if (m_artist && *m_artist)
            {
                float textWidth = ImGui::CalcTextSize(m_artist).x;
                ImGui::SetCursorPos(ImVec2((popupSize.x - textWidth) * 0.5f, currentY));
                ImGui::PushStyleColor(ImGuiCol_Text, lb.ArtistColor);
                ImGui::TextUnformatted(m_artist);
                ImGui::PopStyleColor();
            }

            // Close on click outside the image area
            if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                ImVec2 mp = ImGui::GetMousePos();
                ImVec2 wp = ImGui::GetWindowPos();
                
                // Check if click is in the top bar area (but not on close button)
                bool clickedTopBar = (mp.y >= wp.y && mp.y <= wp.y + topBarHeight);
                // Check if click is below the image+text area
                bool clickedBottom = (mp.y >= wp.y + imageY + displayH + textAreaHeight + 20.0f);
                
                // Close only if clicking on border areas (not on image or text)
                if (clickedTopBar || clickedBottom)
                    m_visible = false;
            }

            ImGui::End();
        }

        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(2);

        // Close on escape key
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
            m_visible = false;
    }

} // namespace moosic