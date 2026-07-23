//==============================================================================
// UI/Widgets/PopupMenu.h
//==============================================================================

#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <functional>

namespace moosic
{

    //==============================================================================
    // MenuItem
    //==============================================================================

    struct MenuItem
    {
        std::string label;
        bool enabled = true;
        bool isSeparator = false;
        std::function<void()> action;
    };

    //==============================================================================
    // PopupMenuTheme
    //==============================================================================
    struct PopupMenuTheme
    {
        // ── Sizing ──────────────────────────────────────
        float MinWidth = 140.0f;
        float MaxWidth = 400.0f;
        float ItemHeight = 0.0f; // ImGui default
        float SeparatorHeight = 6.0f;
        float SeparatorThickness = 1.0f;
        float SeparatorWidth = 1.0f; // Full width
        float TextPaddingRight = 30.0f;
        float TextPaddingLeft = 0.0f; // No extra left padding
        float ScreenEdgePadding = 5.0f;
        float ExtraHeightBottom = 10.0f; // No extra bottom
        float ExtraHeightTop = 0.0f;    // No extra top
        float ExtraWidth = 0.0f;

        // ── Padding & Spacing ──────────────────────────
        float WindowPaddingX = 4.0f;
        float WindowPaddingY = 4.0f;
        float ItemSpacingX = 4.0f;
        float ItemSpacingY = 2.0f;

        // ── Appearance ─────────────────────────────────
        float WindowRounding = 4.0f;   // Standard ImGui rounding
        float WindowBorderSize = 1.5f; // Standard border

        // ── Colors ─────────────────────────────────────
        ImVec4 BackgroundColor = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
        ImVec4 BorderColor = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
        ImVec4 TextColor = ImVec4(0.90f, 0.90f, 0.92f, 1.00f);
        ImVec4 TextDisabledColor = ImVec4(0.45f, 0.45f, 0.48f, 1.00f);
        ImVec4 HoverColor = ImVec4(0.22f, 0.38f, 0.62f, 1.00f);
        ImVec4 HoverTextColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        ImVec4 SeparatorColor = ImVec4(0.24f, 0.25f, 0.28f, 1.00f);
        ImVec4 ShadowColor = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
    };

    //==============================================================================
    // ContextMenu
    //==============================================================================

    class ContextMenu
    {
    public:
        //--------------------------------------------------------------------------
        // Configuration
        //--------------------------------------------------------------------------

        void SetItems(const std::vector<MenuItem> &items) { m_items = items; }
        void ApplyTheme(const PopupMenuTheme &theme) { m_theme = theme; }
        const PopupMenuTheme &GetStyle() const { return m_theme; }

        //--------------------------------------------------------------------------
        // State
        //--------------------------------------------------------------------------

        void Open(float mouseX, float mouseY)
        {
            m_isOpen = true;
            m_posX = mouseX;
            m_posY = mouseY;
            m_justOpened = true;
        }

        void Close() { m_isOpen = false; }
        bool IsOpen() const { return m_isOpen; }

        //--------------------------------------------------------------------------
        // Draw - call every frame
        //--------------------------------------------------------------------------

        bool Draw(const char *id = "##ContextMenu")
        {
            if (!m_isOpen)
                return false;

            bool actionExecuted = false;

            if (m_justOpened)
            {
                m_justOpened = false;
            }
            else
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) ||
                    ImGui::IsMouseClicked(ImGuiMouseButton_Right) ||
                    ImGui::IsMouseClicked(ImGuiMouseButton_Middle))
                {
                    ImVec2 mousePos = ImGui::GetMousePos();
                    if (mousePos.x < m_posX || mousePos.x > m_posX + m_menuWidth ||
                        mousePos.y < m_posY || mousePos.y > m_posY + m_menuHeight)
                    {
                        m_isOpen = false;
                        return false;
                    }
                }
            }

            CalculateSize();
            ClampToScreen();
            PushColors();

            ImGui::SetNextWindowPos(ImVec2(m_posX, m_posY));
            ImGui::SetNextWindowSize(ImVec2(m_menuWidth, m_menuHeight));

            ImGuiWindowFlags flags =
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoSavedSettings;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, m_theme.WindowRounding);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(m_theme.WindowPaddingX, m_theme.WindowPaddingY));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(m_theme.ItemSpacingX, m_theme.ItemSpacingY));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, m_theme.WindowBorderSize);

            if (ImGui::Begin(id, nullptr, flags))
            {
                // Add extra top spacing
                if (m_theme.ExtraHeightTop > 0.0f)
                    ImGui::Dummy(ImVec2(1.0f, m_theme.ExtraHeightTop));

                actionExecuted = DrawItems();

                // Add extra bottom spacing
                if (m_theme.ExtraHeightBottom > 0.0f)
                    ImGui::Dummy(ImVec2(1.0f, m_theme.ExtraHeightBottom));
            }
            ImGui::End();

            ImGui::PopStyleVar(4);
            PopColors();

            return actionExecuted;
        }

    private:
        void CalculateSize()
        {
            float w = m_theme.MinWidth;
            float itemHeight = (m_theme.ItemHeight > 0) ? m_theme.ItemHeight : ImGui::GetTextLineHeightWithSpacing();

            for (const auto &item : m_items)
            {
                if (!item.isSeparator)
                {
                    float textWidth = ImGui::CalcTextSize(item.label.c_str()).x;
                    float required = textWidth + m_theme.TextPaddingRight + m_theme.TextPaddingLeft;
                    if (required > w)
                        w = required;
                }
            }

            if (w > m_theme.MaxWidth)
                w = m_theme.MaxWidth;
            m_menuWidth = w + m_theme.ExtraWidth;

            float h = m_theme.WindowPaddingY * 2.0f;
            for (const auto &item : m_items)
            {
                if (item.isSeparator)
                    h += m_theme.SeparatorHeight;
                else
                    h += itemHeight;
            }
            m_menuHeight = h + m_theme.ExtraHeightTop + m_theme.ExtraHeightBottom;
        }

        void ClampToScreen()
        {
            ImVec2 screenSize = ImGui::GetIO().DisplaySize;
            float pad = m_theme.ScreenEdgePadding;

            if (m_posX + m_menuWidth > screenSize.x)
                m_posX = screenSize.x - m_menuWidth - pad;
            if (m_posY + m_menuHeight > screenSize.y)
                m_posY = screenSize.y - m_menuHeight - pad;
            if (m_posX < pad)
                m_posX = pad;
            if (m_posY < pad)
                m_posY = pad;
        }

        void PushColors()
        {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, m_theme.BackgroundColor);
            ImGui::PushStyleColor(ImGuiCol_Border, m_theme.BorderColor);
            ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextColor);
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_theme.HoverColor);
            ImGui::PushStyleColor(ImGuiCol_Header, m_theme.BackgroundColor);
            ImGui::PushStyleColor(ImGuiCol_Separator, m_theme.SeparatorColor);
            ImGui::PushStyleColor(ImGuiCol_PopupBg, m_theme.BackgroundColor);
        }

        void PopColors()
        {
            ImGui::PopStyleColor(7);
        }

        bool DrawItems()
        {
            float itemHeight = (m_theme.ItemHeight > 0) ? m_theme.ItemHeight : ImGui::GetTextLineHeightWithSpacing();
            float itemWidth = m_menuWidth - m_theme.WindowPaddingX * 2.0f;

            for (const auto &item : m_items)
            {
                if (item.isSeparator)
                {
                    ImVec2 cursor = ImGui::GetCursorScreenPos();
                    float availWidth = ImGui::GetContentRegionAvail().x;
                    float halfHeight = m_theme.SeparatorHeight * 0.5f;
                    float lineY = cursor.y + halfHeight;

                    float separatorWidth = availWidth * m_theme.SeparatorWidth;
                    float startX = cursor.x + (availWidth - separatorWidth) * 0.5f;
                    float endX = startX + separatorWidth;

                    ImGui::GetWindowDrawList()->AddLine(
                        ImVec2(startX, lineY),
                        ImVec2(endX, lineY),
                        ImGui::GetColorU32(m_theme.SeparatorColor),
                        m_theme.SeparatorThickness);

                    ImGui::Dummy(ImVec2(availWidth, m_theme.SeparatorHeight));
                    continue;
                }

                if (!item.enabled)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextDisabledColor);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + m_theme.TextPaddingLeft);
                    ImGui::Selectable(item.label.c_str(), false, ImGuiSelectableFlags_Disabled,
                                      ImVec2(itemWidth - m_theme.TextPaddingLeft, itemHeight));
                    ImGui::PopStyleColor();
                    continue;
                }

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + m_theme.TextPaddingLeft);

                if (ImGui::Selectable(item.label.c_str(), false, 0,
                                      ImVec2(itemWidth - m_theme.TextPaddingLeft, itemHeight)))
                {
                    if (item.action)
                    {
                        item.action();
                        m_isOpen = false;
                        return true;
                    }
                }

                if (ImGui::IsItemHovered())
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                }
            }

            return false;
        }

        std::vector<MenuItem> m_items;
        PopupMenuTheme m_theme;
        bool m_isOpen = false;
        bool m_justOpened = false;
        float m_posX = 0;
        float m_posY = 0;
        float m_menuWidth = 0;
        float m_menuHeight = 0;
    };

} // namespace moosic