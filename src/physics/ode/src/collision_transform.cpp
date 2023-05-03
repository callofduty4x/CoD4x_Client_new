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

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include <new>
#include "collision_transform.h"
#include "collision_std.h"
#include "collision_util.h"
#include "../../../src/common/sys_thread.h"
#include "../../../src/physics/pool_allocator.h"
#include "iw_definternal.h"



#ifdef _MSC_VER
#pragma warning(disable:4291)  // for VC++, no complaints about "no matching operator delete found"
#endif

//****************************************************************************
// dxGeomTransform class



dxGeomTransform::dxGeomTransform (dSpaceID space, dxBody *body) : dxGeom (space,1, body)
{
  type = dGeomTransformClass;
  obj = 0;
  cleanup = 1;
  infomode = 0;
  dRSetIdentity (localR);
  dRSetIdentity (finalR);
  dSetZero (localPos,3);
  dSetZero (finalPos,3);
}


dxGeomTransform::~dxGeomTransform()
{
  if (obj && cleanup) ODE_GeomDestruct(obj);
}


void dxGeomTransform::computeAABB()
{
  if (!obj) {
    dSetZero (aabb,6);
    return;
  }

  // backup the relative pos and R pointers of the encapsulated geom object
  dReal *posbak = obj->pos;
  dReal *Rbak = obj->R;

  // compute temporary pos and R for the encapsulated geom object
  computeFinalTx();
  obj->pos = finalPos;
  obj->R = finalR;

  // compute the AABB
  obj->computeAABB();
  memcpy (aabb,obj->aabb,6*sizeof(dReal));

  // restore the pos and R
  obj->pos = posbak;
  obj->R = Rbak;
}


// utility function for dCollideTransform() : compute final pos and R
// for the encapsulated geom object

void dxGeomTransform::computeFinalTx()
{
  dMULTIPLY0_333(finalR, R, localR);
  dMULTIPLY0_331(finalPos, R, localPos);

  localPos[0] += pos[0];
  localPos[1] += pos[1];
  localPos[2] += pos[2];
}

void dxGeomTransform::Destruct()
{
  if(obj && cleanup)
  {
    ODE_GeomDestruct(obj);
  }
}
//#include <windows.h>
//****************************************************************************
// collider function:
// this collides a transformed geom with another geom. the other geom can
// also be a transformed geom, but this case is not handled specially.

int dCollideTransform (dxGeom *o1, dxGeom *o2, int flags,
		       dContactGeom *contact, int skip)
{
  //MessageBoxA(NULL, "dCollideTransform", "dCollideTransform", MB_OK);
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dGeomTransformClass);

  dxGeomTransform *tr = (dxGeomTransform*) o1;
  if (!tr->obj) return 0;
  
  dUASSERT (tr->obj->parent_space==0, "GeomTransform encapsulated object must not be in a space");

/*
  dUASSERT (tr->obj->body==0,
	    "GeomTransform encapsulated object must not be attached "
	    "to a body");
*/
  // backup the relative pos and R pointers of the encapsulated geom object,
  // and the body pointer
  dReal *posbak = tr->obj->pos;
  dReal *Rbak = tr->obj->R;
  dxBody *bodybak = tr->obj->body;

  // compute temporary pos and R for the encapsulated geom object.
  // note that final_pos and final_R are valid if no GEOM_AABB_BAD flag,
  // because computeFinalTx() will have already been called in
  // dxGeomTransform::computeAABB()

  if (tr->gflags & GEOM_AABB_BAD) tr->computeFinalTx();
  tr->obj->pos = tr->finalPos;
  tr->obj->R = tr->finalR;
  tr->obj->body = o1->body;

  // do the collision
  int n = dCollide (tr->obj,o2,flags,contact,skip);

  // if required, adjust the 'g1' values in the generated contacts so that
  // thay indicated the GeomTransform object instead of the encapsulated
  // object.
  if (tr->infomode) {
    for (int i=0; i<n; i++) {
      dContactGeom *c = CONTACT(contact,skip*i);
      c->g1 = o1;
    }
  }

  // restore the pos, R and body
  tr->obj->pos = posbak;
  tr->obj->R = Rbak;
  tr->obj->body = bodybak;
  return n;
}



//****************************************************************************
// public API


dxGeomTransform* dCreateGeomTransform (dSpaceID space, dxBody *body)
{
  void* place = ODE_AllocateGeom();
  if(place == NULL)
  {
    return NULL;
  }
  dxGeomTransform *geom = new(place) dxGeomTransform (space, body);
  return geom;

}


void dGeomTransformSetGeom (dGeomID g, dGeomID obj)
{
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
  dxGeomTransform *tr = (dxGeomTransform*) g;
  if (tr->obj && tr->cleanup) delete tr->obj;
  dSpaceRemove (obj->parent_space, obj);
  obj->bodyRemove();
  tr->obj = obj;
}


dGeomID dGeomTransformGetGeom (dGeomID g)
{
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
  dxGeomTransform *tr = (dxGeomTransform*) g;
  return tr->obj;
}


void dGeomTransformSetCleanup (dGeomID g, int mode)
{
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
  dxGeomTransform *tr = (dxGeomTransform*) g;
  tr->cleanup = mode;
}


int dGeomTransformGetCleanup (dGeomID g)
{
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
  dxGeomTransform *tr = (dxGeomTransform*) g;
  return tr->cleanup;
}


void dGeomTransformSetInfo (dGeomID g, int mode)
{
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
  dxGeomTransform *tr = (dxGeomTransform*) g;
  tr->infomode = mode;
}


int dGeomTransformGetInfo (dGeomID g)
{
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
  dxGeomTransform *tr = (dxGeomTransform*) g;
  return tr->infomode;
}

void ODE_GeomTransformGetOffset(dxGeom *geom, float *origin)
{
  dxGeomTransform* g = (dxGeomTransform*)geom;
  
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
    
  origin[0] = g->localPos[0];
  origin[1] = g->localPos[1];
  origin[2] = g->localPos[2];
}

void ODE_GeomTransformSetOffset(dxGeom *geom, const float *origin)
{
  dxGeomTransform* g = (dxGeomTransform*)geom;
  
  dUASSERT (g && g->type == dGeomTransformClass,
	    "argument not a geom transform");
    
  g->localPos[0] = origin[0];
  g->localPos[1] = origin[1];
  g->localPos[2] = origin[2];
  g->finalR[0] = 0.0;

}

int ODE_WorldGetBodyCount(dxWorld *world)
{
  return world->bodyCount;
}

void ODE_GeomTransformGetAAContainedBox(dxGeom *geom, float *mins, float *maxs)
{

  dUASSERT (geom && geom->type == dGeomTransformClass,
	  "argument not a geom transform");

  dxGeomTransform *tr = (dxGeomTransform*)geom;

  dAASSERT(tr->obj);

  if ( (tr->gflags & 2) != 0 )
  {
    tr->computeFinalTx( );
  }
  tr->obj->pos = tr->finalPos;
  tr->obj->R = tr->finalR;
  ODE_GeomGetAAContainedBox(tr->obj, mins, maxs);
}

void ODE_GeomTransformSetRotation(dxGeom *g, const float *origin, const float *rotation)
{

  dAASSERT(g);
  dAASSERT(g->type == dGeomTransformClass);

  dxGeomTransform* tr = (dxGeomTransform*)g;

  Phys_AxisToOdeMatrix3(rotation, tr->localR);
  tr->localPos[0] = origin[0];
  tr->localPos[1] = origin[1];
  tr->localPos[2] = origin[2];
  tr->finalR[0] = 0.0;
}