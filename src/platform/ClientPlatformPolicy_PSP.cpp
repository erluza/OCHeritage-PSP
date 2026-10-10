#include "platform/ClientPlatformPolicy.h"

#ifdef PSP_PLATFORM

#include "net/minecraft/src/GameSettings.h"
#include "net/minecraft/src/RenderEngine.h"
#include "platform/Log.h"

namespace ClientPlatformPolicy
{
int initialWidth()
{
    return 480;
}

int initialHeight()
{
    return 272;
}

std::string minecraftDirectory()
{
    return "ms0:/PSP/GAME/OptiCraft";
}

bool saveConverterUsesSavesSubdirectory()
{
    return false;
}

void applyGameSettingsDefaults(GameSettings* settings)
{
    if (settings == nullptr)
        return;

    // Optimized PSP defaults: Fast graphics, Tiny render distance for 333MHz single core
    settings->renderDistance = 3; // Tiny (minimal chunk radius)
    settings->fancyGraphics = false;
    settings->ambientOcclusion = false;
    settings->ofAnimatedWater = 2;
    settings->ofAnimatedLava = 2;
    settings->ofAnimatedFire = false;
    settings->ofAnimatedPortal = false;
    settings->ofAnimatedRedstone = false;
    settings->ofAnimatedExplosion = false;
    settings->ofAnimatedFlame = false;
    settings->ofAnimatedSmoke = false;
    settings->advancedOpengl = false;
    settings->ofOcclusionFancy = false;
}

void preloadStartupTextures(RenderEngine* renderEngine)
{
    (void)renderEngine;
}

void releaseWorldEntryAssets(RenderEngine* renderEngine)
{
    (void)renderEngine;
}

int panoramaSampleGrid()
{
    return 8;
}

void reportCrash(const std::string& description)
{
    MC_LOG_ERROR("crash", "[PSP Crash] %s\n", description.c_str());
}

} // namespace ClientPlatformPolicy

#endif // PSP_PLATFORM
