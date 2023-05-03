#include "r_types_d3d.h"
#include "../common/cvar.h"

extern dvar_s* r_showCollision;
extern dvar_s* r_showCollisionGroups;
extern dvar_s* r_showCollisionPolyType;
extern dvar_s* r_showCollisionDepthTest;
extern dvar_s* r_showCollisionDist;

struct GfxPointVertex
{
  float xyz[3];
  char color[4];
};

void RB_SetPolyVert(const float *xyz, GfxColor color, int tessVertIndex);
int RB_AddDebugLine(const float *start, const float *end, const float *color, bool depthTest, int vertCount, int vertLimit, GfxPointVertex *verts);
int RB_EndDebugLines(int vertCount, GfxPointVertex *verts);
void RB_DrawLines3D(int count, int width, const GfxPointVertex *verts, unsigned char depthTest);
