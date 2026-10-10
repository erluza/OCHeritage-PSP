#ifdef PSP_PLATFORM

#include <SDL.h>
#include "platform/Log.h"
#include "client/Minecraft.h"
#include "psp/system/PspBootstrap.h"

int main(int argc, char* argv[])
{
    McLog::openSessionFile("ms0:/PSP/GAME/OptiCraft");
    MC_LOG_INFO("game", "[PSP] main() start\n");

    PspBootstrap::init();

    MC_LOG_INFO("game", "[PSP] Minecraft::start()\n");

    try
    {
        jstring username = "PspPlayer";
        jstring auth = "-";
        Minecraft::start(&username, &auth);
    }
    catch (const std::exception &e)
    {
        MC_LOG_ERROR("game", "[PSP] Uncaught exception: %s\n", e.what());
    }
    catch (...)
    {
        MC_LOG_ERROR("game", "[PSP] Uncaught unknown exception\n");
    }

    MC_LOG_INFO("game", "[PSP] Minecraft::start returned, shutting down\n");
    PspBootstrap::shutdown();
    return 0;
}

#endif // PSP_PLATFORM
