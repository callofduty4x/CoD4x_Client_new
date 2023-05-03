#include <ctype.h>
#include "../q_shared.h"

void LAN_CleanHostname(const char *hostName, char *cleanHostName)
{
  unsigned char c;

  while ( 1 )
  {
    c = *hostName;
    if ( !*hostName )
    {
      break;
    }
    if ( isalpha(c) )
    {
      *cleanHostName++ = c;
    }
    ++hostName;
  }
  *cleanHostName = 0;
}

int LAN_CompareHostname(const char *hostName1, const char *hostName2)
{
  char cleanHostName2[32];
  char cleanHostName1[32];
  int res;

  LAN_CleanHostname(hostName1, cleanHostName1);
  LAN_CleanHostname(hostName2, cleanHostName2);
  res = Q_stricmp(cleanHostName1, cleanHostName2);
  if ( res )
  {
    return res;
  }
  return Q_stricmp(hostName1, hostName2);
}