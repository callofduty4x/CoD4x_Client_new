#include <ctype.h>
#include <algorithm>
#include "client_shared.h"
#include "client_local.h"
#include "keys.h"
#include "../common/qcommon.h"
#include "../common/sys_thread.h"
#include "../common/stringed_public.h"
#include "../version/version.h"
#include "cl_console.h"

#define CONSOLE_COLOR  COLOR_WHITE //COLOR_BLACK

extern const float con_inputDvarInfoColor[4];
const float con_versionColor[] = { 1.0, 1.0, 0.0, 1.0 };

extern dvar_s* con_outputWindowColor;
extern dvar_s* con_outputBarColor;
extern dvar_s* con_outputSliderColor;
extern dvar_s* con_inputBoxColor;
extern dvar_s* con_typewriterPrintSpeed;
extern dvar_s* con_typewriterDecayStartTime;
extern dvar_s* con_typewriterDecayDuration;
extern dvar_s* con_inputHintBoxColor;

float con_outputBarSize = 10.0;
const float con_inputDvarMatchColor[] = { 1.0, 1.0, 0.8, 1.0 };
const float con_inputDvarValueColor[] = { 1.0, 1.0, 1.0, 1.0 };
const float con_inputDvarInactiveValueColor[] = { 0.8, 0.8, 0.8, 1.0 };
const float con_inputDvarDescriptionColor[] = { 1.0, 1.0, 1.0, 1.0 };
const float con_inputCommandMatchColor[] = { 0.8, 0.8, 1.0, 1.0 };
bool con_ignoreMatchPrefixOnly;
const float con_inputDvarInfoColor[] = { 0.8, 0.8, 1.0, 1.0 };

struct ConDrawInputGlob
{
  char autoCompleteChoice[64];
  int matchIndex;
  int matchCount;
  const char *inputText;
  int inputTextLen;
  bool hasExactMatch;
  bool mayAutoComplete;
  float x;
  float y;
  float leftX;
  float fontHeight;
};

struct MessageWindow
{
  struct MessageLine *lines;
  struct Message *messages;
  char *circularTextBuffer;
  int textBufSize;
  int lineCount;
  int padding;
  int scrollTime;
  int fadeIn;
  int fadeOut;
  int textBufPos;
  int firstLineIndex;
  int activeLineCount;
  int messageIndex;
};

struct MessageLine
{
  int messageIndex;
  int textBufPos;
  int textBufSize;
  int typingStartTime;
  int lastTypingSoundTime;
  int flags;
};

struct Message
{
  int startTime;
  int endTime;
};

struct MessageBuffer
{
  char gamemsgText[4][2048];
  MessageWindow gamemsgWindows[4];
  MessageLine gamemsgLines[4][12];
  Message gamemsgMessages[4][12];
  char miniconText[4096];
  MessageWindow miniconWindow;
  MessageLine miniconLines[100];
  Message miniconMessages[100];
  char errorText[1024];
  MessageWindow errorWindow;
  MessageLine errorLines[5];
  Message errorMessages[5];
};

struct Console
{
  int initialized;
  MessageWindow consoleWindow;
  MessageLine consoleLines[1024];
  Message consoleMessages[1024];
  char consoleText[32768];
  char textTempLine[512];
  unsigned int lineOffset;
  int displayLineOffset;
  int prevChannel;
  bool outputVisible;
  int fontHeight;
  int visibleLineCount;
  int visiblePixelWidth;
  float screenMin[2];
  float screenMax[2];
  MessageBuffer messageBuffer[1];
  float color[4];
};


extern ConDrawInputGlob conDrawInputGlob;
extern Console con;
extern field_t g_consoleField; 


const char * Con_TokenizeInput()
{
  const char *cmd;

  Cmd_TokenizeString(g_consoleField.buffer);
  cmd = Cmd_Argv(0);
  if ( *cmd == '\\' || *cmd == '/' )
  {
    ++cmd;
  }
  while ( isspace(*cmd) )
  {
    ++cmd;
  }
  return cmd;
}

void ConDraw_Box(float x, float y, float w, float h, const float *color) //Calling convention!
{
  float darkColor[4];

  if ( color[3] != 0.0 )
  {
    R_AddCmdDrawStretchPic(x, y, w, h, 0.0, 0.0, 0.0, 0.0, color, cls.whiteMaterial);
    VectorScale4(color, 0.5,darkColor);
    darkColor[3] = color[3];
    R_AddCmdDrawStretchPic(x, y, 2.0, h, 0.0, 0.0, 0.0, 0.0, darkColor, cls.whiteMaterial);
    R_AddCmdDrawStretchPic(x + w - 2.0, y, 2.0, h, 0.0, 0.0, 0.0, 0.0, darkColor, cls.whiteMaterial);
    R_AddCmdDrawStretchPic(x, y, w, 2.0, 0.0, 0.0, 0.0, 0.0, darkColor, cls.whiteMaterial);
    R_AddCmdDrawStretchPic(x, y + h - 2.0, w, 2.0, 0.0, 0.0, 0.0, 0.0, darkColor, cls.whiteMaterial);
  }
}


bool Console_IsClientDisconnected()
{
    return CL_AllLocalClientsDisconnected();
}

bool Console_IsRconCmd(const char *commandString)
{
  return strncmp(commandString, "rcon", strlen("rcon")) == 0;
}

enum e_restricted_initState
{
  RESTRICTED_DISABLED = 0x0,
  RESTRICTED_CONFIGURING = 0x1,
  RESTRICTED_PROTECTED = 0x2,
  RESTRICTED_STATE_COUNT = 0x3
};


e_restricted_initState g_restricted_state;

void Con_Restricted_SetState(e_restricted_initState state)
{
  assert(state < RESTRICTED_STATE_COUNT);
  g_restricted_state = state;
}

e_restricted_initState Con_Restricted_GetState()
{
    return g_restricted_state;
}

void Con_Restricted_InitLists()
{
/*
    StringTable *table;

    Con_Restricted_ShutDown();
    if ( SV_IsServerRanked() )
    {
        StringTable_GetAsset("mp/devconsole_restrict_access_dedicated_ranked_mp.csv", &table);
    }
    else
    {
        StringTable_GetAsset("mp/devconsole_restrict_access_dedicated_mp.csv", &table);
    }
    if ( table )
    {
        Con_Restricted_LoadTable(table);
        g_restricted_ranked = SV_IsServerRanked();
        Con_Restricted_SetState(RESTRICTED_PROTECTED);
    }
    else if ( Dvar_GetBool("con_restricted_access") )
    {
        Com_DPrintf(CON_CHANNEL_SYSTEM, "ConAccess: the table asset was not found.\n");
    }
*/
}

void Con_Restricted_Reset()
{
/*
    Dvar_ResetConAccessDvars();
    Cmd_ResetConAccessCommands();
*/
}

void Con_Restricted_ResetLists()
{
//  assert(Sys_IsMainThread());

  if ( Dvar_GetBool("con_restricted_access") )
  {
/*
    assert(Con_Restricted_GetState() == RESTRICTED_PROTECTED);
    if ( (signed int)Con_Restricted_GetState() < RESTRICTED_PROTECTED )
    {
        Con_Restricted_InitLists();
    }
    if ( g_restricted_ranked != (unsigned __int8)SV_IsServerRanked(SV_GetLicenseType()) )
    {
        Con_Restricted_InitLists();
    }
    Con_Restricted_Reset();
    Con_Restricted_SetLists();
*/
  }
}

/*
void Con_Restricted_SetLists()
{
    int i; // [esp+0h] [ebp-8h]
    dvar_s *dvar; // [esp+4h] [ebp-4h]

    for ( i = 0; i < g_restricted_count; ++i )
    {
        if ( g_restricted[i].valid )
        {
            dvar = Dvar_FindVar(g_restricted[i].name);
            if ( dvar )
            {
                Dvar_AddFlags(dvar, 0x10000);
            }
            else if ( !Cmd_SetConAccess(g_restricted[i].name) && Dvar_GetBool("con_restricted_access") )
            {
                Com_DPrintf(CON_CHANNEL_SYSTEM, "ConAccess: Couldn't find: %s.\n", &g_restricted[i]);
            }
        }
    }
}

*/


int Con_Restricted_RestrictBuf(const char *buf, int start, int length, char *buffer, int buffer_size)
{
    char quotes;
    int size;
    int i;

    quotes = 0;
    memset(buffer, 0, buffer_size);
    Q_strncat(buffer, buffer_size, "#dcr#");
    size = 5;
    for ( i = start; i < length; ++i )
    {
        if ( buf[i] == '"' )
        {
            ++quotes;
        }
        if ( buf[i] == 10 || buf[i] == 13 || size + 1 >= buffer_size )
        {
            break;
        }
        buffer[size++] = buf[i];
        if ( !(quotes & 1) && buf[i] == ';' )
        {
            if ( size + 5 >= buffer_size )
            {
                return i;
            }
            Q_strncat(buffer, buffer_size, "#dcr#");
            size += 5;
        }
    }
    return i;
}

void Con_Restricted_AddBuf(const char *buf)
{
    int start;
    char buffer[4096];
    int length;

    if ( Dvar_GetBool("con_restricted_access") )
    {
        Con_Restricted_ResetLists();
        length = strlen_noncrt(buf);
        start = 0;
        do
        {
            start = Con_Restricted_RestrictBuf(buf, start, length, buffer, 4096);
            Cbuf_AddText(0, buffer);
            Cbuf_AddText(0, "\n");
        }
        while ( start < length );
    }
    else
    {
        Cbuf_AddText(0, buf);
        Cbuf_AddText(0, "\n");
    }
}


void Con_Restricted_ForEach(bool isDvarCommand, void (*callbackDvar)(const char *), void (*callbackCmd)(const char *))
{
  Dvar_ForEachConsoleAccessName(callbackDvar);
  if ( !isDvarCommand )
  {
    Cmd_ForEachConsoleAccessName(callbackCmd);
  }
}

void Con_ForEach(bool isDvarCommand, void (*callbackDvar)(const char *), void (*callbackCmd)(const char *))
{
  Con_Restricted_ForEach(isDvarCommand, callbackDvar, callbackCmd);
}

int ConDrawInput_CompareStrings(const void *e0, const void *e1)
{
  return Q_stricmp(*(const char **)e0, *(const char **)e1);
}

int ConDrawInput_TextWidth(const char *text)
{
    assert(text);
    
    return R_TextWidth(text, 0, cls.consoleFont);
}

void ConDrawInput_Text(const char *str, const float *color)
{
    assert(str);
    
    R_AddCmdDrawText(str, 0x7FFFFFFF, cls.consoleFont, conDrawInputGlob.x, conDrawInputGlob.y + conDrawInputGlob.fontHeight, 1.0, 1.0, 0.0, color, 0);
}

int ConDrawInput_TextFieldFirstArgChar()
{
  int charIndex;

  for ( charIndex = 0; isspace(g_consoleField.buffer[charIndex]); ++charIndex );

  while ( !isspace(g_consoleField.buffer[charIndex]) )
  {
    ++charIndex;
  }
  while ( isspace(g_consoleField.buffer[charIndex]) )
  {
    ++charIndex;
  }
  return charIndex;
}

void ConDrawInput_AutoCompleteArg(const char **stringList, int stringCount)
{
  int matchIndex;
  int matchCount;
  char matchBuffer[1024];
  int prefixLen;
  int matchLenMax;
  int matchLen;
  const char *prefix;
  char *matches[16];
  int matchBufferUsed;
  int stringIndex;
  float x;
  float y;
  float h;
  float w;

  prefix = Cmd_Argv(1);
  prefixLen = strlen(prefix);
  if ( prefixLen )
  {
    matchCount = 0;
    matchBufferUsed = 0;
    matchLenMax = 0;
    for ( stringIndex = 0; stringIndex < stringCount; ++stringIndex )
    {
      if ( !Q_stricmpn(prefix, stringList[stringIndex], prefixLen) )
      {
        if ( matchCount == ARRAY_COUNT(matches) || matchBufferUsed + strlen(stringList[stringIndex]) >= sizeof(matchBuffer) )
        {
          return;
        }
        matches[matchCount] = &matchBuffer[matchBufferUsed];
        Com_StripExtension(stringList[stringIndex], matches[matchCount]);
        matchBufferUsed += strlen(matches[matchCount]) + 1;
        matchLen = ConDrawInput_TextWidth(matches[matchCount]);
        if ( matchLenMax < matchLen )
        {
          matchLenMax = matchLen;
        }
        ++matchCount;
      }
    }
    if ( matchCount )
    {
      qsort(matches, matchCount, 4u, ConDrawInput_CompareStrings);
      x = ((float)R_TextWidth(g_consoleField.buffer, ConDrawInput_TextFieldFirstArgChar(), cls.consoleFont) + conDrawInputGlob.leftX) - 6.0;
      y = (con.screenMin[1] + conDrawInputGlob.fontHeight) + 6.0;
      w = (float)matchLenMax + 6.0 * 2.0;
      h = (float)matchCount * conDrawInputGlob.fontHeight + 6.0 * 2.0;
      ConDraw_Box(x, y, w, h, &con_inputHintBoxColor->current.value);
      conDrawInputGlob.x = x + 6.0;
      conDrawInputGlob.y = y + 6.0;
      conDrawInputGlob.leftX = x + 6.0;
      for ( matchIndex = 0; matchIndex < matchCount; ++matchIndex )
      {
        ConDrawInput_Text(matches[matchIndex], con_inputDvarInfoColor);
        conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
        conDrawInputGlob.x = conDrawInputGlob.leftX;
      }
    }
  }
}

int PrintableCharsCount(MessageWindow *msgwnd, MessageLine *line)
{
  int usedCharCnt;
  char c[2];
  int letter;
  int printedCnt;
  int idx;

  printedCnt = 0;
  idx = 0;
  while ( idx < line->textBufSize )
  {
    c[0] = msgwnd->circularTextBuffer[(msgwnd->textBufSize - 1) & (idx + line->textBufPos)];
    c[1] = msgwnd->circularTextBuffer[(msgwnd->textBufSize - 1) & (line->textBufPos + idx + 1)];
    letter = SEH_DecodeLetter(c[0], c[1], &usedCharCnt, 0);
    idx += usedCharCnt;
    ++printedCnt;
    if ( letter == '^' )
    {
      c[0] = msgwnd->circularTextBuffer[(msgwnd->textBufSize - 1) & (idx + line->textBufPos)];
      if ( (c[0] != '^' && c[0] >= '0' && c[0] <= '@') || (c[0] != '^' && c[0] == 'F') )
      {
        ++idx;
      }
    }
  }
  return printedCnt;
}

int PrintTimeWriteOut(MessageWindow *msgwnd, MessageLine *line)
{
  if ( line->flags & 1 )
  {
    return con_typewriterPrintSpeed->current.integer * PrintableCharsCount(msgwnd, line);
  }
  return 0;
}

int LatestActiveTypewrittenLineIdx(MessageWindow *msgwnd)
{
  int idx;

  if ( !msgwnd->activeLineCount )
  {
    return -1;
  }
  for ( idx = msgwnd->activeLineCount - 1; idx >= 0; --idx )
  {
    if ( msgwnd->lines[(idx + msgwnd->firstLineIndex) % msgwnd->lineCount].flags & 1 )
    {
      return (idx + msgwnd->firstLineIndex) % msgwnd->lineCount;
    }
  }
  return -1;
}

int GetNextValidPrintTimeForLine(int localClientNum, MessageWindow *msgwnd, int flags)
{
  MessageLine *line;
  int lineIdx;
  int serverTime;

  if ( !(flags & 1) )
  {
    return 0;
  }
  serverTime = CL_GetLocalClientGlobals(localClientNum)->serverTime;
  lineIdx = LatestActiveTypewrittenLineIdx(msgwnd);
  if ( lineIdx == -1 )
  {
    return serverTime + 250;
  }
  line = &msgwnd->lines[lineIdx];
  int nexttime = line->typingStartTime + PrintTimeWriteOut(msgwnd, line) + 150;
  if ( nexttime - serverTime >= 250 )
  {
    return nexttime;
  }
  return serverTime + 250;
}

int PrintTimeTotal(MessageWindow *msgwnd, MessageLine *line)
{
  int time;

  if ( !(line->flags & 1) )
  {
    return 0;
  }
  time = con_typewriterPrintSpeed->current.integer * PrintableCharsCount(msgwnd, line);
  if ( time < con_typewriterDecayStartTime->current.integer )
  {
    time = con_typewriterDecayStartTime->current.integer;
  }
  return con_typewriterDecayDuration->current.integer + time;
}

bool Con_NeedToFreeMessageWindowLine(MessageWindow *msgwnd, int charCount)
{
  int pastLastChar;
  MessageLine *line;

  if ( !msgwnd->activeLineCount )
  {
    return false;
  }

  assert(msgwnd->lineCount > 0);

  line = &msgwnd->lines[msgwnd->firstLineIndex];

  assert(!( msgwnd->textBufSize & (msgwnd->textBufSize - 1) ));

  pastLastChar = (msgwnd->textBufSize - 1) & (charCount + msgwnd->textBufPos);
  if ( pastLastChar < msgwnd->textBufPos )
  {
    return line->textBufPos >= msgwnd->textBufPos || line->textBufPos < pastLastChar;
  }
  return line->textBufPos >= msgwnd->textBufPos && line->textBufPos < pastLastChar;
}

void Con_FreeFirstMessageWindowLine(MessageWindow *msgwnd)
{
  assert(msgwnd->activeLineCount > 0);

  --msgwnd->activeLineCount;
  if ( ++msgwnd->firstLineIndex == msgwnd->lineCount )
  {
    msgwnd->firstLineIndex = 0;
  }
  if ( msgwnd == &con.consoleWindow && --con.displayLineOffset < con.visibleLineCount )
  {
    if ( con.consoleWindow.activeLineCount < con.visibleLineCount )
    {
      con.displayLineOffset = con.consoleWindow.activeLineCount;
    }
    else
    {
      con.displayLineOffset = con.visibleLineCount;
    }
  }
}

void Con_CopyCurrentConsoleLineText(MessageWindow *msgwnd, MessageLine *msgLine)
{
  unsigned int poolRemaining;

  assert(msgLine);

  while ( Con_NeedToFreeMessageWindowLine(msgwnd, con.lineOffset + 1) )
  {
    Con_FreeFirstMessageWindowLine(msgwnd);
  }
  poolRemaining = msgwnd->textBufSize - msgwnd->textBufPos;
  if ( con.lineOffset > poolRemaining )
  {
    memcpy(&msgwnd->circularTextBuffer[msgwnd->textBufPos], con.textTempLine, poolRemaining);
    memcpy(msgwnd->circularTextBuffer, &con.textTempLine[poolRemaining], con.lineOffset - poolRemaining);
  }
  else
  {
    memcpy(&msgwnd->circularTextBuffer[msgwnd->textBufPos], con.textTempLine, con.lineOffset);
  }
  msgLine->textBufPos = msgwnd->textBufPos;
  msgLine->textBufSize = con.lineOffset;

  assert(!(msgwnd->textBufSize & (msgwnd->textBufSize - 1)));

  msgwnd->textBufPos = (msgwnd->textBufSize - 1) & (con.lineOffset + msgwnd->textBufPos);
  msgwnd->circularTextBuffer[msgwnd->textBufPos] = '\n';
  msgwnd->textBufPos = (msgwnd->textBufSize - 1) & (msgwnd->textBufPos + 1);
}

void Con_UpdateMessageWindowLine(int localClientNum, MessageWindow *msgwnd, int linefeed, int flags)
{
  int newPadLineOffset;
  Message *message;
  unsigned int imod;
  MessageLine *line;
  int serverTime;
  clientActive_t *locClient;

  assert(msgwnd);
  assert((unsigned)msgwnd->firstLineIndex < (unsigned)msgwnd->lineCount);
  assert((unsigned)msgwnd->messageIndex < (unsigned)msgwnd->lineCount);

  serverTime = 0;
  locClient = CL_GetLocalClientGlobals(localClientNum);
  if ( locClient )
  {
    serverTime = locClient->serverTime;
  }
  line = &msgwnd->lines[(msgwnd->activeLineCount + msgwnd->firstLineIndex) % msgwnd->lineCount];
  line->messageIndex = msgwnd->messageIndex;
  line->typingStartTime = 0;
  line->lastTypingSoundTime = 0;
  line->flags = flags;
  line->typingStartTime = GetNextValidPrintTimeForLine(localClientNum, msgwnd, flags);
  if ( line->typingStartTime )
  {
    msgwnd->messages[line->messageIndex].endTime = line->typingStartTime + PrintTimeTotal(msgwnd, line);
  }
  Con_CopyCurrentConsoleLineText(msgwnd, line);
  if ( linefeed )
  {
    if ( msgwnd->activeLineCount == msgwnd->lineCount )
    {
      Con_FreeFirstMessageWindowLine(msgwnd);
    }
    newPadLineOffset = ++msgwnd->activeLineCount - (msgwnd->lineCount - msgwnd->padding);
    if ( newPadLineOffset > 0 )
    {
      imod = (msgwnd->firstLineIndex + newPadLineOffset - 1) % msgwnd->lineCount;
      assert(imod < (unsigned)msgwnd->lineCount);

      line = &msgwnd->lines[imod];

      assert((unsigned)line->messageIndex < (unsigned)msgwnd->lineCount);

      message = &msgwnd->messages[line->messageIndex];
      if ( message->endTime - msgwnd->fadeOut > serverTime )
      {
        assert(message->endTime >= message->startTime);
        message->endTime = msgwnd->fadeOut + serverTime;
      }
    }
  }
}


MessageWindow* Con_GetDestWindow(int localClientNum, print_msg_dest_t dest)
{
  switch ( dest )
  {
    case CON_DEST_CONSOLE:
      return &con.consoleWindow;
    case CON_DEST_MINICON:
      return &con.messageBuffer[localClientNum].miniconWindow;
    case CON_DEST_ERROR:
      return &con.messageBuffer[localClientNum].errorWindow;
    default:
        break;
  }
  assert(dest >= CON_DEST_GAME_FIRST && dest <= CON_DEST_GAME_LAST);

  return &con.messageBuffer[localClientNum].gamemsgWindows[dest - CON_DEST_GAME_FIRST];
}

void Con_UpdateNotifyLineWindow(int localClientNum, int channel, bool lineFeed, int flags, print_msg_dest_t dest)
{
  MessageWindow *window;

  if ( Con_IsChannelVisible(dest, (conChannel_t)channel, flags) )
  {
    window = Con_GetDestWindow(localClientNum, dest);
    Con_UpdateMessageWindowLine(localClientNum, window, lineFeed, flags);
  }
}


REGPARM(3) void Con_UpdateNotifyLine(int localClientNum, int channel, bool lineFeed, int flags)
{
  unsigned int dest;

  assert(Con_IsChannelOpen(channel));

  Con_UpdateNotifyLineWindow(localClientNum, channel, lineFeed, flags, CON_DEST_CONSOLE);
  Con_UpdateNotifyLineWindow(localClientNum, channel, lineFeed, flags, CON_DEST_MINICON);
  for ( dest = CON_DEST_GAME_FIRST; dest <= CON_DEST_GAME_LAST; ++dest )
  {
    Con_UpdateNotifyLineWindow(localClientNum, channel, lineFeed, flags, (print_msg_dest_t)dest);
  }

  assert(com_developer);

  if ( com_developer->current.integer )
  {
    Con_UpdateNotifyLineWindow(localClientNum, channel, lineFeed, flags, CON_DEST_ERROR);
  }
}

void Con_Linefeed(int localClientNum, int channel, int flags)
{
  Con_UpdateNotifyLine(localClientNum, channel, 1, flags);
  con.lineOffset = 0;
  if ( con.displayLineOffset == con.consoleWindow.activeLineCount - 1 )
  {
    ++con.displayLineOffset;
  }
}

const char * Con_GetVersionString()
{
  return va("Build %d %s", Sys_GetBuild(), "win-x86");
}

void Con_DrawOutputVersion(float x, float y, float width, float height)
{
  const char *versionString;

  versionString = Con_GetVersionString();
  SCR_DrawSmallStringExt((signed int)x, (signed int)(height - 16.0 + y), versionString, con_versionColor);
}

void Con_DrawOutputScrollBar(float x, float y, float width, float height)
{
  float h;
  float ww;
  float scale;

  x = x + width - con_outputBarSize;
  ConDraw_Box(x, y, con_outputBarSize, height, con_outputBarColor->current.vector);
  if ( con.consoleWindow.activeLineCount > con.visibleLineCount )
  {
    scale = 1.0 / (float)(con.consoleWindow.activeLineCount - con.visibleLineCount);

    ww = _clip2domain((float)(con.displayLineOffset - con.visibleLineCount) * scale, 0.0, 1.0);

    h = std::min(con_outputBarSize, ceil((float)con.visibleLineCount * scale * height));
    ConDraw_Box(x, (y + height - h - y) * ww + y, con_outputBarSize, h, con_outputSliderColor->current.vector);
  }
  else
  {
    ConDraw_Box(x, y, con_outputBarSize, height, con_outputSliderColor->current.vector);
  }
}

void Con_DrawOutputText(float x, float y)
{
  int rowCount;
  int firstRow;
  float color[4];
  int lineIndex;
  int rowIndex;

  CL_LookupColor(0, 55, color);

  assert(con.fontHeight);

  rowCount = con.visibleLineCount;
  firstRow = con.displayLineOffset - con.visibleLineCount;
  if ( con.displayLineOffset - con.visibleLineCount < 0 )
  {
    y = y - (float)(con.fontHeight * firstRow);
    rowCount = con.displayLineOffset;
    firstRow = 0;
  }
  for ( rowIndex = 0; rowIndex < rowCount; ++rowIndex )
  {
    lineIndex = (rowIndex + firstRow + con.consoleWindow.firstLineIndex) % con.consoleWindow.lineCount;
    y = (float)con.fontHeight + y;
    R_AddCmdDrawConsoleText(con.consoleWindow.circularTextBuffer, con.consoleWindow.textBufSize, con.consoleWindow.lines[lineIndex].textBufPos,
      con.consoleWindow.lines[lineIndex].textBufSize, cls.consoleFont, x, y, 1.0, 1.0, color, 0);
  }
}

void Con_DrawOuputWindow()
{
  float x, y;
  float width; 
  float height;
  float dx;
  float dy;
  float dw;
  float dh;

  x = con.screenMin[0];
  width = con.screenMax[0] - con.screenMin[0];
  y = con.screenMin[1] + 32.0;
  height = con.screenMax[1] - con.screenMin[1] - 32.0;
  ConDraw_Box(con.screenMin[0], con.screenMin[1] + 32.0, con.screenMax[0] - con.screenMin[0], height, con_outputWindowColor->current.vector);
  dx = x + 6.0;
  dy = y + 6.0;
  dw = width - 6.0 * 2.0;
  dh = height - 6.0 * 2.0;
  Con_DrawOutputVersion(dx, dy, dw, dh);
  Con_DrawOutputScrollBar(dx, dy, dw, dh);
  Con_DrawOutputText(dx, dy);
}

void ConDrawInput_Box(int lines, const float *color)
{
  ConDraw_Box(conDrawInputGlob.x - 6.0, conDrawInputGlob.y - 6.0,
    (con.screenMax[0] - con.screenMin[0]) - ((conDrawInputGlob.x - 6.0) - con.screenMin[0]),
    (float)lines * conDrawInputGlob.fontHeight + 2.0 * 6.0, color);
}

void ConDrawInput_TextAndOver(const char *str, const float *color)
{
  assert(str);

  ConDrawInput_Text(str, color);
  conDrawInputGlob.x = (float)ConDrawInput_TextWidth(str) + conDrawInputGlob.x;
}

bool Con_IsAutoCompleteMatch(const char *query, const char *matchToText, int matchTextLen)
{
  int matchLetter;
  int matchTextPos;
  const char *queryPos;

  assert(query);
  assert(matchToText);
  assert(matchTextLen);

  if ( con_ignoreMatchPrefixOnly || !con_matchPrefixOnly->current.enabled )
  {
    matchTextPos = 0;
    matchLetter = tolower(matchToText[0]);
    for ( queryPos = query; queryPos[0]; ++queryPos )
    {
      if ( tolower(queryPos[0]) == matchLetter )
      {
        if ( ++matchTextPos == matchTextLen )
        {
            return true;
        }
        matchLetter = tolower(matchToText[matchTextPos]);
      }
      else if ( con_matchPrefixOnly->current.enabled )
      {
        if ( matchTextPos )
        {
          matchTextPos = 0;
          matchLetter = tolower(matchToText[0]);
        }
      }
    }
    return false;
  }
  return Q_stricmpn(query, matchToText, matchTextLen) == 0;
}

void ConDrawInput_IncrMatchCounter(const char *str)
{
  if ( Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen) )
  {
    if ( conDrawInputGlob.matchCount == conDrawInputGlob.matchIndex )
    {
      Q_strncpyz(conDrawInputGlob.autoCompleteChoice, str, sizeof(conDrawInputGlob.autoCompleteChoice));
    }
    ++conDrawInputGlob.matchCount;
    if ( !str[conDrawInputGlob.inputTextLen] )
    {
      conDrawInputGlob.hasExactMatch = true;
    }
  }
}

void Con_DrawInputPrompt(int localClientNum)
{
  Field_Draw(localClientNum, &g_consoleField, (signed int)conDrawInputGlob.x, (signed int)conDrawInputGlob.y, 5, 5);
}

int Con_GetAutoCompleteColorCodedStringContiguous(const char *query, const char *matchToText, int matchTextLen, char *colorCoded)
{
  int colorpos;
  int colorCodedPos;
  const char *queryPos;
  int len;

  assert(query);
  assert(matchToText);
  assert(matchTextLen);

  colorCodedPos = 0;
  queryPos = Q_stristr(query, matchToText);
  if ( queryPos )
  {
    strncpy(colorCoded, query, queryPos - query);
    strcpy(&colorCoded[queryPos - query], "^2");
    len = strlen(matchToText);
    colorpos = queryPos - query + 2;
    strncpy(&colorCoded[colorpos], queryPos, len);
    colorpos += len;

    strcpy(&colorCoded[colorpos], "^7");
    colorCodedPos = colorpos + 2;
    strcpy(&colorCoded[colorCodedPos], &queryPos[len]);
    colorpos = strlen(&queryPos[len]) + colorCodedPos;
    colorCoded[colorpos] = ' ';
    colorCodedPos = colorpos + 1;
    colorCoded[colorCodedPos] = 0;
  }
  else
  {
    assert(strlen( query ) > 0);
    strcpy(colorCoded, query);
  }
  assert(strlen( colorCoded ) > 0);
  return colorCodedPos;
}

int Con_GetAutoCompleteColorCodedStringDiscontiguous(const char *query, const char *matchToText, int matchTextLen, char *colorCoded)
{
  int matchLetter;
  int colorCodedPos;
  bool wasMatching;
  int matchTextPos;
  const char *queryPos;
  bool isMatching;

  assert(query);
  assert(matchToText);
  assert(matchTextLen);

  wasMatching = 0;
  matchTextPos = 0;
  colorCodedPos = 0;
  matchLetter = tolower(matchToText[0]);
  for ( queryPos = query; queryPos[0]; ++queryPos )
  {
    isMatching = tolower(*queryPos) == matchLetter;
    if ( isMatching )
    {
      matchLetter = tolower(matchToText[++matchTextPos]);
    }
    if ( isMatching != wasMatching )
    {
      wasMatching = isMatching;
      if ( isMatching )
      {
        strcpy(&colorCoded[colorCodedPos], "^2");
      }
      else
      {
        strcpy(&colorCoded[colorCodedPos], "^7");
      }
      colorCodedPos += 2;
    }
    colorCoded[colorCodedPos++] = queryPos[0];
  }
  
  strcpy(&colorCoded[colorCodedPos], "^7");

  colorCodedPos += 2;
  colorCoded[colorCodedPos] = 32;
  colorCodedPos += 1;
  colorCoded[colorCodedPos] = 0;

  assert(strlen( colorCoded ) > 0);

  return colorCodedPos;
}

unsigned int Con_GetAutoCompleteColorCodedString(const char *query, const char *matchToText, int matchTextLen, bool isDvarCommand, const char *originalCommand, char *colorCoded)
{
  unsigned int prefixLen;

  if ( isDvarCommand )
  {
    prefixLen = sprintf(colorCoded, "^2%s ", originalCommand);
  }
  else
  {
    prefixLen = 0;
  }
  if ( con_matchPrefixOnly->current.enabled )
  {
    return prefixLen + Con_GetAutoCompleteColorCodedStringContiguous(query, matchToText, matchTextLen, &colorCoded[prefixLen]);
  }
  return prefixLen + Con_GetAutoCompleteColorCodedStringDiscontiguous(query, matchToText, matchTextLen, &colorCoded[prefixLen]);
}

void Con_DrawAutoCompleteChoice(int localClientNum, bool isDvarCommand, const char *originalCommand)
{
  int drawLen;
  char colorCodedLine[256];
  int cursorPos;
  int x;
  int y;

  cursorPos = Con_GetAutoCompleteColorCodedString(conDrawInputGlob.autoCompleteChoice, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen, isDvarCommand, originalCommand, colorCodedLine);
  x = (signed int)conDrawInputGlob.x;
  y = (signed int)conDrawInputGlob.y;

  assert(strlen( colorCodedLine ) > 0);

  drawLen = SEH_PrintStrlen(colorCodedLine);

  assertx(drawLen > 0, "(colorCodedLine) = %s", colorCodedLine);

  Field_DrawTextOverride(localClientNum, &g_consoleField, x, y, 5, 5, colorCodedLine, drawLen, cursorPos);
}

void ConDrawInput_TextLimitChars(const char *str, int maxChars, const float *color)
{
    assert(str);
    R_AddCmdDrawText(str, maxChars, cls.consoleFont, conDrawInputGlob.x, conDrawInputGlob.y + conDrawInputGlob.fontHeight, 1.0, 1.0, 0.0, color, 0);
}

int ConDrawInput_GetDvarDescriptionLines(dvar_s *dvar)
{
  int linecount;
  int index;
  int len;

  assert(dvar->description);

  len = strlen(dvar->description);
  linecount = 1;
  for ( index = 0; index < len; ++index )
  {
    if ( dvar->description[index] == 10 )
    {
      ++linecount;
    }
  }
  return linecount;
}

void ConDrawInput_DetailedDvarMatch(const char *str)
{
  DvarLimits domain;
  bool hasLatchedValue;
  int infoLineCount;
  char dvarInfo[1024];
  int descriptionLineCount;
  dvar_s *dvar;
  int lineIndex;

  assert(str);

  if ( Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen) && (!conDrawInputGlob.hasExactMatch || !str[conDrawInputGlob.inputTextLen]) )
  {
    dvar = Dvar_FindVar(str);

    assert(dvar);

    hasLatchedValue = Dvar_HasLatchedValue(dvar);
    if ( hasLatchedValue )
    {
      ConDrawInput_Box(3, con_inputHintBoxColor->current.vector);
    }
    else
    {
      ConDrawInput_Box(2, con_inputHintBoxColor->current.vector);
    }
    ConDrawInput_TextLimitChars(str, 24, con_inputDvarMatchColor);
    conDrawInputGlob.x = conDrawInputGlob.x + 200.0;

    ConDrawInput_TextLimitChars(Dvar_DisplayableValue(dvar), 40, con_inputDvarValueColor);
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.x = conDrawInputGlob.leftX;
    if ( hasLatchedValue )
    {
      ConDrawInput_Text("  latched value", con_inputDvarInactiveValueColor);
      conDrawInputGlob.x = conDrawInputGlob.x + 200.0;
      ConDrawInput_TextLimitChars(Dvar_DisplayableLatchedValue(dvar), 40, con_inputDvarInactiveValueColor);
      conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
      conDrawInputGlob.x = conDrawInputGlob.leftX;
    }
    ConDrawInput_Text("  default", con_inputDvarInactiveValueColor);
    conDrawInputGlob.x = conDrawInputGlob.x + 200.0;
    ConDrawInput_TextLimitChars(Dvar_DisplayableResetValue(dvar), 40, con_inputDvarInactiveValueColor);
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.x = conDrawInputGlob.leftX;

    domain.imin = dvar->imin;
    domain.imax = dvar->imax;
    Dvar_DomainToString_GetLines(dvar->type, domain, dvarInfo, sizeof(dvarInfo), &infoLineCount);
    if ( dvar->description )
    {
      descriptionLineCount = ConDrawInput_GetDvarDescriptionLines(dvar);
    }
    else
    {
      descriptionLineCount = 0;
    }
    ConDrawInput_Box(descriptionLineCount + infoLineCount + 1, con_inputHintBoxColor->current.vector);
    if ( dvar->description )
    {
      ConDrawInput_Text(dvar->description, con_inputDvarDescriptionColor);
      for ( lineIndex = 0; lineIndex < descriptionLineCount; ++lineIndex )
      {
        conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
        conDrawInputGlob.x = conDrawInputGlob.leftX;
      }
    }
    ConDrawInput_Text(dvarInfo, con_inputDvarInfoColor);
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.x = conDrawInputGlob.leftX;
    if ( dvar->type == CVAR_ENUM && Cmd_Argc() == 2 )
    {
      ConDrawInput_AutoCompleteArg(dvar->enumStrings, dvar->enumCount);
    }
  }
}


void ConDrawInput_DvarMatch(const char *str)
{
  assert(str);

  if ( Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen) )
  {
    ConDrawInput_TextLimitChars(str, 24, con_inputDvarMatchColor);
    conDrawInputGlob.x = conDrawInputGlob.x + 200.0;
    ConDrawInput_TextLimitChars(Dvar_GetVariantString(str), 40, con_inputDvarValueColor);
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.x = conDrawInputGlob.leftX;
  }
}


void ConDrawInput_DetailedCmdMatch(const char *str)
{
  int fileCount;
  const char **files;

  assert(str);

  if ( Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen) && (!conDrawInputGlob.hasExactMatch || !str[conDrawInputGlob.inputTextLen]) )
  {
    ConDrawInput_Box(1, con_inputHintBoxColor->current.vector);
    ConDrawInput_Text(str, con_inputCommandMatchColor);
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.x = conDrawInputGlob.leftX;
    if ( Cmd_Argc() == 2 )
    {
      files = Cmd_GetAutoCompleteFileList(str, &fileCount, 11);
      if ( fileCount )
      {
        ConDrawInput_AutoCompleteArg(files, fileCount);
        FS_FreeFileList(files);
      }
    }
  }
}

void ConDrawInput_CmdMatch(const char *str)
{
  assert(str);

  if ( Con_IsAutoCompleteMatch(str, conDrawInputGlob.inputText, conDrawInputGlob.inputTextLen) )
  {
    ConDrawInput_Text(str, con_inputCommandMatchColor);
    conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
    conDrawInputGlob.x = conDrawInputGlob.leftX;
  }
}

bool Con_AnySpaceAfterCommand()
{
  int charIndex;

  for ( charIndex = 0; isspace(g_consoleField.buffer[charIndex]); ++charIndex );
  
  while ( g_consoleField.buffer[charIndex] )
  {
    if ( isspace(g_consoleField.buffer[charIndex]) )
    {
      return true;
    }
    ++charIndex;
  }
  return false;
}

void Con_DrawInput(int localClientNum)
{
  const char *promptString;
  int inputTextLenPrev;
  char *tooManyMatchesStr;
  bool isDvarArgument;
  int matchCount;
  const char *originalCommand;

  assert(Sys_IsMainThread() || Sys_IsRenderThread());

  if ( Key_IsCatcherActive(localClientNum, 1) )
  {
    promptString = ">";
    conDrawInputGlob.fontHeight = (float)R_TextHeight(cls.consoleFont);
    conDrawInputGlob.x = con.screenMin[0] + 6.0;
    conDrawInputGlob.y = con.screenMin[1] + 6.0;
    conDrawInputGlob.leftX = con.screenMin[0] + 6.0;
    ConDrawInput_Box(1, con_inputBoxColor->current.vector);
    ConDrawInput_TextAndOver(promptString, con_versionColor);
    conDrawInputGlob.leftX = conDrawInputGlob.x;
    g_consoleField.widthInPixels = (signed int)(con.screenMax[0] - 6.0 - conDrawInputGlob.x);
    inputTextLenPrev = conDrawInputGlob.inputTextLen;
    conDrawInputGlob.inputText = Con_TokenizeInput();
    conDrawInputGlob.inputTextLen = strlen(conDrawInputGlob.inputText);
    conDrawInputGlob.autoCompleteChoice[0] = 0;
    if ( inputTextLenPrev != conDrawInputGlob.inputTextLen )
    {
      Con_CancelAutoComplete();
    }
    if ( conDrawInputGlob.inputTextLen )
    {
      originalCommand = conDrawInputGlob.inputText;
      isDvarArgument = Cmd_Argc() > 1 && Con_IsDvarCommand(conDrawInputGlob.inputText);
      if ( !isDvarArgument || (conDrawInputGlob.inputText = Cmd_Argv(1), (conDrawInputGlob.inputTextLen = strlen(conDrawInputGlob.inputText)) != 0) )
      {
        if ( con_matchPrefixOnly->current.enabled )
        {
          conDrawInputGlob.hasExactMatch = 0;
          conDrawInputGlob.matchCount = 0;
          con_ignoreMatchPrefixOnly = 1;
          Con_ForEach(isDvarArgument, ConDrawInput_IncrMatchCounter, ConDrawInput_IncrMatchCounter);
          if ( conDrawInputGlob.matchCount > con_inputMaxMatchesShown )
          {
            conDrawInputGlob.hasExactMatch = 0;
            conDrawInputGlob.matchCount = 0;
            con_ignoreMatchPrefixOnly = 0;
            Con_ForEach(0, ConDrawInput_IncrMatchCounter, ConDrawInput_IncrMatchCounter);
            if ( !conDrawInputGlob.matchCount )
            {
              conDrawInputGlob.hasExactMatch = 0;
              conDrawInputGlob.matchCount = 0;
              con_ignoreMatchPrefixOnly = 1;
              Con_ForEach(isDvarArgument, ConDrawInput_IncrMatchCounter, ConDrawInput_IncrMatchCounter);
            }
          }
        }
        else
        {
          conDrawInputGlob.hasExactMatch = 0;
          conDrawInputGlob.matchCount = 0;
          con_ignoreMatchPrefixOnly = 0;
          Con_ForEach(isDvarArgument, ConDrawInput_IncrMatchCounter, ConDrawInput_IncrMatchCounter);
        }
        matchCount = conDrawInputGlob.matchCount;
        if ( conDrawInputGlob.matchCount )
        {
          if ( conDrawInputGlob.matchIndex >= conDrawInputGlob.matchCount || !conDrawInputGlob.autoCompleteChoice[0] )
          {
            conDrawInputGlob.matchIndex = -1;
          }
          if ( conDrawInputGlob.matchIndex < 0 )
          {
            Con_DrawInputPrompt(localClientNum);
          }
          else
          {
            Con_DrawAutoCompleteChoice(localClientNum, isDvarArgument, originalCommand);
          }
          conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
          conDrawInputGlob.y = conDrawInputGlob.y + conDrawInputGlob.fontHeight;
          conDrawInputGlob.x = conDrawInputGlob.leftX;
          if ( matchCount <= con_inputMaxMatchesShown )
          {
            if ( matchCount == 1 || (conDrawInputGlob.hasExactMatch && Con_AnySpaceAfterCommand()) )
            {
              Con_ForEach(isDvarArgument, ConDrawInput_DetailedDvarMatch, ConDrawInput_DetailedCmdMatch);
            }
            else
            {
              ConDrawInput_Box(matchCount, con_inputHintBoxColor->current.vector);
              Con_ForEach(isDvarArgument, ConDrawInput_DvarMatch, ConDrawInput_CmdMatch);
            }
          }
          else
          {
            tooManyMatchesStr = va("%i matches (too many to show here, press shift+tilde to open full console)", matchCount);
            ConDrawInput_Box(1, con_inputHintBoxColor->current.vector);
            ConDrawInput_Text(tooManyMatchesStr, con_inputDvarMatchColor);
          }
          Cmd_EndTokenizedString();
        }
        else
        {
          Con_DrawInputPrompt(localClientNum);
          Cmd_EndTokenizedString();
        }
      }
      else
      {
        Con_AllowAutoCompleteCycling(0);
        Con_DrawInputPrompt(localClientNum);
        Cmd_EndTokenizedString();
      }
    }
    else
    {
      Con_AllowAutoCompleteCycling(0);
      Con_DrawInputPrompt(localClientNum);
      Cmd_EndTokenizedString();
    }
  }
}

void Con_DrawSolidConsole(int localClientNum)
{
  Sys_EnterCriticalSection(CRITSECT_CONSOLE);
  if ( con.lineOffset )
  {
    Con_Linefeed(localClientNum, con.prevChannel, 0);
  }
  Sys_LeaveCriticalSection(CRITSECT_CONSOLE);
  if ( !Key_IsCatcherActive(localClientNum, 1) )
  {
    con.outputVisible = 0;
  }
  if ( con.outputVisible )
  {
    Con_DrawOuputWindow();
  }
  Con_DrawInput(localClientNum);
}

void Con_DrawConsole(int localClientNum)
{
  Con_CheckResize();
  if ( Key_IsCatcherActive(localClientNum, 1) )
  {
    Con_DrawSolidConsole(localClientNum);
  }
}

bool Con_CycleAutoComplete(int step)
{
  if ( !conDrawInputGlob.mayAutoComplete || conDrawInputGlob.matchCount <= 1 || 
        conDrawInputGlob.matchCount >= con_inputMaxMatchesShown || 
        (conDrawInputGlob.hasExactMatch && Con_AnySpaceAfterCommand()) )
  {
    return false;
  }
  conDrawInputGlob.matchIndex += step;
  if ( conDrawInputGlob.matchIndex >= 0 )
  {
    if ( conDrawInputGlob.matchIndex >= conDrawInputGlob.matchCount )
    {
      conDrawInputGlob.matchIndex = 0;
    }
  }
  else
  {
    conDrawInputGlob.matchIndex = conDrawInputGlob.matchCount - 1;
  }
  return true;
}

bool Con_HasActiveAutoComplete()
{
  return conDrawInputGlob.matchIndex >= 0 && conDrawInputGlob.autoCompleteChoice[0];
}

bool Con_CommitToAutoComplete()
{
  const char *originalCommand;

  if ( !Con_HasActiveAutoComplete() )
  {
    return false;
  }
  originalCommand = Con_TokenizeInput();
  if ( Con_IsDvarCommand(originalCommand) )
  {
    Com_sprintf(g_consoleField.buffer, sizeof(g_consoleField.buffer), "%s %s", originalCommand, conDrawInputGlob.autoCompleteChoice);
  }
  else
  {
    Q_strncpyz(g_consoleField.buffer, conDrawInputGlob.autoCompleteChoice, sizeof(g_consoleField.buffer));
  }
  Cmd_EndTokenizedString();
  g_consoleField.cursor = strlen(g_consoleField.buffer);
  g_consoleField.buffer[g_consoleField.cursor++] = ' ';
  g_consoleField.buffer[g_consoleField.cursor] = 0;
  g_consoleField.drawWidth = SEH_PrintStrlen(g_consoleField.buffer);
  Con_CancelAutoComplete();
  return true;
}


void CL_ConsolePrint(int localClientNum, int channel, const char *txt, int duration, int pixelWidth, int flags)
{
  assert(txt);

  if ( cl_noprint && !cl_noprint->current.enabled && channel != CON_CHANNEL_LOGFILEONLY )
  {
    if(!Con_IsChannelOpen(channel))
    {
      return;
    }
    if ( !con.initialized )
    {
      Con_OneTimeInit();
      assert(con.initialized);
    }
    /*
    if ( Con_IsChannelVisible(CON_DEST_CONSOLE, channel, flags) )
      RConsWriteTextToRemote(txt);
    */
    Sys_EnterCriticalSection(CRITSECT_CONSOLE);
    CL_ConsolePrint_AddLine(localClientNum, channel, txt, duration, pixelWidth, CONSOLE_COLOR, flags);
    Sys_LeaveCriticalSection(CRITSECT_CONSOLE);
  }
}

