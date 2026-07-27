//==============================================================================
// ThemeManager.h
//==============================================================================
// Central theme management with theme registration and switching
//==============================================================================

#pragma once

#include "Theme.h"

#include "Themes/Default_Themes/DarkTheme.h"
#include "Themes/Default_Themes/LightTheme.h"
#include "Themes/Default_Themes/DarkGreenTheme.h"
#include "Themes/Default_Themes/LightGreenTheme.h"
#include "Themes/Default_Themes/DarkPurpleTheme.h"
#include "Themes/Default_Themes/LightPurpleTheme.h"
#include "Themes/Default_Themes/DarkRedTheme.h"
#include "Themes/Default_Themes/LightRedTheme.h"
#include "Themes/Default_Themes/DarkOrangeTheme.h"
#include "Themes/Default_Themes/LightOrangeTheme.h"
#include "Themes/Default_Themes/DarkPinkTheme.h"
#include "Themes/Default_Themes/LightPinkTheme.h"

#include "Themes/Ocean_Themes/CoralReefTheme.h"
#include "Themes/Ocean_Themes/DeepBlueTheme.h"
#include "Themes/Ocean_Themes/LagoonTheme.h"
#include "Themes/Ocean_Themes/WhaleSongTheme.h"
#include "Themes/Ocean_Themes/StormTheme.h"
#include "Themes/Ocean_Themes/TsunamiTheme.h"
#include "Themes/Ocean_Themes/SeafoamTheme.h"
#include "Themes/Ocean_Themes/PearlTheme.h"


#include "Themes/Coffee_Themes/CoffeeTheme.h"
#include "Themes/Coffee_Themes/CoffeeCreamTheme.h"
#include "Themes/Coffee_Themes/CoffeeBlackTheme.h"
#include "Themes/Coffee_Themes/MatchaTheme.h"
#include "Themes/Coffee_Themes/LatteTheme.h"

#include <vector>
#include <string>
#include <functional>

namespace moosic
{

    //==============================================================================
    // ThemeEntry
    //==============================================================================

    struct ThemeEntry
    {
        std::string Name;
        std::function<Theme()> Factory;
    };

    //==============================================================================
    // ThemeManager
    //==============================================================================

    class ThemeManager
    {
    public:
        ThemeManager()
        {
            RegisterThemes();
            m_currentTheme = CreateDarkTheme();
            m_currentThemeName = "Dark";
        }

        //--------------------------------------------------------------------------
        // Theme Registration
        //--------------------------------------------------------------------------

        void RegisterTheme(const std::string &name, std::function<Theme()> factory)
        {
            m_themes.push_back({name, factory});
        }
        void RegisterThemes()
        {
            //===================================
            // Default Themes
            //===================================
            RegisterTheme("Dark", CreateDarkTheme);
            RegisterTheme("Light", CreateLightTheme);
            RegisterTheme("Dark Green", CreateDarkGreenTheme);
            RegisterTheme("Light Green", CreateLightGreenTheme);
            RegisterTheme("Dark Purple", CreateDarkPurpleTheme);
            RegisterTheme("Light Purple", CreateLightPurpleTheme);
            RegisterTheme("Dark Red", CreateDarkRedTheme);
            RegisterTheme("Light Red", CreateLightRedTheme);
            RegisterTheme("Dark Orange", CreateDarkOrangeTheme);
            RegisterTheme("Light Orange", CreateLightOrangeTheme);
            RegisterTheme("Dark Pink", CreateDarkPinkTheme);
            RegisterTheme("Light Pink", CreateLightPinkTheme);

            //===================================
            // Ocean Themes
            //===================================
            RegisterTheme("Coral Reef", CreateCoralReefTheme);
            RegisterTheme("Deep Blue", CreateDeepBlueTheme);
            RegisterTheme("Lagoon", CreateLagoonTheme);
            RegisterTheme("Whale Song", CreateWhaleSongTheme);
            RegisterTheme("Storm", CreateStormTheme);
            RegisterTheme("Tsunami", CreateTsunamiTheme);
            RegisterTheme("Seafoam", CreateSeafoamTheme);
            RegisterTheme("Pearl", CreatePearlTheme);
        
        
            //===================================
            // Coffee Themes
            //===================================
            RegisterTheme("Coffee", CreateCoffeeTheme);
            RegisterTheme("Coffe Cream", CreateCoffeeCreamTheme);
            RegisterTheme("Coffe Black", CreateCoffeeBlackTheme);
            RegisterTheme("Matcha", CreateMatchaTheme);
            RegisterTheme("Latte", CreateLatteTheme);
            
        
        
        }

        //--------------------------------------------------------------------------
        // Theme Access
        //--------------------------------------------------------------------------

        const std::vector<ThemeEntry> &GetAvailableThemes() const
        {
            return m_themes;
        }

        std::vector<std::string> GetThemeNames() const
        {
            std::vector<std::string> names;
            names.reserve(m_themes.size());
            for (const auto &theme : m_themes)
            {
                names.push_back(theme.Name);
            }
            return names;
        }

        //--------------------------------------------------------------------------
        // Theme Switching
        //--------------------------------------------------------------------------

        bool SetTheme(const std::string &name)
        {
            for (const auto &theme : m_themes)
            {
                if (theme.Name == name)
                {
                    m_currentTheme = theme.Factory();
                    m_currentThemeName = name;
                    return true;
                }
            }
            return false;
        }

        void SetTheme(const Theme &theme)
        {
            m_currentTheme = theme;
            m_currentThemeName = "";
        }

        const Theme &GetTheme() const
        {
            return m_currentTheme;
        }

        int GetCurrentThemeIndex() const
        {
            for (size_t i = 0; i < m_themes.size(); ++i)
            {
                if (m_themes[i].Name == m_currentThemeName)
                {
                    return static_cast<int>(i);
                }
            }
            return 0;
        }

        std::string GetCurrentThemeName() const
        {
            return m_currentThemeName.empty() ? "Dark" : m_currentThemeName;
        }

        bool SetThemeByIndex(int index)
        {
            if (index >= 0 && index < static_cast<int>(m_themes.size()))
            {
                const auto &entry = m_themes[index];
                m_currentTheme = entry.Factory();
                m_currentThemeName = entry.Name;
                return true;
            }
            return false;
        }

    private:
        std::vector<ThemeEntry> m_themes;
        Theme m_currentTheme;
        std::string m_currentThemeName;
    };

} // namespace moosic