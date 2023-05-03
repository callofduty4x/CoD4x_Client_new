#ifndef COLLISION_SPACE_H__
#define COLLISION_SPACE_H__

#include "collision_kernel.h"

//****************************************************************************
// simple space - reports all n^2 object intersections

struct dxSimpleSpace : public dxSpace {
  dxSimpleSpace (dSpaceID _space);
  dxSimpleSpace ( );
  void cleanGeoms();
  void collide (void *data, dNearCallback *callback);
  void collide2 (void *data, dxGeom *geom, dNearCallback *callback);
};

#endif