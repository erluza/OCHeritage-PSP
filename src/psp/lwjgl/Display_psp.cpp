#include "lwjgl/Display.h"
#include "lwjgl/Mouse.h"
#include "lwjgl/Keyboard.h"

#ifdef PSP_PLATFORM

#include <SDL.h>
#include "psp/system/PspBootstrap.h"
#include "psp/input/PspPadState.h"
#include "client/Minecraft.h"
#include "net/minecraft/src/GuiScreen.h"

namespace
{
    SDL_Window* s_window = nullptr;
    SDL_GLContext s_glContext = nullptr;
    bool s_created = false;
}

namespace lwjgl
{
namespace Display
{

void setDisplayMode(const DisplayMode &) {}

DisplayMode getDisplayMode()
{
    return DisplayMode(480, 272);
}

void setTitle(const jstring &) {}
void setFullscreen(bool) {}

bool isCloseRequested()
{
    return !PspBootstrap::isRunning();
}

bool isVisible() { return true; }
bool isActive()  { return true; }

void create()
{
    if (s_created) return;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);
    s_window = SDL_CreateWindow("OptiCraft Heritage", 0, 0, 480, 272, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (s_window)
    {
        s_glContext = SDL_GL_CreateContext(s_window);
        if (s_glContext)
            SDL_GL_MakeCurrent(s_window, s_glContext);
    }

    PspPadState::init();
    s_created = true;
}

void swapBuffers()
{
    if (s_window)
        SDL_GL_SwapWindow(s_window);
}

void processMessages()
{
    PspPadState::update();

    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
            PspBootstrap::shutdown();
    }
}

void update(bool doProcessMessages)
{
    swapBuffers();
    if (doProcessMessages)
        processMessages();
}

int_t getX() { return 0; }
int_t getY() { return 0; }
int_t getWidth()  { return 480; }
int_t getHeight() { return 272; }

} // namespace Display
} // namespace lwjgl

#endif // PSP_PLATFORM
