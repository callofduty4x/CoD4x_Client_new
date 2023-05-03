;Imports of scr_main:
	extern gScrCompilePub
	extern gScrAnimPub
	extern _Z17SL_ShutdownSystemj
	extern gScrVarPub
	extern _Z16Hunk_UserDestroyP8HunkUser
	extern _Z8I_iscsymi
	extern _Z11ClearObjectj
	extern _Z17RemoveRefToObjectj
	extern _Z14Scr_AllocArrayv
	extern _Z15Hunk_UserCreateiPKchhi
	extern _Z15TempMemoryResetP8HunkUser
	extern _Z10TempMalloci
	extern memset
	extern _Z13SL_FindStringPKc
	extern _Z13SL_GetString_PKcji
	extern _Z20SL_TransferRefToUserjj
	extern _Z12FindVariablejj
	extern _Z20SL_RemoveRefToStringj
	extern _Z10FindObjectj
	extern _Z22SL_FindLowercaseStringPKc
	extern _Z12GetValueTypej
	extern _Z22Scr_EvalVariableExternj
	extern _Z23Scr_LoadAnimTreeAtIndexjPFPviEi
	extern _Z14GetNewVariablejj
	extern _Z18SL_ConvertToStringj
	extern _Z11Com_sprintfPciPKcz
	extern gScrParserPub
	extern _Z11GetVariablejj
	extern _Z9GetObjectj

;Exports of scr_main:
	global _Z12Scr_ScanFilePci
	global _Z20Scr_EndLoadAnimTreesv
	global _Z21SL_GetCanonicalStringPKc
	global _Z21Scr_PrecacheAnimTreesPFPviEi
	global _Z22Scr_BeginLoadAnimTreesi
	global _Z22Scr_PostCompileScriptsv
	global _Z28SL_TransferToCanonicalStringj


SECTION .text


;Scr_ScanFile(char*, int)
_Z12Scr_ScanFilePci:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	mov edi, [ebp+0x8]
	mov esi, [ebp+0xc]
	test esi, esi
	jg Scr_ScanFile_10
	xor ecx, ecx
Scr_ScanFile_90:
	mov eax, ecx
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
Scr_ScanFile_10:
	mov ebx, gScrCompilePub
	mov eax, [ebx+0x20018]
	movzx edx, byte [eax]
	add eax, 0x1
	mov [ebx+0x20018], eax
	test dl, dl
	jnz Scr_ScanFile_20
	xor ecx, ecx
Scr_ScanFile_60:
	mov eax, [ebx+0x2001c]
	test eax, eax
	jz Scr_ScanFile_30
	mov [ebx+0x20018], eax
	mov dword [ebx+0x2001c], 0x0
	mov eax, ecx
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
Scr_ScanFile_20:
	cmp dl, 0xa
	jz Scr_ScanFile_40
	xor ecx, ecx
Scr_ScanFile_70:
	mov [edi+ecx], dl
	add ecx, 0x1
	cmp esi, ecx
	jz Scr_ScanFile_50
	mov eax, [ebx+0x20018]
	movzx edx, byte [eax]
	add eax, 0x1
	mov [ebx+0x20018], eax
	test dl, dl
	jz Scr_ScanFile_60
	cmp dl, 0xa
	jnz Scr_ScanFile_70
Scr_ScanFile_100:
	mov eax, ecx
	add ecx, 0x1
	mov byte [eax+edi], 0xa
Scr_ScanFile_80:
	mov eax, ecx
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
Scr_ScanFile_40:
	xor eax, eax
	mov ecx, 0x1
	mov byte [eax+edi], 0xa
	jmp Scr_ScanFile_80
Scr_ScanFile_30:
	sub dword [ebx+0x20018], 0x1
	jmp Scr_ScanFile_90
Scr_ScanFile_50:
	cmp dl, 0xa
	jz Scr_ScanFile_100
	test dl, dl
	jz Scr_ScanFile_60
	jmp Scr_ScanFile_90
	nop



;Scr_EndLoadAnimTrees()
_Z20Scr_EndLoadAnimTreesv:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, gScrAnimPub
	mov eax, [ebx]
	mov [esp], eax
	call _Z11ClearObjectj
	mov eax, [ebx]
	mov [esp], eax
	call _Z17RemoveRefToObjectj
	mov dword [ebx], 0x0
	mov eax, [ebx+0x4]
	test eax, eax
	jnz Scr_EndLoadAnimTrees_10
Scr_EndLoadAnimTrees_40:
	mov dword [esp], 0x2
	call _Z17SL_ShutdownSystemj
	mov ebx, gScrVarPub
	mov eax, [ebx+0x48]
	test eax, eax
	jz Scr_EndLoadAnimTrees_20
	mov ecx, [ebx+0x4c]
	test ecx, ecx
	jz Scr_EndLoadAnimTrees_30
Scr_EndLoadAnimTrees_20:
	mov eax, gScrAnimPub
	mov byte [eax+0x418], 0x0
	add esp, 0x14
	pop ebx
	pop ebp
	ret
Scr_EndLoadAnimTrees_10:
	mov [esp], eax
	call _Z17RemoveRefToObjectj
	jmp Scr_EndLoadAnimTrees_40
Scr_EndLoadAnimTrees_30:
	mov dword [esp], 0x0
	call _Z10TempMalloci
	mov [ebx+0x4c], eax
	mov eax, gScrAnimPub
	mov byte [eax+0x418], 0x0
	add esp, 0x14
	pop ebx
	pop ebp
	ret
	nop


;SL_GetCanonicalString(char const*)
_Z21SL_GetCanonicalStringPKc:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x10
	mov ebx, [ebp+0x8]
	mov [esp], ebx
	call _Z13SL_FindStringPKc
	mov esi, gScrCompilePub
	movzx eax, word [esi+eax*2+0x18]
	movzx edx, ax
	test ax, ax
	jz SL_GetCanonicalString_10
SL_GetCanonicalString_20:
	mov eax, edx
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
SL_GetCanonicalString_10:
	mov dword [esp+0x8], 0x10
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z13SL_GetString_PKcji
	mov ebx, eax
	mov dword [esp+0x4], 0x2
	mov [esp], eax
	call _Z20SL_TransferRefToUserjj
	movzx eax, word [esi+ebx*2+0x18]
	movzx edx, ax
	test ax, ax
	jnz SL_GetCanonicalString_20
	mov edx, gScrVarPub
	movzx eax, word [edx+0x4]
	add eax, 0x1
	mov [edx+0x4], ax
	mov [esi+ebx*2+0x18], ax
	movzx edx, ax
	mov eax, edx
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
	add [eax], al


;Scr_PrecacheAnimTrees(void* (*)(int), int)
_Z21Scr_PrecacheAnimTreesPFPviEi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x1c
	mov esi, [ebp+0xc]
	mov eax, gScrAnimPub
	mov edx, [eax+esi*4+0x40c]
	test edx, edx
	jnz Scr_PrecacheAnimTrees_10
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
Scr_PrecacheAnimTrees_10:
	mov ebx, 0x1
	mov edi, eax
Scr_PrecacheAnimTrees_20:
	mov [esp+0x8], esi
	mov eax, [ebp+0x8]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z23Scr_LoadAnimTreeAtIndexjPFPviEi
	add ebx, 0x1
	cmp [edi+esi*4+0x40c], ebx
	jae Scr_PrecacheAnimTrees_20
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;Scr_BeginLoadAnimTrees(int)
_Z22Scr_BeginLoadAnimTreesi:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x4
	mov eax, [ebp+0x8]
	mov ebx, gScrAnimPub
	mov byte [ebx+0x418], 0x1
	mov dword [ebx+eax*4+0x40c], 0x0
	shl eax, 0x9
	mov dword [eax+ebx+0xc], 0x0
	call _Z14Scr_AllocArrayv
	mov [ebx], eax
	mov dword [ebx+0x4], 0x0
	mov eax, gScrCompilePub
	mov dword [eax+0x20024], 0x0
	add esp, 0x4
	pop ebx
	pop ebp
	ret


;Scr_PostCompileScripts()
_Z22Scr_PostCompileScriptsv:
	push ebp
	mov ebp, esp
	pop ebp
	ret
	nop


;SL_TransferToCanonicalString(unsigned int)
_Z28SL_TransferToCanonicalStringj:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov dword [esp+0x4], 0x2
	mov [esp], ebx
	call _Z20SL_TransferRefToUserjj
	mov ecx, gScrCompilePub
	movzx eax, word [ecx+ebx*2+0x18]
	movzx edx, ax
	test ax, ax
	jnz SL_TransferToCanonicalString_10
	mov edx, gScrVarPub
	movzx eax, word [edx+0x4]
	add eax, 0x1
	mov [edx+0x4], ax
	mov [ecx+ebx*2+0x18], ax
	movzx edx, ax
SL_TransferToCanonicalString_10:
	mov eax, edx
	add esp, 0x14
	pop ebx
	pop ebp
	ret


;Initialized global or static variables of scr_main:
SECTION .data


;Initialized constant data of scr_main:
SECTION .rdata


;Zero initialized global or static variables of scr_main:
SECTION .bss


;All cstrings:
SECTION .rdata
_cstring_:		db "+",0



;All constant floats and doubles:
SECTION .rdata

