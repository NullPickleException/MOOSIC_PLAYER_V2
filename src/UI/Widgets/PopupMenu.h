//==============================================================================
// UI/Widgets/PopupMenu.h
//==============================================================================
// Reusable right-click context menu system.
// Define menu items as a list, then call Show() to render.
//==============================================================================

#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <functional>

namespace moosic
{

//==============================================================================
// PopupMenuItem
//==============================================================================

struct PopupMenuItem
{
    std::string label;
    bool enabled = true;
    bool separator = false;  // If true, renders a separator instead of a menu item
};

//==============================================================================
// PopupMenuResult
//==============================================================================

struct PopupMenuResult
{
    int clickedIndex = -1;      // Index of the clicked item, -1 if nothing clicked
    bool isOpen = false;        // Whether the menu should remain open
};

//==============================================================================
// PopupMenu
//==============================================================================

class PopupMenu
{
public:
    //--------------------------------------------------------------------------
    // Set the menu items and optional ID for ImGui
    //--------------------------------------------------------------------------

    void SetItems(const std::vector<PopupMenuItem>& items, const std::string& id = "PopupMenu")
    {
        m_items = items;
        m_id = id;
    }

    //--------------------------------------------------------------------------
    // Call this on right-click to open the menu.
    // Returns the index of the clicked item, or -1.
    //--------------------------------------------------------------------------

    PopupMenuResult Show()
    {
        PopupMenuResult result;

        if (ImGui::BeginPopupContextItem(m_id.c_str()))
        {
            for (int i = 0; i < static_cast<int>(m_items.size()); ++i)
            {
                const auto& item = m_items[i];

                if (item.separator)
                {
                    ImGui::Separator();
                    continue;
                }

                if (!item.enabled)
                    ImGui::BeginDisabled();

                if (ImGui::MenuItem(item.label.c_str()))
                {
                    result.clickedIndex = i;
                }

                if (!item.enabled)
                    ImGui::EndDisabled();
            }

            ImGui::EndPopup();
        }

        return result;
    }

private:
    std::vector<PopupMenuItem> m_items;
    std::string m_id = "PopupMenu";
};

} // namespace moosic