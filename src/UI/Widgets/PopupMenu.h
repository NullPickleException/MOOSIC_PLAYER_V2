//==============================================================================
// UI/Widgets/PopupMenu.h - Context menu with submenu support
//==============================================================================

#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <functional>
#include <deque>

namespace moosic
{

    //==========================================================================
    // MenuItem - single item in a context menu
    //==========================================================================

    struct MenuItem
    {
        std::string label;
        bool enabled = true;
        bool isSeparator = false;
        std::function<void()> action;

        // Submenu support - if children is not empty, this item opens a submenu
        std::vector<MenuItem> children;
        bool isSubmenuArrow = true; // Show ">" arrow indicator for submenus
    };

    //==========================================================================
    // PopupMenuTheme - appearance configuration
    //==========================================================================

    struct PopupMenuTheme
    {
        // Sizing
        float MinWidth = 140.0f;
        float MaxWidth = 400.0f;
        float ItemHeight = 0.0f;
        float SeparatorHeight = 6.0f;
        float SeparatorThickness = 1.0f;
        float SeparatorWidth = 1.0f;
        float TextPaddingRight = 30.0f;
        float TextPaddingLeft = 0.0f;
        float ScreenEdgePadding = 5.0f;
        float ExtraHeightBottom = 10.0f;
        float ExtraHeightTop = 0.0f;
        float ExtraWidth = 0.0f;

        // Padding & Spacing
        float WindowPaddingX = 4.0f;
        float WindowPaddingY = 4.0f;
        float ItemSpacingX = 4.0f;
        float ItemSpacingY = 2.0f;

        // Appearance
        float WindowRounding = 4.0f;
        float WindowBorderSize = 1.5f;

        // Colors
        ImVec4 BackgroundColor = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
        ImVec4 BorderColor = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
        ImVec4 TextColor = ImVec4(0.90f, 0.90f, 0.92f, 1.00f);
        ImVec4 TextDisabledColor = ImVec4(0.45f, 0.45f, 0.48f, 1.00f);
        ImVec4 HoverColor = ImVec4(0.22f, 0.38f, 0.62f, 1.00f);
        ImVec4 HoverTextColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        ImVec4 SeparatorColor = ImVec4(0.24f, 0.25f, 0.28f, 1.00f);
        ImVec4 ShadowColor = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);

        // Submenu styling
        float SubmenuArrowOffset = 10.0f;
        float SubmenuOpenDelay = 0.25f;
        ImVec4 SubmenuArrowColor = ImVec4(0.70f, 0.70f, 0.72f, 1.00f);

        //--------------------------------------------------------------------------
        // Classic 2000s Popup Menu Effects
        //--------------------------------------------------------------------------

        bool UseMenuGloss = false;
        float MenuGlossIntensity = 0.0f;
        ImVec4 MenuGlossColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);

        bool UseMenuGradient = false;
        ImVec4 MenuGradientTop = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);
        ImVec4 MenuGradientBottom = ImVec4(0.16f, 0.17f, 0.19f, 1.00f);

        bool UseGlossySelection = false;
        float SelectionGlossIntensity = 0.0f;
    };

    //==========================================================================
    // ContextMenu - popup context menu with submenu support
    //==========================================================================

    class ContextMenu
    {
    public:
        //----------------------------------------------------------------------
        // SubmenuState - tracks an open submenu
        //----------------------------------------------------------------------

        struct SubmenuState
        {
            std::vector<MenuItem> items;
            float posX = 0;
            float posY = 0;
            float width = 0;
            float height = 0;
            int parentMenuId = 0;
            int parentItemIndex = -1;
        };

        //----------------------------------------------------------------------
        // Configuration
        //----------------------------------------------------------------------

        void SetItems(const std::vector<MenuItem> &items) { m_items = items; }
        void ApplyTheme(const PopupMenuTheme &theme) { m_theme = theme; }
        const PopupMenuTheme &GetStyle() const { return m_theme; }

        //----------------------------------------------------------------------
        // State
        //----------------------------------------------------------------------

        void Open(float mouseX, float mouseY)
        {
            m_isOpen = true;
            m_posX = mouseX;
            m_posY = mouseY;
            m_justOpened = true;
            m_openSubmenus.clear();
            m_submenuHoverTimers.clear();
        }

        void Close()
        {
            m_isOpen = false;
            m_openSubmenus.clear();
            m_submenuHoverTimers.clear();
        }

        bool IsOpen() const { return m_isOpen; }

        //----------------------------------------------------------------------
        // Draw - call every frame
        //----------------------------------------------------------------------

        bool Draw(const char *id = "##ContextMenu")
        {
            if (!m_isOpen)
                return false;

            bool actionExecuted = false;

            //------------------------------------------------------------------
            // Handle click-outside-to-close
            //------------------------------------------------------------------

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
                    bool clickedOutside = true;

                    // Check main menu
                    if (mousePos.x >= m_posX && mousePos.x <= m_posX + m_menuWidth &&
                        mousePos.y >= m_posY && mousePos.y <= m_posY + m_menuHeight)
                    {
                        clickedOutside = false;
                    }

                    // Check all open submenus
                    for (const auto &sub : m_openSubmenus)
                    {
                        if (mousePos.x >= sub.posX && mousePos.x <= sub.posX + sub.width &&
                            mousePos.y >= sub.posY && mousePos.y <= sub.posY + sub.height)
                        {
                            clickedOutside = false;
                            break;
                        }
                    }

                    if (clickedOutside)
                    {
                        Close();
                        return false;
                    }
                }
            }

            //------------------------------------------------------------------
            // Calculate size and draw main menu
            //------------------------------------------------------------------

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
                // Draw gradient background if enabled
                if (m_theme.UseMenuGradient)
                {
                    ImVec2 wp = ImGui::GetWindowPos();
                    ImVec2 ws = ImGui::GetWindowSize();
                    ImDrawList *dl = ImGui::GetWindowDrawList();
                    dl->AddRectFilledMultiColor(
                        wp, ImVec2(wp.x + ws.x, wp.y + ws.y),
                        ImGui::GetColorU32(m_theme.MenuGradientTop),
                        ImGui::GetColorU32(m_theme.MenuGradientTop),
                        ImGui::GetColorU32(m_theme.MenuGradientBottom),
                        ImGui::GetColorU32(m_theme.MenuGradientBottom));
                }

                // Draw menu gloss overlay if enabled
                if (m_theme.UseMenuGloss && m_theme.MenuGlossIntensity > 0.0f)
                {
                    ImVec2 wp = ImGui::GetWindowPos();
                    ImVec2 ws = ImGui::GetWindowSize();
                    ImDrawList *dl = ImGui::GetWindowDrawList();
                    float glossH = ws.y * 0.30f;
                    ImVec4 glossCol = m_theme.MenuGlossColor;
                    glossCol.w *= m_theme.MenuGlossIntensity;
                    ImVec4 fadeOut = ImVec4(glossCol.x, glossCol.y, glossCol.z, 0.0f);
                    dl->AddRectFilledMultiColor(
                        ImVec2(wp.x + 2.0f, wp.y + 2.0f),
                        ImVec2(wp.x + ws.x - 2.0f, wp.y + glossH),
                        ImGui::GetColorU32(glossCol),
                        ImGui::GetColorU32(glossCol),
                        ImGui::GetColorU32(fadeOut),
                        ImGui::GetColorU32(fadeOut));
                }

                // Add extra top spacing
                if (m_theme.ExtraHeightTop > 0.0f)
                    ImGui::Dummy(ImVec2(1.0f, m_theme.ExtraHeightTop));

                actionExecuted = DrawItems(m_items, 0, -1);

                // Add extra bottom spacing
                if (m_theme.ExtraHeightBottom > 0.0f)
                    ImGui::Dummy(ImVec2(1.0f, m_theme.ExtraHeightBottom));
            }
            ImGui::End();

            ImGui::PopStyleVar(4);
            PopColors();

            //------------------------------------------------------------------
            // Draw all open submenus
            //------------------------------------------------------------------

            DrawAllSubmenus();

            return actionExecuted;
        }

    private:
        //----------------------------------------------------------------------
        // Size Calculation
        //----------------------------------------------------------------------

        void CalculateSize()
        {
            CalculateMenuSize(m_items, m_menuWidth, m_menuHeight);
        }

        void CalculateMenuSize(const std::vector<MenuItem> &items, float &outWidth, float &outHeight)
        {
            float w = m_theme.MinWidth;
            float itemHeight = (m_theme.ItemHeight > 0) ? m_theme.ItemHeight : ImGui::GetTextLineHeightWithSpacing();

            for (const auto &item : items)
            {
                if (!item.isSeparator)
                {
                    float textWidth = ImGui::CalcTextSize(item.label.c_str()).x;
                    // Add extra space for submenu arrow if item has children
                    float extraArrowSpace = item.children.empty() ? 0.0f : 20.0f;
                    float required = textWidth + m_theme.TextPaddingRight + m_theme.TextPaddingLeft + extraArrowSpace;
                    if (required > w)
                        w = required;
                }
            }

            if (w > m_theme.MaxWidth)
                w = m_theme.MaxWidth;
            outWidth = w + m_theme.ExtraWidth;

            float h = m_theme.WindowPaddingY * 2.0f;
            for (const auto &item : items)
            {
                if (item.isSeparator)
                    h += m_theme.SeparatorHeight;
                else
                    h += itemHeight;
            }
            outHeight = h + m_theme.ExtraHeightTop + m_theme.ExtraHeightBottom;
        }

        //----------------------------------------------------------------------
        // Screen Clamping
        //----------------------------------------------------------------------

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

        void ClampSubmenuToScreen(float &posX, float &posY, float width, float height)
        {
            ImVec2 screenSize = ImGui::GetIO().DisplaySize;
            float pad = m_theme.ScreenEdgePadding;

            if (posX + width > screenSize.x)
                posX = screenSize.x - width - pad;
            if (posY + height > screenSize.y)
                posY = screenSize.y - height - pad;
            if (posX < pad)
                posX = pad;
            if (posY < pad)
                posY = pad;
        }

        //----------------------------------------------------------------------
        // Style Push/Pop
        //----------------------------------------------------------------------

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

        //----------------------------------------------------------------------
        // Draw Items (recursive for submenus)
        //----------------------------------------------------------------------

        bool DrawItems(const std::vector<MenuItem> &items, int menuId, int parentItemIndex)
        {
            float itemHeight = (m_theme.ItemHeight > 0) ? m_theme.ItemHeight : ImGui::GetTextLineHeightWithSpacing();

            // Calculate item width based on which menu we're drawing
            float itemWidth;
            if (menuId == 0)
            {
                itemWidth = m_menuWidth - m_theme.WindowPaddingX * 2.0f;
            }
            else
            {
                // Find the submenu state to get its width
                for (const auto &sub : m_openSubmenus)
                {
                    if (sub.parentMenuId == menuId - 1 && sub.parentItemIndex == parentItemIndex)
                    {
                        itemWidth = sub.width - m_theme.WindowPaddingX * 2.0f;
                        break;
                    }
                }
            }

            for (size_t i = 0; i < items.size(); ++i)
            {
                const auto &item = items[i];

                //--------------------------------------------------------------
                // Separator
                //--------------------------------------------------------------

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

                //--------------------------------------------------------------
                // Disabled Item
                //--------------------------------------------------------------

                if (!item.enabled)
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextDisabledColor);
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + m_theme.TextPaddingLeft);
                    ImGui::Selectable(item.label.c_str(), false, ImGuiSelectableFlags_Disabled,
                                      ImVec2(itemWidth - m_theme.TextPaddingLeft, itemHeight));
                    ImGui::PopStyleColor();
                    continue;
                }

                //--------------------------------------------------------------
                // Normal Item (with optional submenu)
                //--------------------------------------------------------------

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + m_theme.TextPaddingLeft);

                bool hasChildren = !item.children.empty();
                std::string displayLabel = item.label;

                // Add arrow indicator for submenu items
                if (hasChildren && item.isSubmenuArrow)
                {
                    displayLabel += "  >";
                }

                if (ImGui::Selectable(displayLabel.c_str(), false, 0,
                                      ImVec2(itemWidth - m_theme.TextPaddingLeft, itemHeight)))
                {
                    if (hasChildren)
                    {
                        // Toggle submenu on click
                        ToggleSubmenu(item, menuId, static_cast<int>(i));
                    }
                    else if (item.action)
                    {
                        item.action();
                        Close();
                        return true;
                    }
                }

                //--------------------------------------------------------------
                // Submenu hover handling
                //--------------------------------------------------------------

                if (hasChildren && ImGui::IsItemHovered())
                {
                    HandleSubmenuHover(item, menuId, static_cast<int>(i));
                }

                //--------------------------------------------------------------
                // Glossy selection overlay on hovered items
                //--------------------------------------------------------------

                if (m_theme.UseGlossySelection && m_theme.SelectionGlossIntensity > 0.0f && ImGui::IsItemHovered())
                {
                    ImVec2 rMin = ImGui::GetItemRectMin();
                    ImVec2 rMax = ImGui::GetItemRectMax();
                    ImDrawList *dl = ImGui::GetWindowDrawList();
                    float glossH = (rMax.y - rMin.y) * 0.45f;
                    ImVec4 glossCol = ImVec4(1.0f, 1.0f, 1.0f, m_theme.SelectionGlossIntensity * 0.4f);
                    ImVec4 fadeOut = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
                    dl->AddRectFilledMultiColor(
                        ImVec2(rMin.x + 2.0f, rMin.y + 1.0f),
                        ImVec2(rMax.x - 2.0f, rMin.y + glossH),
                        ImGui::GetColorU32(glossCol),
                        ImGui::GetColorU32(glossCol),
                        ImGui::GetColorU32(fadeOut),
                        ImGui::GetColorU32(fadeOut));
                }

                if (ImGui::IsItemHovered())
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                }
            }

            return false;
        }

        //----------------------------------------------------------------------
        // Submenu Management
        //----------------------------------------------------------------------

        void ToggleSubmenu(const MenuItem &item, int parentMenuId, int itemIndex)
        {
            // Check if submenu is already open for this item
            for (auto it = m_openSubmenus.begin(); it != m_openSubmenus.end();)
            {
                if (it->parentMenuId == parentMenuId && it->parentItemIndex == itemIndex)
                {
                    // Close this submenu and all its children
                    it = m_openSubmenus.erase(it);
                    // Also close any submenus that were children of this one
                    while (it != m_openSubmenus.end() && it->parentMenuId > parentMenuId)
                    {
                        it = m_openSubmenus.erase(it);
                    }
                    return;
                }
                else
                {
                    ++it;
                }
            }

            // Open new submenu
            OpenSubmenu(item, parentMenuId, itemIndex);
        }

        void OpenSubmenu(const MenuItem &item, int parentMenuId, int itemIndex)
        {
            SubmenuState submenu;
            submenu.items = item.children;
            submenu.parentMenuId = parentMenuId;
            submenu.parentItemIndex = itemIndex;

            // Get the item's screen position
            ImVec2 itemRectMin = ImGui::GetItemRectMin();
            ImVec2 itemRectMax = ImGui::GetItemRectMax();

            // Position submenu to the right of the parent item
            submenu.posX = itemRectMax.x + 2.0f;
            submenu.posY = itemRectMin.y - 2.0f;

            // Calculate submenu size
            float w, h;
            CalculateMenuSize(item.children, w, h);
            submenu.width = w;
            submenu.height = h;

            // Try to position on right first, if no room, position on left
            ImVec2 screenSize = ImGui::GetIO().DisplaySize;
            float pad = m_theme.ScreenEdgePadding;
            if (submenu.posX + submenu.width > screenSize.x - pad)
            {
                submenu.posX = itemRectMin.x - submenu.width - 2.0f;
            }

            // Clamp to screen
            ClampSubmenuToScreen(submenu.posX, submenu.posY, submenu.width, submenu.height);

            m_openSubmenus.push_back(submenu);
        }

        void HandleSubmenuHover(const MenuItem &item, int parentMenuId, int itemIndex)
        {
            // Check if submenu is already open
            bool alreadyOpen = false;
            for (const auto &sub : m_openSubmenus)
            {
                if (sub.parentMenuId == parentMenuId && sub.parentItemIndex == itemIndex)
                {
                    alreadyOpen = true;
                    break;
                }
            }

            if (alreadyOpen)
                return;

            // Handle hover timer for auto-open
            EnsureHoverTimerSize(itemIndex);

            m_submenuHoverTimers[itemIndex] += ImGui::GetIO().DeltaTime;
            if (m_submenuHoverTimers[itemIndex] >= m_theme.SubmenuOpenDelay)
            {
                // Close sibling submenus at the same level
                for (auto it = m_openSubmenus.begin(); it != m_openSubmenus.end();)
                {
                    if (it->parentMenuId == parentMenuId)
                    {
                        it = m_openSubmenus.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }

                OpenSubmenu(item, parentMenuId, itemIndex);
                m_submenuHoverTimers[itemIndex] = 0.0f;
            }
        }

        void EnsureHoverTimerSize(int index)
        {
            while (m_submenuHoverTimers.size() <= static_cast<size_t>(index))
            {
                m_submenuHoverTimers.push_back(0.0f);
            }
        }

        //----------------------------------------------------------------------
        // Draw All Submenus
        //----------------------------------------------------------------------

        void DrawAllSubmenus()
        {
            for (size_t i = 0; i < m_openSubmenus.size(); ++i)
            {
                const auto &sub = m_openSubmenus[i];

                ImGui::SetNextWindowPos(ImVec2(sub.posX, sub.posY));
                ImGui::SetNextWindowSize(ImVec2(sub.width, sub.height));

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

                char submenuId[64];
                snprintf(submenuId, sizeof(submenuId), "##Submenu_%p_%d_%d", this, sub.parentMenuId, sub.parentItemIndex);

                if (ImGui::Begin(submenuId, nullptr, flags))
                {
                    // Draw gradient background if enabled
                    if (m_theme.UseMenuGradient)
                    {
                        ImVec2 wp = ImGui::GetWindowPos();
                        ImVec2 ws = ImGui::GetWindowSize();
                        ImDrawList *dl = ImGui::GetWindowDrawList();
                        dl->AddRectFilledMultiColor(
                            wp, ImVec2(wp.x + ws.x, wp.y + ws.y),
                            ImGui::GetColorU32(m_theme.MenuGradientTop),
                            ImGui::GetColorU32(m_theme.MenuGradientTop),
                            ImGui::GetColorU32(m_theme.MenuGradientBottom),
                            ImGui::GetColorU32(m_theme.MenuGradientBottom));
                    }

                    DrawItems(sub.items, sub.parentMenuId + 1, sub.parentItemIndex);
                }
                ImGui::End();

                ImGui::PopStyleVar(4);
            }
        }

        //----------------------------------------------------------------------
        // Member Variables
        //----------------------------------------------------------------------

        std::vector<MenuItem> m_items;
        PopupMenuTheme m_theme;

        // Main menu state
        bool m_isOpen = false;
        bool m_justOpened = false;
        float m_posX = 0;
        float m_posY = 0;
        float m_menuWidth = 0;
        float m_menuHeight = 0;

        // Submenu state
        std::vector<SubmenuState> m_openSubmenus;
        std::vector<float> m_submenuHoverTimers;
    };

} // namespace moosic