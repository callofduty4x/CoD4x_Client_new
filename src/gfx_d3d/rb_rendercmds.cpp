#include "r_local.h"

void R_ShutdownDynamicMesh(GfxMeshData *mesh)
{
  R_FreeGlobalVariable(mesh->indices);
  mesh->indices = 0;
  if ( mesh->vb.buffer )
  {
    D3DRELEASEBUFFER(mesh->vb.buffer);
  }
}