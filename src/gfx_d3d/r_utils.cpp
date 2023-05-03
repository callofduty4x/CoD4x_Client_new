#include "../q_shared.h"

int R_HashAssetName(const char *name)
{
  const char *pos;
  int hash;

  hash = 0;
  for ( pos = name; *pos; ++pos )
  {
    assertx((*pos < 'A' || *pos > 'Z'), "(name) = %s", name);
    assertx((*pos != '\\\\' || *pos == '/'), "(name) = %s", name);

    hash = *pos ^ 33 * hash;
  }
  return hash;
}
/*
void R_ConvertColorToBytes(const float *colorFloat, char *colorBytes)
{
  if ( colorFloat )
  {
    Byte4PackVertexColor(colorFloat, colorBytes);
  }
  else
  {
    *(int32_t*)colorBytes = -1;
  }
}
*/