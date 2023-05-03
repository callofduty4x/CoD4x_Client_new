#include <q_shared.h>
#include <game/game.h>
#include <common/qcommon.h>
#include <xanim/dobj_shared.h>

void G_SafeServerDObjFree(int handle, int unusedLocalClientNum)
{
    assert(unusedLocalClientNum == UNUSED_LOCAL_CLIENT_NUM);
    Com_SafeServerDObjFree(handle);
}