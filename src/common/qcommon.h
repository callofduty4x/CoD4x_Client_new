#include "cvar.h"
#include "qcommon_mem.h"

extern dvar_s* com_dedicated;
extern dvar_s* com_sv_running;
extern dvar_s* com_developer;
extern dvar_s* useFastFile;
extern dvar_s* com_wideScreen;

extern qboolean com_errorEntered;

struct cmd_function_s
{
	struct cmd_function_s   *next;
	const char              *name;
	const char				*autoCompleteDir;
	const char				*autoCompleteExt;
	void 					(*function)();
};

void Cmd_AddCommandInternal(const char *cmdName, void (*function)(), cmd_function_s *allocedCmd);

enum sysEventType_t: int {
	// SE_NONE must be zero
	SE_NONE = 0,	// evTime is still valid
	SE_KEY,			// evValue is a key code, evValue2 is the down flag
	SE_CHAR,		// evValue is an ascii char
	SE_CONSOLE		// evPtr is a char*
};


qboolean	CL_CDKeyValidate(const char* key1234, const char* key5);
void		Cmd_Shutdown();
void 		Cbuf_Execute(int localClientNum, int controllerIndex);

//===========================================================================

/*

Command execution takes a null terminated string, breaks it into tokens,
then searches for a command or variable that matches the first token.

*/

void	Cmd_Init (void);


void	Cmd_RemoveCommand( const char *cmd_name );

char 	*Cmd_CompleteCommand( const char *partial );
// attempts to match a partial command for automatic command line completion
// returns NULL if nothing fits

int			Cmd_Argc (void);
const char	*Cmd_Argv (int arg);
void		Cmd_ArgvBuffer( int arg, char *buffer, int bufferLength );
void		Cmd_ArgsBuffer( char *buffer, int bufferLength );
// The functions that execute commands get their parameters with these
// functions. Cmd_Argv () will return an empty string, not a NULL
// if arg > argc, so string operations are allways safe.

void		Cmd_TokenizeString( const char *text );
// Takes a null terminated string.  Does not need to be /n terminated.
// breaks the string up into arg tokens.
void		Cmd_EndTokenizedString();
// End the string. This is required after tokenization, Always
void		Cmd_ExecuteString( const char *text );
// Parses a single line of text into arguments and tries to execute it
// as if it was typed at the console
void 		Cmd_ForEach(void (*callback)(const char *));
void		Cmd_ForEachConsoleAccessName(void (*callback)(const char *));
const char **Cmd_GetAutoCompleteFileList(const char *cmdName, int *fileCount, int allocTrackType);

char*		Com_AllocEvent(int len);
void		Com_SyncThreads();
void		Com_Quit_f();
void 		Com_Close();
void 		Com_ForceSafeMode();
void		Com_SetCSV(int csv);
int 		Com_GetConfigureDvarNames(const char **text, char (*dvarNames)[32]);
void		Com_GetConfigureDvarValues(int dvarCount, const char **text, char (*dvarValues)[32]);
void		Com_SetConfigureDvars(int dvarCount, const char (*dvarNames)[32], const char (*dvarValues)[32]);
int			Com_GpuStringCompare(const char *wild, const char *s);
void 		Com_InitParse();
void		Com_Init(char* cmdline);
void 		Com_Frame();
bool		Com_FilterPath(const char *filter, const char *name, int casesensitive);



enum FsListBehavior_e
{
  FS_LIST_PURE_ONLY,
  FS_LIST_ALL
};

typedef enum {
	FS_SEEK_CUR,
	FS_SEEK_END,
	FS_SEEK_SET
} fsOrigin_t;

extern const dvar_s* fs_restrict;
extern const dvar_s* fs_basepath;
extern const dvar_s* fs_homepath;

void		FS_Shutdown( int closemfp );
void		FS_ShutDownIwdPureCheckReferences();
void		FS_ShutdownServerReferencedIwds();
void		FS_ShutdownServerReferencedFFs();
void		FS_ShutdownIwdPureCheckReferences();
void		FS_ShutdownServerIwdNames();
void		FS_FCloseLogFile(fileHandle_t h);

int			FS_FOpenFileReadStream(const char *filename, int *file);
void 		FS_FCloseFile(fileHandle_t h);
int 		FS_Seek(fileHandle_t f, long offset, fsOrigin_t origin);
unsigned int FS_FTell(fileHandle_t f);
int 		FS_Read(void *buffer, int len, fileHandle_t h);
void 		FS_BuildOSPath(const char *base, const char *game, const char *qpath, char *ospath);
long		FS_FOpenFileRead(const char* filename, fileHandle_t* returnhandle);
int     	FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode );


extern "C"
{
  int FS_ReadFile( const char *qpath, void **buffer );
  void FS_FreeFile( void *buffer );
  const char ** FS_ListFiles(const char *path, const char *extension, FsListBehavior_e behavior, int *numfiles, int dummyflag);
  void FS_FreeFileList(const char ** list);
}


void	    Sys_Error( const char *error, ...);
void		Sys_Sleep(int msec);


void Cbuf_AddText( int localclient, const char *text );
// Adds command text at the end of the buffer, does NOT add a final \n

void 		Com_StripExtension(const char *in, char *out);

//===========================================================================
/*
	Hunk
*/
struct HunkUser;
HunkUser*   Hunk_UserCreate(int maxSize, const char *name, unsigned char fixed, unsigned char unknown, int type);
int			Hunk_UserAlloc(HunkUser *user, int size, int alignment);
const char *Hunk_CopyString(HunkUser *user, const char *in);
void		RefreshQuitOnErrorCondition();

