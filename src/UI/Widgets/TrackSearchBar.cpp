//==============================================================================
// UI/Widgets/TrackSearchBar.cpp
//==============================================================================

#include "TrackSearchBar.h"
#include <imgui_internal.h>
#include <algorithm>
#include <cctype>

namespace moosic
{

    static std::string ToLower(const std::string &s)
    {
        std::string out = s;
        std::transform(out.begin(), out.end(), out.begin(),
                       [](unsigned char c)
                       { return static_cast<char>(std::tolower(c)); });
        return out;
    }

    //==============================================================================
    // Construction
    //==============================================================================

    TrackSearchBar::TrackSearchBar()
    {
    }

    //==============================================================================
    // Result Building
    //==============================================================================

    void TrackSearchBar::BuildResults()
    {
        m_results.clear();
        m_scrollOffset = 0.0f;

        std::string q(m_query);
        if (q.empty() || !m_searchCallback)
            return;

        m_results = m_searchCallback(q);

        if (static_cast<int>(m_results.size()) > k_maxResults)
            m_results.resize(k_maxResults);
    }

    //==============================================================================
    // Close Dropdown
    //==============================================================================

    void TrackSearchBar::CloseDropdown()
    {
        m_dropdownOpen = false;
        m_scrollOffset = 0.0f;
        m_results.clear();
    }

    //==============================================================================
    // Highlighted Text
    //==============================================================================

    void TrackSearchBar::DrawHighlightedText(ImDrawList *dl, const ImVec2 &pos, const std::string &display)
    {
        const auto &st = m_theme;
        std::string lower = ToLower(display);
        std::string q = ToLower(std::string(m_query));

        size_t found = lower.find(q);
        if (found == std::string::npos)
        {
            dl->AddText(pos, ImGui::ColorConvertFloat4ToU32(st.textColor), display.c_str());
            return;
        }

        std::string before = display.substr(0, found);
        std::string match = display.substr(found, q.size());
        std::string after = display.substr(found + q.size());

        float x = pos.x;

        if (!before.empty())
        {
            dl->AddText(ImVec2(x, pos.y), ImGui::ColorConvertFloat4ToU32(st.textColor), before.c_str());
            x += ImGui::CalcTextSize(before.c_str()).x;
        }

        dl->AddText(ImVec2(x, pos.y), ImGui::ColorConvertFloat4ToU32(st.highlightTextColor), match.c_str());
        x += ImGui::CalcTextSize(match.c_str()).x;

        if (!after.empty())
        {
            dl->AddText(ImVec2(x, pos.y), ImGui::ColorConvertFloat4ToU32(st.textColor), after.c_str());
        }
    }

    //==============================================================================
    // Dropdown Background
    //==============================================================================

    void TrackSearchBar::DrawDropdownBackground(ImDrawList *dl, const ImVec2 &dropMin, const ImVec2 &dropMax)
    {
        const auto &st = m_theme;

        float o = st.shadowOffset;

        // Shadow
        dl->AddRectFilled(
            ImVec2(dropMin.x + o, dropMin.y + o),
            ImVec2(dropMax.x + o, dropMax.y + o),
            ImGui::ColorConvertFloat4ToU32(st.shadowColor),
            st.dropdownRounding);

        // Background (gradient or flat)
        if (st.UseSearchGradient)
        {
            dl->AddRectFilledMultiColor(
                dropMin, dropMax,
                ImGui::GetColorU32(st.SearchGradientTop),
                ImGui::GetColorU32(st.SearchGradientTop),
                ImGui::GetColorU32(st.SearchGradientBottom),
                ImGui::GetColorU32(st.SearchGradientBottom));
        }
        else
        {
            dl->AddRectFilled(dropMin, dropMax,
                              ImGui::ColorConvertFloat4ToU32(st.backgroundColor),
                              st.dropdownRounding);
        }

        // Glossy dropdown overlay
        if (st.UseGlossyDropdown && st.DropdownGlossIntensity > 0.0f)
        {
            float glossHeight = (dropMax.y - dropMin.y) * 0.35f;
            ImVec4 glossColor = ImVec4(1.0f, 1.0f, 1.0f, st.DropdownGlossIntensity * 0.4f);
            ImVec4 fadeOut = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
            dl->AddRectFilledMultiColor(
                ImVec2(dropMin.x, dropMin.y),
                ImVec2(dropMax.x, dropMin.y + glossHeight),
                ImGui::GetColorU32(glossColor),
                ImGui::GetColorU32(glossColor),
                ImGui::GetColorU32(fadeOut),
                ImGui::GetColorU32(fadeOut));
        }

        // Border
        if (st.borderThickness > 0.0f)
        {
            dl->AddRect(dropMin, dropMax,
                        ImGui::ColorConvertFloat4ToU32(st.borderColor),
                        st.dropdownRounding, 0, st.borderThickness);
        }
    }

    //==============================================================================
    // Single Row
    //==============================================================================

    void TrackSearchBar::DrawSingleRow(ImDrawList *dl, int index, const ImVec2 &rowMin, float dropW, bool hovered)
    {
        const auto &st = m_theme;

        if (hovered)
        {
            dl->AddRectFilled(rowMin, ImVec2(rowMin.x + dropW, rowMin.y + st.rowHeight),
                              ImGui::ColorConvertFloat4ToU32(st.rowHoverColor));
        }

        if (index > 0)
        {
            dl->AddLine(
                ImVec2(rowMin.x + st.rowSeparatorPadding, rowMin.y),
                ImVec2(rowMin.x + dropW - st.rowSeparatorPadding, rowMin.y),
                ImGui::ColorConvertFloat4ToU32(st.separatorColor));
        }

        ImVec2 textPos(rowMin.x + st.textPaddingX,
                       rowMin.y + (st.rowHeight - ImGui::GetTextLineHeight()) * 0.5f);

        DrawHighlightedText(dl, textPos, m_results[index].displayText);
    }

    //==============================================================================
    // Rows
    //==============================================================================

    void TrackSearchBar::DrawRows(ImDrawList *dl, const ImVec2 &dropMin, float dropW, float dropH, bool mouseInDrop)
    {
        const auto &st = m_theme;

        dl->PushClipRect(
            ImVec2(dropMin.x, dropMin.y + 2),
            ImVec2(dropMin.x + dropW, dropMin.y + dropH - 2), true);

        ImGuiIO &io = ImGui::GetIO();

        float yBase = dropMin.y + 2.0f - m_scrollOffset;
        int hoveredIndex = -1;

        for (int i = 0; i < static_cast<int>(m_results.size()); ++i)
        {
            float rowTop = yBase + i * st.rowHeight;
            float rowBottom = rowTop + st.rowHeight;

            if (rowBottom < dropMin.y + 2.0f)
                continue;
            if (rowTop > dropMin.y + dropH - 2.0f)
                break;

            ImVec2 rowMin(dropMin.x, rowTop);

            bool hovered = mouseInDrop &&
                           io.MousePos.x >= rowMin.x && io.MousePos.x <= rowMin.x + dropW &&
                           io.MousePos.y >= rowTop && io.MousePos.y <= rowBottom;

            if (hovered)
                hoveredIndex = i;

            DrawSingleRow(dl, i, rowMin, dropW, hovered);
        }

        dl->PopClipRect();

        // Handle click selection - consume the click to prevent track table activation
        if (hoveredIndex >= 0 && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
        {
            if (m_selectCallback)
                m_selectCallback(m_results[hoveredIndex]);
            CloseDropdown();
            m_query[0] = '\0';

            // CRITICAL: Consume mouse click to prevent it from reaching the track table
            ImGuiIO &io2 = ImGui::GetIO();
            io2.MouseClicked[ImGuiMouseButton_Left] = false;
            io2.MouseClickedPos[ImGuiMouseButton_Left] = ImVec2(-FLT_MAX, -FLT_MAX);
        }
    }

    //==============================================================================
    // Scroll Sink - Captures scroll events AND click events over the dropdown
    //==============================================================================

    void TrackSearchBar::RenderScrollSink(const ImVec2 &dropMin,
                                          float dropW,
                                          float dropH)
    {
        const auto &st = m_theme;
        ImGuiIO &io = ImGui::GetIO();

        m_dropMin = dropMin;
        m_dropMax = ImVec2(dropMin.x + dropW, dropMin.y + dropH);

        ImGui::SetNextWindowPos(dropMin);
        ImGui::SetNextWindowSize(ImVec2(dropW, dropH));
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoBringToFrontOnFocus;

        if (ImGui::Begin("##TrackSearchScrollSink", nullptr, flags))
        {
            ImGui::InvisibleButton("##Capture",
                                   ImVec2(dropW, dropH),
                                   ImGuiButtonFlags_MouseButtonLeft |
                                       ImGuiButtonFlags_MouseButtonRight);

            bool hovered = ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly);

            m_wasMouseInDrop = hovered;

            if (hovered)
            {
                //--------------------------------------------------
                // Scroll
                //--------------------------------------------------

                if (io.MouseWheel != 0.0f)
                {
                    m_scrollOffset -= io.MouseWheel *
                                      st.scrollSpeed *
                                      st.rowHeight;

                    float maxScroll =
                        std::max(0.0f,
                                 (float)m_results.size() * st.rowHeight - dropH + 4.0f);

                    m_scrollOffset =
                        std::clamp(m_scrollOffset,
                                   0.0f,
                                   maxScroll);

                    io.MouseWheel = 0.0f;
                    io.MouseWheelH = 0.0f;
                }

                //--------------------------------------------------
                // Eat mouse click
                //--------------------------------------------------

                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    m_clickConsumed = true;

                    io.MouseClicked[ImGuiMouseButton_Left] = false;
                    io.MouseDown[ImGuiMouseButton_Left] = false;
                }

                //--------------------------------------------------
                // Eat release
                //--------------------------------------------------

                if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
                {
                    io.MouseReleased[ImGuiMouseButton_Left] = false;
                }
            }
            else
            {
                m_clickConsumed = false;
            }
        }

        ImGui::End();

        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
    }

    //==============================================================================
    // Main Draw
    //==============================================================================

    void TrackSearchBar::Draw()
    {
        const auto &st = m_theme;
        ImGuiIO &io = ImGui::GetIO();

        //----------------------------------------------------------------------
        // Input
        //----------------------------------------------------------------------

        ImGui::PushStyleColor(ImGuiCol_FrameBg, st.inputBgColor);
        ImGui::PushStyleColor(ImGuiCol_Border, st.inputBorderColor);
        ImGui::PushStyleColor(ImGuiCol_Text, st.inputTextColor);
        ImGui::PushStyleColor(ImGuiCol_TextDisabled, st.inputHintColor);

        // Apply rounded input if enabled
        if (st.UseRoundedInput)
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, st.InputRounding);

        ImGui::SetNextItemWidth(m_width);

        bool edited =
            ImGui::InputTextWithHint(
                "##TrackSearchBar",
                m_hint.c_str(),
                m_query,
                sizeof(m_query),
                ImGuiInputTextFlags_AutoSelectAll);

        if (st.UseRoundedInput)
            ImGui::PopStyleVar();

        ImGui::PopStyleColor(4);

        // Draw search gradient on the input background if enabled
        // if (st.UseSearchGradient)
        // {
        //     ImVec2 inMin = ImGui::GetItemRectMin();
        //     ImVec2 inMax = ImGui::GetItemRectMax();
        //     ImDrawList *dl = ImGui::GetWindowDrawList();
        //     dl->AddRectFilledMultiColor(
        //         inMin, inMax,
        //         ImGui::GetColorU32(st.SearchGradientTop),
        //         ImGui::GetColorU32(st.SearchGradientTop),
        //         ImGui::GetColorU32(st.SearchGradientBottom),
        //         ImGui::GetColorU32(st.SearchGradientBottom));
        // }

        // // Draw search gloss on the input if enabled
        // if (st.UseSearchGloss && st.SearchGlossIntensity > 0.0f)
        // {
        //     ImVec2 inMin = ImGui::GetItemRectMin();
        //     ImVec2 inMax = ImGui::GetItemRectMax();
        //     ImDrawList *dl = ImGui::GetWindowDrawList();
        //     float glossH = (inMax.y - inMin.y) * 0.40f;
        //     ImVec4 glossCol = st.SearchGlossColor;
        //     glossCol.w *= st.SearchGlossIntensity;
        //     ImVec4 fadeOut = ImVec4(glossCol.x, glossCol.y, glossCol.z, 0.0f);
        //     dl->AddRectFilledMultiColor(
        //         ImVec2(inMin.x + 2.0f, inMin.y + 1.0f),
        //         ImVec2(inMax.x - 2.0f, inMin.y + glossH),
        //         ImGui::GetColorU32(glossCol),
        //         ImGui::GetColorU32(glossCol),
        //         ImGui::GetColorU32(fadeOut),
        //         ImGui::GetColorU32(fadeOut));
        // }

        bool inputActive = ImGui::IsItemActive();
        bool inputHovered = ImGui::IsItemHovered();

        //----------------------------------------------------------------------
        // Store SCREEN coordinates instead of child coordinates
        //----------------------------------------------------------------------

        ImVec2 inputMin = ImGui::GetItemRectMin();
        ImVec2 inputMax = ImGui::GetItemRectMax();

        //----------------------------------------------------------------------
        // Build results
        //----------------------------------------------------------------------

        if (edited)
        {
            BuildResults();
            m_dropdownOpen =
                (m_query[0] != '\0' && !m_results.empty());
        }

        if (ImGui::IsItemActivated() && m_query[0] != '\0')
        {
            BuildResults();
            m_dropdownOpen = !m_results.empty();
        }

        //----------------------------------------------------------------------
        // Dropdown
        //----------------------------------------------------------------------

        if (m_dropdownOpen)
        {
            float dropW = m_width;

            float visRows =
                std::min(
                    (float)m_results.size(),
                    st.maxVisibleRows);

            float dropH =
                visRows * st.rowHeight + 4.0f;

            ImVec2 dropMin(
                inputMin.x,
                inputMax.y);

            ImVec2 dropMax(
                dropMin.x + dropW,
                dropMin.y + dropH);

            bool mouseInDrop =
                io.MousePos.x >= dropMin.x &&
                io.MousePos.x <= dropMax.x &&
                io.MousePos.y >= dropMin.y &&
                io.MousePos.y <= dropMax.y;

            ImDrawList *dl =
                ImGui::GetForegroundDrawList();

            DrawDropdownBackground(
                dl,
                dropMin,
                dropMax);

            DrawRows(
                dl,
                dropMin,
                dropW,
                dropH,
                mouseInDrop);

            RenderScrollSink(
                dropMin,
                dropW,
                dropH);
        }

        //----------------------------------------------------------------------
        // Close when clicking outside
        //----------------------------------------------------------------------

        if (m_dropdownOpen && !inputHovered)
        {
            float dropH =
                std::min(
                    (float)m_results.size(),
                    st.maxVisibleRows) *
                    st.rowHeight +
                4.0f;

            bool mouseInDrop =
                io.MousePos.x >= inputMin.x &&
                io.MousePos.x <= inputMin.x + m_width &&
                io.MousePos.y >= inputMax.y &&
                io.MousePos.y <= inputMax.y + dropH;

            if (!mouseInDrop &&
                ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                CloseDropdown();
            }
        }

        //----------------------------------------------------------------------
        // Escape
        //----------------------------------------------------------------------

        if (inputActive &&
            ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            CloseDropdown();
        }
    }

} // namespace moosic