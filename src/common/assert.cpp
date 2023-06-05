#include <q_shared.h>
#include "sys_shared.h"
#include <windows.h>

qboolean Assert_MyHandler(const char* exp, const char *filename, int line, const char* func, const char *fmt, ...)
{
    char buf[8192];
    const char* message = "";

    if(fmt != NULL)
    {
        strcpy(buf, "\nAssert Message: ");
        int l = strlen(message);
        va_list argptr;
        va_start (argptr,fmt);
        Q_vsnprintf(buf +l, sizeof(buf) -l, fmt, argptr);
        va_end (argptr);
        message = buf;
    }
    Com_PrintError(CON_CHANNEL_DONT_FILTER, "Assert failed - Exp: %s, File: %s, Line: %d, Function: %s %s\n",exp, filename, line, func, message);
    //Sys_PrintBacktrace();
    asm("int $3");
    return qfalse;
}


static HINSTANCE GetModuleBase(const char *name)
{
  char moduleName[260];
  HINSTANCE moduleHandle;
  int nameLength;
  int nameIndex;

  nameLength = strlen(name);
  if(static_cast<unsigned>(nameLength) > sizeof(moduleName) -5)
  {
    return NULL;
  }
  for ( nameIndex = nameLength - 1; nameIndex >= 0 && name[nameIndex] != '.' && name[nameIndex] != '/' && name[nameIndex] != '\\'; --nameIndex )
  {
    ;
  }
  if ( nameIndex >= 0 && name[nameIndex] == '.' )
  {
    nameLength = nameIndex;
  }
  memcpy(moduleName, name, nameLength);
  strcpy(&moduleName[nameLength], ".exe");
  moduleHandle = GetModuleHandleA(moduleName);
  if ( moduleHandle )
  {
    return moduleHandle;
  }
  strcpy(&moduleName[nameLength], ".dll");
  return GetModuleHandleA(moduleName);
}


struct AddressInfo_s
{
  unsigned int address;
  char moduleName[64];
  char bestFunction[64];
  char bestFunctionFilename[64];
  unsigned int bestFunctionAddress;
  char bestLineFilename[64];
  unsigned int bestLineAddress;
  unsigned int bestLineNumber;
};


static AddressInfo_s g_assertAddress[32];
static int g_assertAddressCount;
static int lineBufferEndPos;
static int lineBufferStartPos;
static char lineBuffer[4096];

static bool ReadLine(FILE *fp)
{
  int readSize;
  int bytesRead;
  int i;

  do
  {
    lineBufferEndPos -= lineBufferStartPos;
    
    assert(lineBufferEndPos >= 0);

    memmove(lineBuffer, &lineBuffer[lineBufferStartPos], lineBufferEndPos);
    lineBufferStartPos = 0;
    for ( i = 0; i < lineBufferEndPos; ++i )
    {
      if ( lineBuffer[i] == '\n' )
      {
        if ( i + 1 != lineBufferEndPos )
        {
          lineBuffer[i] = 0;
          if ( lineBuffer[i + 1] == '\r' )
          {
            lineBufferStartPos = i + 2;
          }
          else
          {
            lineBufferStartPos = i + 1;
          }
          return true;
        }
        break;
      }
    }
    readSize = sizeof(lineBuffer) - lineBufferEndPos - 1;
    bytesRead = fread(&lineBuffer[lineBufferEndPos], 1u, readSize, fp);

    assert(bytesRead <= readSize);

    lineBufferEndPos += bytesRead;
    lineBuffer[lineBufferEndPos] = 0;
  }
  while ( bytesRead );
  if ( !lineBufferEndPos )
  {
    return false;
  }
  lineBufferStartPos = lineBufferEndPos;
  return true;
}

static bool SkipLines(int lineCount, FILE *fp)
{
  int i;

  for ( i = 0; i < lineCount; ++i )
  {
    if ( !ReadLine(fp) )
    {
      return false;
    }
  }
  return true;
}

static void ParseError(const char *msg)
{
  HWND ActiveWindow;

  ActiveWindow = GetActiveWindow();
  MessageBoxA(ActiveWindow, msg, ".map parse error", MB_ICONSTOP);
}

static void ParseMapFile(FILE *fp, unsigned int baseAddress, const char *mapName)
{
  char *pszNameStop;
  char *pszNameStart;
  unsigned int loadAddress;
  const char *filenameSubStr;
  int j;
  unsigned int address;
  const char *filename;
  AddressInfo_s *addressInfo;
  unsigned int relAddress;
  unsigned int lineOffset[4];
  char filenameBuffer[1024];
  unsigned int offset;
  unsigned int baseEndAddress;
  unsigned int group;
  const char *funcName;
  unsigned int lineGroup[4];
  int i;
  unsigned int lineNumber[4];
  char *atChar;
  char function[1024];
  int readCount;

  lineBufferEndPos = 0;
  lineBufferStartPos = 0;
  while ( ReadLine(fp) )
  {
    if ( sscanf(lineBuffer, " Preferred load address is %x\r\n", &loadAddress) == 1 )
    {
      if ( SkipLines(2, fp) )
      {
        baseEndAddress = 0;
        while ( ReadLine(fp) )
        {
          if ( !lineBuffer[0] )
          {
            for ( j = 0; j < g_assertAddressCount; ++j )
            {
              addressInfo = &g_assertAddress[j];
              if ( addressInfo->address >= baseAddress && addressInfo->address < baseEndAddress )
              {
                Q_strncpyz(addressInfo->moduleName, mapName, sizeof(addressInfo->moduleName));
              }
            }
            while ( ReadLine(fp) )
            {
              if ( strstr(lineBuffer, "Publics by Value") )
              {
                if ( SkipLines(1, fp) )
                {
                  while ( ReadLine(fp) )
                  {
                    if ( !lineBuffer[0] )
                    {
                        if ( !SkipLines(2, fp) || !ReadLine(fp) )
                        {
                            return;
                        }
                        if ( !strcmp(lineBuffer, " Static symbols\r") )
                        {
                            if ( !SkipLines(1, fp) )
                            {
                                return;
                            }
                            while ( ReadLine(fp) && lineBuffer[0] )
                            {
                                if ( sscanf(lineBuffer, "%x:%x %s %x", &group, &offset, function, &address) != 4 )
                                {
                                    ParseError("Unknown line format in the static symbols section");
                                    return;
                                }
                                filenameSubStr = strrchr(lineBuffer, ' ');
                                if ( !filenameSubStr || sscanf(filenameSubStr + 1, "%s", filenameBuffer) != 1 )
                                {
                                    ParseError("Couldn't parse file name in the static symbols section");
                                    return;
                                }
                                relAddress = address;
                                for ( j = 0; j < g_assertAddressCount; ++j )
                                {
                                    addressInfo = &g_assertAddress[j];
                                    if ( addressInfo->address >= baseAddress && addressInfo->address < baseEndAddress && relAddress <= addressInfo->address
                                        && (!addressInfo->bestFunction[0] || addressInfo->bestFunctionAddress < relAddress) )
                                    {
                                        addressInfo->bestFunctionAddress = relAddress;
                                        funcName = function;
                                        if ( function[0] == '_' || funcName[0] == '?' )
                                        {
                                            ++funcName;
                                        }
                                        Q_strncpyz(addressInfo->bestFunction, funcName, sizeof(addressInfo->bestFunction));
                                        atChar = strchr(addressInfo->bestFunction, '@');
                                        if ( atChar )
                                        {
                                            *atChar = 0;
                                        }
                                        filename = strrchr(filenameBuffer, '\\');
                                        if ( filename )
                                        {
                                            ++filename;
                                        }
                                        else
                                        {
                                            filename = filenameBuffer;
                                        }
                                        Q_strncpyz(addressInfo->bestFunctionFilename, filename, sizeof(addressInfo->bestFunctionFilename));
                                    }
                                }
                            }
                        }

                        while ( ReadLine(fp) )
                        {
                            if ( strncmp(lineBuffer, "Line numbers for ", 17) )
                            {
                                ParseError("Expected line number section");
                                return;
                            }
                            pszNameStart = strchr(lineBuffer, '(');
                            if ( !pszNameStart )
                            {
                                ParseError("Couldn't find '(' for the name of the source file in line number section");
                                return;
                            }
                            pszNameStop = strchr(pszNameStart, ')');
                            if ( !pszNameStop )
                            {
                                ParseError("Couldn't find ')' for the name of the source file in line number section");
                                return;
                            }
                            strncpy(filenameBuffer, pszNameStart + 1, pszNameStop - pszNameStart - 1);
                            filenameBuffer[pszNameStop - pszNameStart -1] = 0;
                            
                            filenameSubStr = filenameBuffer;
                            if ( !SkipLines(1, fp) )
                            {
                                return;
                            }
                            while ( ReadLine(fp) && lineBuffer[0] )
                            {
                                readCount = sscanf(lineBuffer, "%i %x:%x %i %x:%x %i %x:%x %i %x:%x\r\n",
                                                lineNumber, lineGroup, lineOffset,
                                                &lineNumber[1], &lineGroup[1], &lineOffset[1], &lineNumber[2],
                                                &lineGroup[2], &lineOffset[2], &lineNumber[3], &lineGroup[3], &lineOffset[3]);
                                if ( readCount % 3 || readCount / 3 <= 0 )
                                {
                                    ParseError("unknown line format in the line number section");
                                    return;
                                }
                                for ( i = 0; 3 * i < readCount; ++i )
                                {
                                    relAddress = lineOffset[i] + baseAddress + 0x1000;
                                    for ( j = 0; j < g_assertAddressCount; ++j )
                                    {
                                        addressInfo = &g_assertAddress[j];
                                        if ( addressInfo->address >= baseAddress && addressInfo->address < baseEndAddress && relAddress <= addressInfo->address
                                            && (!addressInfo->bestLineFilename[0] || addressInfo->bestLineAddress < relAddress) )
                                        {
                                            addressInfo->bestLineAddress = relAddress;
                                            addressInfo->bestLineNumber = lineNumber[i];
                                            filename = strrchr((char *)filenameSubStr, '\\');
                                            if ( filename )
                                            {
                                                ++filename;
                                            }
                                            else
                                            {
                                                filename = filenameSubStr;
                                            }
                                            Q_strncpyz(addressInfo->bestLineFilename, filename, sizeof(addressInfo->bestLineFilename));
                                        }
                                    }
                                }
                            }
                        }
                        return;
                    }
                    if ( sscanf(lineBuffer, "%x:%x %s %x", &group, &offset, function, &address) != 4 )
                    {
                      ParseError("Unknown line format in the public symbols section");
                      return;
                    }
                    filenameSubStr = strrchr(lineBuffer, ' ');
                    if ( !filenameSubStr || sscanf(filenameSubStr + 1, "%s", filenameBuffer) != 1 )
                    {
                      ParseError("Couldn't parse file name in the public symbols section");
                      return;
                    }
                    relAddress = address;
                    for ( j = 0; j < g_assertAddressCount; ++j )
                    {
                      addressInfo = &g_assertAddress[j];
                      if ( addressInfo->address >= baseAddress
                        && addressInfo->address < baseEndAddress
                        && relAddress <= addressInfo->address
                        && (!addressInfo->bestFunction[0] || addressInfo->bestFunctionAddress < relAddress) )
                      {
                        addressInfo->bestFunctionAddress = relAddress;
                        funcName = function;
                        if ( function[0] == '_' || *funcName == '?' )
                        {
                          ++funcName;
                        }
                        Q_strncpyz(addressInfo->bestFunction, funcName, sizeof(addressInfo->bestFunction));
                        atChar = strchr(addressInfo->bestFunction, '@');
                        if ( atChar )
                        {
                          *atChar = 0;
                        }
                        filename = strrchr(filenameBuffer, '\\');
                        if ( filename )
                        {
                          ++filename;
                        }
                        else
                        {
                          filename = filenameBuffer;
                        }
                        Q_strncpyz(addressInfo->bestFunctionFilename, filename, sizeof(addressInfo->bestFunctionFilename));
                      }
                    }
                  }
                }
                return;
              }
            }
            return;
          }
          if ( sscanf(lineBuffer, "%x:%x %xH %s %s", &group, &offset, &address, function, filenameBuffer) != 5 )
          {
            ParseError("Unknown line format in the segments section");
            return;
          }
          if ( group == 1 && baseEndAddress < address + offset + baseAddress + 0x1000 )
          {
            baseEndAddress = address + offset + baseAddress + 0x1000;
          }
        }
      }
      return;
    }
  }
}


static void LoadMapFilesForDir(const char *dir)
{
  const char *filepath;
  WIN32_FIND_DATAA FindFileData;
  char file[64];
  unsigned int baseAddress;
  FILE *fp;
  HANDLE hFindFile;
  char string[64];

  if ( *dir )
  {
    snprintf(string, sizeof(string), "%s\\%s\\*.map", Sys_DefaultInstallPath(), dir);
  }
  else
  {
    snprintf(string, sizeof(string), "%s\\*.map", Sys_DefaultInstallPath());
  }
  hFindFile = FindFirstFileA(string, &FindFileData);
  if ( hFindFile != INVALID_HANDLE_VALUE )
  {
    do
    {
      baseAddress = (unsigned int)GetModuleBase(FindFileData.cFileName);
      if ( baseAddress )
      {
        filepath = Sys_DefaultInstallPath();
        snprintf(file, sizeof(file), "%s\\%s", filepath, FindFileData.cFileName);
        fp = fopen(file, "rb");
        if ( fp )
        {      
          strncpy(file, FindFileData.cFileName, sizeof(file));
          file[strlen(file) -5] = 0; //cut extension .dll/.exe
          ParseMapFile(fp, baseAddress, file);
          fclose(fp);
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    FindClose(hFindFile);
  }
}

static int LoadMapFiles(char *msg)
{
  int j;
  AddressInfo_s *addressInfo;
  char *curPos;

  LoadMapFilesForDir("");
  if ( !msg )
  {
    return 0;
  }
  curPos = msg;
  for ( j = 0; j < g_assertAddressCount; ++j )
  {
    addressInfo = &g_assertAddress[j];
    if ( addressInfo->moduleName[0] )
    {
      curPos += sprintf(curPos, "%s:    ", addressInfo->moduleName);
      if ( addressInfo->bestLineFilename[0] )
      {
        curPos += sprintf(curPos, "%s        ...%s, line %i", addressInfo->bestFunction, addressInfo->bestLineFilename, addressInfo->bestLineNumber);
        curPos += sprintf(curPos, "\n");
      }
      else
      {
        if ( addressInfo->bestFunction[0] )
        {
          curPos += sprintf(curPos, "%s        ...%s, address %x", addressInfo->bestFunction, addressInfo->bestFunctionFilename, addressInfo->address);
        }
        else
        {
          curPos += sprintf(curPos, "%s, address %x", addressInfo->bestFunction, addressInfo->address);
        }
        curPos += sprintf(curPos, "\n");
      }
    }
  }
  return curPos - msg;
}



void Assert_DoStackTrace(char *msg, unsigned int nIgnore, int type, void* context)
{
  unsigned int *frame;
  unsigned int i;
  static bool g_inStackTrace;

  msg[0] = 0;

  if ( !g_inStackTrace )
  {
    g_inStackTrace = 1;
    memset(g_assertAddress, 0, sizeof(g_assertAddress));
    g_assertAddressCount = 0;
    if ( context )
    {
        frame = static_cast<unsigned int*>(context);
    }
    else
    {
        frame = static_cast<unsigned int*>(__builtin_frame_address (0));
    }

    for ( i = 0; i < nIgnore + ARRAY_COUNT(g_assertAddress); ++i )
    {
        if ( i >= nIgnore )
        {
            g_assertAddress[g_assertAddressCount++].address = frame[1] - 5;
        }
        frame = reinterpret_cast<unsigned int*>(*frame);
        if ( !frame )
        {
            break;
        }
    }
    LoadMapFiles(msg);
    g_inStackTrace = 0;
  }
}

void Assert_ResetAddressInfo()
{
  g_assertAddressCount = 0;
}
