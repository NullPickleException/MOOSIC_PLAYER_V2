//==============================================================================
// UI/Windows/DirectoryWindow.h
//==============================================================================
// Directory management window - just renders, no data ownership
//==============================================================================

#pragma once

#include "../Data/DirectoryDataModel.h"
#include "IWindow.h"

#include <vector>
#include <filesystem>

namespace moosic
{

class DirectoryWindow : public IWindow
{
public:
    explicit DirectoryWindow(DirectoryDataModel& dataModel);
    ~DirectoryWindow() = default;

    void Draw() override;
    void ApplyTheme(const WindowTheme& theme) override { m_theme = theme; }

private:
    DirectoryDataModel& m_data;  // Shared data - we don't own it!
    WindowTheme m_theme;
};

} // namespace moosic   