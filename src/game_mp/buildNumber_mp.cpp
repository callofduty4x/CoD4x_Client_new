#include <stdio.h>

extern "C" const char *getBuildNumber()
{
  static char build_string_buffer[32];

  sprintf(build_string_buffer, "%d %s", 549, "Thu Oct 04 00:43:04 2007");
  return build_string_buffer;
}

extern "C" signed int getBuildNumberAsInt()
{
  return 549;
}
