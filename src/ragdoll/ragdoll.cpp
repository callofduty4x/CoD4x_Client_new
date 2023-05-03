#include "../common/sys_thread.h"

struct RagdollDef
{
  bool8 inUse;
  bool8 bound;
  char tobedefined[3790];
};

struct RagdollBody
{
    char tobedefined[2516];
};




void Ragdoll_InitBody(RagdollBody *body)
{
    assert(body);
    memset((char *)body, 0, sizeof(*body));
}

extern bool ragdollFirstInit;
extern bool ragdollInited;
extern RagdollDef ragdollDefs[2];
extern RagdollBody ragdollBodies[32];

void Ragdoll_Init()
{
    unsigned int i;

    //assert(Sys_IsMainThread());
    assert(ragdollFirstInit);

    if ( !ragdollInited )
    {
        for( i = 0; i < ARRAY_COUNT(ragdollBodies); ++i)
        {
            Ragdoll_InitBody(&ragdollBodies[i]);
        }

        for ( i = 0; i < ARRAY_COUNT(ragdollDefs); ++i )
        {
            ragdollDefs[i].bound = false;
            ragdollDefs[i].inUse = false;
        }
        ragdollInited = true;
    }
}