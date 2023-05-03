#ifndef __CVAR_H__
#define __CVAR_H__

#include "../q_shared.h"
/*
==========================================================

CVARS (console variables)

Many variables can be used for cheating purposes, so when
cheats is zero, force all unspecified variables to their
default values.
==========================================================
*/
// nothing outside the Cvar_*() functions should modify these fields!
#pragma pack(push, 1)

typedef enum{
    CVAR_BOOL,
    CVAR_FLOAT,
    CVAR_VEC2,
    CVAR_VEC3,
    CVAR_VEC4,
    CVAR_INT,
    CVAR_ENUM,
    CVAR_STRING,
    CVAR_COLOR
}cvarType_t;

union CvarValue
{
  bool enabled;
  int integer;
  unsigned int unsignedInt;
//  int64_t integer64;
//  uint64_t unsignedInt64;
  float value;
  vec4_t vector;
  const char *string;
  ucolor_t color;
};


struct DvarLimits
{
	union{
		int imin;
		float fmin;
		int enumCount;
	};
	union{
		int imax;
		float fmax;
		const char** enumStrings;
	};
};



typedef struct dvar_s {
	const char *name;
	const char *description;
	short int flags;
	byte type;
	byte modified;
	CvarValue current;
	union{
		float latchedFloatval;
		int latchedInteger;
		const char* latchedString;
		byte latchedBoolean;
		vec2_t latchedVec2;
		vec3_t latchedVec3;
		vec4_t latchedVec4;
		ucolor_t latchedColor;
	};
	union{
		float resetFloatval;
		int resetInteger;
		const char* resetString;
		byte resetBoolean;
		vec2_t resetVec2;
		vec3_t resetVec3;
		vec4_t resetVec4;
		ucolor_t resetColor;
	};
	union{
		int imin;
		float fmin;
		int enumCount;
	};
	union{
		int imax;
		float fmax;
		const char** enumStrings;
	};
	byte (*domainFunc)(struct dvar_s *, CvarValue);
	struct dvar_s *hashNext;
} cvar_t;

#pragma pack(pop)
extern int cvar_modifiedFlags;


enum DvarSetSource
{
	DVAR_SOURCE_INTERNAL,
	DVAR_SOURCE_EXTERNAL,
	DVAR_SOURCE_SCRIPT,
	DVAR_SOURCE_DEVGUI
};


//Defines Cvarrelated functions inside executable file
cvar_t* Dvar_RegisterString(const char *var_name, const char *var_value, unsigned short flags, const char *var_description);
cvar_t* Dvar_RegisterBool(const char *var_name, byte var_value, unsigned short flags, const char *var_description);
cvar_t* Dvar_RegisterInt(const char *var_name, int var_value, int min_value, int max_value, unsigned short flags, const char *var_description);
cvar_t* Dvar_RegisterEnum(const char *var_name, const char** valnames, int defaultval, unsigned short flags, const char *var_description);
cvar_t* Dvar_RegisterFloat(const char *var_name, float var_value, float min_value, float max_value, unsigned short flags, const char *var_description);
cvar_t* Dvar_RegisterVec2(const char* name, float x, float y, float min, float max, unsigned short flags, const char* description);
cvar_t* Dvar_RegisterVec3(const char* name, float x, float y, float z, float min, float max, unsigned short flags, const char* description);
cvar_t* Dvar_RegisterVec4(const char* name, float x, float y, float z, float imag, float min, float max, unsigned short flags, const char* description);
cvar_t* Dvar_RegisterColor(const char* name, float r, float g, float b, float alpha, unsigned short flags, const char* description);

void Dvar_SetInt(const dvar_s* var, int val);
void Dvar_SetBool(const dvar_s* var, bool val);
void Dvar_SetString(const dvar_s* var, char const* string);
void Dvar_SetFloat(const dvar_s* var, float val);
void Dvar_SetVec2(const dvar_s* cvar, float x, float y);
void Dvar_SetVec3(const dvar_s* cvar, float x, float y, float z);
void Dvar_SetVec4(const dvar_s* cvar, float x, float y, float z, float imag);
void Dvar_SetColor(const dvar_s* cvar, float red, float green, float blue, float alpha);
void Dvar_Set_f(void);
void Dvar_SetS_f(void);
void Dvar_Toggle_f(void);
void Dvar_TogglePrint_f(void);
void Dvar_SetA_f(void);
void Dvar_SetFromDvar_f(void);
void Dvar_SetFromLocalizedStr_f(void);
void Dvar_SetToTime_f(void);
void Dvar_Reset_f(void);
void Dvar_ResetVar(const dvar_s* var);
void Dvar_List_f(void);
void Dvar_Dump_f(void);
void Dvar_RegisterBool_f(void);
void Dvar_RegisterInt_f(void);
void Dvar_RegisterFloat_f(void);
void Dvar_SetU_f(void);
qboolean Dvar_Command( void );
int  g_cvar_valueforkey(char* key);
char* Dvar_InfoString(int bit);
char* Dvar_InfoString_IW_Wrapper(int dummy, int bit);
void Dvar_ForEach(void (*callback)(dvar_s const*, void* passedhere), void* passback);
char* Dvar_DisplayableValue(const dvar_s*);
const char* Dvar_GetVariantString(const char* name);
dvar_s* Dvar_FindMalleableVar(const char* name);
void Dvar_Init(void);
void Dvar_CommandCompletion( void(*callback)(const char *s) );
const char *Dvar_VariableString( const char *var_name );
float Dvar_VariableValue( const char *var_name );
int Dvar_VariableIntegerValue( const char *var_name );
qboolean Dvar_VariableBooleanValue( const char *var_name );
dvar_s* Dvar_Set( const char *var_name, const char *value);
void Dvar_SetAllowCheatOnly( const char *var_name, const char *value);
void Dvar_Reset(const dvar_s* cvar);
void Dvar_ResetByName(const char* var_name);

void Dvar_SetFloatByName( const char* var_name, float value);
void Dvar_SetIntByName( const char* var_name, int value);
void Dvar_SetBoolByName( const char* var_name, unsigned char value);
void Dvar_SetStringByName( const char* var_name, const char* val);
dvar_s *Dvar_FindVar( const char *var_name );
qboolean Dvar_ValidateString( const char *s );
void Dvar_AddFlags(const dvar_s* var, int flags);
void Dvar_AddFlagsByName(const char* var_name, unsigned short flags);
void Dvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );
dvar_s* Dvar_FindMalleable(const char* name);
void Dvar_ClearModified(const dvar_s* cvar);
char* Dvar_GetValueAsString(char* name);
qboolean Dvar_ValueEqualStringToString(const char *varname, const char* ctx, const char * str1, const char *str2);
dvar_s* Dvar_SetFromStringByNameFromSource(const char* var, const char* valstr, DvarSetSource setsrc);
dvar_s * Dvar_SetFromStringByNameFromSource(const char *dvarName, const char *string, DvarSetSource source, uint16_t flags);
void Dvar_SetStringByName(const char *var_name, const char *valuestr);
void Dvar_SetCheatState();
const char *Dvar_ToString(const dvar_s *var);
void Dvar_GetUnpackedColorByName(const char* name, float *expandedColor);
void Dvar_GetUnpackedColor(const dvar_s *cvar, float *expandedColor);
int Dvar_GetInt(const char*);
#define Dvar_GetFloat Dvar_VariableValue
#define Dvar_GetString Dvar_VariableString
bool Dvar_GetBool(const char *dvarName);
//#define cvar_modifiedFlags 
//#define Dvar_InfoString(X,Y) Dvar_InfoString(Y)
void Dvar_ClearFlags(const dvar_s* var, int flags);
int Dvar_GetFlags (const dvar_s *var);
void Dvar_SetModified(dvar_s const* var);
qboolean Dvar_HasLatchedValue(const dvar_s *cvar);
bool Dvar_AnyLatchedValues();
void Dvar_SetFromStringFromSource(const dvar_s *dvar, const char *string, DvarSetSource source);
const char *Dvar_EnumToString(const dvar_s *dvar);
bool CheckDvarModified(dvar_s const*);
void Dvar_ForEachName(void (*callback)(const char *));
void Dvar_Sort();
void Dvar_ForEachConsoleAccessName(void (*callback)(const char *));
const char *Dvar_DisplayableLatchedValue(const dvar_s *dvar);
const char *Dvar_DisplayableResetValue(const dvar_s *dvar);
const char *Dvar_DomainToString_GetLines(unsigned char type, DvarLimits domain, char *outBuffer, int outBufferLen, int *outLineCount);
void Dvar_Shutdown();
/*
void __cdecl Cvar_SetInt(cvar_t const* var, int val);
void __cdecl Cvar_SetBool(cvar_t const* var, qboolean val);
void __cdecl Cvar_SetString(cvar_t const* var, char const* string);
void __cdecl Cvar_SetFloat(cvar_t const* var, float val);
void __cdecl Cvar_Set_f(void);
void __cdecl Cvar_SetS_f(void);
void __cdecl Cvar_Toggle_f(void);
void __cdecl Cvar_TogglePrint_f(void);
void __cdecl Cvar_SetA_f(void);
void __cdecl Cvar_SetFromCvar_f(void);
void __cdecl Cvar_SetFromLocalizedStr_f(void);
void __cdecl Cvar_SetToTime_f(void);
void __cdecl Cvar_Reset_f(void);
void __cdecl Cvar_List_f(void);
void __cdecl Cvar_Dump_f(void);
void __cdecl Cvar_RegisterBool_f(void);
void __cdecl Cvar_RegisterInt_f(void);
void __cdecl Cvar_RegisterFloat_f(void);
void __cdecl Cvar_SetU_f(void);
int __cdecl g_cvar_valueforkey(char* key);
char* __cdecl Cvar_InfoString(int unk, int bit);
void __cdecl Cvar_ForEach(void (*callback)(cvar_t const*, void* passedhere), void* passback);
char* __cdecl Cvar_DisplayableValue(cvar_t const*);
char* __cdecl Cvar_GetVariantString(const char* name);
cvar_t* __regparm1 Cvar_FindMalleableVar(const char* name);
void Cvar_Init(void);
*/

//defines Cvarflags
#define	CVAR_ARCHIVE		1	// set to cause it to be saved to vars.rc
								// used for system variables, not for player
								// specific configurations
#define	CVAR_USERINFO		2	// sent to server on connect or change
#define	CVAR_SERVERINFO		4	// sent in response to front end requests
#define	CVAR_SYSTEMINFO		8	// these cvars will be duplicated on all clients
#define	CVAR_INIT		16	// don't allow change from console at all,
								// but can be set from the command line
#define	CVAR_LATCH		32	// will only change when C code next does
								// a Cvar_Get(), so it can't be changed
								// without proper initialization.  modified
								// will be set, even though the value hasn't
								// changed yet
#define	CVAR_ROM		64	// display only, cannot be set by user at all
#define CVAR_CHEAT		128	// can not be changed if cheats are disabled
#define	CVAR_TEMP		256	// can be set even when cheats are disabled, but is not archived
#define CVAR_NORESTART		1024	// do not clear when a cvar_restart is issued
#define	CVAR_USER_CREATED	16384	// created by a set command
#define CVAR_UNRESTRICTED	65536	//Cvar that is not restricted to be changed by the user

#endif