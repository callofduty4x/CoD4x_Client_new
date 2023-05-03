#include "cm_local.h"

struct __align(4) ShowCollisionBrushPt
{
  float xyz[3];
  int16_t sideIndex[3];
};

#define MAX_INTERSECTIONPOINTS 1024

//a winding gives the bounding points of a convex polygon
typedef struct
{
	int numpoints;
	vec3_t p[4];            //variable sized
} winding_t;

struct windingPool_t
{
    winding_t w;
    char pool[12292];
};

static windingPool_t windingPool;

void CM_GetShowCollisionColor(float *colorFloat, int colorCounter)
{
  assert(colorFloat);

  if ( colorCounter & 1 )
  {
    colorFloat[0] = 1.0;
  }
  else
  {
    colorFloat[0] = 0.0;
  }
  if ( colorCounter & 2 )
  {
    colorFloat[1] = 1.0;
  }
  else
  {
    colorFloat[1] = 0.0;
  }
  if ( colorCounter & 4 )
  {
    colorFloat[2] = 1.0;
  }
  else
  {
    colorFloat[2] = 0.0;
  }
  colorFloat[3] = 0.5;
}

bool CM_BrushInView(cbrush_t *brush, cplane_s *frustumPlanes, int frustumPlaneCount)
{
  int frustumPlaneIndex;

  assert(frustumPlanes);

  for ( frustumPlaneIndex = 0; frustumPlaneIndex < frustumPlaneCount; ++frustumPlaneIndex )
  {
    if ( !(BoxOnPlaneSide(brush->mins, brush->maxs, &frustumPlanes[frustumPlaneIndex]) & 1) )
    {
      return false;
    }
  }
  return true;
}

void CM_BuildAxialPlanes(cbrush_t *brush, float axialPlanes[][4])
{
  axialPlanes[0][0] = -1.0;
  axialPlanes[0][1] = 0.0;
  axialPlanes[0][2] = 0.0;
  axialPlanes[0][3] = -brush->mins[0];

  axialPlanes[1][0] = 1.0;
  axialPlanes[1][1] = 0.0;
  axialPlanes[1][2] = 0.0;
  axialPlanes[1][3] = brush->maxs[0];

  axialPlanes[2][0] = 0.0;
  axialPlanes[2][1] = -1.0;
  axialPlanes[2][2] = 0.0;
  axialPlanes[2][3] = -brush->mins[1];

  axialPlanes[3][0] = 0.0;
  axialPlanes[3][1] = 1.0;
  axialPlanes[3][2] = 0.0;
  axialPlanes[3][3] = brush->maxs[1];

  axialPlanes[4][0] = 0.0;
  axialPlanes[4][1] = 0.0;
  axialPlanes[4][2] = -1.0;
  axialPlanes[4][3] = -brush->mins[2];

  axialPlanes[5][0] = 0.0;
  axialPlanes[5][1] = 0.0;
  axialPlanes[5][2] = 1.0;
  axialPlanes[5][3] = brush->maxs[2];
}

void CM_GetPlaneVec4Form(cbrushside_t *sides, const float axialPlanes[][4], int index, float *expandedPlane)
{

  if ( index >= 6 )
  {
    assert(sides);

    VectorCopy(sides[index - 6].plane->normal, expandedPlane);
    expandedPlane[3] = sides[index - 6].plane->dist;
  }
  else
  {
    assert(axialPlanes);
    Vector4Copy(axialPlanes[index], expandedPlane);
  }
}


int CM_AddSimpleBrushPoint(cbrush_t *brush, const float axialPlanes[][4], const int16_t *sideIndices, const float *xyz, int ptCount, ShowCollisionBrushPt *brushPts)
{
  cplane_s *plane;
  unsigned int sideIndex;

  assert(brush);
  assert(brushPts);

  for ( sideIndex = 0; sideIndex < 6; ++sideIndex )
  {
        
    if ( DotProduct(axialPlanes[sideIndex], xyz) - axialPlanes[sideIndex][3] > 0.1 )
    {
      return ptCount;
    }
  }
  for ( sideIndex = 0; sideIndex < brush->numsides; ++sideIndex )
  {
    plane = brush->sides[sideIndex].plane;
    if ( plane != brush->sides[sideIndices[0] - 6].plane && plane != brush->sides[sideIndices[1] - 6].plane  && plane != brush->sides[sideIndices[2] - 6].plane)
    {      
        if( DotProduct(plane->normal, xyz) - plane->dist > 0.1 )
        {
            return ptCount;
        }
    }
  }
  if ( ptCount >= MAX_INTERSECTIONPOINTS )
  {
    Com_Error(ERR_DROP, "More than %i points from plane intersections on %i-sided brush\n", ptCount, brush->numsides);
  }
  VectorCopy(xyz, brushPts[ptCount].xyz);

  brushPts[ptCount].sideIndex[0] = sideIndices[0];
  brushPts[ptCount].sideIndex[1] = sideIndices[1];
  brushPts[ptCount].sideIndex[2] = sideIndices[2];
  return ptCount + 1;
}


int CM_ForEachBrushPlaneIntersection(cbrush_t *brush, const float axialPlanes[][4], ShowCollisionBrushPt *brushPts)
{
  const float *plane[3];
  int sideCount;
  int ptCount;
  float xyz[3];
  float expandedPlane[3][4];
  int16_t sideIndex[3];
  cbrushside_t *sides;

  assert(brush);
  assert(brushPts);

  ptCount = 0;
  plane[0] = expandedPlane[0];
  plane[1] = expandedPlane[1];
  plane[2] = expandedPlane[2];
  sideCount = brush->numsides + 6;
  sides = brush->sides;
  for ( sideIndex[0] = 0; sideIndex[0] < sideCount - 2; ++sideIndex[0] )
  {
    CM_GetPlaneVec4Form(sides, axialPlanes, sideIndex[0], expandedPlane[0]);
    for ( sideIndex[1] = sideIndex[0] + 1; sideIndex[1] < sideCount - 1; ++sideIndex[1] )
    {
      if ( sideIndex[0] < 6 || sideIndex[1] < 6 || sides[sideIndex[0] - 6].plane != sides[sideIndex[1] - 6].plane )
      {
        CM_GetPlaneVec4Form(sides, axialPlanes, sideIndex[1], expandedPlane[1]);
        for ( sideIndex[2] = sideIndex[1] + 1; sideIndex[2] < sideCount; ++sideIndex[2] )
        {
          if ( (sideIndex[0] < 6 || sideIndex[2] < 6 || sides[sideIndex[0] - 6].plane != sides[sideIndex[2] - 6].plane)
            && (sideIndex[1] < 6 || sideIndex[2] < 6 || sides[sideIndex[1] - 6].plane != sides[sideIndex[2] - 6].plane) )
          {
            CM_GetPlaneVec4Form(sides, axialPlanes, sideIndex[2], expandedPlane[2]);
            if ( IntersectPlanes(plane, xyz) )
            {
              SnapPointToIntersectingPlanes(plane, xyz, 0.25, 0.01);
              ptCount = CM_AddSimpleBrushPoint(brush, axialPlanes, sideIndex, xyz, ptCount, brushPts);
            }
          }
        }
      }
    }
  }
  return ptCount;
}

int CM_PointInList(const float *point, const float xyzList[][3], int xyzCount)
{
  int xyzIndex;

  for ( xyzIndex = 0; xyzIndex < xyzCount; ++xyzIndex )
  {
    if ( VecNCompareCustomEpsilon(xyzList[xyzIndex], point, 0.1, 3) )
    {
      return 1;
    }
  }
  return 0;
}

int CM_GetXyzList(int sideIndex, ShowCollisionBrushPt *pts, int ptCount, float xyz[][3], int xyzLimit)
{
  int xyzCount;
  int ptIndex;

  assert(pts);
  assert(xyz);

  xyzCount = 0;
  for ( ptIndex = 0; ptIndex < ptCount; ++ptIndex )
  {
    if ( (sideIndex == pts[ptIndex].sideIndex[0] || sideIndex == pts[ptIndex].sideIndex[1] || sideIndex == pts[ptIndex].sideIndex[2]) && !CM_PointInList(pts[ptIndex].xyz, xyz, xyzCount) )
    {
      if ( xyzCount == xyzLimit )
      {
        Com_Error(ERR_DROP, "Winding point limit (%i) exceeded on brush face", xyzLimit);
      }
      VectorCopy(pts[ptIndex].xyz, xyz[xyzCount]);
      ++xyzCount;
    }
  }
  return xyzCount;
}

void CM_PickProjectionAxes(const float *normal, int *i, int *j)
{
  int k;

  k = 0;
  if ( fabsf(normal[1]) > fabsf(normal[0]) )
  {
    k = 1;
  }
  if ( fabsf(normal[2]) > fabsf(normal[k]) )
  {
    k = 2;
  }
  *i = ~(uint8_t)k & 1;
  *j = ~(uint8_t)k & 2;
}

void CM_AddColinearExteriorPointToWindingProjected(winding_t *w, const float *pt, int i, int j, int index0, int index1)
{
  float delta;
  int axis;

  assert(w->p[index0][i] != w->p[index1][i] || w->p[index0][j] != w->p[index1][j]);

  if ( fabsf(w->p[index1][i] - w->p[index0][i]) < fabsf(w->p[index1][j] - w->p[index0][j]) )
  {
    axis = j;
    delta = w->p[index1][j] - w->p[index0][j];
  }
  else
  {
    axis = i;
    delta = w->p[index1][i] - w->p[index0][i];
  }
  if ( delta <= 0.0 )
  {
    assert(w->p[index0][axis] > w->p[index1][axis]);

    if ( pt[axis] <= w->p[index0][axis] )
    {
      if ( w->p[index1][axis] > pt[axis] )
      {
        VectorCopy(pt, w->p[index1]);
      }
    }
    else
    {
      VectorCopy(pt, w->p[index0]);
    }
  }
  else
  {
    assert(w->p[index0][axis] < w->p[index1][axis]);

    if ( w->p[index0][axis] <= pt[axis] )
    {
      if ( pt[axis] > w->p[index1][axis] )
      {
        VectorCopy(pt, w->p[index1]);
      }
    }
    else
    {
      VectorCopy(pt, w->p[index0]);
    }
  }
}


double CM_SignedAreaForPointsProjected(const float *pt0, const float *pt1, const float *pt2, int i, int j)
{
  return (pt2[j] - pt1[j]) * pt0[i] + (pt0[j] - pt2[j]) * pt1[i] + (pt1[j] - pt0[j]) * pt2[i];
}

void CM_AddExteriorPointToWindingProjected(winding_t *w, const float *pt, int i, int j)
{
  int indexPrev;
  int bestIndex;
  int index;
  float signedArea;
  float bestSignedArea;

  bestIndex = -1;
  bestSignedArea = 3.4028235e38;
  indexPrev = w->numpoints - 1;
  for ( index = 0; index < w->numpoints; ++index )
  {
    signedArea = CM_SignedAreaForPointsProjected(w->p[indexPrev], pt, w->p[index], i, j);
    if ( bestSignedArea > signedArea )
    {
      bestSignedArea = signedArea;
      bestIndex = index;
    }
    indexPrev = index;
  }

  assert(bestIndex >= 0);

  if ( bestSignedArea < -EQUAL_EPSILON )
  {
    memmove((char *)w->p[bestIndex + 1], (char *)w->p[bestIndex], 12 * (w->numpoints - bestIndex));
    VectorCopy(pt, w->p[bestIndex]);
    ++w->numpoints;
  }
  else if ( bestSignedArea <= EQUAL_EPSILON )
  {
    CM_AddColinearExteriorPointToWindingProjected(w, pt, i, j, (bestIndex + w->numpoints - 1) % w->numpoints, bestIndex);
  }
}

double CM_RepresentativeTriangleFromWinding(winding_t *w, const float *normal, int *i0, int *i1, int *i2)
{
  signed int j;
  float areaBest;
  float vb[3];
  int k;
  float vc[3];
  float va[3];
  int i;

  *i0 = 0;
  *i1 = 1;
  *i2 = 2;
  areaBest = 0.0;
  for ( k = 2; k < w->numpoints; ++k )
  {
    for ( j = 1; j < k; ++j )
    {
      VectorSubtract(w->p[k], w->p[j], vb);
      for ( i = 0; i < j; ++i )
      {
        VectorSubtract(w->p[i], w->p[j], va);
        CrossProduct(va, vb, vc);

        float newAreaBest = fabsf(DotProduct(vc, normal));
        if ( newAreaBest > areaBest )
        {
          areaBest = newAreaBest;
          *i0 = i;
          *i1 = j;
          *i2 = k;
        }
      }
    }
  }
  return areaBest;
}

void CM_ReverseWinding(winding_t *w)
{
  vec3_t pt;
  int i;

  for ( i = 0; i < w->numpoints / 2; ++i )
  {
    VectorCopy(w->p[i], pt);
    VectorCopy(w->p[w->numpoints - 1 - i], w->p[i]);
    VectorCopy(pt, w->p[w->numpoints - 1 - i]);
  }
}

bool CM_BuildBrushWindingForSide(winding_t *winding, float *planeNormal, int sideIndex, ShowCollisionBrushPt *pts, int ptCount)
{
  int j;
  int i2;
  int xyzCount;
  vec3_t xyz[1024];
  int i0;
  int i1;
  int k;
  int i;
  vec3_t plane;

  assert(winding);
  assert(planeNormal);
  assert(pts);

  xyzCount = CM_GetXyzList(sideIndex, pts, ptCount, xyz, 1024);
  if ( xyzCount < 3 )
  {
    return false;
  }
  CM_PickProjectionAxes(planeNormal, &i, &j);

  VectorCopy(xyz[0], winding->p[0]);
  VectorCopy(xyz[1], winding->p[1]);

  winding->numpoints = 2;
  for ( k = 2; k < xyzCount; ++k )
  {
    CM_AddExteriorPointToWindingProjected(winding, xyz[k], i, j);
  }
  if ( CM_RepresentativeTriangleFromWinding(winding, planeNormal, &i0, &i1, &i2) < EQUAL_EPSILON )
  {
    return false;
  }
  PlaneFromPoints(plane, winding->p[i0], winding->p[i1], winding->p[i2]);
  if ( DotProduct(plane, planeNormal) > 0.0 )
  {
    CM_ReverseWinding(winding);
  }
  return true;
}


void CM_ShowSingleBrushCollision(cbrush_t *brush, const float *color, void (__cdecl *drawCollisionPoly)(int, float (*)[3], const float *))
{
  int ptCount;
  ShowCollisionBrushPt brushPts[MAX_INTERSECTIONPOINTS];
  unsigned int sideIndex;
  float axialPlanes[6][4];

  assert(brush);
  assert(color);

  CM_BuildAxialPlanes(brush, axialPlanes);
  ptCount = CM_ForEachBrushPlaneIntersection(brush, axialPlanes, brushPts);
  if ( ptCount >= 4 )
  {
    for ( sideIndex = 0; (unsigned int)sideIndex < 6; ++sideIndex )
    {
      if ( CM_BuildBrushWindingForSide(&windingPool.w, axialPlanes[sideIndex], sideIndex, brushPts, ptCount) )
      {
        drawCollisionPoly(windingPool.w.numpoints, windingPool.w.p, color);
      }
    }
    for ( sideIndex = 6; sideIndex < brush->numsides + 6; ++sideIndex )
    {
      if ( CM_BuildBrushWindingForSide(&windingPool.w, brush->sides[sideIndex - 6].plane->normal, sideIndex, brushPts, ptCount) )
      {
        drawCollisionPoly(windingPool.w.numpoints, windingPool.w.p, color);
      }
    }
  }
}


void CM_ShowBrushCollision(int contentMask, cplane_s *frustumPlanes, int frustumPlaneCount, void (*drawCollisionPoly)(int, float [][3], const float *))
{
  float colorFloat[4];
  int brushIndex;
  cbrush_t *brush;
  int colorCounter;

  assert(frustumPlanes);

  colorCounter = 0;
  for ( brushIndex = 0; brushIndex < cm.numBrushes; ++brushIndex )
  {
    brush = &cm.brushes[brushIndex];
    if ( contentMask & cm.brushes[brushIndex].contents )
    {
      CM_GetShowCollisionColor(colorFloat, colorCounter++);
      colorCounter %= 8;
      if ( CM_BrushInView(brush, frustumPlanes, frustumPlaneCount) )
      {
        CM_ShowSingleBrushCollision(brush, colorFloat, drawCollisionPoly);
      }
    }
  }
}

