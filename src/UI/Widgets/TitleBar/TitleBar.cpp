//==============================================================================
// TitleBar.cpp
//==============================================================================
#include "TitleBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace moosic
{

    TitleBar::TitleBar() = default;

    TitleBar::~TitleBar()
    {
        ClearLogo();
    }

    void TitleBar::Initialize(SDL_Window *window)
    {
        m_window = window;
        m_renderer = SDL_GetRenderer(window);

        if (!m_window)
            return;

        SDL_SetWindowMinimumSize(m_window, m_theme.MinWindowWidth, m_theme.MinWindowHeight);

#ifdef _WIN32
        SDL_SetWindowHitTest(m_window, HitTestCallback, this);
#else
        SDL_SetWindowHitTest(m_window, HitTestCallback, this);
#endif
        SDL_SetWindowResizable(m_window, SDL_TRUE);

        // Load default logo from assets folder
        std::vector<std::string> logoPaths = {
            "assets/Logo_img/Moosic_Logo_Default.png",
            "../assets/Logo_img/Moosic_Logo_Default.png",
            "../../assets/Logo_img/Moosic_Logo_Default.png"};

        for (const auto &path : logoPaths)
        {
            if (LoadLogo(path))
            {
                std::cout << "[TitleBar] Logo loaded from: " << path << "\n";
                break;
            }
        }
    }

    bool TitleBar::LoadLogo(const std::string &path)
    {
        ClearLogo();

        if (!std::filesystem::exists(path))
            return false;

        if (!m_renderer)
        {
            m_renderer = SDL_GetRenderer(m_window);
            if (!m_renderer)
                return false;
        }

        // Use ImageLoader to load the file
        ImageLoader loader;
        ImageData imageData = loader.LoadFromFile(path);
        if (imageData.data.empty() || imageData.width <= 0 || imageData.height <= 0)
        {
            std::cout << "[TitleBar] ImageLoader failed to load: " << path << "\n";
            return false;
        }

        // Convert to RGBA
        ImageData rgbaData = loader.ToRGBA(imageData);

        // Calculate desired logo size (height = title bar height - padding) WITH SCALE
        int targetHeight = (int)((m_theme.Height - 6.0f) * m_theme.LogoScale);  // <<-- CHANGE HERE: Added * m_theme.LogoScale
        int targetWidth = (int)(targetHeight * ((float)rgbaData.width / (float)rgbaData.height));
        
        // If the logo is pixel art, use nearest neighbor scaling
        bool isPixelArt = true;
        if (isPixelArt && (rgbaData.width != targetWidth || rgbaData.height != targetHeight)) {
            int scale = 1;
            while (rgbaData.width * (scale + 1) <= targetWidth && 
                   rgbaData.height * (scale + 1) <= targetHeight) {
                scale++;
            }
            
            if (scale > 1) {
                int newWidth = rgbaData.width * scale;
                int newHeight = rgbaData.height * scale;
                
                if (newWidth <= targetWidth * 1.5f && newHeight <= targetHeight * 1.5f) {
                    rgbaData = loader.ResizePixelArt(rgbaData, newWidth, newHeight, true);
                } else {
                    rgbaData = loader.Resize(rgbaData, targetWidth, targetHeight);
                }
            }
        }

        SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(
            rgbaData.data.data(),
            rgbaData.width,
            rgbaData.height,
            32,
            rgbaData.width * 4,
            0x000000FF,
            0x0000FF00,
            0x00FF0000,
            0xFF000000
        );

        if (!surface)
            return false;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture)
            return false;

        SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        m_logoTexture = texture;
        m_logoWidth = rgbaData.width;
        m_logoHeight = rgbaData.height;
        m_theme.ShowLogo = true;
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

    void TitleBar::SetCustomButtons(const std::vector<std::string> &labels, CustomButtonCallback callback)
    {
        m_customButtonLabels = labels;
        m_customButtonCallback = std::move(callback);
        m_theme.ShowCustomButtons = !labels.empty();
    }

    void TitleBar::Render()
    {
        if (!m_window)
            return;

        Uint32 flags = SDL_GetWindowFlags(m_window);
        m_isMaximized = (flags & SDL_WINDOW_MAXIMIZED) != 0;
        m_isFocused = (flags & SDL_WINDOW_INPUT_FOCUS) != 0;

        ImGuiViewport *vp = ImGui::GetMainViewport();
        float barH = m_theme.Height;

        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(ImVec2(vp->Size.x, barH));

        ImGuiWindowFlags wflags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                  ImGuiWindowFlags_NoSavedSettings;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        if (ImGui::Begin("##MoosicTitleBar", nullptr, wflags))
        {
            ImDrawList *dl = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetWindowPos();
            ImVec2 size = ImGui::GetWindowSize();
            const float btnW = m_theme.ButtonWidth;

            // ── Background ──
            if (m_theme.UseTitleBarGradient)
            {
                dl->AddRectFilledMultiColor(
                    pos, ImVec2(pos.x + size.x, pos.y + size.y),
                    ImGui::GetColorU32(m_theme.TitleBarGradientTop),
                    ImGui::GetColorU32(m_theme.TitleBarGradientTop),
                    ImGui::GetColorU32(m_theme.TitleBarGradientBottom),
                    ImGui::GetColorU32(m_theme.TitleBarGradientBottom));
            }
            else
            {
                ImVec4 bg = m_isFocused ? m_theme.BackgroundColorActive : m_theme.BackgroundColorInactive;
                bg.w *= m_theme.BackgroundOpacity;
                dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImGui::GetColorU32(bg));
            }

            // ── Title bar gloss ──
            if (m_theme.UseTitleBarGloss && m_theme.TitleBarGlossIntensity > 0.0f)
            {
                float glossH = size.y * 0.45f;
                ImVec4 glossCol = m_theme.TitleBarGlossColor;
                glossCol.w *= m_theme.TitleBarGlossIntensity;
                ImVec4 fadeOut = ImVec4(glossCol.x, glossCol.y, glossCol.z, 0.0f);
                dl->AddRectFilledMultiColor(
                    ImVec2(pos.x, pos.y + 1.0f),
                    ImVec2(pos.x + size.x, pos.y + glossH),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(fadeOut),
                    ImGui::GetColorU32(fadeOut));
            }

            // ── Title bar bevel ──
            if (m_theme.UseTitleBarBevel && m_theme.TitleBarBevelThickness > 0.0f)
            {
                float t = m_theme.TitleBarBevelThickness;
                ImU32 lightCol = ImGui::GetColorU32(m_theme.TitleBarBevelLight);
                ImU32 darkCol = ImGui::GetColorU32(m_theme.TitleBarBevelDark);

                dl->AddRectFilled(
                    ImVec2(pos.x, pos.y),
                    ImVec2(pos.x + size.x, pos.y + t),
                    lightCol);
                dl->AddRectFilled(
                    ImVec2(pos.x, pos.y + size.y - t),
                    ImVec2(pos.x + size.x, pos.y + size.y),
                    darkCol);
            }

            // ── Window border ──
            if (m_theme.ShowWindowBorder && m_theme.WindowBorderThickness > 0.0f)
            {
                dl->AddRect(
                    pos,
                    ImVec2(pos.x + size.x, pos.y + size.y),
                    ImGui::GetColorU32(m_theme.WindowBorderColor),
                    m_theme.WindowBorderRounding,
                    ImDrawFlags_RoundCornersAll,
                    m_theme.WindowBorderThickness);
            }

            if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                ImVec2 mp = ImGui::GetMousePos();
                if (mp.y < m_theme.Height)
                {
                    float btnArea = ImGui::GetWindowWidth() -
                                    m_theme.ButtonWidth * (3 + m_customButtonLabels.size());
                    if (mp.x < btnArea)
                    {
                        if (m_isMaximized)
                            SDL_RestoreWindow(m_window);
                        else
                            SDL_MaximizeWindow(m_window);
                    }
                }
            }

            // ── Accent ──
            if (m_theme.ShowAccentLine)
                dl->AddLine(pos, ImVec2(pos.x + size.x, pos.y),
                            ImGui::GetColorU32(m_theme.AccentLineColor), m_theme.AccentLineThickness);

            // ── Logo ──
            float xOff = m_theme.TitleOffsetX;
            if (m_theme.ShowLogo && m_logoTexture)
            {
                float logoH = (barH - 6.0f) * m_theme.LogoScale;  // <<-- CHANGE HERE: Added * m_theme.LogoScale
                float logoW = logoH * ((float)m_logoWidth / (float)m_logoHeight);
                float yOff = 3.0f;
                ImVec2 lp(pos.x + m_theme.LogoPaddingLeft, pos.y + yOff);
                dl->AddImage((ImTextureID)(intptr_t)m_logoTexture, lp, ImVec2(lp.x + logoW, lp.y + logoH));
                xOff = m_theme.LogoPaddingLeft + logoW + m_theme.LogoPaddingRight;
            }

            // ── Title ──
            ImVec4 tc = m_isFocused ? m_theme.TitleTextColor : m_theme.TitleTextColorInactive;
            dl->AddText(ImVec2(pos.x + xOff, pos.y + (barH - ImGui::GetTextLineHeight()) * 0.5f),
                        ImGui::GetColorU32(tc), m_theme.TitleText.c_str());

            float xPos = size.x - btnW * 3.0f;

            // ── Custom buttons ──
            if (m_theme.ShowCustomButtons && !m_customButtonLabels.empty())
            {
                xPos -= btnW * (float)m_customButtonLabels.size();
                float cx = xPos;
                for (size_t i = 0; i < m_customButtonLabels.size(); ++i)
                {
                    ImGui::SetCursorPos(ImVec2(cx, 0));
                    if (ImGui::InvisibleButton(("##CB" + std::to_string(i)).c_str(), ImVec2(btnW, barH)))
                    {
                        if (m_customButtonCallback)
                            m_customButtonCallback((int)i);
                    }
                    ImVec2 bMin(pos.x + cx, pos.y);
                    if (ImGui::IsItemHovered())
                        dl->AddRectFilled(bMin, ImVec2(bMin.x + btnW, bMin.y + barH),
                                          ImGui::GetColorU32(m_theme.CustomButtonHoverBg));
                    ImVec2 ts = ImGui::CalcTextSize(m_customButtonLabels[i].c_str());
                    dl->AddText(ImVec2(bMin.x + (btnW - ts.x) * 0.5f, bMin.y + (barH - ts.y) * 0.5f),
                                ImGui::GetColorU32(m_theme.CustomButtonColor), m_customButtonLabels[i].c_str());
                    cx += btnW;
                }
                xPos += btnW * (float)m_customButtonLabels.size();
            }

            // ── Minimize ──
            ImGui::SetCursorPos(ImVec2(xPos, 0));
            if (ImGui::InvisibleButton("##Min", ImVec2(btnW, barH)))
                SDL_MinimizeWindow(m_window);
            {
                ImVec2 b(pos.x + xPos, pos.y);
                if (ImGui::IsItemHovered())
                    dl->AddRectFilled(b, ImVec2(b.x + btnW, b.y + barH),
                                      ImGui::GetColorU32(m_theme.MinimizeButtonHoverBg));
                ImVec2 c(b.x + btnW * 0.5f, b.y + barH * 0.5f + 3.0f);
                dl->AddLine(ImVec2(c.x - 5, c.y), ImVec2(c.x + 5, c.y),
                            ImGui::GetColorU32(m_theme.MinimizeButtonColor), m_theme.ButtonIconSize);
            }
            xPos += btnW;

            // ── Maximize ──
            ImGui::SetCursorPos(ImVec2(xPos, 0));
            if (ImGui::InvisibleButton("##Max", ImVec2(btnW, barH)))
            {
                if (m_isMaximized)
                    SDL_RestoreWindow(m_window);
                else
                    SDL_MaximizeWindow(m_window);
            }
            {
                ImVec2 b(pos.x + xPos, pos.y);
                if (ImGui::IsItemHovered())
                    dl->AddRectFilled(b, ImVec2(b.x + btnW, b.y + barH),
                                      ImGui::GetColorU32(m_theme.MaximizeButtonHoverBg));
                ImVec2 c(b.x + btnW * 0.5f, b.y + barH * 0.5f);
                float s = 5.0f, t = m_theme.ButtonIconSize;
                if (m_isMaximized)
                {
                    dl->AddRect(ImVec2(c.x - s + 2, c.y - s + 2), ImVec2(c.x + s + 2, c.y + s + 2),
                                ImGui::GetColorU32(m_theme.MaximizeButtonColor), 0, 0, t);
                    dl->AddRect(ImVec2(c.x - s - 2, c.y - s - 2), ImVec2(c.x + s - 2, c.y + s - 2),
                                ImGui::GetColorU32(m_theme.MaximizeButtonColor), 0, 0, t);
                }
                else
                {
                    dl->AddRect(ImVec2(c.x - s, c.y - s), ImVec2(c.x + s, c.y + s),
                                ImGui::GetColorU32(m_theme.MaximizeButtonColor), 0, 0, t);
                }
            }
            xPos += btnW;

            // ── Close ──
            ImGui::SetCursorPos(ImVec2(xPos, 0));
            if (ImGui::InvisibleButton("##Cls", ImVec2(btnW, barH)))
            {
                SDL_Event e;
                e.type = SDL_QUIT;
                SDL_PushEvent(&e);
            }
            {
                ImVec2 b(pos.x + xPos, pos.y);
                if (ImGui::IsItemHovered())
                    dl->AddRectFilled(b, ImVec2(b.x + btnW, b.y + barH),
                                      ImGui::GetColorU32(m_theme.CloseButtonHoverBg));
                ImVec2 c(b.x + btnW * 0.5f, b.y + barH * 0.5f);
                float s = 5.0f, t = m_theme.ButtonIconSize;
                dl->AddLine(ImVec2(c.x - s, c.y - s), ImVec2(c.x + s, c.y + s),
                            ImGui::GetColorU32(m_theme.CloseButtonColor), t);
                dl->AddLine(ImVec2(c.x + s, c.y - s), ImVec2(c.x - s, c.y + s),
                            ImGui::GetColorU32(m_theme.CloseButtonColor), t);
            }

            // ── Bottom border ──
            if (m_theme.ShowBottomBorder)
                dl->AddLine(ImVec2(pos.x, pos.y + size.y), ImVec2(pos.x + size.x, pos.y + size.y),
                            ImGui::GetColorU32(m_theme.BottomBorderColor), m_theme.BottomBorderThickness);

            ImGui::BringWindowToDisplayFront(ImGui::GetCurrentWindow());
        }
        ImGui::End();
        ImGui::SetItemAllowOverlap();
        ImGui::PopStyleVar(4);
    }

    //==============================================================================
    // SDL Hit Testing
    //==============================================================================

    SDL_HitTestResult TitleBar::HitTestCallback(SDL_Window *, const SDL_Point *area, void *data)
    {
        return static_cast<TitleBar *>(data)->HitTest(area);
    }

    SDL_HitTestResult TitleBar::HitTest(const SDL_Point *area)
    {
        if (!m_window)
            return SDL_HITTEST_NORMAL;

#ifdef _WIN32
        if (m_isMaximized)
            return SDL_HITTEST_NORMAL;

        int w, h;
        SDL_GetWindowSize(m_window, &w, &h);

        const int B = (int)m_theme.ResizeBorderWidth;

        bool left = area->x < B;
        bool right = area->x >= w - B;
        bool top = area->y < B;
        bool bottom = area->y >= h - B;

        if (left && top)
            return SDL_HITTEST_RESIZE_TOPLEFT;
        if (right && top)
            return SDL_HITTEST_RESIZE_TOPRIGHT;
        if (left && bottom)
            return SDL_HITTEST_RESIZE_BOTTOMLEFT;
        if (right && bottom)
            return SDL_HITTEST_RESIZE_BOTTOMRIGHT;
        if (left)
            return SDL_HITTEST_RESIZE_LEFT;
        if (right)
            return SDL_HITTEST_RESIZE_RIGHT;
        if (top)
            return SDL_HITTEST_RESIZE_TOP;
        if (bottom)
            return SDL_HITTEST_RESIZE_BOTTOM;

        if (area->y < (int)m_theme.Height)
        {
            int buttonArea = w - (int)(m_theme.ButtonWidth * (3 + m_customButtonLabels.size()));
            if (area->x >= buttonArea)
                return SDL_HITTEST_NORMAL;
            return SDL_HITTEST_DRAGGABLE;
        }

        return SDL_HITTEST_NORMAL;

#else
        if (area->y < (int)m_theme.Height)
        {
            int w, h;
            SDL_GetWindowSize(m_window, &w, &h);
            int buttonArea = w - (int)(m_theme.ButtonWidth * (3 + m_customButtonLabels.size()));

            if (area->x >= buttonArea)
                return SDL_HITTEST_NORMAL;
            return SDL_HITTEST_DRAGGABLE;
        }

        return SDL_HITTEST_NORMAL;
#endif
    }

} // namespace moosic