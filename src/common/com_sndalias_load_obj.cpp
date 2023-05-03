#include <ctype.h>

bool Com_IsValidAliasName(const char *name)
{
  int i;

  for ( i = 0; name[i] >= ' ' && (isalnum(name[i]) || name[i] == '_'); ++i );
  if(name[i] == '\0' && i > 0)
  {
      return true;
  }
  return false;
}