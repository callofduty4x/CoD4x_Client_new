#include "r_local.h"
#include "rb_backend.h"
#include "../common/sys_thread.h"

#pragma msg "Needs to be implemented to multi threading"

void R_EndRemoteScreenUpdate(void (*pumpfunc)())
{
  --r_glob.remoteScreenUpdateNesting;
}

void R_BeginRemoteScreenUpdate()
{
  ++r_glob.remoteScreenUpdateNesting;
}


void R_ShutdownRenderCommands()
{
  R_ShutdownModelLightingGlobals();
  R_FreeGlobalVariable(s_backEndData.commands->cmds);
  R_ShutdownDebugEntry(&s_backEndData.debugGlobals);
  R_ShutdownSceneBuffers();
}

void R_ShutdownSpotShadowMeshes()
{
  unsigned int sunShadowIndex;
  unsigned int spotShadowIndex;

  for ( spotShadowIndex = 0; spotShadowIndex < ARRAY_COUNT(gfxMeshGlob.spotShadowClearMeshData); ++spotShadowIndex )
  {
    R_ShutdownDynamicMesh(&gfxMeshGlob.spotShadowClearMeshData[spotShadowIndex]);
  }
  for ( sunShadowIndex = 0; sunShadowIndex < ARRAY_COUNT(gfxMeshGlob.sunShadowClearMeshData); ++sunShadowIndex )
  {
    R_ShutdownDynamicMesh(&gfxMeshGlob.sunShadowClearMeshData[sunShadowIndex]);
  }
}

void R_ShutdownRenderBuffers()
{
  unsigned int viewIndex;
  unsigned int partitionIndex;


  s_backEndData.endFence = 0;
  s_backEndData.preTessIb = 0;
  R_ShutdownDynamicMesh(&s_backEndData.codeMesh);
  R_ShutdownDynamicMesh(&s_backEndData.markMesh);

  for ( viewIndex = 0; viewIndex < ARRAY_COUNT(g_viewInfo); ++viewIndex )
  {
    for ( partitionIndex = 0; partitionIndex < ARRAY_COUNT(g_viewInfo[viewIndex].pointLightMeshData); ++partitionIndex )
    {
      R_ShutdownDynamicMesh(&g_viewInfo[viewIndex].pointLightMeshData[partitionIndex]);
    }
  }
  r_dx.swapFence = 0;
  for ( viewIndex = 0; viewIndex < ARRAY_COUNT(gfxMeshGlob.fullSceneViewMesh); ++viewIndex )
  {
    R_ShutdownDynamicMesh(&gfxMeshGlob.fullSceneViewMesh[viewIndex].meshData);
  }

  R_ShutdownSpotShadowMeshes();
  R_ShutdownDynamicIndices(&gfxBuf.smodelCache);
}

int R_PopRemoteScreenUpdate()
{
  int remoteScreenUpdateNesting;

  assert(Sys_IsMainThread());

  remoteScreenUpdateNesting = r_glob.remoteScreenUpdateNesting;
  while ( r_glob.remoteScreenUpdateNesting )
  {
    R_EndRemoteScreenUpdate(NULL);
  }
  assert(remoteScreenUpdateNesting >= 0);
  return remoteScreenUpdateNesting;
}

void R_PushRemoteScreenUpdate(int remoteScreenUpdateNesting)
{
  assert(Sys_IsMainThread());

  while ( remoteScreenUpdateNesting )
  {
    R_BeginRemoteScreenUpdate();
    --remoteScreenUpdateNesting;
  }
}