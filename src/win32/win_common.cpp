#include <string.h>
#include <direct.h>
#include "../q_shared.h"
#include "../common/qcommon.h"

/*
==============================================================

DIRECTORY SCANNING

==============================================================
*/

#define MAX_FOUND_FILES 0x1000


bool Sys_InDirExclusionList(const char* dir)
{
    if(strcmp(dir, ".") == 0 || strcmp(dir, "..") == 0 || strcmp(dir, "CVS") == 0)
    {
        return true;
    }
    return false;
}

/*
==============
Sys_ListFilteredFiles
==============
*/
void Sys_ListFilteredFiles( HunkUser* user, const char *basedir, const char *subdirs, const char *filter, const char **list, int *numfiles )
{
	char	search[MAX_OSPATH], newsubdirs[MAX_OSPATH];
	char	filename[MAX_OSPATH];
	intptr_t	findhandle;
	struct _finddata64i32_t findinfo;

	if ( *numfiles >= MAX_FOUND_FILES - 1 ) {
		return;
	}

	if (strlen(subdirs)) {
		Com_sprintf( search, sizeof(search), "%s\\%s\\*", basedir, subdirs );
	}
	else {
		Com_sprintf( search, sizeof(search), "%s\\*", basedir );
	}

	findhandle = _findfirst64i32 (search, &findinfo);
	if (findhandle == -1) {
		return;
	}

	do {
		if (findinfo.attrib & _A_SUBDIR) {

			if (!Sys_InDirExclusionList(findinfo.name)) {

				if (strlen(subdirs)) {
					Com_sprintf( newsubdirs, sizeof(newsubdirs), "%s\\%s", subdirs, findinfo.name);
				}
				else {
					Com_sprintf( newsubdirs, sizeof(newsubdirs), "%s", findinfo.name);
				}
				Sys_ListFilteredFiles( user, basedir, newsubdirs, filter, list, numfiles );
			}
		}
		if ( *numfiles >= MAX_FOUND_FILES - 1 ) {
			break;
		}
		Com_sprintf( filename, sizeof(filename), "%s\\%s", subdirs, findinfo.name );
		if (!Com_FilterPath( filter, filename, qfalse ))
			continue;
            
		list[ *numfiles ] = Hunk_CopyString( user, filename );
		(*numfiles)++;
	} while ( _findnext64i32 (findhandle, &findinfo) != -1 );

	_findclose (findhandle);
}

#if 0
void Sys_ListFilteredFilesW( const wchar_t *basedir, wchar_t *subdirs, wchar_t *filter, wchar_t **list, int *numfiles )
{
	wchar_t	search[MAX_OSPATH], newsubdirs[MAX_OSPATH];
	wchar_t	filename[MAX_OSPATH];
	intptr_t	findhandle;
	struct _wfinddata64i32_t findinfo;

	if ( *numfiles >= MAX_FOUND_FILES - 1 ) {
		return;
	}

	if (subdirs[0]) {
		Com_sprintfUni( search, sizeof(search), L"%s\\%s\\*", basedir, subdirs );
	}
	else {
		Com_sprintfUni( search, sizeof(search), L"%s\\*", basedir );
	}

	findhandle = _wfindfirst64i32 (search, &findinfo);
	if (findhandle == -1) {
		return;
	}

	do {
		if (findinfo.attrib & _A_SUBDIR) {

			if (wcscmp(findinfo.name, L".") && wcscmp(findinfo.name, L"..")) {

				if (wcslen(subdirs)) {
					Com_sprintfUni( newsubdirs, sizeof(newsubdirs), L"%s\\%s", subdirs, findinfo.name);
				}
				else {
					Com_sprintfUni( newsubdirs, sizeof(newsubdirs), L"%s", findinfo.name);
				}
				Sys_ListFilteredFilesW( basedir, newsubdirs, filter, list, numfiles );
			}
		}
		if ( *numfiles >= MAX_FOUND_FILES - 1 ) {
			break;
		}
		Com_sprintfUni( filename, sizeof(filename), L"%s\\%s", subdirs, findinfo.name );
		if (!Com_FilterPathW( filter, filename, qfalse ))
			continue;
		list[ *numfiles ] = _wcsdup( filename );
		(*numfiles)++;
	} while ( _wfindnext64i32 (findhandle, &findinfo) != -1 );

	_findclose (findhandle);
}

#endif

/*
==============
strgtr
==============
*/

static bool strgtr(const char *s0, const char *s1)
{
	int l0, l1, i;

	l0 = strlen(s0);
	l1 = strlen(s1);

	if (l1<l0) {
		l0 = l1;
	}

	for(i=0;i<l0;i++) {
		if (s1[i] > s0[i]) {
			return true;
		}
		if (s1[i] < s0[i]) {
			return false;
		}
	}
	return false;
}


qboolean strgtrw(const wchar_t *s0, const wchar_t *s1)
{
	int l0, l1, i;

	l0 = wcslen(s0);
	l1 = wcslen(s1);

	if (l1<l0) {
		l0 = l1;
	}

	for(i=0;i<l0;i++) {
		if (s1[i] > s0[i]) {
			return qtrue;
		}
		if (s1[i] < s0[i]) {
			return qfalse;
		}
	}
	return qfalse;
}

/*
==============
Sys_ListFiles
==============
*/
const char **Sys_ListFiles( const char *directory, const char *extension, const char *filter, int *numfiles, int wantsubs )
{
	char	search[MAX_OSPATH];
	int	nfiles;
	const char	**listCopy;
	const char	*list[MAX_FOUND_FILES];
	struct _finddata64i32_t findinfo;
	intptr_t	findhandle;
	int	flag;
	int	i;
    HunkUser *user;

	if (filter) {

		nfiles = 0;
        user = Hunk_UserCreate(0x20000, "Sys_ListFiles", 0, 0, 3);

		Sys_ListFilteredFiles(user, directory, "", filter, list, &nfiles );

		list[ nfiles ] = 0;
		*numfiles = nfiles;

		if (!nfiles)
        {
            Hunk_UserDestroy(user);
		    return NULL;
        }
        listCopy = (const char **)Hunk_UserAlloc(user, ( nfiles + 1 ) * sizeof( *listCopy ) + 4, 4);
        *listCopy = (char *)user;
        ++listCopy;
		for ( i = 0 ; i < nfiles ; i++ ) {
			listCopy[i] = list[i];
		}
		listCopy[i] = NULL;

		return listCopy;
	}

	if ( !extension) {
		extension = "";
	}

	// passing a slash as extension will find directories
	if ( extension[0] == '/' && extension[1] == 0 ) {
		extension = "";
		flag = 0;
	} else {
		flag = _A_SUBDIR;
	}

	Com_sprintf( search, sizeof(search), "%s\\*%s", directory, extension );

	// search
	nfiles = 0;

	findhandle = _findfirst64i32 (search, &findinfo);
	if (findhandle == -1) {
		*numfiles = 0;
		return NULL;
	}
    
    user = Hunk_UserCreate(0x20000, "Sys_ListFiles", 0, 0, 3);

	do {
		if ( (!wantsubs && flag ^ ( findinfo.attrib & _A_SUBDIR )) || (wantsubs && findinfo.attrib & _A_SUBDIR) ) {
			if ( nfiles == MAX_FOUND_FILES - 1 ) {
				break;
			}
            if(findinfo.attrib & _A_SUBDIR && Sys_InDirExclusionList(findinfo.name))
            {
                continue;
            }


			list[ nfiles ] = (char*)Hunk_CopyString( user, findinfo.name );
			nfiles++;
		}
	} while ( _findnext64i32 (findhandle, &findinfo) != -1 );

	list[ nfiles ] = 0;

	_findclose (findhandle);

	// return a copy of the list
	*numfiles = nfiles;

	if ( !nfiles ) {
        Hunk_UserDestroy(user);
		return NULL;
	}
    listCopy = (const char **)Hunk_UserAlloc(user, ( nfiles + 1 ) * sizeof( *listCopy ) + 4, 4);
    *listCopy = (char *)user;
    ++listCopy;
	for ( i = 0 ; i < nfiles ; i++ ) {
		listCopy[i] = list[i];
	}
	listCopy[i] = NULL;

	do {
		flag = 0;
		for(i=1; i<nfiles; i++) {
			if (strgtr(listCopy[i-1], listCopy[i])) {
				const char *temp = listCopy[i];
				listCopy[i] = listCopy[i-1];
				listCopy[i-1] = temp;
				flag = 1;
			}
		}
	} while(flag);

	return listCopy;
}


#if 0
/*
==============
Sys_ListFiles
==============
*/
wchar_t **Sys_ListFilesW( const wchar_t *directory, const wchar_t *extension, wchar_t *filter, int *numfiles, qboolean wantsubs )
{
	wchar_t	search[MAX_OSPATH];
	int	nfiles;
	wchar_t	**listCopy;
	wchar_t	*list[MAX_FOUND_FILES];
	struct _wfinddata64i32_t findinfo;
	intptr_t	findhandle;
	int	flag;
	int	i;

	if (filter) {

		nfiles = 0;
		Sys_ListFilteredFilesW( directory, L"", filter, list, &nfiles );

		list[ nfiles ] = 0;
		*numfiles = nfiles;

		if (!nfiles)
		return NULL;

		listCopy = Z_Malloc( ( nfiles + 1 ) * sizeof( *listCopy ) );
		for ( i = 0 ; i < nfiles ; i++ ) {
			listCopy[i] = list[i];
		}
		listCopy[i] = NULL;

		return listCopy;
	}

	if ( !extension) {
		extension = L"";
	}

	// passing a slash as extension will find directories
	if ( extension[0] == '/' && extension[1] == 0 ) {
		extension = L"";
		flag = 0;
	} else {
		flag = _A_SUBDIR;
	}

	Com_sprintfUni( search, sizeof(search), L"%s\\*%s", directory, extension );

	// search
	nfiles = 0;

	findhandle = _wfindfirst64i32 (search, &findinfo);
	if (findhandle == -1) {
		*numfiles = 0;
		return NULL;
	}

	do {
		if ( (!wantsubs && flag ^ ( findinfo.attrib & _A_SUBDIR )) || (wantsubs && findinfo.attrib & _A_SUBDIR) ) {
			if ( nfiles == MAX_FOUND_FILES - 1 ) {
				break;
			}
			list[ nfiles ] = _wcsdup( findinfo.name );
			nfiles++;
		}
	} while ( _wfindnext64i32 (findhandle, &findinfo) != -1 );

	list[ nfiles ] = 0;

	_findclose (findhandle);

	// return a copy of the list
	*numfiles = nfiles;

	if ( !nfiles ) {
		return NULL;
	}

	listCopy = Z_Malloc( ( nfiles + 1 ) * sizeof( *listCopy ) );
	for ( i = 0 ; i < nfiles ; i++ ) {
		listCopy[i] = list[i];
	}
	listCopy[i] = NULL;

	do {
		flag = 0;
		for(i=1; i<nfiles; i++) {
			if (strgtrw(listCopy[i-1], listCopy[i])) {
				wchar_t *temp = listCopy[i];
				listCopy[i] = listCopy[i-1];
				listCopy[i-1] = temp;
				flag = 1;
			}
		}
	} while(flag);

	return listCopy;
}
#endif


/*
==============
Sys_FreeFileList
==============
*/
void Sys_FreeFileList( const char **list )
{
	if ( !list ) {
		return;
	}
    HunkUser* user = (HunkUser*)*(list - 1);
    Hunk_UserDestroy(user);
}
/*
void Sys_FreeFileListW( wchar_t **list )
{
	int i;

	if ( !list ) {
		return;
	}

	for ( i = 0 ; list[i] ; i++ ) {
		free( list[i] );
	}

	Z_Free( list );
}
*/