//==============================================================================
// TitleBar.cpp
//==============================================================================
// Implementation of custom title bar
//==============================================================================

#include "TitleBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <cstdio>

namespace moosic
{

//==============================================================================
// Constructor / Destructor
//==============================================================================

TitleBar::TitleBar() = default;

TitleBar::~TitleBar()
{
    ClearLogo();
}

//==============================================================================
// Initialize
//==============================================================================

void TitleBar::Initialize(SDL_Window* window)
{
    m_window = window;
    m_renderer = SDL_GetRenderer(window);

    if (m_window)
    {
        SDL_SetWindowHitTest(m_window, HitTestCallback, this);
    }
}

//==============================================================================
// Logo
//==============================================================================

bool TitleBar::LoadLogo(const std::string& path)
{
    ClearLogo();

    if (!m_renderer)
    {
        m_renderer = SDL_GetRenderer(m_window);
        if (!m_renderer) return false;
    }

    // Use ImageLoader to load the image
    ImageLoader loader;
    ImageData imageData = loader.LoadFromFile(path);

    if (imageData.data.empty() || imageData.width <= 0 || imageData.height <= 0)
    {
        printf("[TitleBar] Failed to load logo: %s\n", path.c_str());
        return false;
    }

    // Convert to RGBA if needed
    ImageData rgbaData = loader.ToRGBA(imageData);

    // Create SDL texture from the image data
    SDL_Texture* texture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STATIC,
        rgbaData.width,
        rgbaData.height
    );

    if (!texture)
    {
        printf("[TitleBar] Failed to create logo texture: %s\n", SDL_GetError());
        return false;
    }

    SDL_UpdateTexture(texture, nullptr, rgbaData.data.data(), rgbaData.width * 4);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    m_logoTexture = texture;
    m_logoWidth = rgbaData.width;
    m_logoHeight = rgbaData.height;

    m_theme.ShowLogo = true;
    m_theme.LogoPath = path;
    return true;
}

void TitleBar::ClearLogo()
{
    if (m_logoTexture)
    {
        SDL_DestroyTexture(m_logoTexture);
        m_logoTexture = nullptr;
    }
    m_logoWidth = 0;
    m_logoHeight = 0;
    m_theme.ShowLogo = false;
}

//==============================================================================
// Custom Buttons
//==============================================================================

void TitleBar::SetCustomButtons(const std::vector<std::string>& labels, CustomButtonCallback callback)
{
    m_customButtonLabels = labels;
    m_customButtonCallback = std::move(callback);
    m_theme.ShowCustomButtons = !labels.empty();
}

//==============================================================================
// State
//==============================================================================

bool TitleBar::IsMaximized() const
{
    return m_isMaximized;
}

//==============================================================================
// Render
//==============================================================================

void TitleBar::Render()
{
    if (!m_window) return;

    // Update window state
    Uint32 flags = SDL_GetWindowFlags(m_window);
    m_isMaximized = (flags & SDL_WINDOW_MAXIMIZED) != 0;
    m_isFocused = (flags & SDL_WINDOW_INPUT_FOCUS) != 0;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    float barHeight = m_theme.Height;

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, barHeight));

    ImGuiWindowFlags wflags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

    if (ImGui::Begin("##MoosicTitleBar", nullptr, wflags))
    {
        DrawBackground();
        DrawAccentLine();
        DrawLogo();
        DrawTitleText();
        DrawCustomButtons();
        DrawWindowControls();
        DrawBottomBorder();
    }

    ImGui::End();
    ImGui::PopStyleVar(4);
}

//==============================================================================
// Draw Background
//==============================================================================

void TitleBar::DrawBackground()
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();

    ImVec4 bgColor = m_isFocused ? m_theme.BackgroundColorActive : m_theme.BackgroundColorInactive;
    bgColor.w *= m_theme.BackgroundOpacity;

    dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                      ImGui::GetColorU32(bgColor));
}

//==============================================================================
// Draw Accent Line
//==============================================================================

void TitleBar::DrawAccentLine()
{
    if (!m_theme.ShowAccentLine) return;

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();

    dl->AddLine(
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + size.x, pos.y),
        ImGui::GetColorU32(m_theme.AccentLineColor),
        m_theme.AccentLineThickness
    );
}

//==============================================================================
// Draw Logo
//==============================================================================

void TitleBar::DrawLogo()
{
    if (!m_theme.ShowLogo || !m_logoTexture) return;

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    float barHeight = m_theme.Height;

    float logoH = m_theme.LogoSize;
    float aspect = (float)m_logoWidth / (float)m_logoHeight;
    float logoW = logoH * aspect;

    float padding = m_theme.LogoPaddingLeft;
    float yOffset = (barHeight - logoH) * 0.5f;

    ImVec2 logoPos(pos.x + padding, pos.y + yOffset);
    ImVec2 logoEnd(logoPos.x + logoW, logoPos.y + logoH);

    dl->AddImage((ImTextureID)(intptr_t)m_logoTexture, logoPos, logoEnd);
}

//==============================================================================
// Draw Title Text
//==============================================================================

void TitleBar::DrawTitleText()
{
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    float barHeight = m_theme.Height;

    float xOffset = m_theme.TitleOffsetX;

    // If logo is showing, offset after logo
    if (m_theme.ShowLogo && m_logoTexture)
    {
        float logoH = m_theme.LogoSize;
        float aspect = (float)m_logoWidth / (float)m_logoHeight;
        float logoW = logoH * aspect;
        xOffset = m_theme.LogoPaddingLeft + logoW + m_theme.LogoPaddingRight;
    }

    ImVec4 textColor = m_isFocused ? m_theme.TitleTextColor : m_theme.TitleTextColorInactive;

    float textY = pos.y + (barHeight - ImGui::GetTextLineHeight()) * 0.5f;
    dl->AddText(ImVec2(pos.x + xOffset, textY),
                ImGui::GetColorU32(textColor),
                m_theme.TitleText.c_str());
}

//==============================================================================
// Draw Custom Buttons
//==============================================================================

void TitleBar::DrawCustomButtons()
{
    if (!m_theme.ShowCustomButtons || m_customButtonLabels.empty()) return;

    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();
    float barHeight = m_theme.Height;
    float btnW = m_theme.ButtonWidth;

    // Position custom buttons right before window controls
    float customCount = (float)m_customButtonLabels.size();
    float windowControlsWidth = btnW * 3.0f;  // Min, Max, Close
    float xPos = size.x - windowControlsWidth - (btnW * customCount);

    for (size_t i = 0; i < m_customButtonLabels.size(); ++i)
    {
        ImGui::SetCursorPos(ImVec2(xPos, 0));

        ImVec2 btnMin(pos.x + xPos, pos.y);
        ImVec2 btnMax(pos.x + xPos + btnW, pos.y + barHeight);

        bool hovered = ImGui::IsMouseHoveringRect(btnMin, btnMax);
        bool clicked = ImGui::InvisibleButton(
            ("##CustomBtn" + std::to_string(i)).c_str(), ImVec2(btnW, barHeight));

        ImDrawList* dl = ImGui::GetWindowDrawList();

        if (hovered)
            dl->AddRectFilled(btnMin, btnMax, ImGui::GetColorU32(m_theme.CustomButtonHoverBg));

        // Draw the label text centered
        ImVec2 textSize = ImGui::CalcTextSize(m_customButtonLabels[i].c_str());
        ImVec2 textPos(
            btnMin.x + (btnW - textSize.x) * 0.5f,
            btnMin.y + (barHeight - textSize.y) * 0.5f
        );
        dl->AddText(textPos, ImGui::GetColorU32(m_theme.CustomButtonColor),
                    m_customButtonLabels[i].c_str());

        if (clicked && m_customButtonCallback)
            m_customButtonCallback((int)i);

        xPos += btnW;
    }
}

//==============================================================================
// Draw Window Controls
//==============================================================================

void TitleBar::DrawWindowControls()
{
    ImVec2 size = ImGui::GetWindowSize();
    float btnW = m_theme.ButtonWidth;
    float xPos = size.x - btnW * 3.0f;

    DrawMinimizeButton(xPos);
    xPos += btnW;
    DrawMaximizeButton(xPos);
    xPos += btnW;
    DrawCloseButton(xPos);
}

//==============================================================================
// Minimize Button
//==============================================================================

void TitleBar::DrawMinimizeButton(float& xPos)
{
    ImVec2 pos = ImGui::GetWindowPos();
    float barHeight = m_theme.Height;
    float btnW = m_theme.ButtonWidth;

    ImGui::SetCursorPos(ImVec2(xPos, 0));

    ImVec2 btnMin(pos.x + xPos, pos.y);
    ImVec2 btnMax(pos.x + xPos + btnW, pos.y + barHeight);

    bool hovered = ImGui::IsMouseHoveringRect(btnMin, btnMax);
    bool clicked = ImGui::InvisibleButton("##Minimize", ImVec2(btnW, barHeight));

    ImDrawList* dl = ImGui::GetWindowDrawList();

    if (hovered)
        dl->AddRectFilled(btnMin, btnMax, ImGui::GetColorU32(m_theme.MinimizeButtonHoverBg));

    if (clicked)
        SDL_MinimizeWindow(m_window);

    // Draw minimize icon (horizontal line)
    float iconThickness = m_theme.ButtonIconSize;
    ImVec2 center(btnMin.x + btnW * 0.5f, btnMin.y + barHeight * 0.5f + 2.0f);
    dl->AddLine(
        ImVec2(center.x - 5, center.y),
        ImVec2(center.x + 5, center.y),
        ImGui::GetColorU32(m_theme.MinimizeButtonColor),
        iconThickness
    );
}

//==============================================================================
// Maximize / Restore Button
//==============================================================================

void TitleBar::DrawMaximizeButton(float& xPos)
{
    ImVec2 pos = ImGui::GetWindowPos();
    float barHeight = m_theme.Height;
    float btnW = m_theme.ButtonWidth;

    ImGui::SetCursorPos(ImVec2(xPos, 0));

    ImVec2 btnMin(pos.x + xPos, pos.y);
    ImVec2 btnMax(pos.x + xPos + btnW, pos.y + barHeight);

    bool hovered = ImGui::IsMouseHoveringRect(btnMin, btnMax);
    bool clicked = ImGui::InvisibleButton("##Maximize", ImVec2(btnW, barHeight));

    ImDrawList* dl = ImGui::GetWindowDrawList();

    if (hovered)
        dl->AddRectFilled(btnMin, btnMax, ImGui::GetColorU32(m_theme.MaximizeButtonHoverBg));

    if (clicked)
    {
        if (m_isMaximized) SDL_RestoreWindow(m_window);
        else               SDL_MaximizeWindow(m_window);
    }

    float iconThickness = m_theme.ButtonIconSize;
    ImVec2 center(btnMin.x + btnW * 0.5f, btnMin.y + barHeight * 0.5f);

    if (m_isMaximized)
    {
        // Restore icon: two overlapping rectangles
        float s = 5.0f;
        dl->AddRect(ImVec2(center.x - s + 2, center.y - s + 2),
                    ImVec2(center.x + s + 2, center.y + s + 2),
                    ImGui::GetColorU32(m_theme.MaximizeButtonColor), 0.0f, 0, iconThickness);
        dl->AddRect(ImVec2(center.x - s - 2, center.y - s - 2),
                    ImVec2(center.x + s - 2, center.y + s - 2),
                    ImGui::GetColorU32(m_theme.MaximizeButtonColor), 0.0f, 0, iconThickness);
    }
    else
    {
        // Maximize icon: single rectangle
        float s = 5.0f;
        dl->AddRect(ImVec2(center.x - s, center.y - s),
                    ImVec2(center.x + s, center.y + s),
                    ImGui::GetColorU32(m_theme.MaximizeButtonColor), 0.0f, 0, iconThickness);
    }
}

//==============================================================================
// Close Button
//==============================================================================

void TitleBar::DrawCloseButton(float& xPos)
{
    ImVec2 pos = ImGui::GetWindowPos();
    float barHeight = m_theme.Height;
    float btnW = m_theme.ButtonWidth;

    ImGui::SetCursorPos(ImVec2(xPos, 0));

    ImVec2 btnMin(pos.x + xPos, pos.y);
    ImVec2 btnMax(pos.x + xPos + btnW, pos.y + barHeight);

    bool hovered = ImGui::IsMouseHoveringRect(btnMin, btnMax);
    bool clicked = ImGui::InvisibleButton("##Close", ImVec2(btnW, barHeight));

    ImDrawList* dl = ImGui::GetWindowDrawList();

    if (hovered)
        dl->AddRectFilled(btnMin, btnMax, ImGui::GetColorU32(m_theme.CloseButtonHoverBg));

    if (clicked)
    {
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    }

    // Draw X icon
    float iconThickness = m_theme.ButtonIconSize;
    ImVec2 center(btnMin.x + btnW * 0.5f, btnMin.y + barHeight * 0.5f);
    float s = 5.0f;
    dl->AddLine(ImVec2(center.x - s, center.y - s), ImVec2(center.x + s, center.y + s),
                ImGui::GetColorU32(m_theme.CloseButtonColor), iconThickness);
    dl->AddLine(ImVec2(center.x + s, center.y - s), ImVec2(center.x - s, center.y + s),
                ImGui::GetColorU32(m_theme.CloseButtonColor), iconThickness);
}

//==============================================================================
// Draw Bottom Border
//==============================================================================

void TitleBar::DrawBottomBorder()
{
    if (!m_theme.ShowBottomBorder) return;

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    ImVec2 size = ImGui::GetWindowSize();

    dl->AddLine(
        ImVec2(pos.x, pos.y + size.y),
        ImVec2(pos.x + size.x, pos.y + size.y),
        ImGui::GetColorU32(m_theme.BottomBorderColor),
        m_theme.BottomBorderThickness
    );
}

//==============================================================================
// SDL Hit Testing for Window Resize
//==============================================================================

SDL_HitTestResult TitleBar::HitTestCallback(SDL_Window*, const SDL_Point* area, void* data)
{
    return static_cast<TitleBar*>(data)->HitTest(area);
}

SDL_HitTestResult TitleBar::HitTest(const SDL_Point* area)
{
    if (!m_window) return SDL_HITTEST_NORMAL;

    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);

    const int B = (int)m_theme.ResizeBorderWidth;
    bool L = area->x < B;
    bool R = area->x > w - B;
    bool T = area->y < B;
    bool Bot = area->y > h - B;

    // Corner resizing
    if (L && T)   return SDL_HITTEST_RESIZE_TOPLEFT;
    if (R && T)   return SDL_HITTEST_RESIZE_TOPRIGHT;
    if (L && Bot) return SDL_HITTEST_RESIZE_BOTTOMLEFT;
    if (R && Bot) return SDL_HITTEST_RESIZE_BOTTOMRIGHT;

    // Edge resizing
    if (L)        return SDL_HITTEST_RESIZE_LEFT;
    if (R)        return SDL_HITTEST_RESIZE_RIGHT;
    if (T)        return SDL_HITTEST_RESIZE_TOP;
    if (Bot)      return SDL_HITTEST_RESIZE_BOTTOM;

    // Title bar area
    if (area->y < (int)m_theme.Height)
    {
        // Window control buttons area — don't drag
        float btnW = m_theme.ButtonWidth;
        int btnAreaX = w - (int)(btnW * 3.0f);

        // Also skip custom buttons area
        if (m_theme.ShowCustomButtons && !m_customButtonLabels.empty())
        {
            float customWidth = btnW * (float)m_customButtonLabels.size();
            btnAreaX -= (int)customWidth;
        }

        if (area->x > btnAreaX)
            return SDL_HITTEST_NORMAL;

        return SDL_HITTEST_DRAGGABLE;
    }

    return SDL_HITTEST_NORMAL;
}

} // namespace moosic