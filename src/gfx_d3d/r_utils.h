#include "r_types_d3d.h"

void R_SetAndClearSceneTarget(const GfxViewport *viewport);
void R_ConvertColorToBytes(const float *colorFloat, unsigned char *colorBytes);
bool R_GetClearColor(float *unpackedRgba);