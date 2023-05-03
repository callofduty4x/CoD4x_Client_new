#include "r_local.h"

void R_ShutdownStaticModelCache()
{
  R_FlushStaticModelCache();
  if ( gfxBuf.smodelCacheVb )
  {
    D3DRELEASEBUFFER(gfxBuf.smodelCacheVb);
  }
}