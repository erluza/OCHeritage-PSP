#include "platform/LegacyControlPromptBackend.h"

#ifdef PSP_PLATFORM

std::string legacyControlPromptLabel(const GameSettings &settings, LegacyControlAction action)
{
    (void)settings;
    switch (action)
    {
    case LegacyControlAction::Attack: return "R";
    case LegacyControlAction::Use: return "L";
    case LegacyControlAction::Jump: return "D-Pad";
    case LegacyControlAction::Inventory: return "Select";
    case LegacyControlAction::Drop: return "Triangle";
    }
    return std::string();
}

#endif // PSP_PLATFORM
