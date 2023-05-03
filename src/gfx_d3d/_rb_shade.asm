;Imports of rb_shade:
	extern tess
	extern gfxCmdBufState
	extern pixelCostMode
	extern _Z35R_PixelCost_GetAccumulationMaterialPK8Material
	extern _Z18RB_DrawTessSurfacev
	
;Exports of rb_shade:
	global _Z15RB_BeginSurfacePK8Material21MaterialTechniqueType
	global _Z15RB_TessOverflowv
	global _Z17RB_EndTessSurfacev
	global _Z19RB_ClearPixelShaderv
	global _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType


SECTION .text


;RB_BeginSurface(Material const*, MaterialTechniqueType)
_Z15RB_BeginSurfacePK8Material21MaterialTechniqueType:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ecx, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov eax, tess
	mov dword [eax+0x22a950], 0x0
	mov dword [eax+0x22a954], 0x0
	mov ebx, gfxCmdBufState
	mov [ebx+0xb8], ecx
	mov [ebx+0xbc], edx
	mov dword [ebx+0x98], 0x0
	mov [ebx+0xa08], ecx
	mov [ebx+0xa0c], edx
	mov eax, pixelCostMode
	cmp dword [eax], 0x2
	jg _Z15RB_BeginSurfacePK8Material21MaterialTechniqueType_10
	mov eax, ecx
	mov eax, [eax+0x40]
	mov edx, [eax+0x8]
	mov eax, [ebx+0xbc]
	mov eax, [edx+eax*4+0xc]
	mov [ebx+0xc0], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z15RB_BeginSurfacePK8Material21MaterialTechniqueType_10:
	mov [esp], ecx
	call _Z35R_PixelCost_GetAccumulationMaterialPK8Material
	mov [ebx+0xb8], eax
	mov dword [ebx+0xbc], 0x4
	mov eax, [eax+0x40]
	mov edx, [eax+0x8]
	mov eax, [ebx+0xbc]
	mov eax, [edx+eax*4+0xc]
	mov [ebx+0xc0], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret


;RB_TessOverflow()
_Z15RB_TessOverflowv:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	call _Z18RB_DrawTessSurfacev
	mov ebx, gfxCmdBufState
	mov edx, [ebx+0xa0c]
	mov ecx, [ebx+0xa08]
	mov eax, tess
	mov dword [eax+0x22a950], 0x0
	mov dword [eax+0x22a954], 0x0
	mov [ebx+0xb8], ecx
	mov [ebx+0xbc], edx
	mov dword [ebx+0x98], 0x0
	mov eax, pixelCostMode
	cmp dword [eax], 0x2
	jg _Z15RB_TessOverflowv_10
	mov eax, ecx
	mov eax, [eax+0x40]
	mov edx, [eax+0x8]
	mov eax, [ebx+0xbc]
	mov eax, [edx+eax*4+0xc]
	mov [ebx+0xc0], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z15RB_TessOverflowv_10:
	mov [esp], ecx
	call _Z35R_PixelCost_GetAccumulationMaterialPK8Material
	mov [ebx+0xb8], eax
	mov dword [ebx+0xbc], 0x4
	mov eax, [eax+0x40]
	mov edx, [eax+0x8]
	mov eax, [ebx+0xbc]
	mov eax, [edx+eax*4+0xc]
	mov [ebx+0xc0], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
	add [eax], al


;RB_EndTessSurface()
_Z17RB_EndTessSurfacev:
	push ebp
	mov ebp, esp
	pop ebp
	jmp _Z18RB_DrawTessSurfacev
	nop


;RB_ClearPixelShader()
_Z19RB_ClearPixelShaderv:
	push ebp
	mov ebp, esp
	mov edx, gfxCmdBufState
	mov eax, [edx+0x9ec]
	test eax, eax
	jz _Z19RB_ClearPixelShaderv_10
	mov eax, [edx+0x90]
	mov dword [eax+0x3b0], 0x0
_Z19RB_ClearPixelShaderv_10:
	mov dword [edx+0x9ec], 0x0
	pop ebp
	ret
	nop


;RB_SetTessTechnique(Material const*, MaterialTechniqueType)
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x1c
	mov edi, [ebp+0x8]
	mov esi, gfxCmdBufState
	cmp [esi+0xa08], edi
	jz _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_10
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_60:
	mov ebx, tess
	mov eax, [ebx+0x22a948]
	test eax, eax
	jnz _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_20
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_40:
	mov dword [ebx+0x22a950], 0x0
	mov dword [ebx+0x22a954], 0x0
	mov [esi+0xb8], edi
	mov eax, [ebp+0xc]
	mov [esi+0xbc], eax
	mov dword [esi+0x98], 0x0
	mov [esi+0xa08], edi
	mov [esi+0xa0c], eax
	mov eax, pixelCostMode
	cmp dword [eax], 0x2
	jg _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_30
	mov eax, edi
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_50:
	mov eax, [eax+0x40]
	mov edx, [eax+0x8]
	mov eax, [esi+0xbc]
	mov eax, [edx+eax*4+0xc]
	mov [esi+0xc0], eax
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_70:
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_20:
	call _Z18RB_DrawTessSurfacev
	jmp _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_40
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_30:
	mov [esp], edi
	call _Z35R_PixelCost_GetAccumulationMaterialPK8Material
	mov [esi+0xb8], eax
	mov dword [esi+0xbc], 0x4
	jmp _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_50
_Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_10:
	mov eax, [ebp+0xc]
	cmp eax, [esi+0xa0c]
	jnz _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_60
	jmp _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType_70
	nop

