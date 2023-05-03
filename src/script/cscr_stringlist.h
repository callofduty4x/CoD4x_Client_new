bool SL_IsDebugging();
unsigned int SL_GetStringForFloat(float f);
unsigned int SL_GetStringForInt(int i);
unsigned int SL_GetStringForVector(const float *v);
int SL_GetStringLen(unsigned int stringValue);
void SL_Init(void);
void SL_RemoveRefToString( unsigned int );
const char* SL_ConvertToString(unsigned int index);
int SL_FindString(const char *string);
unsigned int SL_FindLowercaseString(const char *upperstring);
unsigned int SL_GetStringOfSize(const char *string, unsigned int user, unsigned int len, int type);
unsigned int SL_GetLowercaseString(const char *str, unsigned int type);
unsigned int SL_GetString(const char *str, unsigned int user);
float* Scr_AllocVectorInternal();
float *Scr_AllocVector(const float *v);
void SL_AddRefToString(unsigned int stringValue);
void AddRefToVector(const float *vectorValue);
void RemoveRefToVector(const float *vectorValue);
unsigned int SL_ConvertFromString(const char *str);
unsigned int SL_GetString_(const char *str, unsigned int user, int type);
void SL_SetScriptCompile(bool active);
void SL_ShutdownSystem(unsigned int user);
unsigned int Scr_CreateCanonicalFilename( const char* name );
void SL_SetIgnoreLeaks(bool enable);
void SL_TransferRefToUser(unsigned int stringValue, unsigned int user);

struct HashEntry;

struct __align(128) scrStringGlob_t
{
  HashEntry *hashTable;
  bool inited;
  HashEntry *nextFreeEntry;
  int indentLevel;
  int stringsUsed[32];
};

extern scrStringGlob_t gScrStringGlob;


