#include "r_types_d3d.h"
#include "r_local.h"

void R_InitContext(const GfxBackEndData *data, GfxCmdBuf *cmdBuf)
{
    cmdBuf->device = r_dx.device;
}

