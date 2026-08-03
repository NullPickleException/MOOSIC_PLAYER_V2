//==============================================================================
// UI/Data/LayoutStateDataModel.h
//==============================================================================
// Holds all persistent UI state shared across layouts.
// Single currentTab + currentLayout - no per-layout arrays.
//==============================================================================

#pragma once

#include <cstdint>

namespace moosic
{

struct LayoutStateDataModel
{
    enum class Tab : uint8_t
    {
        Library,
        Playlists,
        Directory,
        Settings,
        Count
    };

    // Matches UI key bindings: 1=Standard, 2=Compact, 3=StandardArtLeft, 4=SidebarLeft, 5=MiniPlayer, 6=Theater
    enum class Layout : uint8_t
    {
        Standard = 0,
        Compact = 1,
        StandardArtLeft = 2,
        SidebarLeft = 3,
        MiniPlayer = 4,
        Theater = 5,
        Count = 6
    };

    // ── Single shared state ──────────────────────
    Layout currentLayout = Layout::Standard;
    Tab currentTab = Tab::Library;

    // ── Layout-specific persistent data ──────────
    float sidebarWidth = 220.0f;
    Tab miniPlayerActiveWindow = Tab::Library;

    // ── Accessors ────────────────────────────────
    Tab GetCurrentTab() const { return currentTab; }
    void SetCurrentTab(Tab tab) { currentTab = tab; }

    Layout GetCurrentLayout() const { return currentLayout; }
    void SetCurrentLayout(Layout layout) { currentLayout = layout; }
};

} // namespace moosic