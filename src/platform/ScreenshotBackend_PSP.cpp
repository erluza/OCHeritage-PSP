#include "platform/ScreenshotBackend.h"

#ifdef PSP_PLATFORM

namespace ScreenshotBackend
{
std::string save(const std::string&, int_t, int_t)
{
    return "Screenshots are not supported on PSP";
}
}

#endif // PSP_PLATFORM
