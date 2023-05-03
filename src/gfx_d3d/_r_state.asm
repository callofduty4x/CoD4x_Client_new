;Imports of r_state:
	extern _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	extern gfxCmdBufState
	extern memcpy
	extern memset
	extern pixelCostMode
	extern r_lightMap
	extern rgp
	extern r_texFilterAnisoMax
	extern gfxMetrics
	extern r_texFilterAnisoMin
	extern r_texFilterDisable
	extern r_texFilterMipBias
	extern r_dx
	extern r_texFilterMipMode
	extern r_aaAlpha
	extern r_polygonOffsetBias
	extern r_polygonOffsetScale
	extern sm_polygonOffsetBias
	extern sm_polygonOffsetScale
	extern _Z17MatrixTranspose44PKfPf
	extern _Z15MatrixInverse44PKfPf
	extern _Z23MatrixTransformVector44PKfPA4_S_Pf
	extern r_outdoorAwayBias
	extern r_outdoorDownBias
	extern _Z16MatrixMultiply44PA4_KfS1_PA4_f
	extern gfxRenderTargets
	extern vidConfig
	extern _Z33RB_PixelCost_OverrideRenderTarget17GfxRenderTargetId
	extern floorf
	extern rg
	extern _Z9Com_Error11errorParm_tPKcz
	extern _Z14UnitQuatToAxisPKfPA3_f
	extern _Z22R_GetActiveWorldMatrixP20GfxCmdBufSourceState
	extern _Z11MatrixSet44PA4_fPKfPA3_S1_f
	extern _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	extern _Z21R_ClearScreenInternalP16IDirect3DDevice9hPKffhPK11GfxViewport
	extern _Z12R_SetSampler16GfxCmdBufContextjhPK8GfxImage


;Exports of r_state:
	global s_viewportBehaviorForRenderTarget
	global s_mipFilterTable
	global _Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport
	global _Z14R_SetTexFilterv
	global _Z15R_BeginMaterialP14GfxCmdBufStatePK8Material21MaterialTechniqueType
	global _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj
	global _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	global _Z19R_SetViewportValuesP20GfxCmdBufSourceStateiiii
	global _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	global _Z22R_ForceSetStencilStateP16IDirect3DDevice9j
	global _Z22R_TextureFromCodeErrorP20GfxCmdBufSourceStatej
	global _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
	global g_renderTargetIsOverridden
	global s_decodeSamplerFilterState
	global s_manualObjectPlacement


SECTION .text



;R_ClearScreen(IDirect3DDevice9*, unsigned char, float const*, float, unsigned char, GfxViewport const*)
_Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4
	mov eax, [ebp+0x8]
	mov [ebp-0x10], eax
	mov edi, [ebp+0x10]
	mov esi, [ebp+0x14]
	mov ebx, [ebp+0x1c]
	movzx edx, byte [ebp+0xc]
	movzx ecx, byte [ebp+0x18]
	mov eax, pixelCostMode
	cmp dword [eax], 0x2
	jle _Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport_10
	and dl, 0xfe
	jz _Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport_20
_Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport_10:
	mov [ebp+0x1c], ebx
	movzx eax, cl
	mov [ebp+0x18], eax
	mov [ebp+0x14], esi
	mov [ebp+0x10], edi
	movzx eax, dl
	mov [ebp+0xc], eax
	mov eax, [ebp-0x10]
	mov [ebp+0x8], eax
	add esp, 0x4
	pop ebx
	pop esi
	pop edi
	pop ebp
	jmp _Z21R_ClearScreenInternalP16IDirect3DDevice9hPKffhPK11GfxViewport
_Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport_20:
	add esp, 0x4
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	add [eax], al



;R_SetTexFilter()
_Z14R_SetTexFilterv:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov eax, r_texFilterAnisoMax
	mov eax, [eax]
	mov edx, [eax+0xc]
	mov [ebp-0x24], edx
	mov ecx, gfxMetrics
	mov eax, [ecx+0xc]
	cmp edx, eax
	cmovle eax, [ebp-0x24]
	mov [ebp-0x24], eax
	sub eax, 0x1
	jle _Z14R_SetTexFilterv_10
	cmp byte [ecx+0x8], 0x1
	sbb eax, eax
	and eax, 0xffffff00
	add eax, 0x300
	mov [ebp-0x30], eax
	cmp byte [ecx+0x9], 0x1
	sbb eax, eax
	and eax, 0xfffff000
	add eax, 0x3000
	or [ebp-0x30], eax
_Z14R_SetTexFilterv_150:
	mov eax, r_texFilterAnisoMin
	mov edx, [eax]
	lea eax, [edx+0xc]
	mov ecx, [ebp-0x24]
	lea ebx, [ebp-0x24]
	cmp [edx+0xc], ecx
	cmovge eax, ebx
	mov edi, [eax]
	mov [ebp-0x28], edi
	cmp edi, 0x1
	mov eax, 0x2200
	cmovnz eax, [ebp-0x30]
	mov [ebp-0x34], eax
	mov dword [ebp-0x20], 0x2
	cmp ecx, 0x2
	jle _Z14R_SetTexFilterv_20
	lea edx, [ebp-0x20]
	lea eax, [ebp-0x28]
	cmp edi, [edx]
	cmovge edx, eax
	mov edx, [edx]
	mov [ebp-0x2c], edx
	mov dword [ebp-0x1c], 0x4
	cmp ecx, 0x4
	jle _Z14R_SetTexFilterv_30
_Z14R_SetTexFilterv_120:
	lea edx, [ebp-0x1c]
	lea eax, [ebp-0x28]
	cmp edi, [edx]
	cmovge edx, eax
	mov edx, [edx]
	mov eax, r_texFilterDisable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z14R_SetTexFilterv_40
_Z14R_SetTexFilterv_130:
	mov dword [ebp-0x30], 0x1100
	mov edi, 0x1
	mov dword [ebp-0x34], 0x1100
	mov dword [ebp-0x2c], 0x1
	mov edx, 0x1
	mov dword [ebp-0x38], 0x1100
	mov eax, 0x3
_Z14R_SetTexFilterv_140:
	xor ecx, ecx
	mov ebx, s_decodeSamplerFilterState
	lea esi, [eax+eax*2]
	or edi, [ebp-0x34]
	mov [ebp-0x3c], edi
	mov edi, [ebp-0x30]
	or edi, [ebp-0x2c]
	or edx, [ebp-0x30]
	mov [ebp-0x40], edx
	jmp _Z14R_SetTexFilterv_50
_Z14R_SetTexFilterv_90:
	cmp edx, 0x3
	jz _Z14R_SetTexFilterv_60
	cmp edx, 0x4
	jz _Z14R_SetTexFilterv_70
	or eax, 0x1101
_Z14R_SetTexFilterv_110:
	mov [ebx], eax
	add ecx, 0x1
	add ebx, 0x4
	cmp ecx, 0x18
	jz _Z14R_SetTexFilterv_80
_Z14R_SetTexFilterv_50:
	mov edx, ecx
	and edx, 0x7
	mov eax, ecx
	and eax, 0x18
	sar eax, 0x3
	lea eax, [esi+eax]
	mov eax, [eax*4+s_mipFilterTable]
	shl eax, 0x10
	cmp edx, 0x2
	jnz _Z14R_SetTexFilterv_90
	test eax, eax
	jnz _Z14R_SetTexFilterv_100
	mov eax, [ebp-0x38]
	or eax, 0x1
	mov [ebx], eax
	add ecx, 0x1
	add ebx, 0x4
	cmp ecx, 0x18
	jnz _Z14R_SetTexFilterv_50
_Z14R_SetTexFilterv_80:
	mov eax, r_texFilterMipBias
	mov eax, [eax]
	mov edx, [eax+0xc]
	mov eax, r_dx
	mov [eax+0x2cd0], edx
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z14R_SetTexFilterv_60:
	or eax, edi
	jmp _Z14R_SetTexFilterv_110
_Z14R_SetTexFilterv_70:
	or eax, [ebp-0x40]
	jmp _Z14R_SetTexFilterv_110
_Z14R_SetTexFilterv_100:
	or eax, [ebp-0x3c]
	jmp _Z14R_SetTexFilterv_110
_Z14R_SetTexFilterv_20:
	mov edx, ebx
	lea eax, [ebp-0x28]
	cmp edi, [edx]
	cmovge edx, eax
	mov edx, [edx]
	mov [ebp-0x2c], edx
	mov dword [ebp-0x1c], 0x4
	cmp ecx, 0x4
	jg _Z14R_SetTexFilterv_120
_Z14R_SetTexFilterv_30:
	lea edx, [ebp-0x24]
	lea eax, [ebp-0x28]
	cmp edi, [edx]
	cmovge edx, eax
	mov edx, [edx]
	mov eax, r_texFilterDisable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jnz _Z14R_SetTexFilterv_130
_Z14R_SetTexFilterv_40:
	mov eax, r_texFilterMipMode
	mov eax, [eax]
	mov eax, [eax+0xc]
	mov dword [ebp-0x38], 0x2200
	jmp _Z14R_SetTexFilterv_140
_Z14R_SetTexFilterv_10:
	mov dword [ebp-0x24], 0x1
	mov dword [ebp-0x30], 0x2200
	jmp _Z14R_SetTexFilterv_150
	nop


;R_BeginMaterial(GfxCmdBufState*, Material const*, MaterialTechniqueType)
_Z15R_BeginMaterialP14GfxCmdBufStatePK8Material21MaterialTechniqueType:
	push ebp
	mov ebp, esp
	push ebx
	mov edx, [ebp+0x8]
	mov ecx, [ebp+0xc]
	mov ebx, [ebp+0x10]
	mov eax, [ecx+0x40]
	mov eax, [eax+0x8]
	mov eax, [eax+ebx*4+0xc]
	test eax, eax
	jz _Z15R_BeginMaterialP14GfxCmdBufStatePK8Material21MaterialTechniqueType_10
	mov [edx+0xb8], ecx
	mov [edx+0xbc], ebx
	mov [edx+0xc0], eax
	mov eax, 0x1
_Z15R_BeginMaterialP14GfxCmdBufStatePK8Material21MaterialTechniqueType_10:
	pop ebx
	pop ebp
	ret
	nop




;R_GetCodeMatrix(GfxCmdBufSourceState*, unsigned int, unsigned int)
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj:
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_90:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xdc
	mov edi, [ebp+0x8]
	mov eax, [ebp+0xc]
	sub eax, 0x3a
	mov [ebp-0xc4], eax
	shr eax, 0x2
	movzx eax, word [edi+eax*2+0xee4]
	mov [ebp-0xcc], eax
	mov edx, [ebp+0xc]
	movzx eax, word [edi+edx*2+0xe30]
	cmp [ebp-0xcc], eax
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_10
	mov ecx, [ebp-0xc4]
	and ecx, 0xfffffffc
	mov [ebp-0xc8], ecx
	movzx eax, word [edi+ecx*2+0xea4]
	cmp [ebp-0xcc], eax
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_20
	mov eax, ecx
	sub eax, 0x4
	cmp eax, 0x18
	jbe _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_30
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80:
	mov edx, [ebp-0xc8]
	cmp [ebp-0xc4], edx
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_10
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_20:
	movzx eax, word [ebp-0xcc]
	mov ecx, [ebp+0xc]
	mov [edi+ecx*2+0xe30], ax
	mov edx, [ebp-0xc4]
	xor edx, 0x2
	movzx eax, word [edi+edx*2+0xea4]
	cmp [ebp-0xcc], eax
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_40
	mov edx, [ebp-0xc4]
	xor edx, 0x1
	lea esi, [edx+0x3a]
	movzx eax, word [edi+esi*2+0xe30]
	cmp [ebp-0xcc], eax
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_50
	shl edx, 0x6
	lea ebx, [edx+edi+0x80]
	mov [esp+0x4], ebx
	shl dword [ebp-0xc8], 0x6
	mov edx, [ebp-0xc8]
	lea eax, [edx+edi+0x80]
	mov [esp], eax
	call _Z17MatrixTranspose44PKfPf
	movzx ecx, word [ebp-0xcc]
	mov [edi+esi*2+0xe30], cx
	mov eax, [ebp-0xc4]
	shl eax, 0x6
	lea eax, [eax+edi+0x80]
	mov [esp+0x4], eax
	mov [esp], ebx
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_70:
	call _Z15MatrixInverse44PKfPf
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_60:
	mov edx, [ebp-0xc4]
	mov ecx, [ebp+0x10]
	lea eax, [ecx+edx*4]
	shl eax, 0x4
	lea eax, [eax+edi+0x80]
	add esp, 0xdc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_30:
	jmp dword [eax*4+_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_jumptab_0]
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_10:
	mov ecx, [ebp-0xc4]
	mov edx, [ebp+0x10]
	lea eax, [edx+ecx*4]
	shl eax, 0x4
	lea eax, [eax+edi+0x80]
	add esp, 0xdc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_40:
	mov eax, [ebp-0xc4]
	shl eax, 0x6
	lea eax, [eax+edi+0x80]
	mov [esp+0x4], eax
	shl edx, 0x6
	lea eax, [edx+edi+0x80]
	mov [esp], eax
	call _Z17MatrixTranspose44PKfPf
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_60
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_50:
	mov eax, [ebp-0xc4]
	shl eax, 0x6
	lea eax, [eax+edi+0x80]
	mov [esp+0x4], eax
	shl edx, 0x6
	lea eax, [edx+edi+0x80]
	mov [esp], eax
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_70
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_260:
	lea edx, [edi+0x180]
	mov eax, [edi+0xcb0]
	mov [edi+0x180], eax
	mov eax, [edi+0xcb4]
	mov [edx+0x4], eax
	mov eax, [edi+0xcb8]
	mov [edx+0x8], eax
	mov eax, [edi+0xcbc]
	mov [edx+0xc], eax
	mov eax, [edi+0xcc0]
	mov [edx+0x10], eax
	mov eax, [edi+0xcc4]
	mov [edx+0x14], eax
	mov eax, [edi+0xcc8]
	mov [edx+0x18], eax
	mov eax, [edi+0xccc]
	mov [edx+0x1c], eax
	mov eax, [edi+0xcd0]
	mov [edx+0x20], eax
	mov eax, [edi+0xcd4]
	mov [edx+0x24], eax
	mov eax, [edi+0xcd8]
	mov [edx+0x28], eax
	mov eax, [edi+0xcdc]
	mov [edx+0x2c], eax
	mov eax, [edi+0xce0]
	mov [edx+0x30], eax
	mov eax, [edi+0xce4]
	mov [edx+0x34], eax
	mov eax, [edi+0xce8]
	mov [edx+0x38], eax
	mov eax, [edi+0xcec]
	mov [edx+0x3c], eax
	lea eax, [edi+0x1b0]
	mov [esp+0x8], eax
	mov [esp+0x4], edx
	lea eax, [edi+0xef4]
	mov [esp], eax
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	movzx eax, word [edi+0xee6]
	mov [edi+0xeac], ax
	mov [esp], edi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_320:
	lea eax, [edi+0x780]
	mov [ebp-0xc0], eax
	mov eax, r_outdoorAwayBias
	mov eax, [eax]
	mov ebx, [eax+0xc]
	mov eax, r_outdoorDownBias
	mov eax, [eax]
	movss xmm0, dword [eax+0xc]
	movss [ebp-0xbc], xmm0
	mov dword [esp+0x8], 0x0
	mov dword [esp+0x4], 0x3f
	mov [esp], edi
	call _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_90
	xor edx, edx
	mov [ebp-0x28], edx
	mov [ebp-0x24], edx
	xor ebx, 0x80000000
	mov [ebp-0x20], ebx
	mov [ebp-0x1c], edx
	lea ebx, [ebp-0x38]
	mov [esp+0x8], ebx
	mov [esp+0x4], eax
	lea eax, [ebp-0x28]
	mov [esp], eax
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	movss xmm0, dword [ebp-0xbc]
	addss xmm0, [ebp-0x30]
	movss [ebp-0x30], xmm0
	lea eax, [ebp-0x78]
	mov [esp+0x8], eax
	mov esi, rgp
	mov eax, [esi+0x20a0]
	add eax, 0x1dc
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	mov eax, [edi+0x80]
	mov [ebp-0xb8], eax
	mov eax, [edi+0x84]
	mov [ebp-0xb4], eax
	mov eax, [edi+0x88]
	mov [ebp-0xb0], eax
	mov eax, [edi+0x8c]
	mov [ebp-0xac], eax
	mov eax, [edi+0x90]
	mov [ebp-0xa8], eax
	mov eax, [edi+0x94]
	mov [ebp-0xa4], eax
	mov eax, [edi+0x98]
	mov [ebp-0xa0], eax
	mov eax, [edi+0x9c]
	mov [ebp-0x9c], eax
	mov eax, [edi+0xa0]
	mov [ebp-0x98], eax
	mov eax, [edi+0xa4]
	mov [ebp-0x94], eax
	mov eax, [edi+0xa8]
	mov [ebp-0x90], eax
	mov eax, [edi+0xac]
	mov [ebp-0x8c], eax
	mov eax, [edi+0xb0]
	mov [ebp-0x88], eax
	mov eax, [edi+0xb4]
	mov [ebp-0x84], eax
	mov eax, [edi+0xb8]
	mov [ebp-0x80], eax
	mov eax, [edi+0xbc]
	mov [ebp-0x7c], eax
	lea eax, [edi+0xef4]
	movss xmm0, dword [ebp-0x88]
	addss xmm0, [edi+0xef4]
	movss [ebp-0x88], xmm0
	lea edx, [ebp-0xb8]
	movss xmm0, dword [ebp-0x84]
	addss xmm0, [eax+0x4]
	movss [ebp-0x84], xmm0
	movss xmm0, dword [ebp-0x80]
	addss xmm0, [eax+0x8]
	movss [ebp-0x80], xmm0
	mov eax, [ebp-0xc0]
	mov [esp+0x8], eax
	mov eax, [esi+0x20a0]
	add eax, 0x1dc
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	lea eax, [edi+0x7b0]
	movss xmm0, dword [edi+0x7b0]
	addss xmm0, [ebp-0x78]
	movss [edi+0x7b0], xmm0
	movss xmm0, dword [eax+0x4]
	addss xmm0, [ebp-0x74]
	movss [eax+0x4], xmm0
	movss xmm0, dword [eax+0x8]
	addss xmm0, [ebp-0x70]
	movss [eax+0x8], xmm0
	movss xmm0, dword [eax+0xc]
	addss xmm0, [ebp-0x6c]
	movss [eax+0xc], xmm0
	movzx eax, word [edi+0xef2]
	mov [edi+0xedc], ax
	mov [esp], edi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_310:
	lea edx, [edi+0x680]
	mov eax, [edi+0xdf0]
	mov [edi+0x680], eax
	mov eax, [edi+0xdf4]
	mov [edx+0x4], eax
	mov eax, [edi+0xdf8]
	mov [edx+0x8], eax
	mov eax, [edi+0xdfc]
	mov [edx+0xc], eax
	mov eax, [edi+0xe00]
	mov [edx+0x10], eax
	mov eax, [edi+0xe04]
	mov [edx+0x14], eax
	mov eax, [edi+0xe08]
	mov [edx+0x18], eax
	mov eax, [edi+0xe0c]
	mov [edx+0x1c], eax
	mov eax, [edi+0xe10]
	mov [edx+0x20], eax
	mov eax, [edi+0xe14]
	mov [edx+0x24], eax
	mov eax, [edi+0xe18]
	mov [edx+0x28], eax
	mov eax, [edi+0xe1c]
	mov [edx+0x2c], eax
	mov eax, [edi+0xe20]
	mov [edx+0x30], eax
	mov eax, [edi+0xe24]
	mov [edx+0x34], eax
	mov eax, [edi+0xe28]
	mov [edx+0x38], eax
	mov eax, [edi+0xe2c]
	mov [edx+0x3c], eax
	lea eax, [edi+0x6b0]
	mov [esp+0x8], eax
	mov [esp+0x4], edx
	lea eax, [edi+0xef4]
	mov [esp], eax
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	movzx eax, word [edi+0xef0]
	mov [edi+0xed4], ax
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_300:
	lea edx, [edi+0xcb0]
	mov eax, [edi+0x80]
	mov [ebp-0x78], eax
	mov eax, [edi+0x84]
	mov [ebp-0x74], eax
	mov eax, [edi+0x88]
	mov [ebp-0x70], eax
	mov eax, [edi+0x8c]
	mov [ebp-0x6c], eax
	mov eax, [edi+0x90]
	mov [ebp-0x68], eax
	mov eax, [edi+0x94]
	mov [ebp-0x64], eax
	mov eax, [edi+0x98]
	mov [ebp-0x60], eax
	mov eax, [edi+0x9c]
	mov [ebp-0x5c], eax
	mov eax, [edi+0xa0]
	mov [ebp-0x58], eax
	mov eax, [edi+0xa4]
	mov [ebp-0x54], eax
	mov eax, [edi+0xa8]
	mov [ebp-0x50], eax
	mov eax, [edi+0xac]
	mov [ebp-0x4c], eax
	mov eax, [edi+0xb0]
	mov [ebp-0x48], eax
	mov eax, [edi+0xb4]
	mov [ebp-0x44], eax
	mov eax, [edi+0xb8]
	mov [ebp-0x40], eax
	mov eax, [edi+0xbc]
	mov [ebp-0x3c], eax
	lea esi, [edi+0x580]
	cmp dword [edi+0xf10], 0x2
	jnz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_100
	movzx eax, word [edi+0xeec]
	cmp ax, [edi+0xec4]
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_110
	lea ebx, [edi+0x480]
	movzx eax, word [edi+0xee8]
	cmp ax, [edi+0xeb4]
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_120
	lea ecx, [edi+0x280]
	mov eax, [edx+0x40]
	mov [edi+0x280], eax
	mov eax, [edx+0x44]
	mov [ecx+0x4], eax
	mov eax, [edx+0x48]
	mov [ecx+0x8], eax
	mov eax, [edx+0x4c]
	mov [ecx+0xc], eax
	mov eax, [edx+0x50]
	mov [ecx+0x10], eax
	mov eax, [edx+0x54]
	mov [ecx+0x14], eax
	mov eax, [edx+0x58]
	mov [ecx+0x18], eax
	mov eax, [edx+0x5c]
	mov [ecx+0x1c], eax
	mov eax, [edx+0x60]
	mov [ecx+0x20], eax
	mov eax, [edx+0x64]
	mov [ecx+0x24], eax
	mov eax, [edx+0x68]
	mov [ecx+0x28], eax
	mov eax, [edx+0x6c]
	mov [ecx+0x2c], eax
	mov eax, [edx+0x70]
	mov [ecx+0x30], eax
	mov eax, [edx+0x74]
	mov [ecx+0x34], eax
	mov eax, [edx+0x78]
	mov [ecx+0x38], eax
	mov eax, [edx+0x7c]
	mov [ecx+0x3c], eax
	cmp dword [edi+0xf10], 0x2
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_130
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_250:
	movzx eax, word [edi+0xee8]
	mov [edi+0xeb4], ax
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_230:
	mov [esp+0x8], ebx
	mov [esp+0x4], ecx
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	lea eax, [ebx+0x30]
	mov [esp+0x8], eax
	mov [esp+0x4], ebx
	lea eax, [edi+0xef4]
	mov [esp], eax
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	movzx eax, word [edi+0xeec]
	mov [edi+0xec4], ax
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_210:
	mov [esp+0x8], esi
	mov [esp+0x4], ebx
	lea eax, [ebp-0x78]
	mov [esp], eax
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_160:
	movzx eax, word [edi+0xeee]
	mov [edi+0xecc], ax
	mov [esp], edi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_290:
	lea edx, [edi+0xcb0]
	lea ebx, [edi+0x480]
	cmp dword [edi+0xf10], 0x2
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_140
	mov eax, [edx+0x80]
	mov [edi+0x480], eax
	mov eax, [edx+0x84]
	mov [ebx+0x4], eax
	mov eax, [edx+0x88]
	mov [ebx+0x8], eax
	mov eax, [edx+0x8c]
	mov [ebx+0xc], eax
	mov eax, [edx+0x90]
	mov [ebx+0x10], eax
	mov eax, [edx+0x94]
	mov [ebx+0x14], eax
	mov eax, [edx+0x98]
	mov [ebx+0x18], eax
	mov eax, [edx+0x9c]
	mov [ebx+0x1c], eax
	mov eax, [edx+0xa0]
	mov [ebx+0x20], eax
	mov eax, [edx+0xa4]
	mov [ebx+0x24], eax
	mov eax, [edx+0xa8]
	mov [ebx+0x28], eax
	mov eax, [edx+0xac]
	mov [ebx+0x2c], eax
	mov eax, [edx+0xb0]
	mov [ebx+0x30], eax
	mov eax, [edx+0xb4]
	mov [ebx+0x34], eax
	mov eax, [edx+0xb8]
	mov [ebx+0x38], eax
	mov eax, [edx+0xbc]
	mov [ebx+0x3c], eax
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_190:
	lea eax, [ebx+0x30]
	mov [esp+0x8], eax
	mov [esp+0x4], ebx
	lea eax, [edi+0xef4]
	mov [esp], eax
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	movzx eax, word [edi+0xeec]
	mov [edi+0xec4], ax
	mov [esp], edi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_280:
	mov eax, [edi+0x80]
	mov [ebp-0x78], eax
	mov eax, [edi+0x84]
	mov [ebp-0x74], eax
	mov eax, [edi+0x88]
	mov [ebp-0x70], eax
	mov eax, [edi+0x8c]
	mov [ebp-0x6c], eax
	mov eax, [edi+0x90]
	mov [ebp-0x68], eax
	mov eax, [edi+0x94]
	mov [ebp-0x64], eax
	mov eax, [edi+0x98]
	mov [ebp-0x60], eax
	mov eax, [edi+0x9c]
	mov [ebp-0x5c], eax
	mov eax, [edi+0xa0]
	mov [ebp-0x58], eax
	mov eax, [edi+0xa4]
	mov [ebp-0x54], eax
	mov eax, [edi+0xa8]
	mov [ebp-0x50], eax
	mov eax, [edi+0xac]
	mov [ebp-0x4c], eax
	mov eax, [edi+0xb0]
	mov [ebp-0x48], eax
	mov eax, [edi+0xb4]
	mov [ebp-0x44], eax
	mov eax, [edi+0xb8]
	mov [ebp-0x40], eax
	mov eax, [edi+0xbc]
	mov [ebp-0x3c], eax
	lea eax, [edi+0xef4]
	movss xmm0, dword [ebp-0x48]
	addss xmm0, [edi+0xef4]
	movss [ebp-0x48], xmm0
	lea edx, [ebp-0x78]
	movss xmm0, dword [ebp-0x44]
	addss xmm0, [eax+0x4]
	movss [ebp-0x44], xmm0
	movss xmm0, dword [ebp-0x40]
	addss xmm0, [eax+0x8]
	movss [ebp-0x40], xmm0
	lea eax, [edi+0x380]
	mov [esp+0x8], eax
	lea eax, [edi+0xcb0]
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	movzx eax, word [edi+0xeea]
	mov [edi+0xebc], ax
	mov [esp], edi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_270:
	lea edx, [edi+0xcb0]
	lea ecx, [edi+0x280]
	mov eax, [edx+0x40]
	mov [edi+0x280], eax
	mov eax, [edx+0x44]
	mov [ecx+0x4], eax
	mov eax, [edx+0x48]
	mov [ecx+0x8], eax
	mov eax, [edx+0x4c]
	mov [ecx+0xc], eax
	mov eax, [edx+0x50]
	mov [ecx+0x10], eax
	mov eax, [edx+0x54]
	mov [ecx+0x14], eax
	mov eax, [edx+0x58]
	mov [ecx+0x18], eax
	mov eax, [edx+0x5c]
	mov [ecx+0x1c], eax
	mov eax, [edx+0x60]
	mov [ecx+0x20], eax
	mov eax, [edx+0x64]
	mov [ecx+0x24], eax
	mov eax, [edx+0x68]
	mov [ecx+0x28], eax
	mov eax, [edx+0x6c]
	mov [ecx+0x2c], eax
	mov eax, [edx+0x70]
	mov [ecx+0x30], eax
	mov eax, [edx+0x74]
	mov [ecx+0x34], eax
	mov eax, [edx+0x78]
	mov [ecx+0x38], eax
	mov eax, [edx+0x7c]
	mov [ecx+0x3c], eax
	cmp dword [edi+0xf10], 0x2
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_150
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_200:
	movzx eax, word [edi+0xee8]
	mov [edi+0xeb4], ax
	mov [esp], edi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_100:
	lea eax, [edi+0xef4]
	movss xmm0, dword [ebp-0x48]
	addss xmm0, [edi+0xef4]
	movss [ebp-0x48], xmm0
	lea edx, [ebp-0x78]
	movss xmm0, dword [ebp-0x44]
	addss xmm0, [eax+0x4]
	movss [ebp-0x44], xmm0
	movss xmm0, dword [ebp-0x40]
	addss xmm0, [eax+0x8]
	movss [ebp-0x40], xmm0
	mov [esp+0x8], esi
	lea eax, [edi+0xd30]
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_160
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_140:
	movzx eax, word [edi+0xee8]
	cmp ax, [edi+0xeb4]
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_170
	lea ecx, [edi+0x280]
	mov eax, [edx+0x40]
	mov [edi+0x280], eax
	mov eax, [edx+0x44]
	mov [ecx+0x4], eax
	mov eax, [edx+0x48]
	mov [ecx+0x8], eax
	mov eax, [edx+0x4c]
	mov [ecx+0xc], eax
	mov eax, [edx+0x50]
	mov [ecx+0x10], eax
	mov eax, [edx+0x54]
	mov [ecx+0x14], eax
	mov eax, [edx+0x58]
	mov [ecx+0x18], eax
	mov eax, [edx+0x5c]
	mov [ecx+0x1c], eax
	mov eax, [edx+0x60]
	mov [ecx+0x20], eax
	mov eax, [edx+0x64]
	mov [ecx+0x24], eax
	mov eax, [edx+0x68]
	mov [ecx+0x28], eax
	mov eax, [edx+0x6c]
	mov [ecx+0x2c], eax
	mov eax, [edx+0x70]
	mov [ecx+0x30], eax
	mov eax, [edx+0x74]
	mov [ecx+0x34], eax
	mov eax, [edx+0x78]
	mov [ecx+0x38], eax
	mov eax, [edx+0x7c]
	mov [ecx+0x3c], eax
	cmp dword [edi+0xf10], 0x2
	jz _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_180
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_240:
	movzx eax, word [edi+0xee8]
	mov [edi+0xeb4], ax
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_220:
	mov [esp+0x8], ebx
	mov [esp+0x4], ecx
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_190
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_150:
	mov eax, [edx+0x134]
	mov [ecx+0x38], eax
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_200
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_110:
	lea ebx, [edi+0x480]
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_210
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_170:
	lea ecx, [edi+0x280]
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_220
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_120:
	lea ecx, [edi+0x280]
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_230
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_180:
	mov eax, [edx+0x134]
	mov [ecx+0x38], eax
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_240
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_130:
	mov eax, [edx+0x134]
	mov [ecx+0x38], eax
	jmp _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_250
	
	
_Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_jumptab_0:
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_260
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_270
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_280
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_290
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_300
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_310
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_80
	dd _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj_320



;R_SetViewportStruct(GfxCmdBufSourceState*, GfxViewport const*)
_Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport:
	push ebp
	mov ebp, esp
	mov ecx, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov eax, [edx]
	mov [ecx+0xf50], eax
	mov eax, [edx+0x4]
	mov [ecx+0xf54], eax
	mov eax, [edx+0x8]
	mov [ecx+0xf58], eax
	mov eax, [edx+0xc]
	mov [ecx+0xf5c], eax
	mov dword [ecx+0xf38], 0x0
	mov byte [ecx+0xf70], 0x1
	pop ebp
	ret
	nop
	add [eax], al


;R_SetViewportValues(GfxCmdBufSourceState*, int, int, int, int)
_Z19R_SetViewportValuesP20GfxCmdBufSourceStateiiii:
	push ebp
	mov ebp, esp
	mov edx, [ebp+0x8]
	mov eax, [ebp+0x18]
	mov [edx+0xf5c], eax
	mov eax, [ebp+0x14]
	mov [edx+0xf58], eax
	mov eax, [ebp+0x10]
	mov [edx+0xf54], eax
	mov eax, [ebp+0xc]
	mov [edx+0xf50], eax
	mov dword [edx+0xf38], 0x0
	mov byte [edx+0xf70], 0x1
	pop ebp
	ret
	nop
	add [eax], al




;R_SetRenderTargetSize(GfxCmdBufSourceState*, GfxRenderTargetId)
_Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x10
	mov esi, [ebp+0x8]
	mov ebx, [ebp+0xc]
	mov byte [g_renderTargetIsOverridden], 0x0
	mov eax, pixelCostMode
	cmp dword [eax], 0x2
	jle _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId_10
	mov [esp], ebx
	call _Z33RB_PixelCost_OverrideRenderTarget17GfxRenderTargetId
	cmp ebx, eax
	setnz byte [g_renderTargetIsOverridden]
	mov ebx, eax
_Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId_10:
	mov eax, [ebx*4+s_viewportBehaviorForRenderTarget]
	mov [esi+0xf64], eax
	lea eax, [ebx+ebx*4]
	shl eax, 0x2
	add eax, gfxRenderTargets
	mov edx, [eax+0xc]
	mov [esi+0xf68], edx
	mov eax, [eax+0x10]
	mov [esi+0xf6c], eax
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret


;R_TextureFromCodeError(GfxCmdBufSourceState*, unsigned int)
_Z22R_TextureFromCodeErrorP20GfxCmdBufSourceStatej:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	mov eax, [ebp+0xc]
	mov edx, rg
	mov eax, [edx+eax*4+0x2270]
	mov [esp+0x8], eax
	mov dword [esp+0x4], _cstring_tried_to_use_s_w
	mov dword [esp], 0x2
	call _Z9Com_Error11errorParm_tPKcz
	leave
	ret


;R_ChangeObjectPlacement(GfxCmdBufSourceState*, GfxScaledPlacement const*)
_Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov esi, [ebp+0x8]
	mov ebx, [ebp+0xc]
	lea edi, [ebp-0x48]
	mov [esp+0x4], edi
	mov [esp], ebx
	call _Z14UnitQuatToAxisPKfPA3_f
	mov [esp], esi
	call _Z22R_GetActiveWorldMatrixP20GfxCmdBufSourceState
	lea edx, [ebx+0x10]
	lea ecx, [esi+0xef4]
	movss xmm0, dword [ebx+0x10]
	subss xmm0, [esi+0xef4]
	movss [ebp-0x24], xmm0
	movss xmm0, dword [edx+0x4]
	subss xmm0, [ecx+0x4]
	movss [ebp-0x20], xmm0
	movss xmm0, dword [edx+0x8]
	subss xmm0, [ecx+0x8]
	movss [ebp-0x1c], xmm0
	mov edx, [ebx+0x1c]
	mov [esp+0xc], edx
	mov [esp+0x8], edi
	lea edx, [ebp-0x24]
	mov [esp+0x4], edx
	mov [esp], eax
	call _Z11MatrixSet44PA4_fPKfPA3_S1_f
	mov [esp], esi
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	mov [esi+0xf08], ebx
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;Initialized global or static variables of r_state:
SECTION .data


;Initialized constant data of r_state:
SECTION .rdata
s_viewportBehaviorForRenderTarget: dd 0x1, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0
s_mipFilterTable: dd 0x0, 0x1, 0x2, 0x0, 0x2, 0x2, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x80000000, 0x0, 0x0, 0x0


;Zero initialized global or static variables of r_state:
SECTION .bss
g_renderTargetIsOverridden: resb 0x20
s_decodeSamplerFilterState: resb 0x60
s_manualObjectPlacement: resb 0x20


;All cstrings:
SECTION .rdata
_cstring_tried_to_use_s_w:		db "Tried to use ",27h,"%s",27h," when it isn",27h,"t valid",0ah,0



;All constant floats and doubles:
SECTION .rdata
_float_1_00000000:		dd 0x3f800000	; 1
_float_0_50000000:		dd 0x3f000000	; 0.5
_float_0_00001526:		dd 0x37800000	; 1.52588e-05
_float_255_00000000:		dd 0x437f0000	; 255

