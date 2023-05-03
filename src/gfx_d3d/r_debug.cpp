#include "../common/cvar.h"
#include "../win32/win_debugcon.h"

dvar_s* r_showCollision;
dvar_s* r_showCollisionGroups;
dvar_s* r_showCollisionPolyType;
dvar_s* r_showCollisionDepthTest;
dvar_s* r_showCollisionDist;


void R_RegisterDebugDvars()
{
    static const char *showCollisionNames[] ={ "None", "All", "Player", "Bullet", "Missile", "Vehicle", "Monster", "Item", "CanShoot", "AINoSight", NULL };
    static const char *showCollisionPolyTypeNames[] = { "All", "Wireframe", "Interior", NULL };
    static const char *showCollisionGroupsNames[] = { "All", "Brush", "Terrain", NULL };


    r_showCollision = Dvar_RegisterEnum("r_showCollision", showCollisionNames, 0, 0x80u, "Show the collision surfaces for the selected mask types");
    r_showCollisionGroups = Dvar_RegisterEnum("r_showCollisionGroups", showCollisionGroupsNames, 0, 0x80u, "Select whether to show the terrain, brush or all collision surface groups");
    r_showCollisionPolyType = Dvar_RegisterEnum("r_showCollisionPolyType", showCollisionPolyTypeNames, 0, 0x80u, "Select whether to display the collision surfaces as wireframe, poly interiors, or both");
    r_showCollisionDepthTest = Dvar_RegisterBool("r_showCollisionDepthTest", 1, 0x80u, "Select whether to use depth test in collision surfaces display");
    r_showCollisionDist = Dvar_RegisterFloat("r_showCollisionDist", 500.0, 1.0, 3.4028235e38, 0x80u, "Maximum distance to show collision surfaces");
}
