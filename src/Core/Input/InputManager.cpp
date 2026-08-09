//==============================================================================
// Core/Input/InputManager.cpp
//==============================================================================

#include "InputManager.h"
#include <iostream>

namespace moosic
{
    void InputManager::Reset()
    {
        m_keyPressed.clear();
        m_keyReleased.clear();
        m_mouseButtonPressed.clear();
        m_mouseButtonReleased.clear();
        m_mediaKeyPressed.clear();
        m_mouseDeltaX = 0;
        m_mouseDeltaY = 0;
        m_mouseWheelDelta = 0;
        m_windowResized = false;
    }

    void InputManager::ProcessEvent(const SDL_Event &event)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_quit = true;
            break;

        case SDL_KEYDOWN:
            if (!event.key.repeat)
            {
                m_keyStates[event.key.keysym.sym] = true;
                m_keyPressed.insert(event.key.keysym.sym);

                // Handle media keys using scancodes
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_AUDIOPLAY: // Play/Pause button
                    m_mediaKeyPressed.insert(HotkeyAction::PlayPause);
                    break;
                case SDL_SCANCODE_AUDIONEXT:
                    m_mediaKeyPressed.insert(HotkeyAction::NextTrack);
                    break;
                case SDL_SCANCODE_AUDIOPREV:
                    m_mediaKeyPressed.insert(HotkeyAction::PreviousTrack);
                    break;
                case SDL_SCANCODE_AUDIOSTOP:
                    m_mediaKeyPressed.insert(HotkeyAction::Stop);
                    break;
                case SDL_SCANCODE_AUDIOMUTE:
                    m_mediaKeyPressed.insert(HotkeyAction::MuteToggle);
                    break;
                default:
                    break;
                }
            }
            break;

        case SDL_KEYUP:
            m_keyStates[event.key.keysym.sym] = false;
            m_keyReleased.insert(event.key.keysym.sym);
            break;

        // Handle controller/headphone buttons (if they map to SDL controller events)
        case SDL_CONTROLLERBUTTONDOWN:
            switch (event.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_START:
            case SDL_CONTROLLER_BUTTON_A:
                m_mediaKeyPressed.insert(HotkeyAction::PlayPause);
                break;
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                m_mediaKeyPressed.insert(HotkeyAction::PreviousTrack);
                break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                m_mediaKeyPressed.insert(HotkeyAction::NextTrack);
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            m_mouseButtonStates[event.button.button] = true;
            m_mouseButtonPressed.insert(event.button.button);
            break;

        case SDL_MOUSEBUTTONUP:
            m_mouseButtonStates[event.button.button] = false;
            m_mouseButtonReleased.insert(event.button.button);
            break;

        case SDL_MOUSEWHEEL:
            m_mouseWheelDelta = event.wheel.y;
            break;

        case SDL_MOUSEMOTION:
            m_mouseDeltaX = event.motion.xrel;
            m_mouseDeltaY = event.motion.yrel;
            m_mouseX = event.motion.x;
            m_mouseY = event.motion.y;
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                m_windowResized = true;
                m_windowWidth = event.window.data1;
                m_windowHeight = event.window.data2;
            }
            break;
        }
    }

    // ---- Keyboard Queries ----
    bool InputManager::IsKeyDown(SDL_Keycode key) const
    {
        auto it = m_keyStates.find(key);
        return it != m_keyStates.end() && it->second;
    }

    bool InputManager::IsKeyPressed(SDL_Keycode key) const
    {
        return m_keyPressed.find(key) != m_keyPressed.end();
    }

    bool InputManager::IsKeyReleased(SDL_Keycode key) const
    {
        return m_keyReleased.find(key) != m_keyReleased.end();
    }

    // ---- Mouse Queries ----
    bool InputManager::IsMouseButtonDown(int button) const
    {
        auto it = m_mouseButtonStates.find(button);
        return it != m_mouseButtonStates.end() && it->second;
    }

    bool InputManager::IsMouseButtonPressed(int button) const
    {
        return m_mouseButtonPressed.find(button) != m_mouseButtonPressed.end();
    }

    bool InputManager::IsMouseButtonReleased(int button) const
    {
        return m_mouseButtonReleased.find(button) != m_mouseButtonReleased.end();
    }

    void InputManager::GetMousePosition(int &x, int &y) const
    {
        x = m_mouseX;
        y = m_mouseY;
    }

    void InputManager::GetMouseDelta(int &dx, int &dy) const
    {
        dx = m_mouseDeltaX;
        dy = m_mouseDeltaY;
    }

    // ---- Hotkey Support ----
    bool InputManager::IsHotkeyPressed(HotkeyAction action) const
    {
        bool ctrl = IsKeyDown(SDLK_LCTRL) || IsKeyDown(SDLK_RCTRL);

        switch (action)
        {
        case HotkeyAction::PlayPause:
            return IsKeyPressed(SDLK_SPACE);

        case HotkeyAction::NextTrack:
            return (ctrl && IsKeyPressed(SDLK_RIGHT));

        case HotkeyAction::PreviousTrack:
            return (ctrl && IsKeyPressed(SDLK_LEFT));

        case HotkeyAction::Stop:
            return (ctrl && IsKeyPressed(SDLK_s));

        case HotkeyAction::VolumeUp:
            return (ctrl && IsKeyPressed(SDLK_UP));

        case HotkeyAction::VolumeDown:
            return (ctrl && IsKeyPressed(SDLK_DOWN));

        case HotkeyAction::MuteToggle:
            return (ctrl && IsKeyPressed(SDLK_m));

        case HotkeyAction::SeekForward:
            return IsKeyPressed(SDLK_RIGHT) && !ctrl;

        case HotkeyAction::SeekBackward:
            return IsKeyPressed(SDLK_LEFT) && !ctrl;
        }
        return false;
    }

    bool InputManager::IsMediaKeyPressed(HotkeyAction action) const
    {
        return m_mediaKeyPressed.find(action) != m_mediaKeyPressed.end();
    }

    void InputManager::ProcessHotkeys()
    {
        // Platform-specific global hotkey registration hook
        // For true global hotkeys (background), register OS-level shortcuts here
    }
}