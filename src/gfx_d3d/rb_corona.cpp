#include "r_local.h"
#include "../common/qcommon.h"

unsigned int RB_HW_ReadOcclusionQuery(D3DQuery *query)
{
  HRESULT hr;
  unsigned int pixelCount;

  while ( 1 )
  {
    hr = D3DCALLNOLOCKNOERROR(query->GetData(&pixelCount, 4, 1));
    if ( hr != 1 )
    {
      break;
    }
    Sys_Sleep(0);
  }
  if ( hr >= 0 )
  {
    return pixelCount;
  }
  return -1;
}

void RB_HW_BeginOcclusionQuery(D3DQuery *query, D3DDevice* device)
{
    assert(query);
    D3DCALLNOLOCKNOERROR(query->Issue( 2 ));
}