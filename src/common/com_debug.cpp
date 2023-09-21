#include "com_debug.h"
#include <q_math.h>

ComDebugConsole *dbgCon = nullptr;

ComDebugConsole& Com_CreateDebugConsole()
{
    HINSTANCE h = GetModuleHandle(NULL);

    static ComDebugConsole dbgcon(h, "Com Debug Console", 800, 600);
    dbgcon.Show(1, true);
    return dbgcon;
}



void Com_InitDebugSystems()
{
   dbgCon = &Com_CreateDebugConsole();

}

