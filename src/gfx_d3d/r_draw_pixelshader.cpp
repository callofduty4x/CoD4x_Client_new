#include "r_types_d3d.h"


unsigned int R_SkipDrawSurfListMaterial(GfxDrawSurf *drawSurfList, unsigned int drawSurfCount)
{
    unsigned int subListCount;

    for ( subListCount = 0; subListCount < drawSurfCount ; ++subListCount )
    {
        if((drawSurfList[subListCount].fields.materialSortedIndex | drawSurfList[subListCount].fields.prepass | drawSurfList[subListCount].fields.primaryLightIndex | drawSurfList[subListCount].fields.surfType | drawSurfList[subListCount].fields.primarySortKey | drawSurfList[subListCount].fields.unused)
            != (drawSurfList[0].fields.materialSortedIndex | drawSurfList[0].fields.prepass | drawSurfList[0].fields.primaryLightIndex | drawSurfList[0].fields.surfType | drawSurfList[0].fields.primarySortKey | drawSurfList[0].fields.unused))
        {
            break;
        }

    }
    return subListCount;
}