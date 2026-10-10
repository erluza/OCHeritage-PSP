#ifdef PSP_PLATFORM

#include "PspBootstrap.h"
#include <pspkernel.h>
#include <psppower.h>
#include <cstdio>

// Maximize newlib heap to all available RAM (64 MB on PSP-2000/3000/Go/Street)
PSP_HEAP_SIZE_KB(-1);

namespace
{
    static volatile bool s_running = true;
}

namespace PspBootstrap
{
    void init()
    {
        // Boost CPU and Bus clock to hardware maximum (333 MHz / 166 MHz)
        scePowerSetClockFrequency(333, 333, 166);
    }

    void shutdown()
    {
        s_running = false;
        sceKernelExitGame();
    }

    bool isRunning()
    {
        return s_running;
    }

    void setCpuClock(int cpuMhz, int busMhz)
    {
        scePowerSetClockFrequency(cpuMhz, cpuMhz, busMhz);
    }
}

#endif // PSP_PLATFORM
