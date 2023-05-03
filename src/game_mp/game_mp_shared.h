struct gentity_s;

unsigned int GScr_AllocString(const char *s);
void CalculateRanks();
int GScr_GetStatusIconIndex(const char *pszIcon);
int GScr_GetHeadIconIndex(const char *pszIcon);
void G_EntUnlink(gentity_s *ent);

const char*  ClientConnect(int clnum, unsigned short clscriptid);  //Something simular to VM_Call


#define MAX_STATUS_ICONS 8
#define STATUS_ICON_CS 2259
#define HEAD_ICON_CS 2267
#define MAX_HEAD_ICONS 15