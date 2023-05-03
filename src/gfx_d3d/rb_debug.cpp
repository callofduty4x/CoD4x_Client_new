#include "rb_backend.h"
#include "rb_debug.h"
#include "r_local.h"
#include "r_utils.h"

void RB_SetPolyVert(const float *xyz, GfxColor color, int tessVertIndex)
{
  VectorCopy(xyz, tess.verts[tessVertIndex].xyzw);
  tess.verts[tessVertIndex].xyzw[3] = 1.0;
  tess.verts[tessVertIndex].normal.packed = 0x3FFE7F7F;
  tess.verts[tessVertIndex].color = color;
  tess.verts[tessVertIndex].texCoord[0] = 1.0;
  tess.verts[tessVertIndex].texCoord[1] = 1.0;
}

bool s_lastDepthTest;
bool s_addingDebugLines;

int RB_EndDebugLines(int vertCount, GfxPointVertex *verts)
{
  if ( vertCount )
  {
    RB_DrawLines3D(vertCount, 1, verts, s_lastDepthTest);
    s_addingDebugLines = false;
  }
  return 0;
}

int RB_AddDebugLine(const float *start, const float *end, const float *color, bool depthTest, int vertCount, int vertLimit, GfxPointVertex *verts)
{
  if ( vertCount + 2 > vertLimit || (s_addingDebugLines && s_lastDepthTest != depthTest ))
  {
    RB_DrawLines3D(vertCount / 2, 1, verts, s_lastDepthTest);
    vertCount = 0;
  }
  s_lastDepthTest = depthTest;
  s_addingDebugLines = true;

  R_ConvertColorToBytes(color, (unsigned char*)verts[vertCount].color);

  *(uint32_t*)verts[vertCount + 1].color = *(uint32_t*)verts[vertCount].color;

  VectorCopy(start, verts[vertCount].xyz);
  VectorCopy(end, verts[vertCount + 1].xyz);

  return vertCount + 2;
}

