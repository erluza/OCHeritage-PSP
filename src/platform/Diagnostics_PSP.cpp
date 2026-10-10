#include "platform/Diagnostics.h"

#ifdef PSP_PLATFORM

const char* platformOomDiagnosticLine(int index)
{
    (void)index;
    return "";
}

void platformMemoryCheckpoint(const char* tag)
{
    (void)tag;
}

void platformHardwareCheckpoint(const char* tag)
{
    (void)tag;
}

long platformHeapFreeKb()
{
    return -1;
}

void platformCaptureBadAlloc()
{
}

#endif // PSP_PLATFORM
