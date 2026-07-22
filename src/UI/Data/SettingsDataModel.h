//==============================================================================
// UI/Data/SettingsDataModel.h
//==============================================================================
// Central data store for application settings (theme, visualizer, etc.)
//==============================================================================

#pragma once

#include <string>
#include <functional>

namespace moosic
{

class SettingsDataModel
{
public:
    SettingsDataModel() = default;

    //--------------------------------------------------------------------------
    // Theme
    //--------------------------------------------------------------------------

    void SetThemeName(const std::string& name) { m_themeName = name; NotifyChanged(); }
    const std::string& GetThemeName() const { return m_themeName; }

    //--------------------------------------------------------------------------
    // Visualizer Mode
    //--------------------------------------------------------------------------

    void SetVisualizerMode(int mode) { m_visualizerMode = mode; NotifyChanged(); }
    int GetVisualizerMode() const { return m_visualizerMode; }

    //--------------------------------------------------------------------------
    // Layout
    //--------------------------------------------------------------------------

    void SetLayoutMode(int mode) { m_layoutMode = mode; NotifyChanged(); }
    int GetLayoutMode() const { return m_layoutMode; }

    //--------------------------------------------------------------------------
    // Change Notification
    //--------------------------------------------------------------------------

    using DataChangedCallback = std::function<void()>;
    void SetOnDataChanged(DataChangedCallback callback) { m_onDataChanged = std::move(callback); }

private:
    void NotifyChanged()
    {
        if (m_onDataChanged) m_onDataChanged();
    }

    std::string m_themeName = "Dark";
    int m_visualizerMode = 0;   // 0=Spectrum, 1=Oscilloscope
    int m_layoutMode = 0;       // 0=Standard

    DataChangedCallback m_onDataChanged;
};

} // namespace moosic