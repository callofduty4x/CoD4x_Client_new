#include "g_misc_mp.h"

#define MAX_TURRETS 32

extern turretInfo_s turretInfo[MAX_TURRETS];


void G_InitTurrets()
{
  int i;

  for(i = 0; i < MAX_TURRETS; ++i){
    turretInfo[i].inuse = 0;
  }
}
