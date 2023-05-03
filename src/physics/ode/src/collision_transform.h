/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

/*

geom transform

*/

#ifndef _ODE_COLLISION_TRANSFORM_H_
#define _ODE_COLLISION_TRANSFORM_H_

#include <ode/common.h>
#include "collision_kernel.h"

//****************************************************************************
// dxGeomTransform class

struct dxGeomTransform : public dxGeom {
  dxGeom *obj;		// object that is being transformed
  int cleanup;		// 1 to destroy obj when destroyed
  int infomode;		// 1 to put Tx geom in dContactGeom g1

  // cached final object transform (body tx + relative tx). this is set by
  // computeAABB(), and it is valid while the AABB is valid.
  dMatrix3 localR;
  dReal    localPos[3];
  dMatrix3 finalR;
  dReal    finalPos[3];


  dxGeomTransform (dSpaceID space, dxBody* body);
  ~dxGeomTransform();
  void computeAABB();
  void computeFinalTx();
  void Destruct();
};


int dCollideTransform (dxGeom *o1, dxGeom *o2, int flags,
		       dContactGeom *contact, int skip);

void ODE_GeomTransformGetAAContainedBox(dxGeom *geom, float *mins, float *maxs);

#endif
