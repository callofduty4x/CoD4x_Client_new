#include <string.h>
#include <bgame/bg_shared.h>
#include "cg_local.h"
#include <common/com_dobj_shared.h>
#include <xanim/xanim_shared.h>
#include <client/client_cgame.h>

#define ASSET_TYPE_WEAPON_COUNT 128


void CG_FreeWeapons(int localClientNum)
{
    weaponInfo_s *weapon;

    for(unsigned int i = 1; i < BG_GetNumWeapons(); ++i)
    {
        weapon = &cg_weaponsArray[localClientNum][i];
        Com_SafeClientDObjFree( CG_WeaponDObjHandle (i), localClientNum);
        if ( weapon->tree )
        {
            XAnimFreeTree(weapon->tree, 0);
            weapon->tree = 0;
        }       

    }
    memset(cg_weaponsArray[localClientNum], 0, sizeof(cg_weaponsArray[0]));

}


void CG_RegisterItems(int localClientNum)
{
  int i;
  signed int item;
  int k;
  char items[1024];

  Q_strncpyz(items,  CL_GetConfigString(localClientNum, 2314), sizeof(items));

  for(i = 1; i < ASSET_TYPE_WEAPON_COUNT; ++i)
  {
    item = items[i / 4];

    if ( item > '9' )
    {
        k = item - 'W';
    }else{
        k = item - '0';
    }

    if ( (1 << (i & 3)) & k )
    {
		CG_RegisterWeapon(localClientNum, i);
    }
  }

}

