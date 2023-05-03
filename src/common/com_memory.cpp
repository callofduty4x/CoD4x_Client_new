#include "../q_shared.h"
#include "sys_thread.h"

struct hunkUsed_t
{
  int permanent;
  int temp;
};
extern hunkUsed_t hunk_high;
extern hunkUsed_t hunk_low;
extern int s_hunkTotal;
extern char* s_hunkData;

extern "C" void HunkAvailMemDebug()
{
    Com_Printf(CON_CHANNEL_CLIENT, "Hunk available: %d, Hunk total: %d\n", (s_hunkTotal - hunk_high.temp + hunk_low.temp) / (1024*1024), s_hunkTotal / (1024*1024));
}

void Hunk_CheckTempMemoryHighClear()
{
  assert(Sys_IsMainThread() || Sys_IsRenderThread());
  assert(s_hunkData);
  assert(hunk_high.temp == hunk_high.permanent);
}
