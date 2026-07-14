//==============================================================================
// SettingsWindow.h
//==============================================================================

#pragma once

#include "IWindow.h"
#include <vector>
#include <string>

namespace moosic
{

// Forward declare Theme
struct Theme;

class SettingsWindow : public IWindow
{
public:
    SettingsWindow();
    void Draw() override;
    void ApplyTheme(const Theme& theme) override {}  // Empty

private:
    void DrawAppearanceSection();

private:
    // No theme storage - just display
};

} // namespace moosic