
enum msgLocErrType_t
{
  LOCMSG_SAFE = 0x0,
  LOCMSG_NOERR = 0x1
};

const char*   SEH_LocalizeTextMessage(const char *pszInputBuffer, const char *pszMessageType, msgLocErrType_t errType);
const char*   SEH_StringEd_GetString(const char *pszReference);
int           SEH_GetCurrentLanguage();
int           SEH_PrintStrlen(const char *string);
int           SEH_DecodeLetter(unsigned int firstChar, unsigned int secondChar, int *usedCount, int *pbIsTrailingPunctuation);
void          SEH_UpdateLanguageInfo();
