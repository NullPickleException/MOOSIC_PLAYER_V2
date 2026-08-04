//==============================================================================
// Core/Input/InputManager.h
//==============================================================================

#pragma once

#include <SDL.h>
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace moosic
{
    // Hotkey action identifiers
    enum class HotkeyAction
    {
        PlayPause,
        NextTrack,
        PreviousTrack,
        Stop,
        VolumeUp,
        VolumeDown,
        MuteToggle,
        SeekForward,
        SeekBackward
    };

    class InputManager
    {
    public:
        InputManager() = default;
        ~InputManager() = default;

        // ---- Event Processing ----
        void Reset();                              // Clear per-frame states
        void ProcessEvent(const SDL_Event& event); // Process individual event

        // ---- Keyboard ----
        bool IsKeyDown(SDL_Keycode key) const;
        bool IsKeyPressed(SDL_Keycode key) const;
        bool IsKeyReleased(SDL_Keycode key) const;

        // ---- Mouse ----
        bool IsMouseButtonDown(int button) const;
        bool IsMouseButtonPressed(int button) const;
        bool IsMouseButtonReleased(int button) const;
        void GetMousePosition(int& x, int& y) const;
        void GetMouseDelta(int& dx, int& dy) const;
        int GetMouseWheelDelta() const { return m_mouseWheelDelta; }

        // ---- Window ----
        bool WasWindowResized() const { return m_windowResized; }
        int GetWindowWidth() const { return m_windowWidth; }
        int GetWindowHeight() const { return m_windowHeight; }

        // ---- Control ----
        bool ShouldQuit() const { return m_quit; }
        void QuitProgram() { m_quit = true; }

        // ---- Hotkey Support ----
        bool IsHotkeyPressed(HotkeyAction action) const;
        void ProcessHotkeys();  // Call once per frame after ProcessEvent

    private:
        // ---- State ----
        bool m_quit = false;
        bool m_windowResized = false;
        int m_mouseX = 0, m_mouseY = 0;
        int m_mouseDeltaX = 0, m_mouseDeltaY = 0;
        int m_mouseWheelDelta = 0;
        int m_windowWidth = 0, m_windowHeight = 0;

        // ---- Keyboard ----
        std::unordered_map<SDL_Keycode, bool> m_keyStates;
        std::unordered_set<SDL_Keycode> m_keyPressed;
        std::unordered_set<SDL_Keycode> m_keyReleased;

        // ---- Mouse ----
        std::unordered_map<int, bool> m_mouseButtonStates;
        std::unordered_set<int> m_mouseButtonPressed;
        std::unordered_set<int> m_mouseButtonReleased;
    };
}