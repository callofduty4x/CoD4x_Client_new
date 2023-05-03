;Imports of mac_common:
	extern opendir
	extern readdir
	extern closedir
	extern access
	extern mkdir

;Exports of mac_common:
	global _ZZ7Sys_CwdvE3cwd
	global _ZZ22Sys_DefaultInstallPathvE7exePath
	global _Z17Sys_DefaultCDPathv
	global _Z19Sys_DefaultHomePathv
	global _Z20Sys_InitStreamThreadv
	global _Z24Sys_DirectoryHasContentsPKc
	global _Z9Sys_MkdirPKc


SECTION .text


;Sys_DefaultCDPath()
_Z17Sys_DefaultCDPathv:
	push ebp
	mov ebp, esp
	mov eax, _cstring_null
	pop ebp
	ret

;Sys_DefaultHomePath()
_Z19Sys_DefaultHomePathv:
	push ebp
	mov ebp, esp
	xor eax, eax
	pop ebp
	ret
	nop


;Sys_InitStreamThread()
_Z20Sys_InitStreamThreadv:
	push ebp
	mov ebp, esp
	pop ebp
	ret
	nop
	add [eax], al

;Sys_DirectoryHasContents(char const*)
_Z24Sys_DirectoryHasContentsPKc:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x10
	mov eax, [ebp+0x8]
	mov [esp], eax
	call opendir
	mov ebx, eax
	test eax, eax
	jz _Z24Sys_DirectoryHasContentsPKc_10
	mov [esp], eax
	call readdir
	test eax, eax
	jz _Z24Sys_DirectoryHasContentsPKc_20
	cmp byte [eax+0x6], 0x4
	jz _Z24Sys_DirectoryHasContentsPKc_30
_Z24Sys_DirectoryHasContentsPKc_40:
	mov esi, 0x1
_Z24Sys_DirectoryHasContentsPKc_60:
	mov [esp], ebx
	call closedir
	mov eax, esi
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
_Z24Sys_DirectoryHasContentsPKc_10:
	xor esi, esi
	mov eax, esi
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
_Z24Sys_DirectoryHasContentsPKc_30:
	cmp byte [eax+0x8], 0x2e
	jnz _Z24Sys_DirectoryHasContentsPKc_40
_Z24Sys_DirectoryHasContentsPKc_50:
	mov [esp], ebx
	call readdir
	test eax, eax
	jz _Z24Sys_DirectoryHasContentsPKc_20
	cmp byte [eax+0x6], 0x4
	jnz _Z24Sys_DirectoryHasContentsPKc_40
	cmp byte [eax+0x8], 0x2e
	jz _Z24Sys_DirectoryHasContentsPKc_50
	jmp _Z24Sys_DirectoryHasContentsPKc_40
_Z24Sys_DirectoryHasContentsPKc_20:
	xor esi, esi
	jmp _Z24Sys_DirectoryHasContentsPKc_60


;Sys_Mkdir(char const*)
_Z9Sys_MkdirPKc:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call access
	test eax, eax
	jz _Z9Sys_MkdirPKc_10
	mov dword [esp+0x4], 0x1ff
	mov [esp], ebx
	call mkdir
_Z9Sys_MkdirPKc_10:
	add esp, 0x14
	pop ebx
	pop ebp
	ret


;Initialized global or static variables of mac_common:
SECTION .data
_ZZ22Sys_DefaultInstallPathvE7exePath: dd 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0


;Initialized constant data of mac_common:
SECTION .rdata


;Zero initialized global or static variables of mac_common:
SECTION .bss
_ZZ7Sys_CwdvE3cwd: resb 0x100


;All cstrings:
SECTION .rdata
_cstring_sys_listfiles:		db "Sys_ListFiles",0
_cstring_s:		db "%s",0
_cstring_ss:		db "%s/%s",0
_cstring_null:		db 0
_cstring_:		db ".",0
_cstring_1:		db "..",0



;All constant floats and doubles:
SECTION .rdata

