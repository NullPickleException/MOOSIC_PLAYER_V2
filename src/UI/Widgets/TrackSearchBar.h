//==============================================================================
// UI/Widgets/TrackSearchBar.h
//==============================================================================

#pragma once

#include <imgui.h>
#include <vector>
#include <string>
#include <functional>

namespace moosic
{

    struct TrackSearchBarTheme
    {
        // Dropdown Colors
        ImVec4 shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);
        ImVec4 backgroundColor = ImVec4(0.15f, 0.16f, 0.17f, 1.0f);
        ImVec4 borderColor = ImVec4(0.25f, 0.25f, 0.27f, 1.0f);
        ImVec4 textColor = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
        ImVec4 highlightTextColor = ImVec4(0.46f, 0.67f, 0.85f, 1.0f);
        ImVec4 rowHoverColor = ImVec4(0.22f, 0.23f, 0.25f, 1.0f);
        ImVec4 separatorColor = ImVec4(0.20f, 0.25f, 0.29f, 1.0f);

        // Input Colors
        ImVec4 inputBgColor = ImVec4(0.12f, 0.13f, 0.14f, 1.0f);
        ImVec4 inputBorderColor = ImVec4(0.25f, 0.25f, 0.27f, 1.0f);
        ImVec4 inputTextColor = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
        ImVec4 inputHintColor = ImVec4(0.42f, 0.42f, 0.42f, 1.0f);

        // Sizing
        float shadowOffset = 3.0f;
        float borderThickness = 1.0f;
        float rowHeight = 22.0f;
        float dropdownRounding = 4.0f;
        float textPaddingX = 10.0f;
        float rowSeparatorPadding = 6.0f;
        float maxVisibleRows = 8.0f;
        float scrollSpeed = 3.0f;

        //--------------------------------------------------------------------------
        // Classic 2000s Search Bar Effects
        //--------------------------------------------------------------------------
        
        bool UseSearchGloss = false;
        float SearchGlossIntensity = 0.0f;
        ImVec4 SearchGlossColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
        
        bool UseSearchGradient = false;
        ImVec4 SearchGradientTop = ImVec4(0.12f, 0.13f, 0.14f, 1.0f);
        ImVec4 SearchGradientBottom = ImVec4(0.12f, 0.13f, 0.14f, 1.0f);
        
        bool UseGlossyDropdown = false;
        float DropdownGlossIntensity = 0.0f;
        
        bool UseRoundedInput = false;
        float InputRounding = 4.0f;
    };


    //==============================================================================
    // TrackSearchResult
    //==============================================================================

    struct TrackSearchResult
    {
        std::string title;
        std::string artist;
        std::string displayText; // "Title — Artist"
        int trackIndex;
    };

    //==============================================================================
    // TrackSearchBar
    //==============================================================================

    class TrackSearchBar
    {
    public:
        //--------------------------------------------------------------------------
        // Callback Types
        //--------------------------------------------------------------------------

        using SearchCallback = std::function<std::vector<TrackSearchResult>(const std::string &query)>;
        using SelectCallback = std::function<void(const TrackSearchResult &result)>;

        //--------------------------------------------------------------------------
        // Construction
        //--------------------------------------------------------------------------

        TrackSearchBar();

        //--------------------------------------------------------------------------
        // Configuration
        //--------------------------------------------------------------------------

        void SetTheme(const TrackSearchBarTheme &theme) { m_theme = theme; }
        void SetWidth(float width) { m_width = width; }
        void SetHint(const std::string &hint) { m_hint = hint; }
        void SetSearchCallback(SearchCallback cb) { m_searchCallback = cb; }
        void SetSelectCallback(SelectCallback cb) { m_selectCallback = cb; }

        //--------------------------------------------------------------------------
        // Drawing
        //--------------------------------------------------------------------------

        void Draw();

        //--------------------------------------------------------------------------
        // Query Access
        //--------------------------------------------------------------------------

        const char *GetQuery() const { return m_query; }
        void ClearQuery()
        {
            m_query[0] = '\0';
            m_dropdownOpen = false;
        }

        bool IsDropdownOpen() const { return m_dropdownOpen; }
        bool IsMouseOverDropdown() const { return m_wasMouseInDrop; }

        bool IsCapturingMouse() const
        {
            return m_dropdownOpen && m_wasMouseInDrop;
        }
        // In the public section of TrackSearchBar class, add:
        void BlockExternalScroll()
        {
            if (m_dropdownOpen && m_wasMouseInDrop)
            {
                ImGuiIO &io = ImGui::GetIO();
                io.MouseWheel = 0.0f;
                io.MouseWheelH = 0.0f;
            }
        }

    private:
        //--------------------------------------------------------------------------
        // Internal Helpers
        //--------------------------------------------------------------------------
        void BuildResults();
        void CloseDropdown();
        void DrawDropdownBackground(ImDrawList *dl, const ImVec2 &dropMin, const ImVec2 &dropMax);
        void DrawRows(ImDrawList *dl, const ImVec2 &dropMin, float dropW, float dropH, bool mouseInDrop);
        void DrawSingleRow(ImDrawList *dl, int index, const ImVec2 &rowMin, float dropW, bool hovered);
        void DrawHighlightedText(ImDrawList *dl, const ImVec2 &pos, const std::string &display);
        void RenderScrollSink(const ImVec2 &dropMin, float dropW, float dropH);

        //--------------------------------------------------------------------------
        // State
        //--------------------------------------------------------------------------

        TrackSearchBarTheme m_theme;
        SearchCallback m_searchCallback;
        SelectCallback m_selectCallback;

        char m_query[256] = {};
        bool m_dropdownOpen = false;
        float m_width = 300.0f;
        float m_scrollOffset = 0.0f;
        std::string m_hint = "Search...";

        // Click/scroll tracking
        bool m_wasMouseInDrop = false;
        bool m_clickConsumed = false;
        ImVec2 m_dropMin = ImVec2(0, 0);
        ImVec2 m_dropMax = ImVec2(0, 0);

        static constexpr int k_maxResults = 100;
        std::vector<TrackSearchResult> m_results;
    };

} // namespace moosic