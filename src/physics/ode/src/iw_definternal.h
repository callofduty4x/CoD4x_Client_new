#ifndef __IW_DEFINTERNAL_H__
#define __IW_DEFINTERNAL_H__

#include <stdint.h>
#include "collision_space.h"
#include "collision_kernel.h"
#include "joint.h"
#include "../../pool_allocator.h"


struct __align(16) odeGlob_t
{
  dxWorld world[3];
  dxSimpleSpace space[3];
  dxJointGroup contactsGroup[3];
  dxBody bodies[512];
  pooldata_t bodyPool;
  uint8_t geoms[2048][208];
  pooldata_t geomPool;
  dxUserGeom worldGeom;
};

extern odeGlob_t odeGlob;

void Phys_GeomUserGetAAContainedBox(dxGeom *geom, float *mins, float *maxs);
void Phys_AxisToOdeMatrix3(const float *inAxis, float *outMatrix);
void Phys_NearCallback(void *userData, dxGeom *geom1, dxGeom *geom2);
#endif
