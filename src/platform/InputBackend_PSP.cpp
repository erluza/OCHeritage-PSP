#include "platform/Input.h"

#ifdef PSP_PLATFORM
#include "psp/input/PspPadState.h"
#include "platform/time.h"
#include <pspctrl.h>

namespace
{
std::uint32_t mapTextButtons(std::uint32_t bits)
{
    std::uint32_t value = 0;
    if (bits & PSP_CTRL_LEFT)     value |= PLATFORM_TEXT_LEFT;
    if (bits & PSP_CTRL_RIGHT)    value |= PLATFORM_TEXT_RIGHT;
    if (bits & PSP_CTRL_UP)       value |= PLATFORM_TEXT_UP;
    if (bits & PSP_CTRL_DOWN)     value |= PLATFORM_TEXT_DOWN;
    if (bits & PSP_CTRL_CROSS)    value |= PLATFORM_TEXT_TYPE;
    if (bits & PSP_CTRL_SQUARE)   value |= PLATFORM_TEXT_BACK;
    if (bits & PSP_CTRL_SELECT)   value |= PLATFORM_TEXT_SPACE;
    if (bits & PSP_CTRL_TRIANGLE) value |= PLATFORM_TEXT_SHIFT;
    if (bits & PSP_CTRL_START)    value |= PLATFORM_TEXT_ENTER;
    if (bits & PSP_CTRL_CIRCLE)   value |= PLATFORM_TEXT_CLOSE;
    return value;
}
}

PlatformTextInputSnapshot platformTextInputSnapshot(int port)
{
    (void)port;
    PlatformTextInputSnapshot out;
    const PspPadSnapshot& pad = PspPadState::getSnapshot();
    out.connected = pad.connected;
    out.held = mapTextButtons(pad.held);
    out.pressed = mapTextButtons(PspPadState::consumePressed());
    out.pointerValid = true;
    out.pointerX = PspPadState::getCursorX();
    out.pointerY = PspPadState::getCursorY();
    out.pointerWidth = 480;
    out.pointerHeight = 272;
    return out;
}

#include "net/minecraft/src/Minecraft.h"

PlatformGamepadSnapshot platformGamepadSnapshot(int port)
{
    (void)port;
    PlatformGamepadSnapshot out;
    const PspPadSnapshot& pad = PspPadState::getSnapshot();
    out.connected = pad.connected;
    out.leftX = pad.leftX;
    out.leftY = pad.leftY;

    Minecraft *mc = Minecraft::getMinecraft();
    if (mc != nullptr && mc->currentScreen == nullptr)
    {
        static uint32_t s_holdStartTickX = 0;
        static uint32_t s_holdStartTickY = 0;
        static uint32_t s_lastButtons = 0;
        const uint32_t nowMs = static_cast<uint32_t>(getTimeUS() / 1000ULL);

        bool lookLeft = (pad.held & PSP_CTRL_SQUARE) != 0;
        bool lookRight = (pad.held & PSP_CTRL_CIRCLE) != 0;
        bool lookUp = (pad.held & PSP_CTRL_TRIANGLE) != 0;
        bool lookDown = (pad.held & PSP_CTRL_CROSS) != 0;

        if (lookLeft && !lookRight)
        {
            if (!(s_lastButtons & PSP_CTRL_SQUARE)) s_holdStartTickX = nowMs;
            uint32_t duration = nowMs - s_holdStartTickX;
            float ramp = duration < 120 ? 0.35f : (duration < 250 ? 0.65f : 1.0f);
            out.rightX -= ramp;
        }
        else if (lookRight && !lookLeft)
        {
            if (!(s_lastButtons & PSP_CTRL_CIRCLE)) s_holdStartTickX = nowMs;
            uint32_t duration = nowMs - s_holdStartTickX;
            float ramp = duration < 120 ? 0.35f : (duration < 250 ? 0.65f : 1.0f);
            out.rightX += ramp;
        }

        if (lookUp && !lookDown)
        {
            if (!(s_lastButtons & PSP_CTRL_TRIANGLE)) s_holdStartTickY = nowMs;
            uint32_t duration = nowMs - s_holdStartTickY;
            float ramp = duration < 120 ? 0.35f : (duration < 250 ? 0.65f : 1.0f);
            out.rightY += ramp;
        }
        else if (lookDown && !lookUp)
        {
            if (!(s_lastButtons & PSP_CTRL_CROSS)) s_holdStartTickY = nowMs;
            uint32_t duration = nowMs - s_holdStartTickY;
            float ramp = duration < 120 ? 0.35f : (duration < 250 ? 0.65f : 1.0f);
            out.rightY -= ramp;
        }

        s_lastButtons = pad.held;
    }

    return out;
}

PlatformGamepadSnapshot platformRawGamepadSnapshot(int port)
{
    return platformGamepadSnapshot(port);
}

int platformMenuPad()
{
    return 0;
}

bool platformMenuPointerActive()
{
    return true;
}

bool platformMenuCursorVisible()
{
    return true;
}

void platformSetMenuCursor(int x, int y)
{
    PspPadState::setCursorPosition(x, y);
}

const PlatformKeyboardHints& platformKeyboardHints()
{
    static const PlatformKeyboardHints hints = {
        { "X:select O:back D-pad:nav",
          "Triangle:shift Square:del",
          "Select:space Start:enter" },
        3
    };
    return hints;
}
#endif
