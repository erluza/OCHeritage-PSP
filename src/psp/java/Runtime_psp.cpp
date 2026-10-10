#include "java/Runtime.h"
#include <pspkernel.h>
#include <pspsysmem.h>
#include <malloc.h>

Runtime Runtime::instance;

Runtime &Runtime::getRuntime()
{
    return instance;
}

long_t Runtime::maxMemory()
{
    // PSP Slim/Brite/Go/Street with MEMSIZE 1 provides up to 64MB RAM.
    return 64LL * 1024LL * 1024LL;
}

long_t Runtime::totalMemory()
{
    struct mallinfo mi = mallinfo();
    return static_cast<long_t>(mi.arena);
}

long_t Runtime::freeMemory()
{
    struct mallinfo mi = mallinfo();
    long_t libcFree = static_cast<long_t>(mi.fordblks);
    SceSize kernelFree = sceKernelTotalFreeMemSize();
    return libcFree + static_cast<long_t>(kernelFree);
}
