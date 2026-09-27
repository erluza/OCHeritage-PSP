#ifdef PSP_PLATFORM

#include "PspPadState.h"
#include <pspctrl.h>
#include <cmath>
#include <algorithm>

#include "lwjgl/Mouse.h"
#include "lwjgl/Keyboard.h"
#include "net/minecraft/src/Minecraft.h"
#include "net/minecraft/src/GuiScreen.h"

namespace
{
    static PspPadSnapshot s_snapshot;
    static std::uint32_t s_lastButtons = 0;
    static std::uint32_t s_latchedPressed = 0;

    static int s_cursorX = 240;
    static int s_cursorY = 136;

    float applyDeadzone(float value, float deadzone)
    {
        if (std::abs(value) < deadzone)
            return 0.0f;
        float sign = (value > 0.0f) ? 1.0f : -1.0f;
        return sign * ((std::abs(value) - deadzone) / (1.0f - deadzone));
    }
}

namespace PspPadState
{
    void init()
    {
        sceCtrlSetSamplingCycle(0);
        sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
        s_cursorX = 240;
        s_cursorY = 136;
        s_lastButtons = 0;
        s_latchedPressed = 0;
        lwjgl::Mouse::detail::pushMotion(240, 136, 0, 0);
    }

    void update()
    {
        SceCtrlData pad;
        if (sceCtrlPeekBufferPositive(&pad, 1) > 0)
        {
            s_snapshot.connected = true;
            s_snapshot.held = pad.Buttons;

            std::uint32_t newlyPressed = pad.Buttons & ~s_lastButtons;
            std::uint32_t released = s_lastButtons & ~pad.Buttons;
            s_snapshot.pressed = newlyPressed;
            s_snapshot.released = released;
            s_latchedPressed |= newlyPressed;
            s_lastButtons = pad.Buttons;

            // Map analog stick (-1.0 to 1.0)
            float rawX = (static_cast<float>(pad.Lx) - 128.0f) / 128.0f;
            float rawY = (static_cast<float>(pad.Ly) - 128.0f) / 128.0f;

            s_snapshot.leftX = applyDeadzone(rawX, 0.18f);
            s_snapshot.leftY = applyDeadzone(rawY, 0.18f);

            Minecraft* mc = Minecraft::getMinecraft();
            const bool inMenu = (mc != nullptr && mc->currentScreen != nullptr);
            static bool s_wasInMenu = false;

            if (inMenu != s_wasInMenu)
            {
                // Release all inputs when switching between menu and gameplay
                lwjgl::Mouse::detail::pushButton(0, false, s_cursorX, s_cursorY);
                lwjgl::Mouse::detail::pushButton(1, false, s_cursorX, s_cursorY);
                lwjgl::Keyboard::detail::pushKey(1, false);   // Esc
                lwjgl::Keyboard::detail::pushKey(15, false);  // Tab
                lwjgl::Keyboard::detail::pushKey(18, false);  // E
                lwjgl::Keyboard::detail::pushKey(28, false);  // Enter
                lwjgl::Keyboard::detail::pushKey(42, false);  // LShift
                lwjgl::Keyboard::detail::pushKey(57, false);  // Space
                lwjgl::Keyboard::detail::pushKey(200, false); // Up
                lwjgl::Keyboard::detail::pushKey(208, false); // Down
                lwjgl::Keyboard::detail::pushKey(203, false); // Left
                lwjgl::Keyboard::detail::pushKey(205, false); // Right
                lwjgl::Mouse::clearDeltas();
                s_wasInMenu = inMenu;
            }

            if (inMenu)
            {
                // Virtual pointer in menus
                if (std::abs(s_snapshot.leftX) > 0.01f || std::abs(s_snapshot.leftY) > 0.01f)
                {
                    int oldX = s_cursorX;
                    int oldY = s_cursorY;
                    s_cursorX += static_cast<int>(s_snapshot.leftX * 4.5f);
                    s_cursorY += static_cast<int>(s_snapshot.leftY * 4.5f);
                    s_cursorX = std::max(0, std::min(480, s_cursorX));
                    s_cursorY = std::max(0, std::min(272, s_cursorY));
                    int dx = s_cursorX - oldX;
                    int dy = s_cursorY - oldY;
                    if (dx != 0 || dy != 0)
                    {
                        lwjgl::Mouse::detail::pushMotion(s_cursorX, s_cursorY, dx, dy);
                    }
                }

                // D-Pad menu navigation
                if (newlyPressed & PSP_CTRL_UP)    lwjgl::Keyboard::detail::pushKey(200, true);
                if (released & PSP_CTRL_UP)        lwjgl::Keyboard::detail::pushKey(200, false);
                if (newlyPressed & PSP_CTRL_DOWN)  lwjgl::Keyboard::detail::pushKey(208, true);
                if (released & PSP_CTRL_DOWN)      lwjgl::Keyboard::detail::pushKey(208, false);
                if (newlyPressed & PSP_CTRL_LEFT)  lwjgl::Keyboard::detail::pushKey(203, true);
                if (released & PSP_CTRL_LEFT)      lwjgl::Keyboard::detail::pushKey(203, false);
                if (newlyPressed & PSP_CTRL_RIGHT) lwjgl::Keyboard::detail::pushKey(205, true);
                if (released & PSP_CTRL_RIGHT)     lwjgl::Keyboard::detail::pushKey(205, false);

                // Cross: Click / Select
                if (newlyPressed & PSP_CTRL_CROSS)
                    lwjgl::Mouse::detail::pushButton(0, true, s_cursorX, s_cursorY);
                if (released & PSP_CTRL_CROSS)
                    lwjgl::Mouse::detail::pushButton(0, false, s_cursorX, s_cursorY);

                // L / R Triggers: Creative menu / Container wheel scrolling
                if (newlyPressed & PSP_CTRL_LTRIGGER)
                    lwjgl::Mouse::detail::pushWheel(1, s_cursorX, s_cursorY);
                if (newlyPressed & PSP_CTRL_RTRIGGER)
                    lwjgl::Mouse::detail::pushWheel(-1, s_cursorX, s_cursorY);

                // Circle: Back / Cancel / Escape
                if (newlyPressed & PSP_CTRL_CIRCLE)
                    lwjgl::Keyboard::detail::pushKey(1, true);
                if (released & PSP_CTRL_CIRCLE)
                    lwjgl::Keyboard::detail::pushKey(1, false);

                // Square: Right Click (e.g. split stack in inventory)
                if (newlyPressed & PSP_CTRL_SQUARE)
                    lwjgl::Mouse::detail::pushButton(1, true, s_cursorX, s_cursorY);
                if (released & PSP_CTRL_SQUARE)
                    lwjgl::Mouse::detail::pushButton(1, false, s_cursorX, s_cursorY);

                // Triangle: Quick-move / Shift
                if (newlyPressed & PSP_CTRL_TRIANGLE)
                    lwjgl::Keyboard::detail::pushKey(42, true);
                if (released & PSP_CTRL_TRIANGLE)
                    lwjgl::Keyboard::detail::pushKey(42, false);

                // Start: Return
                if (newlyPressed & PSP_CTRL_START)
                    lwjgl::Keyboard::detail::pushKey(28, true);
                if (released & PSP_CTRL_START)
                    lwjgl::Keyboard::detail::pushKey(28, false);

                // Select: Tab
                if (newlyPressed & PSP_CTRL_SELECT)
                    lwjgl::Keyboard::detail::pushKey(15, true);
                if (released & PSP_CTRL_SELECT)
                    lwjgl::Keyboard::detail::pushKey(15, false);
            }
            else // in gameplay
            {
                // R Trigger: Attack / Mine (Left Click / Button 0)
                if (newlyPressed & PSP_CTRL_RTRIGGER)
                    lwjgl::Mouse::detail::pushButton(0, true, 0, 0);
                if (released & PSP_CTRL_RTRIGGER)
                    lwjgl::Mouse::detail::pushButton(0, false, 0, 0);

                // L Trigger: Use Item / Place Block (Right Click / Button 1)
                if (newlyPressed & PSP_CTRL_LTRIGGER)
                    lwjgl::Mouse::detail::pushButton(1, true, 0, 0);
                if (released & PSP_CTRL_LTRIGGER)
                    lwjgl::Mouse::detail::pushButton(1, false, 0, 0);

                // D-Pad Up: Jump (Space / Key 57)
                if (newlyPressed & PSP_CTRL_UP)
                    lwjgl::Keyboard::detail::pushKey(57, true);
                if (released & PSP_CTRL_UP)
                    lwjgl::Keyboard::detail::pushKey(57, false);

                // D-Pad Down: Sneak (LShift / Key 42)
                if (newlyPressed & PSP_CTRL_DOWN)
                    lwjgl::Keyboard::detail::pushKey(42, true);
                if (released & PSP_CTRL_DOWN)
                    lwjgl::Keyboard::detail::pushKey(42, false);

                // D-Pad Left: Hotbar Previous (Wheel +1)
                if (newlyPressed & PSP_CTRL_LEFT)
                    lwjgl::Mouse::detail::pushWheel(1, 0, 0);

                // D-Pad Right: Hotbar Next (Wheel -1)
                if (newlyPressed & PSP_CTRL_RIGHT)
                    lwjgl::Mouse::detail::pushWheel(-1, 0, 0);

                // Select: Open / Close Inventory (E / Key 18) or F5 if L is held
                if (newlyPressed & PSP_CTRL_SELECT)
                {
                    if (pad.Buttons & PSP_CTRL_LTRIGGER)
                    {
                        lwjgl::Keyboard::detail::pushKey(63, true);
                        lwjgl::Keyboard::detail::pushKey(63, false);
                    }
                    else
                    {
                        lwjgl::Keyboard::detail::pushKey(18, true);
                    }
                }
                if (released & PSP_CTRL_SELECT)
                {
                    lwjgl::Keyboard::detail::pushKey(18, false);
                }

                // Start: Pause / Menu (Escape / Key 1)
                if (newlyPressed & PSP_CTRL_START)
                    lwjgl::Keyboard::detail::pushKey(1, true);
                if (released & PSP_CTRL_START)
                    lwjgl::Keyboard::detail::pushKey(1, false);
            }
        }
        else
        {
            s_snapshot.connected = false;
        }
    }

    const PspPadSnapshot& getSnapshot()
    {
        return s_snapshot;
    }

    std::uint32_t consumePressed()
    {
        std::uint32_t pressed = s_latchedPressed;
        s_latchedPressed = 0;
        return pressed;
    }

    void clearLatches()
    {
        s_latchedPressed = 0;
    }

    int getCursorX()
    {
        return s_cursorX;
    }

    int getCursorY()
    {
        return s_cursorY;
    }

    void setCursorPosition(int x, int y)
    {
        s_cursorX = std::max(0, std::min(480, x));
        s_cursorY = std::max(0, std::min(272, y));
    }
}

#endif // PSP_PLATFORM
