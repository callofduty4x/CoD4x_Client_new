#include "r_local.h"
#include "rb_debug.h"
#include "rb_backend.h"
#include "../common/cm_public.h"
#include "r_utils.h"

static int showCollisionContentMasks[10] = { 0, 210624, 65536, 8192, 128, 512, 131072, 1024, 64, 4096 };
static const float frustumSidePlanes[5][4] =
{
  { -1.0,  0.0,  0.0,  1.0 },
  {  1.0,  0.0,  0.0,  1.0 },
  {  0.0, -1.0,  0.0,  1.0 },
  {  0.0,  1.0,  0.0,  1.0 },
  {  0.0,  0.0,  1.0,  1.0 }
};





void RB_DrawCollisionPoly(int numPoints, float points[][3], const float *colorFloat)
{
  GfxPointVertex debugLineVerts[2725];
  int vertCount;
  int vertIndex;
  int vertIndexPrev;
  GfxColor color;

    assert(numPoints >= 3);
    assert(points);

  if ( r_showCollisionPolyType->current.integer == 2 || !r_showCollisionPolyType->current.integer )
  {
    R_ConvertColorToBytes(colorFloat, (unsigned char *)&color);
    RB_BeginSurface(rgp.whiteMaterial, TECHNIQUE_UNLIT);
//    R_TrackPrims(&gfxCmdBufState.prim, GFX_PRIM_STATS_DEBUG);
    RB_CheckTessOverflow(numPoints, 3 * (numPoints - 2));
    for ( vertIndex = 0; vertIndex < numPoints; ++vertIndex )
    {
      RB_SetPolyVert(points[vertIndex], color, vertIndex + tess.vertexCount);
    }
    for ( vertIndex = 2; vertIndex < numPoints; ++vertIndex )
    {
      tess.indices[tess.indexCount] = tess.vertexCount;
      tess.indices[tess.indexCount + 1] = vertIndex + tess.vertexCount;
      tess.indices[tess.indexCount + 2] = tess.vertexCount + vertIndex - 1;
      tess.indexCount += 3;
    }
    tess.vertexCount += numPoints;
    RB_EndTessSurface();
  }
  if ( r_showCollisionPolyType->current.integer == 1 || !r_showCollisionPolyType->current.integer )
  {
    vertCount = 0;
    vertIndexPrev = numPoints - 1;
    for ( vertIndex = 0; vertIndex < numPoints; ++vertIndex )
    {
      vertCount = RB_AddDebugLine(points[vertIndexPrev], points[vertIndex], colorFloat, r_showCollisionDepthTest->current.enabled, vertCount, 2725, debugLineVerts);
      vertIndexPrev = vertIndex;
    }
    RB_EndDebugLines(vertCount / 2, debugLineVerts);
  }
}

void BuildFrustumPlanes(GfxViewParms *viewParms, cplane_s *frustumPlanes)
{
  cplane_s *plane;
  DpvsPlane *dvpsPlane;
  int i;
  DpvsPlane dpvsFrustumPlanes[5];
  unsigned int planeIndex;

    assert(viewParms);
    assert(frustumPlanes);

  R_FrustumClipPlanes(&viewParms->viewProjectionMatrix, frustumSidePlanes, 5, dpvsFrustumPlanes);
  for ( planeIndex = 0; planeIndex < 5; ++planeIndex )
  {
    plane = &frustumPlanes[planeIndex];
    dvpsPlane = &dpvsFrustumPlanes[planeIndex];

    VectorCopy(dvpsPlane->coeffs, plane->normal);
    plane->dist = dvpsPlane->coeffs[3];
    
    assert(plane->normal[3] == plane->dist);

    plane->dist = plane->dist * -1.0;

    for(i = 0; i < 3; ++i)
    {
        if ( frustumPlanes[planeIndex].normal[i] == 1.0 )
        {
            break;
        } 
    }
    frustumPlanes[planeIndex].type = i;
    SetPlaneSignbits(&frustumPlanes[planeIndex]);
  }
}

void RB_ShowCollision(GfxViewParms *viewParms)
{
    int contentMask;
    cplane_s frustumPlanes[6];
    int i;

    assert(viewParms);

    if ( !r_showCollision->current.integer )
    {
        return;
    }
    if((unsigned)(r_showCollision->current.integer) >= ARRAY_COUNT(showCollisionContentMasks))
    {
        return;
    }
    contentMask = showCollisionContentMasks[r_showCollision->current.integer];
    BuildFrustumPlanes(viewParms, frustumPlanes);
    frustumPlanes[5].normal[0] = -1.0 * frustumPlanes[4].normal[0];
    frustumPlanes[5].normal[1] = -1.0 * frustumPlanes[4].normal[1];
    frustumPlanes[5].normal[2] = -1.0 * frustumPlanes[4].normal[2];
    frustumPlanes[5].dist = -frustumPlanes[4].dist - r_showCollisionDist->current.value;
    
    for(i = 0; i < 3; ++i)
    {
        if ( frustumPlanes[5].normal[i] == 1.0 )
        {
            break;
        } 
    }
    frustumPlanes[5].type = i;
    SetPlaneSignbits(&frustumPlanes[5]);

    if ( r_showCollisionGroups->current.integer == 1 || !r_showCollisionGroups->current.integer )
    {
      CM_ShowBrushCollision(contentMask, frustumPlanes, 6, RB_DrawCollisionPoly);
    }
    if ( tess.indexCount )
    {
      RB_EndTessSurface();
    }
}
