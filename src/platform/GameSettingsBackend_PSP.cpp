#include "platform/GameSettingsBackend.h"

#ifdef PSP_PLATFORM

#include "net/minecraft/src/GameSettings.h"
#include <unordered_set>

void platformGameSettingsInitialize(GameSettings& settings)
{
    settings.renderDistance = 3; // Tiny by default on PSP
    settings.fancyGraphics = false;
    settings.ambientOcclusion = false;
}

void platformGameSettingsResetControlBindings(GameSettings&) {}
void platformGameSettingsApplyLegacyCrafting(GameSettings&) {}
int_t platformGameSettingsDefaultChunkUpdates() { return 1; }
int_t platformGameSettingsDefaultConnectedTextures() { return 0; }

int_t platformGameSettingsCycleRenderDistance(int_t current, int_t delta)
{
    return (current + delta) & 3;
}

int_t platformGameSettingsClampRenderDistance(int_t value)
{
    return value < 0 ? 0 : (value > 3 ? 3 : value);
}

int_t platformGameSettingsClampFineRenderDistance(int_t value)
{
    return value < 32 ? 32 : (value > 128 ? 128 : value);
}

void platformGameSettingsUpdateRenderDistanceFromFine(int_t fineDistance, int_t& renderDistance)
{
    renderDistance = 3;
    if (fineDistance > 32) renderDistance = 2;
    if (fineDistance > 64) renderDistance = 1;
    if (fineDistance > 128) renderDistance = 0;
}

bool platformGameSettingsAnaglyphValue(bool, bool) { return false; }
bool platformGameSettingsLoadOption(GameSettings&, const std::string&, const std::string&) { return false; }
void platformGameSettingsFinalizeLoad(GameSettings&) {}
void platformGameSettingsSyncControllerBindings(const GameSettings&) {}
void platformGameSettingsAddKnownKeys(std::unordered_set<std::string>&) {}
void platformGameSettingsWriteOptions(const GameSettings&, std::ostream&) {}

#endif // PSP_PLATFORM
