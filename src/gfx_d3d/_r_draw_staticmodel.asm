;Imports of r_draw_staticmodel:
	extern _Z22R_GetActiveWorldMatrixP20GfxCmdBufSourceState
	extern _Z11MatrixSet44PA4_fPKfPA3_S1_f
	extern _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	extern _Z24DB_GetIndexBufferAndBasehPvS_Pi
	extern _Z27DB_GetVertexBufferAndOffsethPvS_Pi
	extern rgp
	extern _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	extern _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	extern _Z20R_SetReflectionProbe16GfxCmdBufContextj
	extern _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	extern _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	extern _Z21R_GetCachedSModelSurfj
	extern gfxBuf
	extern _Z18R_ReserveIndexDataP18GfxCmdBufPrimStatei
	extern _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	extern _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	extern _Z16XModelGetSurfacePK6XModelii
	extern _Z18XSurfaceGetNumTrisPK8XSurface
	extern _Z19XSurfaceGetNumVertsPK8XSurface
	extern _Z15R_SetVertexDataP14GfxCmdBufStatePKvii
	extern _Z32R_SetupCachedStaticModelLightingP20GfxCmdBufSourceState
	extern _Z15R_ChangeIndicesP18GfxCmdBufPrimStateP21IDirect3DIndexBuffer9
	extern _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj

;Exports of r_draw_staticmodel:
	global _Z34R_DrawStaticModelDrawSurfPlacementPK22GfxStaticModelDrawInstP20GfxCmdBufSourceState
	global _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo
	global _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo
	global _Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext
	global _Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext
	global _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext
	global _Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext
	global _Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext
	global _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext


SECTION .text


;R_DrawStaticModelDrawSurfPlacement(GfxStaticModelDrawInst const*, GfxCmdBufSourceState*)
_Z34R_DrawStaticModelDrawSurfPlacementPK22GfxStaticModelDrawInstP20GfxCmdBufSourceState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x8c
	mov ebx, eax
	mov [ebp-0x7c], edx
	lea eax, [eax+0x10]
	movss xmm0, dword [ebx+0x10]
	movss [ebp-0x78], xmm0
	movss xmm0, dword [eax+0x4]
	movss [ebp-0x44], xmm0
	movss [ebp-0x74], xmm0
	movss xmm0, dword [eax+0x8]
	movss [ebp-0x40], xmm0
	movss [ebp-0x70], xmm0
	xor edx, edx
	mov [ebp-0x6c], edx
	lea eax, [ebx+0x1c]
	movss xmm0, dword [ebx+0x1c]
	movss [ebp-0x68], xmm0
	movss xmm0, dword [eax+0x4]
	movss [ebp-0x38], xmm0
	movss [ebp-0x64], xmm0
	mov edi, [eax+0x8]
	mov [ebp-0x60], edi
	mov [ebp-0x5c], edx
	lea eax, [ebx+0x28]
	mov esi, [ebx+0x28]
	mov [ebp-0x58], esi
	mov ecx, [eax+0x4]
	mov [ebp-0x54], ecx
	mov eax, [eax+0x8]
	mov [ebp-0x50], eax
	mov [ebp-0x4c], edx
	movss xmm0, dword [ebx+0x10]
	movss [ebp-0x48], xmm0
	movss xmm0, dword [ebx+0x1c]
	movss [ebp-0x3c], xmm0
	mov [ebp-0x34], edi
	mov [ebp-0x30], esi
	mov [ebp-0x2c], ecx
	mov [ebp-0x28], eax
	mov esi, [ebx+0x34]
	mov eax, [ebp-0x7c]
	mov [esp], eax
	call _Z22R_GetActiveWorldMatrixP20GfxCmdBufSourceState
	lea edx, [ebx+0x4]
	mov ecx, [ebp-0x7c]
	add ecx, 0xef4
	movss xmm0, dword [ebx+0x4]
	mov ebx, [ebp-0x7c]
	subss xmm0, [ebx+0xef4]
	movss [ebp-0x24], xmm0
	movss xmm0, dword [edx+0x4]
	subss xmm0, [ecx+0x4]
	movss [ebp-0x20], xmm0
	movss xmm0, dword [edx+0x8]
	subss xmm0, [ecx+0x8]
	movss [ebp-0x1c], xmm0
	mov [esp+0xc], esi
	lea edx, [ebp-0x48]
	mov [esp+0x8], edx
	lea edx, [ebp-0x24]
	mov [esp+0x4], edx
	mov [esp], eax
	call _Z11MatrixSet44PA4_fPKfPA3_S1_f
	mov [esp], ebx
	call _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;R_DrawStaticModelSurf(unsigned int const*, GfxCmdBufContext, GfxDrawSurfListInfo const*)
_Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov dword [ebp-0x58], 0x0
	mov dword [ebp-0x54], 0x0
	mov eax, [ebp+0xc]
	mov [ebp-0x4c], eax
	mov edx, [ebp+0x10]
	mov [ebp-0x50], edx
	mov edx, [ebp+0x8]
	mov eax, [edx]
	mov [ebp-0x44], eax
	lea ecx, [edx+0x4]
	test eax, eax
	jz _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_10
_Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_60:
	add eax, 0x1
	shr eax, 1
	lea eax, [ecx+eax*4+0x4]
	mov [ebp-0x3c], eax
	mov ebx, [edx+0x4]
	add edx, 0x8
	mov [ebp-0x48], edx
	mov edx, [ebp-0x4c]
	mov [ebp+0xc], edx
	mov eax, [ebp-0x50]
	mov [ebp+0x10], eax
	mov [ebp-0x40], edx
	mov esi, eax
	add esi, 0x90
	movzx eax, word [ebx+0x2]
	mov [ebp-0x2c], eax
	movzx eax, word [ebx+0x4]
	mov [ebp-0x28], eax
	lea eax, [ebp-0x24]
	mov [esp+0xc], eax
	lea edi, [ebp-0x1c]
	mov [esp+0x8], edi
	mov eax, [ebx+0xc]
	mov [esp+0x4], eax
	movzx eax, byte [ebx+0x6]
	mov [esp], eax
	call _Z24DB_GetIndexBufferAndBasehPvS_Pi
	mov ecx, [ebp-0x1c]
	cmp ecx, [esi+0x4]
	jz _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_20
	mov [esp+4], ecx
	mov [esp], esi
	call _Z15R_ChangeIndicesP18GfxCmdBufPrimStateP21IDirect3DIndexBuffer9
_Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_20:
	lea eax, [ebp-0x20]
	mov [esp+0xc], eax
	mov [esp+0x8], edi
	mov eax, [ebx+0x1c]
	mov [esp+0x4], eax
	movzx eax, byte [ebx+0x6]
	mov [esp], eax
	call _Z27DB_GetVertexBufferAndOffsethPvS_Pi
	mov ebx, [ebp-0x20]
	mov ecx, [ebp-0x1c]
	mov dword [esp+12], 32
	mov [esp+8], ebx
	mov [esp+4], ecx
	mov [esp], esi
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_100:
	mov eax, rgp
	mov eax, [eax+0x20a0]
	mov edi, [eax+0x29c]
	xor ebx, ebx
_Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_50:
	mov eax, [ebp-0x48]
	movzx edx, word [eax+ebx*2]
	lea eax, [edx+edx*8]
	lea eax, [edx+eax*2]
	lea eax, [edi+eax*4]
	mov edx, [ebp-0x40]
	call _Z34R_DrawStaticModelDrawSurfPlacementPK22GfxStaticModelDrawInstP20GfxCmdBufSourceState
	mov edx, [ebp-0x40]
	mov [ebp-0x58], edx
	mov eax, [ebp-0x50]
	mov [ebp-0x54], eax
	mov eax, [ebp-0x58]
	mov edx, [ebp-0x54]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	lea edx, [ebp-0x2c]
	mov [esp+0x4], edx
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	add ebx, 0x1
	cmp [ebp-0x44], ebx
	jnz _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_50
	mov edx, [ebp-0x3c]
	mov eax, [edx]
	mov [ebp-0x44], eax
	lea ecx, [edx+0x4]
	test eax, eax
	jnz _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_60
_Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo_10:
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret



;R_DrawStaticModelSurfLit(unsigned int const*, GfxCmdBufContext, GfxCmdBufContext, GfxDrawSurfListInfo const*)
_Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x7c
	mov dword [ebp-0x60], 0x0
	mov dword [ebp-0x5c], 0x0
	mov dword [ebp-0x68], 0x0
	mov dword [ebp-0x64], 0x0
	mov eax, [ebp+0xc]
	mov [ebp-0x4c], eax
	mov edx, [ebp+0x10]
	mov [ebp-0x50], edx
	mov edx, [ebp+0x8]
	mov eax, [edx]
	mov [ebp-0x44], eax
	lea ecx, [edx+0x4]
	test eax, eax
	jz _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_10
_Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_60:
	add eax, 0x1
	shr eax, 1
	lea eax, [ecx+eax*4+0x4]
	mov [ebp-0x3c], eax
	mov ebx, [edx+0x4]
	add edx, 0x8
	mov [ebp-0x48], edx
	mov edx, [ebp-0x4c]
	mov [ebp+0xc], edx
	mov eax, [ebp-0x50]
	mov [ebp+0x10], eax
	mov [ebp-0x40], edx
	mov edi, eax
	add edi, 0x90
	movzx eax, word [ebx+0x2]
	mov [ebp-0x2c], eax
	movzx eax, word [ebx+0x4]
	mov [ebp-0x28], eax
	lea eax, [ebp-0x24]
	mov [esp+0xc], eax
	lea esi, [ebp-0x1c]
	mov [esp+0x8], esi
	mov eax, [ebx+0xc]
	mov [esp+0x4], eax
	movzx eax, byte [ebx+0x6]
	mov [esp], eax
	call _Z24DB_GetIndexBufferAndBasehPvS_Pi
	mov ecx, [ebp-0x1c]
	cmp ecx, [edi+0x4]
	jz _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_20
	mov [esp+4], ecx
	mov [esp], edi
	call _Z15R_ChangeIndicesP18GfxCmdBufPrimStateP21IDirect3DIndexBuffer9
_Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_20:
	lea eax, [ebp-0x20]
	mov [esp+0xc], eax
	mov [esp+0x8], esi
	mov eax, [ebx+0x1c]
	mov [esp+0x4], eax
	movzx eax, byte [ebx+0x6]
	mov [esp], eax
	call _Z27DB_GetVertexBufferAndOffsethPvS_Pi
	mov ebx, [ebp-0x20]
	mov ecx, [ebp-0x1c]
	mov dword [esp+12], 32
	mov [esp+8], ebx
	mov [esp+4], ecx
	mov [esp], edi
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_100:
	mov eax, rgp
	mov eax, [eax+0x20a0]
	mov eax, [eax+0x29c]
	mov [ebp-0x54], eax
	xor esi, esi
_Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_50:
	mov edx, [ebp-0x48]
	movzx eax, word [edx+esi*2]
	lea ebx, [eax+eax*8]
	lea ebx, [eax+ebx*2]
	mov eax, [ebp-0x54]
	lea ebx, [eax+ebx*4]
	movzx eax, byte [ebx+0x44]
	mov edx, [ebp-0x40]
	mov [ebp-0x68], edx
	mov edx, [ebp-0x50]
	mov [ebp-0x64], edx
	mov [esp+0x8], eax
	mov eax, [ebp-0x68]
	mov edx, [ebp-0x64]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x40]
	mov eax, ebx
	call _Z34R_DrawStaticModelDrawSurfPlacementPK22GfxStaticModelDrawInstP20GfxCmdBufSourceState
	mov edx, [ebp-0x40]
	mov [esp+0x4], edx
	movzx eax, word [ebx+0x46]
	mov [esp], eax
	call _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	mov eax, [ebp-0x40]
	mov [ebp-0x60], eax
	mov edx, [ebp-0x50]
	mov [ebp-0x5c], edx
	mov eax, [ebp-0x60]
	mov edx, [ebp-0x5c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	lea edx, [ebp-0x2c]
	mov [esp+0x4], edx
	mov [esp], edi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	add esi, 0x1
	cmp [ebp-0x44], esi
	jnz _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_50
	mov edx, [ebp-0x3c]
	mov eax, [edx]
	mov [ebp-0x44], eax
	lea ecx, [edx+0x4]
	test eax, eax
	jnz _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_60
_Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo_10:
	add esp, 0x7c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret



;R_DrawStaticModelCachedSurf(unsigned int const*, GfxCmdBufContext)
_Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov ecx, [ebp+0xc]
	mov [ebp-0x3c], ecx
	mov ebx, [ebp+0x10]
	mov [ebp-0x40], ebx
	mov [esp], ecx
	mov [esp+0x4], ebx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebp+0x8]
	mov [ebp-0x30], eax
	mov esi, ebx
	add esi, 0x90
	mov ebx, eax
_Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_50:
	mov edi, [ebx]
	test edi, edi
	jnz _Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_10
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_10:
	mov eax, [ebx+0x4]
	mov [ebp-0x38], eax
	add ebx, 0x8
	mov [ebp-0x2c], ebx
	lea eax, [edi+0x1]
	shr eax, 1
	lea eax, [ebx+eax*4]
	mov [ebp-0x30], eax
	movzx eax, word [ebx]
	mov [esp], eax
	call _Z21R_GetCachedSModelSurfj
	mov edx, [ebp-0x3c]
	mov [ebp+0xc], edx
	mov ecx, [ebp-0x40]
	mov [ebp+0x10], ecx
	mov [ebp-0x34], edx
	mov dword [ebp-0x24], 0x10000
	mov edx, [ebp-0x38]
	movzx eax, word [edx+0x4]
	mov [ebp-0x20], eax
	mov ecx, [ebp-0x2c]
	movzx eax, word [ecx]
	lea ecx, [eax-0x1]
	and ecx, 0xfffff000
	shl ecx, 0x9
	mov eax, gfxBuf
	mov ebx, [eax+0xc]
	mov dword [esp+12], 32
	mov [esp+8], ecx
	mov [esp+4], ebx
	mov [esp], esi
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_90:
	mov edx, [ebp-0x34]
	mov [ebp-0x48], edx
	mov ecx, [ebp-0x40]
	mov [ebp-0x44], ecx
	mov eax, [ebp-0x48]
	mov edx, [ebp-0x44]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov edx, [ebp-0x38]
	movzx eax, word [edx+0x8]
	lea eax, [eax+eax*2]
	mov [ebp-0x4c], eax
	movzx eax, word [edx+0x4]
	imul eax, edi
	mov [ebp-0x20], eax
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z18R_ReserveIndexDataP18GfxCmdBufPrimStatei
	mov [ebp-0x1c], eax
	xor ebx, ebx
_Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_40:
	mov ecx, [ebp-0x2c]
	movzx eax, word [ecx+ebx*2]
	mov [esp], eax
	call _Z21R_GetCachedSModelSurfj
	mov ecx, [ebp-0x38]
	movzx edx, word [ecx+0x4]
	mov [esp+0x8], edx
	mov eax, [eax]
	mov edx, [ebp-0x4c]
	lea eax, [edx+eax*4]
	mov ecx, gfxBuf
	mov edx, [ecx+0x8]
	lea eax, [edx+eax*2]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	add ebx, 0x1
	cmp edi, ebx
	jnz _Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_40
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	mov ebx, [ebp-0x30]
	jmp _Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext_50



;R_DrawStaticModelPreTessSurf(unsigned int const*, GfxCmdBufContext)
_Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x5c
	mov dword [ebp-0x30], 0x0
	mov dword [ebp-0x2c], 0x0
	mov ebx, [ebp+0xc]
	mov esi, [ebp+0x10]
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebp+0x8]
	mov [ebp-0x1c], eax
	mov [ebp-0x3c], ebx
	mov [ebp-0x40], esi
_Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_50:
	lea edx, [ebp-0x1c]
	mov [esp], edx
	call _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	mov [ebp-0x34], eax
	test eax, eax
	jnz _Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_10
	add esp, 0x5c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_10:
	lea eax, [ebp-0x1c]
	mov [esp], eax
	call _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	mov edi, eax
	lea edx, [ebp-0x1c]
	mov [esp], edx
	call _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	mov [ebp-0x38], eax
	mov eax, edi
	movzx ebx, al
	mov edx, edi
	movzx esi, dh
	shr edi, 0x10
	mov [esp], edi
	call _Z21R_GetCachedSModelSurfj
	mov [esp+0x8], ebx
	mov [esp+0x4], esi
	mov edx, rgp
	mov ecx, [edx+0x20a0]
	movzx edx, word [eax+0x6]
	mov ecx, [ecx+0x29c]
	lea eax, [edx+edx*8]
	lea eax, [edx+eax*2]
	mov eax, [ecx+eax*4+0x38]
	mov [esp], eax
	call _Z16XModelGetSurfacePK6XModelii
	mov dword [ebp-0x28], 0x10000
	movzx eax, word [eax+0x4]
	imul eax, [ebp-0x34]
	mov [ebp-0x24], eax
	lea ecx, [edi-0x1]
	and ecx, 0xfffff000
	shl ecx, 0x9
	mov eax, gfxBuf
	mov ebx, [eax+0xc]
	mov edi, [ebp-0x40]
	add edi, 0x90
	mov dword [esp+12], 32
	mov [esp+8], ecx
	mov [esp+4], ebx
	mov [esp], edi
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_90:
	mov eax, [ebp-0x3c]
	mov [ebp-0x30], eax
	mov edx, [ebp-0x40]
	mov [ebp-0x2c], edx
	mov eax, [ebp-0x30]
	mov edx, [ebp-0x2c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov edx, [ebp-0x3c]
	mov eax, [edx+0xca8]
	mov ecx, [eax+0x11e6a0]
	cmp ecx, [edi+0x4]
	jz _Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_40
	mov [esp+4], ecx
	mov [esp], edi
	call _Z15R_ChangeIndicesP18GfxCmdBufPrimStateP21IDirect3DIndexBuffer9
_Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_40:
	mov eax, [ebp-0x38]
	mov [ebp-0x20], eax
	lea eax, [ebp-0x28]
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	jmp _Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext_50



;R_DrawStaticModelSkinnedSurf(unsigned int const*, GfxCmdBufContext)
_Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov ecx, [ebp+0xc]
	mov [ebp-0x40], ecx
	mov ebx, [ebp+0x10]
	mov [ebp-0x44], ebx
	mov [esp], ecx
	mov [esp+0x4], ebx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp+0x8]
	mov ebx, [edx]
	mov [ebp-0x38], ebx
	lea ecx, [edx+0x4]
	test ebx, ebx
	jz _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_10
_Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_60:
	mov eax, ebx
	add eax, 0x1
	shr eax, 1
	lea eax, [ecx+eax*4+0x4]
	mov [ebp-0x2c], eax
	mov eax, [edx+0x4]
	mov [ebp-0x34], eax
	add edx, 0x8
	mov [ebp-0x3c], edx
	mov edx, [ebp-0x40]
	mov [ebp+0xc], edx
	mov ecx, [ebp-0x44]
	mov [ebp+0x10], ecx
	mov ebx, [ebp+0xc]
	mov [ebp-0x30], ebx
	add ecx, 0x90
	mov [ebp-0x58], ecx
	mov [esp], eax
	call _Z18XSurfaceGetNumTrisPK8XSurface
	mov [ebp-0x20], eax
	mov eax, [ebp-0x34]
	mov [esp], eax
	call _Z19XSurfaceGetNumVertsPK8XSurface
	mov [ebp-0x24], eax
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov edx, [ebp-0x34]
	mov eax, [edx+0xc]
	mov [esp+0x4], eax
	mov ecx, [ebp-0x58]
	mov [esp], ecx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	mov eax, gfxBuf
	mov edi, [eax+0x70]
	mov edx, [edi]
	mov ecx, [ebp-0x24]
	mov eax, ecx
	shl eax, 0x5
	add eax, edx
	cmp eax, [edi+0x4]
	jle _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_20
	mov dword [edi], 0x0
	mov ecx, [ebp-0x24]
_Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_20:
	mov dword [esp+0xc], 0x20
	mov [esp+0x8], ecx
	mov edx, [ebp-0x34]
	mov eax, [edx+0x1c]
	mov [esp+0x4], eax
	mov ecx, [ebp-0x44]
	mov [esp], ecx
	call _Z15R_SetVertexDataP14GfxCmdBufStatePKvii
	mov edi, eax
	mov eax, gfxBuf
	mov eax, [eax+0x70]
	mov ecx, [eax+0x8]
	mov eax, [ebp-0x58]
	mov dword [esp+12], 32
	mov [esp+8], edi
	mov [esp+4], ecx
	mov [esp], eax
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_110:
	mov eax, rgp
	mov eax, [eax+0x20a0]
	mov eax, [eax+0x29c]
	mov [ebp-0x54], eax
	xor edi, edi
_Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_50:
	mov ecx, [ebp-0x3c]
	movzx edx, word [ecx+edi*2]
	lea eax, [edx+edx*8]
	lea eax, [edx+eax*2]
	mov edx, [ebp-0x54]
	lea eax, [edx+eax*4]
	mov ebx, [ebp-0x30]
	mov edx, ebx
	call _Z34R_DrawStaticModelDrawSurfPlacementPK22GfxStaticModelDrawInstP20GfxCmdBufSourceState
	mov ecx, [ebp-0x44]
	mov [ebp-0x4c], ecx
	mov [ebp-0x50], ebx
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	lea edx, [ebp-0x24]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x58]
	mov [esp], ecx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	add edi, 0x1
	cmp [ebp-0x38], edi
	jnz _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_50
	mov edx, [ebp-0x2c]
	mov ebx, [edx]
	mov [ebp-0x38], ebx
	lea ecx, [edx+0x4]
	test ebx, ebx
	jnz _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_60
_Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext_10:
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;R_DrawStaticModelCachedSurfLit(unsigned int const*, GfxCmdBufContext)
_Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov dword [ebp-0x58], 0x0
	mov dword [ebp-0x54], 0x0
	mov eax, [ebp+0x10]
	mov [ebp-0x48], eax
	mov edx, [ebp+0xc]
	mov [ebp-0x44], edx
	mov eax, rgp
	mov eax, [eax+0x2008]
	mov [edx+0xc60], eax
	mov ecx, [ebp+0xc]
	mov [esp], ecx
	call _Z32R_SetupCachedStaticModelLightingP20GfxCmdBufSourceState
	mov esi, [ebp+0x10]
	mov ebx, [ebp+0xc]
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebp-0x48]
	mov eax, [eax+0x54]
	mov [ebp-0x34], eax
	mov edx, [ebp+0x8]
	mov [ebp-0x2c], edx
	mov eax, edx
_Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_50:
	mov eax, [eax]
	mov [ebp-0x40], eax
	test eax, eax
	jnz _Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_10
	mov eax, [ebp-0x34]
	mov ecx, [ebp-0x48]
	mov [ecx+0x54], eax
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_10:
	mov edx, [ebp-0x2c]
	mov edx, [edx+0x4]
	mov [ebp-0x3c], edx
	mov ecx, [ebp-0x2c]
	add ecx, 0x8
	mov [ebp-0x30], ecx
	add eax, 0x1
	shr eax, 1
	lea eax, [ecx+eax*4]
	mov [ebp-0x2c], eax
	movzx eax, word [ecx]
	mov [esp], eax
	call _Z21R_GetCachedSModelSurfj
	mov edx, rgp
	mov ecx, [edx+0x20a0]
	movzx edx, word [eax+0x6]
	mov ecx, [ecx+0x29c]
	lea eax, [edx+edx*8]
	lea eax, [edx+eax*2]
	movzx eax, byte [ecx+eax*4+0x44]
	mov [ebp-0x38], eax
	mov eax, [ebp-0x48]
	mov [ebp+0x10], eax
	mov edx, [ebp-0x44]
	mov [ebp+0xc], edx
	mov edi, eax
	mov dword [ebp-0x24], 0x10000
	mov ecx, [ebp-0x3c]
	movzx eax, word [ecx+0x4]
	mov [ebp-0x20], eax
	mov edx, [ebp-0x30]
	movzx eax, word [edx]
	lea ecx, [eax-0x1]
	and ecx, 0xfffff000
	shl ecx, 0x9
	mov eax, gfxBuf
	mov ebx, [eax+0xc]
	lea esi, [edi+0x90]
	mov dword [esp+12], 32
	mov [esp+8], ecx
	mov [esp+4], ebx
	mov [esp], esi
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_90:
	mov ecx, [ebp-0x44]
	mov [ebp-0x58], ecx
	mov [ebp-0x54], edi
	mov eax, [ebp-0x58]
	mov edx, [ebp-0x54]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov edx, [ebp-0x44]
	mov [ebp-0x50], edx
	mov [ebp-0x4c], edi
	mov ecx, [ebp-0x38]
	mov [esp+0x8], ecx
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x3c]
	movzx eax, word [edx+0x8]
	lea edi, [eax+eax*2]
	movzx eax, word [edx+0x4]
	imul eax, [ebp-0x40]
	mov [ebp-0x20], eax
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z18R_ReserveIndexDataP18GfxCmdBufPrimStatei
	mov [ebp-0x1c], eax
	xor ebx, ebx
_Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_40:
	mov ecx, [ebp-0x30]
	movzx eax, word [ecx+ebx*2]
	mov [esp], eax
	call _Z21R_GetCachedSModelSurfj
	mov ecx, [ebp-0x3c]
	movzx edx, word [ecx+0x4]
	mov [esp+0x8], edx
	mov eax, [eax]
	lea eax, [edi+eax*4]
	mov ecx, gfxBuf
	mov edx, [ecx+0x8]
	lea eax, [edx+eax*2]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	add ebx, 0x1
	cmp [ebp-0x40], ebx
	jnz _Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_40
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	mov eax, [ebp-0x2c]
	jmp _Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext_50



;R_DrawStaticModelPreTessSurfLit(unsigned int const*, GfxCmdBufContext)
_Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov dword [ebp-0x40], 0x0
	mov dword [ebp-0x3c], 0x0
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov eax, [ebp+0x10]
	mov [ebp-0x30], eax
	mov edx, [ebp+0xc]
	mov [ebp-0x34], edx
	mov eax, rgp
	mov eax, [eax+0x2008]
	mov [edx+0xc60], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z32R_SetupCachedStaticModelLightingP20GfxCmdBufSourceState
	mov esi, [ebp+0x10]
	mov ebx, [ebp+0xc]
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebp+0x8]
	mov [ebp-0x1c], eax
_Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_50:
	lea edx, [ebp-0x1c]
	mov [esp], edx
	call _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	mov [ebp-0x4c], eax
	test eax, eax
	jnz _Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_10
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_10:
	lea eax, [ebp-0x1c]
	mov [esp], eax
	call _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	mov edi, eax
	lea edx, [ebp-0x1c]
	mov [esp], edx
	call _Z21R_ReadPrimDrawSurfIntP13GfxReadCmdBuf
	mov [ebp-0x50], eax
	mov eax, [ebp-0x30]
	mov [ebp+0x10], eax
	mov edx, [ebp-0x34]
	mov [ebp+0xc], edx
	mov [ebp-0x2c], eax
	mov edx, edi
	movzx ebx, dl
	mov eax, edi
	movzx esi, ah
	shr edi, 0x10
	mov [esp], edi
	call _Z21R_GetCachedSModelSurfj
	mov edx, rgp
	mov ecx, [edx+0x20a0]
	movzx eax, word [eax+0x6]
	lea edx, [eax+eax*8]
	lea edx, [eax+edx*2]
	mov eax, [ecx+0x29c]
	lea edx, [eax+edx*4]
	mov [ebp-0x38], edx
	mov [esp+0x8], ebx
	mov [esp+0x4], esi
	mov eax, [edx+0x38]
	mov [esp], eax
	call _Z16XModelGetSurfacePK6XModelii
	mov dword [ebp-0x28], 0x10000
	movzx eax, word [eax+0x4]
	imul eax, [ebp-0x4c]
	mov [ebp-0x24], eax
	lea ecx, [edi-0x1]
	and ecx, 0xfffff000
	shl ecx, 0x9
	mov eax, gfxBuf
	mov esi, [eax+0xc]
	mov ebx, [ebp-0x2c]
	add ebx, 0x90
	mov dword [esp+12], 32
	mov [esp+8], ecx
	mov [esp+4], esi
	mov [esp], ebx
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_90:
	mov edx, [ebp-0x34]
	mov [ebp-0x48], edx
	mov eax, [ebp-0x2c]
	mov [ebp-0x44], eax
	mov eax, [ebp-0x48]
	mov edx, [ebp-0x44]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov edx, [ebp-0x38]
	movzx eax, byte [edx+0x44]
	mov edx, [ebp-0x34]
	mov [ebp-0x40], edx
	mov edx, [ebp-0x2c]
	mov [ebp-0x3c], edx
	mov [esp+0x8], eax
	mov eax, [ebp-0x40]
	mov edx, [ebp-0x3c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x34]
	mov eax, [edx+0xca8]
	mov ecx, [eax+0x11e6a0]
	cmp ecx, [ebx+0x4]
	jz _Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_40
	mov [esp+4], ecx
	mov [esp], ebx
	call _Z15R_ChangeIndicesP18GfxCmdBufPrimStateP21IDirect3DIndexBuffer9
_Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_40:
	mov eax, [ebp-0x50]
	mov [ebp-0x20], eax
	lea eax, [ebp-0x28]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	jmp _Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext_50


;R_DrawStaticModelSkinnedSurfLit(unsigned int const*, GfxCmdBufContext)
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x8c
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov dword [ebp-0x58], 0x0
	mov dword [ebp-0x54], 0x0
	mov ecx, [ebp+0x10]
	mov [ebp-0x44], ecx
	mov ebx, [ebp+0xc]
	mov [ebp-0x40], ebx
	mov ecx, rgp
	mov ecx, [ecx+0x2008]
	mov [ebx+0xc60], ecx
	mov edx, [ebp+0x10]
	mov eax, [ebp+0xc]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebp-0x44]
	mov eax, [eax+0x54]
	mov [ebp-0x34], eax
	mov edx, [ebp+0x8]
	mov ebx, [edx]
	mov [ebp-0x38], ebx
	lea ecx, [edx+0x4]
	test ebx, ebx
	jz _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_10
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_70:
	mov eax, ebx
	add eax, 0x1
	shr eax, 1
	lea eax, [ecx+eax*4+0x4]
	mov [ebp-0x2c], eax
	mov esi, [edx+0x4]
	add edx, 0x8
	mov [ebp-0x3c], edx
	mov eax, [ebp-0x44]
	mov [ebp+0x10], eax
	mov edx, [ebp-0x40]
	mov [ebp+0xc], edx
	mov ecx, [ebp+0xc]
	mov ebx, [ebp+0x10]
	mov [ebp-0x68], ecx
	mov [ebp-0x64], ebx
	mov [ebp-0x30], ebx
	add ebx, 0x90
	mov [ebp-0x6c], ebx
	mov [esp], esi
	call _Z18XSurfaceGetNumTrisPK8XSurface
	mov [ebp-0x20], eax
	mov [esp], esi
	call _Z19XSurfaceGetNumVertsPK8XSurface
	mov [ebp-0x24], eax
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov eax, [esi+0xc]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	mov eax, gfxBuf
	mov ebx, [eax+0x70]
	mov edx, [ebx]
	mov ecx, [ebp-0x24]
	mov eax, ecx
	shl eax, 0x5
	add eax, edx
	cmp eax, [ebx+0x4]
	jle _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_20
	mov dword [ebx], 0x0
	mov ecx, [ebp-0x24]
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_20:
	mov dword [esp+0xc], 0x20
	mov [esp+0x8], ecx
	mov eax, [esi+0x1c]
	mov [esp+0x4], eax
	mov edx, [ebp-0x30]
	mov [esp], edx
	call _Z15R_SetVertexDataP14GfxCmdBufStatePKvii
	mov ebx, eax
	mov eax, gfxBuf
	mov eax, [eax+0x70]
	mov ecx, [eax+0x8]
	mov eax, [ebp-0x6c]
	mov dword [esp+12], 32
	mov [esp+8], ebx
	mov [esp+4], ecx
	mov [esp], eax
	call _Z17R_SetStreamSourceP18GfxCmdBufPrimStateP22IDirect3DVertexBuffer9jj
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_120:
	mov eax, rgp
	mov eax, [eax+0x20a0]
	mov eax, [eax+0x29c]
	mov [ebp-0x5c], eax
	xor edi, edi
	mov ecx, eax
	jmp _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_50
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_60:
	mov ecx, [ebp-0x5c]
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_50:
	mov edx, [ebp-0x3c]
	movzx eax, word [edx+edi*2]
	lea ebx, [eax+eax*8]
	lea ebx, [eax+ebx*2]
	lea ebx, [ecx+ebx*4]
	movzx esi, word [ebx+0x46]
	mov eax, [ebp-0x40]
	mov [ebp-0x68], eax
	mov edx, [ebp-0x30]
	mov [ebp-0x64], edx
	movzx eax, byte [ebx+0x44]
	mov [ebp-0x54], edx
	mov ecx, [ebp-0x68]
	mov [ebp-0x58], ecx
	mov [esp+0x8], eax
	mov eax, [ebp-0x58]
	mov edx, [ebp-0x54]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x68]
	mov eax, ebx
	call _Z34R_DrawStaticModelDrawSurfPlacementPK22GfxStaticModelDrawInstP20GfxCmdBufSourceState
	mov edx, [ebp-0x68]
	mov [esp+0x4], edx
	mov [esp], esi
	call _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	mov ecx, [ebp-0x30]
	mov [ebp-0x4c], ecx
	mov ebx, [ebp-0x68]
	mov [ebp-0x50], ebx
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	lea edx, [ebp-0x24]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x6c]
	mov [esp], ecx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	add edi, 0x1
	cmp [ebp-0x38], edi
	jnz _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_60
	mov edx, [ebp-0x2c]
	mov ebx, [edx]
	mov [ebp-0x38], ebx
	lea ecx, [edx+0x4]
	test ebx, ebx
	jnz _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_70
_Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext_10:
	mov eax, [ebp-0x34]
	mov ebx, [ebp-0x44]
	mov [ebx+0x54], eax
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret

;Initialized global or static variables of r_draw_staticmodel:
SECTION .data


;Initialized constant data of r_draw_staticmodel:
SECTION .rdata


;Zero initialized global or static variables of r_draw_staticmodel:
SECTION .bss



;All cstrings:
SECTION .rdata



;All constant floats and doubles:
SECTION .rdata

