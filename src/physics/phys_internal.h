#include "ode/src/collision_kernel.h"
#include "phys_alloc.h"
#include "ode/src/joint.h"
#include "pool_allocator.h"
#include "ode/include/ode/iw_definitions.h"


struct PhysTriMeshInfo
{
  float *verts;
  int vertStride;
  int vertCount;
  unsigned int *indices;
  unsigned int indexCount;
};

enum physStuckState_t : int
{
  PHYS_OBJ_STATE_POSSIBLY_STUCK = 0x0,
  PHYS_OBJ_STATE_STUCK = 0x1,
  PHYS_OBJ_STATE_FREE = 0x2,
};


struct __align(4) PhysObjUserData
{
  float translation[3];
  dxBody *body;
  float savedPos[3];
  float savedRot[3][3];
  int sndClass;
  float friction;
  float bounce;
  physStuckState_t state;
  float contactCentroid[3];
};

struct Jitter
{
  float origin[3];
  float innerRadiusSq;
  float outerRadiusSq;
  float innerRadius;
  float outerRadius;
  float minDisplacement;
  float maxDisplacement;
};

struct PhysWorldData
{
  int timeLastSnapshot;
  int timeLastUpdate;
  float timeNowLerpFrac;
  void (__cdecl *collisionCallback)();
  int numJitterRegions;
  bool useContactCentroids;
  Jitter jitterRegions[5];
};


struct PhysGlob
{
  dxWorld *world[3];
  PhysWorldData worldData[3];
  dxSpace *space[3];
  dxJointGroup *contactgroup[3];
  PhysObjUserData userData[512];
  pooldata_t userDataPool;
  PhysTriMeshInfo triMeshInfo;
  struct dxTriMeshData *triMeshDataID;
  bool dumpContacts;
  dxGeom *visTrisGeom;
  dxGeom *worldGeom;
  int debugActiveObjCount;
  PhysStaticArray<dxJointHinge,192> hingeArray;
  PhysStaticArray<dxJointBall,160> ballArray;
  PhysStaticArray<dxJointAMotor,160> aMotorArray;
  float gravityDirection[3];
};


extern PhysGlob physGlob;

void Phys_SetAngularMotorParams(PhysWorld worldIndex, int id, const float *motorSpeeds, const float *motorFMaxs, const float *lowStops, const float *highStops);
void Phys_SetHingeParams(PhysWorld worldIndex, int id, float motorSpeed, float motorMaxForce, float lowStop, float highStop);
