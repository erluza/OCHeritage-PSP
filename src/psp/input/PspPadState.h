#pragma once

#ifdef PSP_PLATFORM

#include <cstdint>

struct PspPadSnapshot
{
    bool connected = false;
    float leftX = 0.0f;
    float leftY = 0.0f;
    std::uint32_t held = 0;
    std::uint32_t pressed = 0;
    std::uint32_t released = 0;
};

namespace PspPadState
{
    void init();
    void update();
    const PspPadSnapshot& getSnapshot();
    std::uint32_t consumePressed();
    void clearLatches();

    // Cursor position in menu
    int getCursorX();
    int getCursorY();
    void setCursorPosition(int x, int y);
}

#endif // PSP_PLATFORM
