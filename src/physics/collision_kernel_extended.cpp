#include <ode/ode.h>
#include <../src/objects.h>

extern "C"
{

dxGeom * ODE_BodyGetFirstGeom(dxBody *body)
{
  return body->geom;
}

};