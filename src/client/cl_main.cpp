#include "../q_shared.h"
#include "client_shared.h"

extern clientUIActive_t clientUIActives[1];

clientUIActive_t *CL_GetLocalClientUIGlobals(const int localClientNum)
{
  assert(localClientNum == 0);
  return clientUIActives;
}
