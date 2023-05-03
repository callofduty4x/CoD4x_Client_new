;Imports of r_draw_bsp:
	extern rgp
	extern _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	extern _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	extern r_lightMap
	extern _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	extern _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	extern _Z22R_ReadPrimDrawSurfDataP13GfxReadCmdBufj
	extern sc_enable
	extern gfxRenderTargets
	extern _Z20R_SetReflectionProbe16GfxCmdBufContextj
	extern _Z13R_SetLightmap16GfxCmdBufContextj
	extern _Z25R_SetStreamsForBspSurfaceP18GfxCmdBufPrimStatePK14srfTriangles_t

;Exports of r_draw_bsp:
	global _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo


SECTION .text



;R_DrawBspDrawSurfs(unsigned int const*, GfxCmdBufState*, GfxDrawSurfListInfo const*)
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov eax, [ebp+0xc]
	add eax, 0x90
	mov [ebp-0x34], eax
	mov edx, [ebp+0x8]
	mov [ebp-0x2c], edx
	xor ecx, ecx
	xor esi, esi
	mov dword [ebp-0x3c], 0xffffffff
	mov dword [ebp-0x38], 0x0
	mov edx, [edx]
	mov [ebp-0x40], edx
	mov ebx, [ebp-0x2c]
	add ebx, 0x4
	mov [ebp-0x30], ebx
	test edx, edx
	jz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_10
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_70:
	mov eax, edx
	add eax, 0x1
	shr eax, 1
	lea eax, [ebx+eax*4]
	mov [ebp-0x2c], eax
	xor edi, edi
	jmp _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_20
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_60:
	mov ecx, ebx
	xor esi, esi
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_100:
	movzx eax, word [ebx+0xa]
	add esi, eax
	add edi, 0x1
	cmp [ebp-0x40], edi
	jz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_30
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_20:
	mov eax, rgp
	mov edx, [eax+0x20a0]
	mov ebx, [ebp-0x30]
	movzx eax, word [ebx+edi*2]
	lea ebx, [eax+eax*2]
	shl ebx, 0x4
	add ebx, [edx+0x294]
	mov eax, [ebp-0x3c]
	cmp eax, [ebx+0x4]
	jz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_40
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_90:
	test ecx, ecx
	jz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_50
	movzx eax, word [ecx+0x8]
	mov [ebp-0x24], eax
	mov [ebp-0x20], esi
	mov [esp+0x8], esi
	mov eax, [ecx+0xc]
	mov edx, [edx+0x14]
	lea eax, [edx+eax*2]
	mov [esp+0x4], eax
	mov edx, [ebp-0x34]
	mov [esp], edx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov eax, [ebp-0x34]
	mov [esp], eax
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_50:
	mov edx, [ebx+0xc]
	mov [ebp-0x38], edx
	mov esi, [ebx+0x4]
	cmp [ebp-0x3c], esi
	jz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_60
	mov [esp+0x4], ebx
	mov eax, [ebp-0x34]
	mov [esp], eax
	call _Z25R_SetStreamsForBspSurfaceP18GfxCmdBufPrimStatePK14srfTriangles_t
	mov ecx, ebx
	mov [ebp-0x3c], esi
	xor esi, esi
	movzx eax, word [ebx+0xa]
	add esi, eax
	add edi, 0x1
	cmp [ebp-0x40], edi
	jnz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_20
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_30:
	mov edx, [ebp-0x2c]
	mov edx, [edx]
	mov [ebp-0x40], edx
	mov ebx, [ebp-0x2c]
	add ebx, 0x4
	mov [ebp-0x30], ebx
	test edx, edx
	jnz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_70
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_10:
	test ecx, ecx
	jz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_80
	movzx eax, word [ecx+0x8]
	mov [ebp-0x24], eax
	mov [ebp-0x20], esi
	mov [esp+0x8], esi
	mov eax, rgp
	mov edx, [eax+0x20a0]
	mov eax, [ecx+0xc]
	mov edx, [edx+0x14]
	lea eax, [edx+eax*2]
	mov [esp+0x4], eax
	mov eax, [ebp-0x34]
	mov [esp], eax
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov edx, [ebp-0x34]
	mov [esp], edx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_80:
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_40:
	lea eax, [esi+esi*2]
	add eax, [ebp-0x38]
	cmp eax, [ebx+0xc]
	jnz _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_90
	jmp _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo_100
	add [eax], al



;Initialized constant data of r_draw_bsp:
SECTION .rdata



;Zero initialized global or static variables of r_draw_bsp:
SECTION .bss


;All cstrings:
SECTION .rdata



;All constant floats and doubles:
SECTION .rdata

