#ifndef _SCRIPT_SCR_SHARED_H_
#define _SCRIPT_SCR_SHARED_H_


#include <q_shared.h>

#ifndef SCR_ENTREF_DEFINED
#define SCR_ENTREF_DEFINED
typedef struct
{
  uint16_t entnum;
  uint16_t classnum;
}scr_entref_t;
#endif

struct gentity_s;

void SL_Shutdown();
void GScr_Shutdown();
void Scr_Shutdown();

void Scr_InitVariables(void);			//VM
void Scr_Init(void);			//VM_Init
void Scr_Settings(int, int, int);
void Scr_AddEntity(gentity_s* ent);
void Scr_Cleanup(void);
void GScr_Shutdown(void);
unsigned int Scr_AllocArray();
unsigned int AllocObject();
int Scr_GetNumParam( void );
int Scr_GetInt( unsigned int );
float Scr_GetFloat( unsigned int );
const char* Scr_GetString( unsigned int );
gentity_s* Scr_GetEntity( unsigned int );
unsigned int Scr_GetConstString( unsigned int );
unsigned int Scr_GetType( unsigned int );
unsigned int Scr_GetPointerType( unsigned int );
void Scr_GetVector( unsigned int, float* );
unsigned int Scr_GetObject( unsigned int );
void Scr_GetObjectField(unsigned int classnum, int entnum, int offset);
const char *Scr_GetIString(unsigned int index);

/* Scr_Error
 *
 * Throws script runtime error with 'string' description.
 * Asterisk points to function name.
 */
void Scr_Error( const char *string);
void Scr_SetLoading( qboolean );

/* Scr_ParamError
 *
 * Throws script runtime error with 'string' description.
 * Asterisk points to 'paramNum' function parameter.
 */
void Scr_ParamError( unsigned int paramNum, const char *string);

/* Scr_ObjectError
 *
 * Throws script runtime error with 'string' description.
 * Asterisk points to function caller.
 */
void Scr_ObjectError( const char *string);

void Scr_AddInt(int value);
void Scr_AddFloat(float);
void Scr_AddBool(bool);
void Scr_AddString(const char *string);
void Scr_AddConstString(unsigned int strindex);
void Scr_AddUndefined(void);
void Scr_AddVector( const float* vec );
void Scr_AddArray( void );
void Scr_MakeArray( void );
void Scr_AddArrayKeys( unsigned int strIdx );
void Scr_Notify( gentity_s*, unsigned short, unsigned int);
void Scr_NotifyNum( int, unsigned int, unsigned int, unsigned int);

enum varType_s
{
  VAR_UNDEFINED = 0x0,
  VAR_BEGIN_REF = 0x1,
  VAR_POINTER = 0x1,
  VAR_STRING = 0x2,
  VAR_ISTRING = 0x3,
  VAR_VECTOR = 0x4,
  VAR_END_REF = 0x5,
  VAR_FLOAT = 0x5,
  VAR_INTEGER = 0x6,
  VAR_CODEPOS = 0x7,
  VAR_PRECODEPOS = 0x8,
  VAR_FUNCTION = 0x9,
  VAR_STACK = 0xA,
  VAR_ANIMATION = 0xB,
  VAR_DEVELOPER_CODEPOS = 0xC,
  VAR_INCLUDE_CODEPOS = 0xD,
  VAR_THREAD = 0xE,
  VAR_NOTIFY_THREAD = 0xF,
  VAR_TIME_THREAD = 0x10,
  VAR_CHILD_THREAD = 0x11,
  VAR_OBJECT = 0x12,
  VAR_DEAD_ENTITY = 0x13,
  VAR_ENTITY = 0x14,
  VAR_ARRAY = 0x15,
  VAR_DEAD_THREAD = 0x16,
  VAR_COUNT = 0x17,
  VAR_THREAD_LIST = 0x18,
  VAR_ENDON_LIST = 0x19
};


enum scriptSystem_s
{
  SCR_SYS_GAME = 1
};


struct PrecacheEntry
{
  uint16_t filename;
  bool include;
  char pad;
  unsigned int sourcePos;
  char bytes[8192];
};



#endif