
#define MAX_KEYS 256
#define MAX_CON_HISTORY_COUNT 32

struct field_t
{
  int cursor;
  int scroll;
  int drawWidth;
  int widthInPixels;
  float charHeight;
  int fixedSize;
  char buffer[256];
};

struct qkey_t
{
  qboolean down;
  int repeats;
  int binding;
};

enum LocSelInputState_t
{
  LOC_SEL_INPUT_NONE = 0x0,
  LOC_SEL_INPUT_CONFIRM = 0x1,
  LOC_SEL_INPUT_CANCEL = 0x2,
};


typedef struct PlayerKeyState_s
{
  field_t chatField;
  int chat_team;
  int overstrikeMode;
  int anyKeyDown;
  qkey_t keys[MAX_KEYS];
  LocSelInputState_t locSelInputState;
}PlayerKeyState_t;

extern PlayerKeyState_t playerKeys[1];
extern field_t g_consoleField;
extern field_t historyEditLines[MAX_CON_HISTORY_COUNT];
extern int g_console_field_width;
extern float g_console_char_height;

REGPARM(3) bool Field_CharEvent(int localClientNum, const ScreenPlacement *scrPlace, field_t *edit, int ch);
void Field_AdjustScroll(const ScreenPlacement *scrPlace, field_t *edit);
void Field_Clear(field_t *edit);
void Field_Draw(int localClientNum, field_t *edit, int x, int y, int horzAlign, int vertAlign);
void Field_DrawTextOverride(int localClientNum, const field_t *edit, int x, int y, int horzAlign, int vertAlign, const char *str, int drawLen, int cursorPos);
void FindMatches(const char *s);
void PrintMatches(const char *s);
bool Key_IsCatcherActive(int localClientNum, int mask);
