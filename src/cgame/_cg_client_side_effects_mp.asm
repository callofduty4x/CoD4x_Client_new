;Imports of cg_client_side_effects_mp:
	extern _Z10I_strncpyzPcPKci
	extern _Z14Com_PrintErroriPKcz
	extern _Z19DB_FindXAssetHeader10XAssetTypePKc
	extern FS_ReadFile
	extern FS_FreeFile
	extern _Z12AnglesToAxisPKfPA3_f
	extern _Z17CG_PlaySoundAliasiiPKfP16snd_alias_list_t
	extern _Z14Dvar_GetStringPKc
	extern _Z11Com_sprintfPciPKcz
	extern useFastFile
	extern _Z17Dvar_RegisterBoolPKchtS0_
	extern _Z21CG_ParseClientEffectsiPKc
	extern _Z27CG_ParseClientEffectMappingPKc
	extern _Z35CG_LoadClientEffectMapping_FastFilePKc

;Exports of cg_client_side_effects_mp:
	global g_clientEntSounds
	global g_clientEntSoundCount
	global g_effectDefMapEntries
	global g_effectDefMap
	global _ZZ39CG_CopyClientSideSoundEntityOrientationiPfPA3_fE8zeroVec3
	global _Z34CG_LoadClientEffectMapping_LoadObjPKc
	global _Z29CG_LoadClientEffects_FastFileiPKc
	global _Z28CG_LoadClientEffects_LoadObjiPKc
	global _Z22CG_AddClientSideSoundsi
	global _Z25CG_StartClientSideEffectsi
	global _Z33CG_ClientSideEffectsRegisterDvarsv
	global _Z39CG_CopyClientSideSoundEntityOrientationiPfPA3_f
	global cg_clientSideEffects


SECTION .text



;CG_LoadClientEffectMapping_LoadObj(char const*)
_Z34CG_LoadClientEffectMapping_LoadObjPKc:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x24
	mov ebx, [ebp+0x8]
	lea eax, [ebp-0xc]
	mov [esp+0x4], eax
	mov [esp], ebx
	call FS_ReadFile
	test eax, eax
	js _Z34CG_LoadClientEffectMapping_LoadObjPKc_10
	mov eax, [ebp-0xc]
	call _Z27CG_ParseClientEffectMappingPKc
	mov eax, [ebp-0xc]
	mov [esp], eax
	call FS_FreeFile
	add esp, 0x24
	pop ebx
	pop ebp
	ret
_Z34CG_LoadClientEffectMapping_LoadObjPKc_10:
	mov [esp+0x8], ebx
	mov dword [esp+0x4], _cstring_file_not_found_s
	mov dword [esp], 0x1
	call _Z14Com_PrintErroriPKcz
	add esp, 0x24
	pop ebx
	pop ebp
	ret


;CG_LoadClientEffects_FastFile(int, char const*)
_Z29CG_LoadClientEffects_FastFileiPKc:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x10
	mov esi, [ebp+0x8]
	mov ebx, [ebp+0xc]
	mov [esp+0x4], ebx
	mov dword [esp], 0x1f
	call _Z19DB_FindXAssetHeader10XAssetTypePKc
	test eax, eax
	jz _Z29CG_LoadClientEffects_FastFileiPKc_10
	mov edx, [eax+0x8]
	mov eax, esi
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	jmp _Z21CG_ParseClientEffectsiPKc
_Z29CG_LoadClientEffects_FastFileiPKc_10:
	mov [esp+0x8], ebx
	mov dword [esp+0x4], _cstring_file_not_found_s
	mov dword [esp], 0x1
	call _Z14Com_PrintErroriPKcz
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
	nop


;CG_LoadClientEffects_LoadObj(int, char const*)
_Z28CG_LoadClientEffects_LoadObjiPKc:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x24
	mov ebx, [ebp+0xc]
	lea eax, [ebp-0xc]
	mov [esp+0x4], eax
	mov [esp], ebx
	call FS_ReadFile
	test eax, eax
	js _Z28CG_LoadClientEffects_LoadObjiPKc_10
	mov edx, [ebp-0xc]
	mov eax, [ebp+0x8]
	call _Z21CG_ParseClientEffectsiPKc
	mov eax, [ebp-0xc]
	mov [esp], eax
	call FS_FreeFile
	add esp, 0x24
	pop ebx
	pop ebp
	ret
_Z28CG_LoadClientEffects_LoadObjiPKc_10:
	mov [esp+0x8], ebx
	mov dword [esp+0x4], _cstring_file_not_found_s
	mov dword [esp], 0x1
	call _Z14Com_PrintErroriPKcz
	add esp, 0x24
	pop ebx
	pop ebp
	ret
	nop


;CG_AddClientSideSounds(int)
_Z22CG_AddClientSideSoundsi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x1c
	mov edi, [ebp+0x8]
	mov eax, [g_clientEntSoundCount]
	test eax, eax
	jg _Z22CG_AddClientSideSoundsi_10
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z22CG_AddClientSideSoundsi_10:
	xor esi, esi
	mov ebx, g_clientEntSounds
_Z22CG_AddClientSideSoundsi_20:
	mov eax, [ebx+0xc]
	mov [esp+0xc], eax
	mov [esp+0x8], ebx
	lea eax, [esi+0x400]
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z17CG_PlaySoundAliasiiPKfP16snd_alias_list_t
	add esi, 0x1
	add ebx, 0x10
	cmp [g_clientEntSoundCount], esi
	jg _Z22CG_AddClientSideSoundsi_20
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;CG_StartClientSideEffects(int)
_Z25CG_StartClientSideEffectsi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x11c
	xor eax, eax
	mov edx, [ebp+0x8]
	test edx, edx
	cmovnz eax, [g_clientEntSoundCount]
	mov [g_clientEntSoundCount], eax
	mov eax, [cg_clientSideEffects]
	cmp byte [eax+0xc], 0x0
	jz _Z25CG_StartClientSideEffectsi_10
	mov dword [esp], _cstring_mapname
	call _Z14Dvar_GetStringPKc
	mov edi, eax
	mov [esp+0xc], eax
	mov dword [esp+0x8], _cstring_mapsmps_fxgsc
	mov dword [esp+0x4], 0x100
	lea ebx, [ebp-0x118]
	mov [esp], ebx
	call _Z11Com_sprintfPciPKcz
	mov esi, useFastFile
	mov eax, [esi]
	mov edx, _Z35CG_LoadClientEffectMapping_FastFilePKc
	cmp byte [eax+0xc], 0x0
	mov eax, _Z34CG_LoadClientEffectMapping_LoadObjPKc
	cmovz edx, eax
	mov [esp], ebx
	call edx
	mov [esp+0xc], edi
	mov dword [esp+0x8], _cstring_mapscreatefxs_fx
	mov dword [esp+0x4], 0x100
	mov [esp], ebx
	call _Z11Com_sprintfPciPKcz
	mov eax, [esi]
	mov edx, _Z29CG_LoadClientEffects_FastFileiPKc
	cmp byte [eax+0xc], 0x0
	mov eax, _Z28CG_LoadClientEffects_LoadObjiPKc
	cmovz edx, eax
	mov [esp+0x4], ebx
	mov eax, [ebp+0x8]
	mov [esp], eax
	call edx
_Z25CG_StartClientSideEffectsi_10:
	add esp, 0x11c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;CG_ClientSideEffectsRegisterDvars()
_Z33CG_ClientSideEffectsRegisterDvarsv:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	mov dword [esp+0xc], _cstring_enable_loading__
	mov dword [esp+0x8], 0x80
	mov dword [esp+0x4], 0x1
	mov dword [esp], _cstring_clientsideeffect
	call _Z17Dvar_RegisterBoolPKchtS0_
	mov [cg_clientSideEffects], eax
	leave
	ret
	nop


;CG_CopyClientSideSoundEntityOrientation(int, float*, float (*) [3])
_Z39CG_CopyClientSideSoundEntityOrientationiPfPA3_f:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0xc]
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov dword [esp], _ZZ39CG_CopyClientSideSoundEntityOrientationiPfPA3_fE8zeroVec3
	call _Z12AnglesToAxisPKfPA3_f
	mov eax, [ebp+0x8]
	shl eax, 0x4
	lea edx, [eax+g_clientEntSounds]
	mov eax, [eax+g_clientEntSounds]
	mov [ebx], eax
	mov eax, [edx+0x4]
	mov [ebx+0x4], eax
	mov eax, [edx+0x8]
	mov [ebx+0x8], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
	nop


;Initialized global or static variables of cg_client_side_effects_mp:
SECTION .data


;Initialized constant data of cg_client_side_effects_mp:
SECTION .rdata


;Zero initialized global or static variables of cg_client_side_effects_mp:
SECTION .bss
g_clientEntSounds: resb 0x800
g_clientEntSoundCount: resb 0x4
g_effectDefMapEntries: resb 0x1c
g_effectDefMap: resb 0x1000
_ZZ39CG_CopyClientSideSoundEntityOrientationiPfPA3_fE8zeroVec3: resb 0x60
cg_clientSideEffects: resb 0x80


;All cstrings:
SECTION .rdata
_cstring_expected_a_quote:		db "Expected a quoted string instead of ",27h,"%s",27h,0ah,0
_cstring_string_was_longe:		db "String was longer than expected ",27h,"%s",27h,0ah,0
_cstring_file_not_found_s:		db "file not found: %s",0ah,0
_cstring_f_f_f:		db "%f, %f, %f",0
_cstring_expected_3_float:		db "Expected 3 floats instead of ",27h,"%s",27h,0ah,0
_cstring__createfx_genera:		db "//_createfx generated. Do not touch!!",0
_cstring_main:		db "main()",0
_cstring_:		db "{",0
_cstring_1:		db "//",0
_cstring_2:		db "}",0
_cstring_entv_soundalias_:		db "ent.v[ ",22h,"soundalias",22h," ] = ",0
_cstring_unexpected_text_:		db "Unexpected text ",27h,"%s",27h," when trying to find ",27h,"%s",27h," in map",27h,"s effect file",0ah,0
_cstring_ent__mapsmp_crea:		db "ent = maps",5ch,"mp",5ch,"_createfx::createLoopSound();",0
_cstring_ent__mapsmp_util:		db "ent = maps",5ch,"mp",5ch,"_utility::createOneshotEffect( ",0
_cstring_entv_origin___:		db "ent.v[ ",22h,"origin",22h," ] = (",0
_cstring_entv_angles___:		db "ent.v[ ",22h,"angles",22h," ] = (",0
_cstring_entv_fxid___:		db "ent.v[ ",22h,"fxid",22h," ] = ",0
_cstring_unexpected_data_:		db "Unexpected data after parsing ",27h,"%s",27h," map",27h,"s effect file",0ah,0
_cstring_entv_delay___:		db "ent.v[ ",22h,"delay",22h," ] = ",0
_cstring_f:		db "%f",0
_cstring_too_many_client_:		db "Too many client ent sounds.  Increase MAX_CLIENT_ENT_SOUNDS.",0ah,0
_cstring_expected_ent__ma:		db "Expected ",27h,"ent = maps",5ch,"mp",5ch,"_createfx::createLoopSound();",27h," or ",27h,"ent = maps",5ch,"mp",5ch,"_utility::createOneshotEffect",27h," instead of ",27h,"%s",27h," in map",27h,"s effect file",0ah,0
_cstring_expected_a_float:		db "Expected a float instead of ",27h,"%s",27h,0ah,0
_cstring_level_effect:		db "level._effect[",0
_cstring_3:		db "]",0
_cstring_4:		db "=",0
_cstring_loadfx:		db "loadfx",0
_cstring_5:		db "(",0
_cstring_tried_to_remap_s:		db "Tried to remap ",27h,"%s",27h," to ",27h,"%s",27h," previously mapped to ",27h,"%s",27h,0ah,0
_cstring_failed_to_added_:		db "Failed to added mapping from ",27h,"%s",27h," to ",27h,"%s",27h,".  Increase MAX_CLIENT_EFFECT_DEFS.",0ah,0
_cstring_mapname:		db "mapname",0
_cstring_mapsmps_fxgsc:		db "maps/mp/%s_fx.gsc",0
_cstring_mapscreatefxs_fx:		db "maps/createfx/%s_fx.gsc",0
_cstring_enable_loading__:		db "Enable loading _fx.gsc files on the client",0
_cstring_clientsideeffect:		db "clientSideEffects",0



;All constant floats and doubles:
SECTION .rdata
_float_1000_00000000:		dd 0x447a0000	; 1000

