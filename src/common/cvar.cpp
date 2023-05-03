#include "cvar.h"

extern unsigned int dvarCount;
extern dvar_s *sortedDvars[4096];

dvar_s * Dvar_SetFromStringByNameFromSource(const char *dvarName, const char *string, DvarSetSource source, uint16_t flags)
{
  dvar_s *dvar;

  dvar = Dvar_FindVar(dvarName);
  if ( !dvar )
  {
    return Dvar_RegisterString(dvarName, string, flags | CVAR_USER_CREATED, "External Dvar");
  }
  Dvar_SetFromStringFromSource(dvar, string, source);
  return dvar;
}

void Dvar_ForEachConsoleAccessName(void (*callback)(const char *))
{
  unsigned int dvarIter;
  
  if ( Dvar_GetBool("con_restricted_access") )
  {
    Dvar_Sort();
    for ( dvarIter = 0; dvarIter < dvarCount; ++dvarIter )
    {
      if ( sortedDvars[dvarIter]->flags & CVAR_UNRESTRICTED )
      {
        callback(sortedDvars[dvarIter]->name);
      }
    }
  }
  else
  {
    Dvar_ForEachName(callback);
  }
}