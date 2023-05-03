#include "../q_shared.h"
#include "r_types_d3d.h"



struct XSurfaceVertexInfo
{
  int16_t vertCount[4];
  uint16_t *vertsBlend;
};

struct XRigidVertList
{
  uint16_t boneOffset;
  uint16_t vertCount;
  uint16_t triOffset;
  uint16_t triCount;
  struct XSurfaceCollisionTree *collisionTree;
};


struct __align(4) XSurface
{
  uint8_t tileMode;
  uint16_t vertCount;
  uint16_t triCount;
  uint8_t XZoneHandle;
  uint16_t baseVertIndex;
  uint16_t *triIndices;
  XSurfaceVertexInfo vertInfo;
  GfxPackedVertex *verts0;
  int vertListCount;
  XRigidVertList *vertList;
  int partBits[4];
};



struct __align(2) GfxModelSurfaceInfo
{
  union
  {
    struct DObjAnimMat *baseMat;
    struct DObjAnimMat *baseMat_local;
  };
  char boneIndex;
  char boneCount;
  uint16_t gfxEntIndex;
  uint16_t lightingHandle;
  char dobjModelIndex;
};



struct GfxModelSkinnedSurface
{
  int skinnedCachedOffset;
  XSurface *xsurf;
  GfxModelSurfaceInfo info;
  union
  {
    GfxPackedVertex *skinnedVert;
    int oldSkinnedCachedOffset;
  };
};



int XSurfaceGetNumTris(const XSurface *surface);
int XSurfaceGetNumVerts(const XSurface *surface);
void R_UnlockSkinnedCache();