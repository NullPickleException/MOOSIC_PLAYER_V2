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

#include "Themes/Classic_Themes/ClassicIceTheme.h"
#include "Themes/Classic_Themes/ClassicBlueTheme.h"
#include "Themes/Classic_Themes/ClassicGreenTheme.h"
#include "Themes/Classic_Themes/ClassicAmberTheme.h"
#include "Themes/Classic_Themes/ClassicRubyTheme.h"
#include "Themes/Classic_Themes/ClassicCrimsonTheme.h"
#include "Themes/Classic_Themes/ClassicVioletTheme.h"
#include "Themes/Classic_Themes/ClassicBronzeTheme.h"
#include "Themes/Classic_Themes/ClassicRoseTheme.h"
#include "Themes/Classic_Themes/ClassicMintTheme.h"
#include "Themes/Classic_Themes/ClassicLavenderTheme.h"
#include "Themes/Classic_Themes/ClassicPeachTheme.h"
#include "Themes/Classic_Themes/ClassicRoseGoldTheme.h"
#include "Themes/Classic_Themes/ClassicCloudTheme.h"
#include "Themes/Classic_Themes/ClassicBubblegumTheme.h"

#include "Themes/Solorized_Themes/SolarizedDark.h"
#include "Themes/Solorized_Themes/SolarizedLight.h"

#include "Themes/Gothic_Themes/CrimsonNightTheme.h"
#include "Themes/Gothic_Themes/BloodMoonTheme.h"
#include "Themes/Gothic_Themes/RavenTheme.h"
#include "Themes/Gothic_Themes/CathedralTheme.h"
#include "Themes/Gothic_Themes/ObsidianTheme.h"
#include "Themes/Gothic_Themes/MidnightChapelTheme.h"
#include "Themes/Gothic_Themes/BlackRoseTheme.h"
#include "Themes/Gothic_Themes/PhantomTheme.h"
#include "Themes/Gothic_Themes/VampireTheme.h"
#include "Themes/Gothic_Themes/AshenTheme.h"
#include "Themes/Gothic_Themes/CursedEmeraldTheme.h"
#include "Themes/Gothic_Themes/WinterMorningTheme.h"
#include "Themes/Gothic_Themes/ThornedBerryTheme.h"
#include "Themes/Gothic_Themes/AmberChapelTheme.h"
#include "Themes/Gothic_Themes/NightCreaturesTheme.h"
#include "Themes/Gothic_Themes/ForgottenCemeteryTheme.h"

#include "Themes/Nature_Themes/ForestTheme.h"
#include "Themes/Nature_Themes/MossTheme.h"
#include "Themes/Nature_Themes/PineTheme.h"
#include "Themes/Nature_Themes/SakuraTheme.h"
#include "Themes/Nature_Themes/DesertTheme.h"
#include "Themes/Nature_Themes/CanyonTheme.h"
#include "Themes/Nature_Themes/GlacierFrostTheme.h"
#include "Themes/Nature_Themes/BambooTheme.h"
#include "Themes/Nature_Themes/OliveTheme.h"

#include "Themes/Neon_Themes/NeonPurpleTheme.h"
#include "Themes/Neon_Themes/NeonCyanTheme.h"
#include "Themes/Neon_Themes/NeonLimeTheme.h"
#include "Themes/Neon_Themes/NeonPinkTheme.h"
#include "Themes/Neon_Themes/CyberpunkTheme.h"
#include "Themes/Neon_Themes/VaporwaveTheme.h"
#include "Themes/Neon_Themes/TronTheme.h"
#include "Themes/Neon_Themes/OutrunTheme.h"
#include "Themes/Neon_Themes/DigitalRainTheme.h"

#include "Themes/Retro_Themes/Commodore64InspiredTheme.h"
#include "Themes/Retro_Themes/AmberCRTTheme.h"
#include "Themes/Retro_Themes/TerminalGreenTheme.h"
#include "Themes/Retro_Themes/DOSTheme.h"
#include "Themes/Retro_Themes/AtariInspiredTheme.h"
#include "Themes/Retro_Themes/NintendoInspiredTheme.h"
#include "Themes/Retro_Themes/XboxInspiredTheme.h"
#include "Themes/Retro_Themes/PlayStationInspiredTheme.h"
#include "Themes/Retro_Themes/GameboyInspiredTheme.h"
#include "Themes/Retro_Themes/RetroOSBlueTheme.h"

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
            RegisterTheme("Coffee Cream", CreateCoffeeCreamTheme);
            RegisterTheme("Coffee Black", CreateCoffeeBlackTheme);
            RegisterTheme("Matcha", CreateMatchaTheme);
            RegisterTheme("Latte", CreateLatteTheme);

            //===================================
            // Ice Themes
            //===================================
            RegisterTheme("Classic Ice", CreateClassicIceTheme);
            RegisterTheme("Classic Blue", CreateClassicBlueTheme);
            RegisterTheme("Classic Green", CreateClassicGreenTheme);
            RegisterTheme("Classic Amber", CreateClassicAmberTheme);
            RegisterTheme("Classic Ruby", CreateClassicRubyTheme);
            RegisterTheme("Classic Crimson", CreateClassicCrimsonTheme);
            RegisterTheme("Classic Violet", CreateClassicVioletTheme);
            RegisterTheme("Classic Bronze", CreateClassicBronzeTheme);
            RegisterTheme("Classic Rose", CreateClassicRoseTheme);
            RegisterTheme("Classic Mint", CreateClassicMintTheme);
            RegisterTheme("Classic Lavender", CreateClassicLavenderTheme);
            RegisterTheme("Classic Peach", CreateClassicPeachTheme);
            RegisterTheme("Classic Rose Gold", CreateClassicRoseGoldTheme);
            RegisterTheme("Classic Cloud", CreateClassicCloudTheme);
            RegisterTheme("Classic Bubblegum", CreateClassicBubblegumTheme);

            //===================================
            // Solarized Themes
            //===================================
            RegisterTheme("Solarized Dark", CreateSolarizedDarkTheme);
            RegisterTheme("Solarized Light", CreateSolarizedLightTheme);

            //===================================
            // Gothic Themes
            //===================================
            RegisterTheme("Crimson Night", CreateCrimsonNightTheme);
            RegisterTheme("Blood Moon", CreateBloodMoonTheme);
            RegisterTheme("Raven", CreateRavenTheme);
            RegisterTheme("Cathedral", CreateCathedralTheme);
            RegisterTheme("Obsidian", CreateObsidianTheme);
            RegisterTheme("Midnight Chapel", CreateMidnightChapelTheme);
            RegisterTheme("Black Rose", CreateBlackRoseTheme);
            RegisterTheme("Phantom", CreatePhantomTheme);
            RegisterTheme("Vampire", CreateVampireTheme);
            RegisterTheme("Ashen", CreateAshenTheme);
            RegisterTheme("Cursed Emerald", CreateCursedEmeraldTheme);
            RegisterTheme("Winter Morning", CreateWinterMorningTheme);
            RegisterTheme("Thorned Berry", CreateThornedBerryTheme);
            RegisterTheme("Amber Chapel", CreateAmberChapelTheme);
            RegisterTheme("Night Creatures", CreateNightCreaturesTheme);
            RegisterTheme("Forgotten Cemetery", CreateForgottenCemeteryTheme);

            //===================================
            // Nature Themes
            //===================================
            RegisterTheme("Forest", CreateForestTheme);
            RegisterTheme("Moss", CreateMossTheme);
            RegisterTheme("Pine", CreatePineTheme);
            RegisterTheme("Sakura", CreateSakuraTheme);
            RegisterTheme("Desert", CreateDesertTheme);
            RegisterTheme("Canyon", CreateCanyonTheme);
            RegisterTheme("Glacier Frost", CreateGlacierFrostTheme);
            RegisterTheme("Bamboo", CreateBambooTheme);
            RegisterTheme("Olive", CreateOliveTheme);

            //===================================
            // Neon Themes
            //===================================
            RegisterTheme("Neon Purple", CreateNeonPurpleTheme);
            RegisterTheme("Neon Cyan", CreateNeonCyanTheme);
            RegisterTheme("Neon Lime", CreateNeonLimeTheme);
            RegisterTheme("Neon Pink", CreateNeonPinkTheme);
            RegisterTheme("Cyberpunk", CreateCyberpunkTheme);
            RegisterTheme("Vaporwave", CreateVaporwaveTheme);
            RegisterTheme("Tron", CreateTronTheme);
            RegisterTheme("Outrun", CreateOutrunTheme);
            RegisterTheme("Digital Rain", CreateDigitalRainTheme);

            //===================================
            // Retro Themes
            //===================================
            RegisterTheme("Commodore 64 Inspired", CreateCommodore64InspiredTheme);
            RegisterTheme("Amber CRT", CreateAmberCRTTheme);
            RegisterTheme("Terminal Green", CreateTerminalGreenTheme);
            RegisterTheme("DOS", CreateDOSTheme);
            RegisterTheme("Atari Inspired", CreateAtariInspiredTheme);
            RegisterTheme("Nintendo Inspired", CreateNintendoInspiredTheme);
            RegisterTheme("Xbox Inspired", CreateXboxInspiredTheme);
            RegisterTheme("PlayStation Inspired", CreatePlayStationInspiredTheme);
            RegisterTheme("Gameboy Inspired", CreateGameboyInspiredTheme);
            RegisterTheme("Retro OS Blue", CreateRetroOSBlueTheme);
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