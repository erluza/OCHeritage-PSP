#pragma once

#ifdef PSP_PLATFORM

namespace PspBootstrap
{
    void init();
    void shutdown();
    bool isRunning();
    void setCpuClock(int cpuMhz, int busMhz);
}

#endif // PSP_PLATFORM
