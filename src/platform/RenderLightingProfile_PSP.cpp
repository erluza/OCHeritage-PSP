#include "RenderLightingProfile.h"

#ifdef PSP_PLATFORM

RenderLightingProfile renderGetStandardItemLightingProfile()
{
    return {0.4f, 0.6f};
}

#endif // PSP_PLATFORM
