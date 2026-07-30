//==============================================================================
// UI/Data/SettingsDataModel.h
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

        void SetThemeName(const std::string &name) { m_themeName = name; NotifyChanged(); }
        const std::string &GetThemeName() const { return m_themeName; }

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
        // Logo Path
        //--------------------------------------------------------------------------

        void SetLogoPath(const std::string &path) { m_logoPath = path; NotifyChanged(); }
        const std::string &GetLogoPath() const { return m_logoPath; }

        //--------------------------------------------------------------------------
        // Font Settings
        //--------------------------------------------------------------------------

        void SetFontPath(const std::string &path) { m_fontPath = path; NotifyChanged(); }
        const std::string &GetFontPath() const { return m_fontPath; }

        void SetFontName(const std::string &name) { m_fontName = name; NotifyChanged(); }
        const std::string &GetFontName() const { return m_fontName; }

        void SetFontSize(float size) { m_fontSize = size; NotifyChanged(); }
        float GetFontSize() const { return m_fontSize; }

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
        int m_visualizerMode = 0;
        int m_layoutMode = 0;
        std::string m_logoPath;

        // Font settings
        std::string m_fontPath;       // Empty = use ImGui default
        std::string m_fontName = "Default";
        float m_fontSize = 16.0f;

        DataChangedCallback m_onDataChanged;
    };

} // namespace moosic