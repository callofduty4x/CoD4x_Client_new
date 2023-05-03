extern _ZN14MacOpenGLUtils34ConvertD3DProjectionMatrixToOpenGLEPfff
extern _ZN15CDirect3DDevice24DrawIndexedPrimitiveFastEjjj


;R_DeriveOpenGLMatrices(GfxCmdBufSourceState*)
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x22c
	mov edi, [ebp+0x8]
	add edi, 0xcb0
	mov eax, [ebp+0x8]
	cmp dword [eax+0xf64], 0x1
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_10
	mov edx, [eax+0xf58]
	test edx, edx
	jnz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_20
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_50:
	mov eax, [ebp+0x8]
	cvtsi2ss xmm0, dword [eax+0xf6c]
	movss [ebp-0x220], xmm0
	cvtsi2ss xmm0, dword [eax+0xf68]
	movss [ebp-0x21c], xmm0
	movss xmm0, dword [ebp-0x220]
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_80:
	mov eax, [edi]
	mov [ebp-0x58], eax
	mov eax, [edi+0x4]
	mov [ebp-0x54], eax
	mov eax, [edi+0x8]
	mov [ebp-0x50], eax
	mov eax, [edi+0xc]
	mov [ebp-0x4c], eax
	mov eax, [edi+0x10]
	mov [ebp-0x48], eax
	mov eax, [edi+0x14]
	mov [ebp-0x44], eax
	mov eax, [edi+0x18]
	mov [ebp-0x40], eax
	mov eax, [edi+0x1c]
	mov [ebp-0x3c], eax
	mov eax, [edi+0x20]
	mov [ebp-0x38], eax
	mov eax, [edi+0x24]
	mov [ebp-0x34], eax
	mov eax, [edi+0x28]
	mov [ebp-0x30], eax
	mov eax, [edi+0x2c]
	mov [ebp-0x2c], eax
	mov eax, [edi+0x30]
	mov [ebp-0x28], eax
	mov eax, [edi+0x34]
	mov [ebp-0x24], eax
	mov eax, [edi+0x38]
	mov [ebp-0x20], eax
	mov eax, [edi+0x3c]
	mov [ebp-0x1c], eax
	mov eax, [edi+0x40]
	mov [ebp-0x118], eax
	mov eax, [edi+0x44]
	mov [ebp-0x114], eax
	mov eax, [edi+0x48]
	mov [ebp-0x110], eax
	mov eax, [edi+0x4c]
	mov [ebp-0x10c], eax
	mov eax, [edi+0x50]
	mov [ebp-0x108], eax
	mov eax, [edi+0x54]
	mov [ebp-0x104], eax
	mov eax, [edi+0x58]
	mov [ebp-0x100], eax
	mov eax, [edi+0x5c]
	mov [ebp-0xfc], eax
	mov eax, [edi+0x60]
	mov [ebp-0xf8], eax
	mov eax, [edi+0x64]
	mov [ebp-0xf4], eax
	mov eax, [edi+0x68]
	mov [ebp-0xf0], eax
	mov eax, [edi+0x6c]
	mov [ebp-0xec], eax
	mov eax, [edi+0x70]
	mov [ebp-0xe8], eax
	mov eax, [edi+0x74]
	mov [ebp-0xe4], eax
	mov eax, [edi+0x78]
	mov [ebp-0xe0], eax
	mov eax, [edi+0x7c]
	mov [ebp-0xdc], eax
	lea ebx, [ebp-0x118]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x21c]
	movss [esp+0x4], xmm0
	mov [esp], ebx
	call _ZN14MacOpenGLUtils34ConvertD3DProjectionMatrixToOpenGLEPfff
	lea eax, [ebp-0x98]
	mov [esp+0x8], eax
	mov [esp+0x4], ebx
	lea edx, [ebp-0x58]
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	mov edx, [ebp+0x8]
	mov eax, [edx+0x80]
	mov [ebp-0x218], eax
	mov eax, [edx+0x84]
	mov [ebp-0x214], eax
	mov eax, [edx+0x88]
	mov [ebp-0x210], eax
	mov eax, [edx+0x8c]
	mov [ebp-0x20c], eax
	mov eax, [edx+0x90]
	mov [ebp-0x208], eax
	mov eax, [edx+0x94]
	mov [ebp-0x204], eax
	mov eax, [edx+0x98]
	mov [ebp-0x200], eax
	mov eax, [edx+0x9c]
	mov [ebp-0x1fc], eax
	mov eax, [edx+0xa0]
	mov [ebp-0x1f8], eax
	mov eax, [edx+0xa4]
	mov [ebp-0x1f4], eax
	mov eax, [edx+0xa8]
	mov [ebp-0x1f0], eax
	mov eax, [edx+0xac]
	mov [ebp-0x1ec], eax
	mov eax, [edx+0xb0]
	mov [ebp-0x1e8], eax
	mov eax, [edx+0xb4]
	mov [ebp-0x1e4], eax
	mov eax, [edx+0xb8]
	mov [ebp-0x1e0], eax
	mov eax, [edx+0xbc]
	mov [ebp-0x1dc], eax
	cmp dword [edx+0xf10], 0x2
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_30
	mov eax, edx
	add eax, 0xef4
	movss xmm0, dword [ebp-0x1e8]
	mov edx, [ebp+0x8]
	addss xmm0, [edx+0xef4]
	movss [ebp-0x1e8], xmm0
	lea edx, [ebp-0x218]
	movss xmm0, dword [ebp-0x1e4]
	addss xmm0, [eax+0x4]
	movss [ebp-0x1e4], xmm0
	movss xmm0, dword [ebp-0x1e0]
	addss xmm0, [eax+0x8]
	movss [ebp-0x1e0], xmm0
	lea esi, [ebp-0xd8]
	mov [esp+0x8], esi
	lea eax, [ebp-0x98]
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_130:
	mov edx, [ebp+0x8]
	mov [esp+0x4], edx
	mov [esp], esi
	call _Z17MatrixTranspose44PKfPf
	mov eax, [ebp-0x118]
	mov [ebp-0x158], eax
	mov eax, [ebp-0x114]
	mov [ebp-0x154], eax
	mov eax, [ebp-0x110]
	mov [ebp-0x150], eax
	mov eax, [ebp-0x10c]
	mov [ebp-0x14c], eax
	mov eax, [ebp-0x108]
	mov [ebp-0x148], eax
	mov eax, [ebp-0x104]
	mov [ebp-0x144], eax
	mov eax, [ebp-0x100]
	mov [ebp-0x140], eax
	mov eax, [ebp-0xfc]
	mov [ebp-0x13c], eax
	mov eax, [ebp-0xf8]
	mov [ebp-0x138], eax
	mov eax, [ebp-0xf4]
	mov [ebp-0x134], eax
	mov eax, [ebp-0xf0]
	mov [ebp-0x130], eax
	mov eax, [ebp-0xec]
	mov [ebp-0x12c], eax
	mov eax, [ebp-0xe8]
	mov [ebp-0x128], eax
	mov eax, [ebp-0xe4]
	mov [ebp-0x124], eax
	mov eax, [ebp-0xe0]
	mov [ebp-0x120], eax
	mov eax, [ebp-0xdc]
	mov [ebp-0x11c], eax
	mov eax, [ebp+0x8]
	cmp dword [eax+0xf10], 0x2
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_40
	lea edx, [ebp-0x158]
	add eax, 0x40
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z17MatrixTranspose44PKfPf
	add esp, 0x22c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_20:
	mov ecx, [eax+0xf5c]
	test ecx, ecx
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_50
	cmp dword [eax+0xf38], 0x2
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_60
	mov eax, r_scaleViewport
	mov eax, [eax]
	movss xmm1, dword [eax+0xc]
	movss xmm3, dword [_float_1_00000000]
	ucomiss xmm1, xmm3
	jnz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_70
	jp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_70
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_60:
	cvtsi2ss xmm0, ecx
	movss [ebp-0x220], xmm0
	cvtsi2ss xmm0, edx
	movss [ebp-0x21c], xmm0
	movss xmm0, dword [ebp-0x220]
	jmp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_80
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_10:
	mov ecx, [eax+0xf68]
	mov edx, [eax+0xf6c]
	cmp dword [eax+0xf38], 0x2
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_90
	mov eax, r_scaleViewport
	mov eax, [eax]
	movss xmm1, dword [eax+0xc]
	movss xmm3, dword [_float_1_00000000]
	ucomiss xmm1, xmm3
	jz _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_100
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_140:
	cvtsi2ss xmm2, edx
	cvtsi2ss xmm0, ecx
	mulss xmm0, xmm1
	cvttss2si eax, xmm0
	cmp eax, 0x1
	jle _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_110
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_150:
	cvtsi2ss xmm0, eax
	movss [ebp-0x21c], xmm0
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_160:
	mulss xmm1, xmm2
	cvttss2si eax, xmm1
	cmp eax, 0x1
	jle _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_120
	cvtsi2ss xmm0, eax
	movss [ebp-0x220], xmm0
	jmp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_80
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_30:
	mov eax, [edi+0x40]
	mov [ebp-0x198], eax
	mov eax, [edi+0x44]
	mov [ebp-0x194], eax
	mov eax, [edi+0x48]
	mov [ebp-0x190], eax
	mov eax, [edi+0x4c]
	mov [ebp-0x18c], eax
	mov eax, [edi+0x50]
	mov [ebp-0x188], eax
	mov eax, [edi+0x54]
	mov [ebp-0x184], eax
	mov eax, [edi+0x58]
	mov [ebp-0x180], eax
	mov eax, [edi+0x5c]
	mov [ebp-0x17c], eax
	mov eax, [edi+0x60]
	mov [ebp-0x178], eax
	mov eax, [edi+0x64]
	mov [ebp-0x174], eax
	mov eax, [edi+0x68]
	mov [ebp-0x170], eax
	mov eax, [edi+0x6c]
	mov [ebp-0x16c], eax
	mov eax, [edi+0x70]
	mov [ebp-0x168], eax
	mov eax, [edi+0x74]
	mov [ebp-0x164], eax
	mov eax, [edi+0x7c]
	mov [ebp-0x15c], eax
	mov eax, [edi+0x134]
	mov [ebp-0x160], eax
	lea esi, [ebp-0x198]
	movss xmm0, dword [ebp-0x220]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x21c]
	movss [esp+0x4], xmm0
	mov [esp], esi
	call _ZN14MacOpenGLUtils34ConvertD3DProjectionMatrixToOpenGLEPfff
	lea ebx, [ebp-0x1d8]
	mov [esp+0x8], ebx
	mov [esp+0x4], esi
	lea eax, [ebp-0x58]
	mov [esp], eax
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	lea eax, [ebp-0x1a8]
	mov [esp+0x8], eax
	mov [esp+0x4], ebx
	mov eax, [ebp+0x8]
	add eax, 0xef4
	mov [esp], eax
	call _Z23MatrixTransformVector44PKfPA4_S_Pf
	lea esi, [ebp-0xd8]
	mov [esp+0x8], esi
	mov [esp+0x4], ebx
	lea eax, [ebp-0x218]
	mov [esp], eax
	call _Z16MatrixMultiply44PA4_KfS1_PA4_f
	jmp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_130
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_40:
	mov eax, [edi+0x40]
	mov [ebp-0x198], eax
	mov eax, [edi+0x44]
	mov [ebp-0x194], eax
	mov eax, [edi+0x48]
	mov [ebp-0x190], eax
	mov eax, [edi+0x4c]
	mov [ebp-0x18c], eax
	mov eax, [edi+0x50]
	mov [ebp-0x188], eax
	mov eax, [edi+0x54]
	mov [ebp-0x184], eax
	mov eax, [edi+0x58]
	mov [ebp-0x180], eax
	mov eax, [edi+0x5c]
	mov [ebp-0x17c], eax
	mov eax, [edi+0x60]
	mov [ebp-0x178], eax
	mov eax, [edi+0x64]
	mov [ebp-0x174], eax
	mov eax, [edi+0x68]
	mov [ebp-0x170], eax
	mov eax, [edi+0x6c]
	mov [ebp-0x16c], eax
	mov eax, [edi+0x70]
	mov [ebp-0x168], eax
	mov eax, [edi+0x74]
	mov [ebp-0x164], eax
	mov eax, [edi+0x7c]
	mov [ebp-0x15c], eax
	mov eax, [edi+0x134]
	mov [ebp-0x160], eax
	lea eax, [ebp-0x198]
	movss xmm0, dword [ebp-0x220]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x21c]
	movss [esp+0x4], xmm0
	mov [esp], eax
	call _ZN14MacOpenGLUtils34ConvertD3DProjectionMatrixToOpenGLEPfff
	mov eax, [ebp+0x8]
	lea edx, [ebp-0x158]
	add eax, 0x40
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z17MatrixTranspose44PKfPf
	add esp, 0x22c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_100:
	jp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_140
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_90:
	cvtsi2ss xmm0, edx
	movss [ebp-0x220], xmm0
	cvtsi2ss xmm0, ecx
	movss [ebp-0x21c], xmm0
	movss xmm0, dword [ebp-0x220]
	jmp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_80
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_70:
	cvtsi2ss xmm2, ecx
	cvtsi2ss xmm0, edx
	mulss xmm0, xmm1
	cvttss2si eax, xmm0
	cmp eax, 0x1
	jg _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_150
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_110:
	movss [ebp-0x21c], xmm3
	jmp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_160
_Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_120:
	movss [ebp-0x220], xmm3
	movaps xmm0, xmm3
	jmp _Z22R_DeriveOpenGLMatricesP20GfxCmdBufSourceState_80
	nop




;R_DrawIndexedPrimitive(GfxCmdBufPrimState*, GfxDrawPrimArgs const*)
_Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	mov edx, [ebp+0xc]
	mov eax, [edx+0x4]
	mov [esp+0xc], eax
	mov eax, [edx+0x8]
	mov [esp+0x8], eax
	mov eax, [edx]
	mov [esp+0x4], eax
	mov eax, [ebp+0x8]
	mov eax, [eax]
	mov [esp], eax
	call _ZN15CDirect3DDevice24DrawIndexedPrimitiveFastEjjj
	leave
	ret




;R_SetupPass(GfxCmdBufContext, unsigned int)
_Z11R_SetupPass16GfxCmdBufContextj:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xdc
	mov dword [ebp-0x78], 0x0
	mov dword [ebp-0x74], 0x0
	mov dword [ebp-0x88], 0x0
	mov dword [ebp-0x84], 0x0
	mov dword [ebp-0xa0], 0x0
	mov dword [ebp-0x9c], 0x0
	mov dword [ebp-0xa8], 0x0
	mov dword [ebp-0xa4], 0x0
	mov ebx, [ebp+0x8]
	mov esi, [ebp+0xc]
	mov eax, [ebp+0x10]
	mov [ebp-0x60], ebx
	mov edi, esi
	lea ecx, [eax+eax*4]
	mov edx, [esi+0xc0]
	lea edx, [edx+ecx*4+0x8]
	mov [ebp-0x90], edx
	mov [esi+0xc4], edx
	mov [esi+0xc8], eax
	mov ecx, [esi+0xb8]
	mov edx, [esi+0xbc]
	movzx edx, byte [edx+ecx+0x18]
	add eax, edx
	mov edx, [ecx+0x4c]
	lea eax, [edx+eax*8]
	mov edx, [eax]
	mov [ebp-0x58], edx
	mov eax, [eax+0x4]
	mov [ebp-0x5c], eax
	cmp edx, [esi+0x9dc]
	jz _Z11R_SetupPass16GfxCmdBufContextj_10
	mov [esp+0x4], edx
	mov [esp], esi
	call _Z15R_ChangeState_0P14GfxCmdBufStatej
	mov ecx, [ebp-0x58]
	mov [esi+0x9dc], ecx
	mov eax, [ebp-0x5c]
_Z11R_SetupPass16GfxCmdBufContextj_10:
	cmp eax, [edi+0x9e0]
	jz _Z11R_SetupPass16GfxCmdBufContextj_20
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z15R_ChangeState_1P14GfxCmdBufStatej
	mov edx, [ebp-0x5c]
	mov [edi+0x9e0], edx
_Z11R_SetupPass16GfxCmdBufContextj_20:
	mov ecx, [ebp-0x90]
	mov eax, [ecx+0x8]
	cmp eax, [edi+0x9ec]
	jz _Z11R_SetupPass16GfxCmdBufContextj_30
	mov edx, [edi+0x90]
	test eax, eax
	jz _Z11R_SetupPass16GfxCmdBufContextj_40
	mov ecx, [eax+0x4]
_Z11R_SetupPass16GfxCmdBufContextj_250:
	mov [edx+0x3b0], ecx
	mov [edi+0x9ec], eax
	mov eax, [ebp-0x90]
_Z11R_SetupPass16GfxCmdBufContextj_240:
	movzx ecx, byte [eax+0xe]
	test cl, cl
	jz _Z11R_SetupPass16GfxCmdBufContextj_50
	movzx edx, byte [eax+0xd]
	mov [ebp-0xac], edx
	movzx edx, byte [eax+0xc]
	add edx, [ebp-0xac]
	mov [ebp-0xac], edx
	mov edx, [eax+0x10]
	mov eax, [ebp-0xac]
	lea edx, [edx+eax*8]
	mov [ebp-0x34], edx
	movzx ecx, cl
	mov [ebp-0x8c], ecx
	mov ebx, [ebp-0x60]
	mov [ebp-0x98], ebx
	mov [ebp-0x94], edi
	mov [ebp-0x54], ebx
	mov edx, [ebp-0x94]
	mov [ebp-0x50], edx
	mov ecx, [edx+0xb8]
	mov [ebp-0x80], ecx
	mov edi, [ecx+0x48]
	mov dword [ebp-0x38], 0x0
_Z11R_SetupPass16GfxCmdBufContextj_130:
	mov edx, [ebp-0x8c]
	sub edx, [ebp-0x38]
	mov [ebp-0x2c], edx
	mov ecx, [ebp-0x34]
	cmp word [ecx], 0x0
	jnz _Z11R_SetupPass16GfxCmdBufContextj_60
	mov ebx, [ecx+0x4]
	cmp ebx, [edi]
	jz _Z11R_SetupPass16GfxCmdBufContextj_70
	lea ecx, [edi+0x20]
	mov edx, ecx
	jmp _Z11R_SetupPass16GfxCmdBufContextj_80
_Z11R_SetupPass16GfxCmdBufContextj_90:
	add ecx, 0x20
_Z11R_SetupPass16GfxCmdBufContextj_80:
	mov edi, ecx
	mov eax, [edx]
	add edx, 0x20
	cmp eax, ebx
	jnz _Z11R_SetupPass16GfxCmdBufContextj_90
	mov ebx, [ebp-0x34]
_Z11R_SetupPass16GfxCmdBufContextj_150:
	movzx eax, word [ebx+0x2]
	movzx edx, ax
	mov [ebp-0x7c], edx
	mov ecx, [ebp-0x50]
	mov dword [ecx+edx*8+0xd8], 0xffffffff
	mov dword [ecx+edx*8+0xdc], 0xffffffff
	mov edx, [ecx+0x90]
	lea ebx, [edi+0x10]
	cmp dword [ebp-0x7c], 0x1f
	jbe _Z11R_SetupPass16GfxCmdBufContextj_100
	cmp ax, 0x20
	jz _Z11R_SetupPass16GfxCmdBufContextj_110
	lea esi, [edx+0x400]
_Z11R_SetupPass16GfxCmdBufContextj_160:
	mov [esp+0x4], ebx
	mov [esp], esi
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z11R_SetupPass16GfxCmdBufContextj_120
_Z11R_SetupPass16GfxCmdBufContextj_140:
	add dword [ebp-0x34], 0x8
	add dword [ebp-0x38], 0x1
	mov eax, [ebp-0x38]
	cmp [ebp-0x8c], eax
	jnz _Z11R_SetupPass16GfxCmdBufContextj_130
_Z11R_SetupPass16GfxCmdBufContextj_50:
	add esp, 0xdc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z11R_SetupPass16GfxCmdBufContextj_120:
	mov eax, [ebx]
	mov [esi], eax
	mov eax, [ebx+0x4]
	mov [esi+0x4], eax
	mov eax, [ebx+0x8]
	mov [esi+0x8], eax
	mov eax, [ebx+0xc]
	mov [esi+0xc], eax
	mov eax, [ebx+0x10]
	mov [esi+0x10], eax
	mov eax, [ebx+0x14]
	mov [esi+0x14], eax
	mov eax, [ebx+0x18]
	mov [esi+0x18], eax
	mov eax, [ebx+0x1c]
	mov [esi+0x1c], eax
	mov eax, [ebx+0x20]
	mov [esi+0x20], eax
	mov eax, [ebx+0x24]
	mov [esi+0x24], eax
	mov eax, [ebx+0x28]
	mov [esi+0x28], eax
	mov eax, [ebx+0x2c]
	mov [esi+0x2c], eax
	mov eax, [ebx+0x30]
	mov [esi+0x30], eax
	mov eax, [ebx+0x34]
	mov [esi+0x34], eax
	mov eax, [ebx+0x38]
	mov [esi+0x38], eax
	mov eax, [ebx+0x3c]
	mov [esi+0x3c], eax
_Z11R_SetupPass16GfxCmdBufContextj_100:
	mov [esp+0xc], ebx
	mov dword [esp+0x8], 0x1
	mov ebx, [ebp-0x7c]
	mov [esp+0x4], ebx
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z11R_SetupPass16GfxCmdBufContextj_140
_Z11R_SetupPass16GfxCmdBufContextj_70:
	mov ebx, ecx
	jmp _Z11R_SetupPass16GfxCmdBufContextj_150
_Z11R_SetupPass16GfxCmdBufContextj_110:
	lea esi, [edx+0x3c0]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_160
_Z11R_SetupPass16GfxCmdBufContextj_60:
	mov dword [ebp-0x3c], 0x0
	mov edi, [ebp-0x2c]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_170
_Z11R_SetupPass16GfxCmdBufContextj_210:
	cmp ax, 0x20
	jz _Z11R_SetupPass16GfxCmdBufContextj_180
	lea ebx, [edx+0x400]
_Z11R_SetupPass16GfxCmdBufContextj_230:
	mov [esp+0x4], esi
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z11R_SetupPass16GfxCmdBufContextj_190
_Z11R_SetupPass16GfxCmdBufContextj_220:
	add dword [ebp-0x34], 0x8
	add dword [ebp-0x3c], 0x1
	mov ebx, [ebp-0x2c]
	cmp [ebp-0x3c], ebx
	jz _Z11R_SetupPass16GfxCmdBufContextj_50
	mov edi, ebx
_Z11R_SetupPass16GfxCmdBufContextj_170:
	sub edi, [ebp-0x3c]
	mov eax, [ebp-0x34]
	cmp word [eax], 0x1
	jnz _Z11R_SetupPass16GfxCmdBufContextj_200
	mov esi, [eax+0x4]
	movzx eax, word [eax+0x2]
	movzx edi, ax
	mov edx, [ebp-0x50]
	mov dword [edx+edi*8+0xd8], 0xffffffff
	mov dword [edx+edi*8+0xdc], 0xffffffff
	mov ecx, [ebp-0x50]
	mov edx, [ecx+0x90]
	cmp edi, 0x1f
	ja _Z11R_SetupPass16GfxCmdBufContextj_210
	mov [esp+0xc], esi
	mov dword [esp+0x8], 0x1
	mov [esp+0x4], edi
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z11R_SetupPass16GfxCmdBufContextj_220
_Z11R_SetupPass16GfxCmdBufContextj_190:
	mov eax, [esi]
	mov [ebx], eax
	mov eax, [esi+0x4]
	mov [ebx+0x4], eax
	mov eax, [esi+0x8]
	mov [ebx+0x8], eax
	mov eax, [esi+0xc]
	mov [ebx+0xc], eax
	mov eax, [esi+0x10]
	mov [ebx+0x10], eax
	mov eax, [esi+0x14]
	mov [ebx+0x14], eax
	mov eax, [esi+0x18]
	mov [ebx+0x18], eax
	mov eax, [esi+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [esi+0x20]
	mov [ebx+0x20], eax
	mov eax, [esi+0x24]
	mov [ebx+0x24], eax
	mov eax, [esi+0x28]
	mov [ebx+0x28], eax
	mov eax, [esi+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [esi+0x30]
	mov [ebx+0x30], eax
	mov eax, [esi+0x34]
	mov [ebx+0x34], eax
	mov eax, [esi+0x38]
	mov [ebx+0x38], eax
	mov eax, [esi+0x3c]
	mov [ebx+0x3c], eax
	mov [esp+0xc], esi
	mov dword [esp+0x8], 0x1
	mov [esp+0x4], edi
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z11R_SetupPass16GfxCmdBufContextj_220
_Z11R_SetupPass16GfxCmdBufContextj_180:
	lea ebx, [edx+0x3c0]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_230
_Z11R_SetupPass16GfxCmdBufContextj_30:
	mov eax, ecx
	jmp _Z11R_SetupPass16GfxCmdBufContextj_240
_Z11R_SetupPass16GfxCmdBufContextj_40:
	xor ecx, ecx
	jmp _Z11R_SetupPass16GfxCmdBufContextj_250
_Z11R_SetupPass16GfxCmdBufContextj_200:
	mov edx, [ebp-0x80]
	mov ebx, [edx+0x44]
	mov dword [ebp-0x40], 0x0
_Z11R_SetupPass16GfxCmdBufContextj_330:
	mov edx, edi
	sub edx, [ebp-0x40]
	mov [ebp-0x30], edx
	mov ecx, [ebp-0x34]
	cmp word [ecx], 0x2
	jnz _Z11R_SetupPass16GfxCmdBufContextj_260
	mov ecx, [ebp-0x54]
	mov [ebp-0x98], ecx
	mov eax, [ebp-0x50]
	mov [ebp-0x94], eax
	mov [ebp-0x4c], ecx
	mov eax, [ebp-0x34]
	mov ecx, [eax+0x4]
	cmp ecx, [ebx]
	jz _Z11R_SetupPass16GfxCmdBufContextj_270
	lea eax, [ebx+0xc]
	mov edx, eax
	jmp _Z11R_SetupPass16GfxCmdBufContextj_280
_Z11R_SetupPass16GfxCmdBufContextj_290:
	lea eax, [ebx+0xc]
_Z11R_SetupPass16GfxCmdBufContextj_280:
	mov ebx, eax
	mov eax, [edx]
	add edx, 0xc
	cmp ecx, eax
	jnz _Z11R_SetupPass16GfxCmdBufContextj_290
_Z11R_SetupPass16GfxCmdBufContextj_270:
	cmp byte [ebx+0x7], 0xb
	jz _Z11R_SetupPass16GfxCmdBufContextj_300
	mov esi, [ebx+0x8]
_Z11R_SetupPass16GfxCmdBufContextj_350:
	movzx eax, byte [ebx+0x6]
	mov [ebp-0x69], al
	mov edx, rg
	cmp byte [edx+0x2214], 0x0
	jz _Z11R_SetupPass16GfxCmdBufContextj_310
	cmp dword [esi], 0x3
	jz _Z11R_SetupPass16GfxCmdBufContextj_320
_Z11R_SetupPass16GfxCmdBufContextj_310:
	mov ecx, [ebp-0x34]
	movzx edx, word [ecx+0x2]
	mov eax, [ebp-0x50]
	mov [ebp-0x74], eax
	mov ecx, [ebp-0x4c]
	mov [ebp-0x78], ecx
	mov [esp+0x10], esi
	movzx eax, byte [ebp-0x69]
	mov [esp+0xc], eax
	mov [esp+0x8], edx
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z12R_SetSampler16GfxCmdBufContextjhPK8GfxImage
	add dword [ebp-0x34], 0x8
	add dword [ebp-0x40], 0x1
	cmp edi, [ebp-0x40]
	jnz _Z11R_SetupPass16GfxCmdBufContextj_330
	jmp _Z11R_SetupPass16GfxCmdBufContextj_50
_Z11R_SetupPass16GfxCmdBufContextj_300:
	mov edx, [ebx+0x8]
	mov esi, [edx+0x40]
	mov eax, r_drawWater
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z11R_SetupPass16GfxCmdBufContextj_340
	mov ecx, [ebp-0x4c]
	mov eax, [ecx+0xf40]
_Z11R_SetupPass16GfxCmdBufContextj_380:
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z20R_UploadWaterTextureP7water_tf
	jmp _Z11R_SetupPass16GfxCmdBufContextj_350
_Z11R_SetupPass16GfxCmdBufContextj_320:
	movzx eax, byte [ebx+0x7]
	cmp al, 0x5
	jz _Z11R_SetupPass16GfxCmdBufContextj_360
	cmp al, 0x8
	jz _Z11R_SetupPass16GfxCmdBufContextj_370
	cmp al, 0x2
	jnz _Z11R_SetupPass16GfxCmdBufContextj_310
	mov eax, r_colorMap
	mov eax, [eax]
	cmp dword [eax+0xc], 0x1
	jz _Z11R_SetupPass16GfxCmdBufContextj_310
_Z11R_SetupPass16GfxCmdBufContextj_530:
	mov [esp], eax
	call _Z24R_OverrideGrayscaleImagePK6dvar_s
	mov esi, eax
	jmp _Z11R_SetupPass16GfxCmdBufContextj_310
_Z11R_SetupPass16GfxCmdBufContextj_340:
	mov ecx, rg
	mov eax, [ecx+0x22fc]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_380
_Z11R_SetupPass16GfxCmdBufContextj_360:
	mov eax, r_normalMap
	mov eax, [eax]
	mov eax, [eax+0xc]
	test eax, eax
	jnz _Z11R_SetupPass16GfxCmdBufContextj_310
	mov eax, rgp
	mov esi, [eax+0x201c]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_310
_Z11R_SetupPass16GfxCmdBufContextj_260:
	mov dword [ebp-0x44], 0x0
	mov esi, [ebp-0x30]
_Z11R_SetupPass16GfxCmdBufContextj_490:
	sub esi, [ebp-0x44]
	mov edx, [ebp-0x34]
	cmp word [edx], 0x3
	jnz _Z11R_SetupPass16GfxCmdBufContextj_390
	mov ecx, edx
	mov ebx, [ebp-0x54]
	mov [ebp-0x98], ebx
	mov eax, [ebp-0x50]
	mov [ebp-0x94], eax
	mov ebx, [ebp-0x98]
	mov edx, [ebp-0x98]
	mov [ebp-0x48], edx
	mov esi, eax
	movzx edx, word [ecx+0x4]
	cmp dx, 0x39
	jbe _Z11R_SetupPass16GfxCmdBufContextj_400
	movzx eax, word [ecx+0x2]
	lea ecx, [esi+eax*8+0xd0]
	mov [ebp-0xbc], ecx
	add ecx, 0x8
	mov [ebp-0x68], ecx
	mov eax, [ebp-0x34]
	mov eax, [eax+0x4]
	mov [ebp-0xa0], eax
	movzx eax, dx
	sub eax, 0x3a
	sar eax, 0x2
	movzx eax, word [ebx+eax*2+0xee4]
	mov [ebp-0x9c], eax
	mov edx, eax
	xor edx, [ecx+0x4]
	mov eax, [ebp-0xa0]
	mov ecx, [ebp-0xbc]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z11R_SetupPass16GfxCmdBufContextj_410
	mov eax, [ebp-0xa0]
	mov edx, [ebp-0x9c]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	mov edx, [ebp-0x34]
	movzx eax, byte [edx+0x7]
	sub eax, 0x1
	jz _Z11R_SetupPass16GfxCmdBufContextj_420
	mov edx, [ebp-0x68]
	xor ecx, ecx
_Z11R_SetupPass16GfxCmdBufContextj_430:
	mov dword [edx+0x8], 0xffffffff
	mov dword [edx+0xc], 0xffffffff
	add ecx, 0x1
	add edx, 0x8
	cmp ecx, eax
	jnz _Z11R_SetupPass16GfxCmdBufContextj_430
_Z11R_SetupPass16GfxCmdBufContextj_420:
	xor eax, eax
_Z11R_SetupPass16GfxCmdBufContextj_500:
	movzx eax, al
	test eax, eax
	jnz _Z11R_SetupPass16GfxCmdBufContextj_440
	mov eax, [ebp-0x34]
	add eax, 0x4
	mov [ebp-0xac], eax
	mov ebx, [ebp-0x48]
	mov esi, [ebp-0x50]
	mov edx, ebx
	mov eax, [ebp-0x34]
	movzx edi, word [eax+0x4]
	cmp di, 0x39
	ja _Z11R_SetupPass16GfxCmdBufContextj_450
	mov ecx, esi
	movzx eax, di
	shl eax, 0x4
	add eax, 0x880
	lea esi, [eax+ebx]
_Z11R_SetupPass16GfxCmdBufContextj_510:
	mov eax, [ebp-0x34]
	movzx eax, byte [eax+0x7]
	mov [ebp-0x64], eax
	mov edx, [ebp-0x34]
	movzx eax, word [edx+0x2]
	movzx edi, ax
	mov edx, [ecx+0x90]
	cmp edi, 0x1f
	jbe _Z11R_SetupPass16GfxCmdBufContextj_460
	cmp ax, 0x20
	jz _Z11R_SetupPass16GfxCmdBufContextj_470
	lea ebx, [edx+0x400]
_Z11R_SetupPass16GfxCmdBufContextj_520:
	mov [esp+0x4], esi
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z11R_SetupPass16GfxCmdBufContextj_480
_Z11R_SetupPass16GfxCmdBufContextj_440:
	add dword [ebp-0x34], 0x8
	add dword [ebp-0x44], 0x1
	mov eax, [ebp-0x30]
	cmp [ebp-0x44], eax
	jz _Z11R_SetupPass16GfxCmdBufContextj_50
	mov esi, eax
	jmp _Z11R_SetupPass16GfxCmdBufContextj_490
_Z11R_SetupPass16GfxCmdBufContextj_400:
	movzx ecx, word [ecx+0x2]
	lea eax, [eax+ecx*8+0xd0]
	mov [ebp-0xbc], eax
	mov ecx, [ebp-0x34]
	mov ecx, [ecx+0x4]
	mov [ebp-0xa8], ecx
	movzx eax, dx
	movzx edi, word [ebx+eax*2+0xe30]
	mov [ebp-0xa4], edi
	mov edx, edi
	mov eax, [ebp-0xbc]
	xor edx, [eax+0xc]
	mov eax, ecx
	mov ecx, [ebp-0xbc]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z11R_SetupPass16GfxCmdBufContextj_410
	mov eax, [ebp-0xa8]
	mov edx, [ebp-0xa4]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	jmp _Z11R_SetupPass16GfxCmdBufContextj_420
_Z11R_SetupPass16GfxCmdBufContextj_410:
	mov eax, 0x1
	jmp _Z11R_SetupPass16GfxCmdBufContextj_500
_Z11R_SetupPass16GfxCmdBufContextj_480:
	mov eax, [esi]
	mov [ebx], eax
	mov eax, [esi+0x4]
	mov [ebx+0x4], eax
	mov eax, [esi+0x8]
	mov [ebx+0x8], eax
	mov eax, [esi+0xc]
	mov [ebx+0xc], eax
	mov eax, [esi+0x10]
	mov [ebx+0x10], eax
	mov eax, [esi+0x14]
	mov [ebx+0x14], eax
	mov eax, [esi+0x18]
	mov [ebx+0x18], eax
	mov eax, [esi+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [esi+0x20]
	mov [ebx+0x20], eax
	mov eax, [esi+0x24]
	mov [ebx+0x24], eax
	mov eax, [esi+0x28]
	mov [ebx+0x28], eax
	mov eax, [esi+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [esi+0x30]
	mov [ebx+0x30], eax
	mov eax, [esi+0x34]
	mov [ebx+0x34], eax
	mov eax, [esi+0x38]
	mov [ebx+0x38], eax
	mov eax, [esi+0x3c]
	mov [ebx+0x3c], eax
_Z11R_SetupPass16GfxCmdBufContextj_460:
	mov [esp+0xc], esi
	mov ebx, [ebp-0x64]
	mov [esp+0x8], ebx
	mov [esp+0x4], edi
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z11R_SetupPass16GfxCmdBufContextj_440
_Z11R_SetupPass16GfxCmdBufContextj_450:
	mov ebx, [ebp-0xac]
	movzx eax, byte [ebx+0x2]
	mov [esp+0x8], eax
	movzx eax, di
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj
	mov esi, eax
	mov ecx, [ebp-0x50]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_510
_Z11R_SetupPass16GfxCmdBufContextj_470:
	lea ebx, [edx+0x3c0]
	jmp _Z11R_SetupPass16GfxCmdBufContextj_520
_Z11R_SetupPass16GfxCmdBufContextj_370:
	mov eax, r_specularMap
	mov eax, [eax]
	cmp dword [eax+0xc], 0x1
	jnz _Z11R_SetupPass16GfxCmdBufContextj_530
	jmp _Z11R_SetupPass16GfxCmdBufContextj_310
_Z11R_SetupPass16GfxCmdBufContextj_390:
	xor edi, edi
	jmp _Z11R_SetupPass16GfxCmdBufContextj_540
_Z11R_SetupPass16GfxCmdBufContextj_550:
	movzx eax, byte [ebp-0x19]
	mov ecx, [ebp-0x34]
	movzx edx, word [ecx+0x2]
	mov ecx, [ebp-0x54]
	mov [ebp-0x88], ecx
	mov ecx, [ebp-0x50]
	mov [ebp-0x84], ecx
	mov [esp+0x10], ebx
	mov [esp+0xc], eax
	mov [esp+0x8], edx
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z12R_SetSampler16GfxCmdBufContextjhPK8GfxImage
	add dword [ebp-0x34], 0x8
	add edi, 0x1
	cmp esi, edi
	jz _Z11R_SetupPass16GfxCmdBufContextj_50
_Z11R_SetupPass16GfxCmdBufContextj_540:
	mov edx, [ebp-0x34]
	cmp word [edx], 0x4
	jnz _Z11R_SetupPass16GfxCmdBufContextj_50
	lea ecx, [ebp-0x19]
	mov [esp+0x8], ecx
	mov eax, [edx+0x4]
	mov [esp+0x4], eax
	mov eax, [ebp-0x54]
	mov [esp], eax
	call _Z20R_GetTextureFromCodeP20GfxCmdBufSourceStatejPh
	mov ebx, eax
	test eax, eax
	jnz _Z11R_SetupPass16GfxCmdBufContextj_550
	mov edx, [ebp-0x34]
	mov eax, [edx+0x4]
	mov [esp+0x4], eax
	mov ecx, [ebp-0x54]
	mov [esp], ecx
	call _Z22R_TextureFromCodeErrorP20GfxCmdBufSourceStatej
	jmp _Z11R_SetupPass16GfxCmdBufContextj_550



;R_SetupPassPerPrimArgs(GfxCmdBufContext)
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x7c
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov ecx, [ebp+0xc]
	mov edx, [ecx+0xc4]
	movzx eax, byte [edx+0xc]
	test al, al
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_10
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_30:
	add esp, 0x7c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_10:
	movzx eax, al
	mov [ebp-0x38], eax
	mov ebx, [ebp+0x8]
	mov esi, [ebp+0xc]
	mov [ebp-0x40], ebx
	mov [ebp-0x3c], esi
	mov [ebp-0x28], esi
	mov [ebp-0x24], ebx
	mov edx, [edx+0x10]
	mov [ebp-0x30], edx
	mov esi, [ecx+0x90]
	lea ebx, [esi+0x3c0]
	mov eax, [ebp-0x40]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_20
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_170:
	mov dword [ebp-0x1c], 0x0
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_130:
	mov ebx, [ebp-0x30]
	cmp word [ebx], 0x3
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_30
	mov ecx, ebx
	mov esi, [ebp-0x28]
	mov [ebp-0x3c], esi
	mov eax, [ebp-0x24]
	mov [ebp-0x40], eax
	mov ebx, [ebp-0x40]
	mov esi, [ebp-0x3c]
	mov edi, ebx
	mov [ebp-0x20], esi
	movzx edx, word [ecx+0x4]
	cmp dx, 0x39
	jbe _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_40
	movzx eax, word [ecx+0x2]
	lea ecx, [esi+eax*8+0xd0]
	mov [ebp-0x6c], ecx
	add ecx, 0x8
	mov [ebp-0x34], ecx
	mov eax, [ebp-0x30]
	mov eax, [eax+0x4]
	mov [ebp-0x48], eax
	movzx eax, dx
	sub eax, 0x3a
	sar eax, 0x2
	movzx eax, word [ebx+eax*2+0xee4]
	mov [ebp-0x44], eax
	mov edx, eax
	xor edx, [ecx+0x4]
	mov eax, [ebp-0x48]
	mov ecx, [ebp-0x6c]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x48]
	mov edx, [ebp-0x44]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	mov edx, [ebp-0x30]
	movzx eax, byte [edx+0x7]
	sub eax, 0x1
	jz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_60
	mov edx, [ebp-0x34]
	xor ecx, ecx
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_70:
	mov dword [edx+0x8], 0xffffffff
	mov dword [edx+0xc], 0xffffffff
	add ecx, 0x1
	add edx, 0x8
	cmp ecx, eax
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_70
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_60:
	xor eax, eax
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_140:
	movzx eax, al
	test eax, eax
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_80
	mov eax, [ebp-0x30]
	add eax, 0x4
	mov [ebp-0x5c], eax
	mov ebx, edi
	mov esi, [ebp-0x20]
	mov edx, edi
	mov eax, [ebp-0x30]
	movzx edi, word [eax+0x4]
	cmp di, 0x39
	ja _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_90
	mov ecx, esi
	movzx eax, di
	shl eax, 0x4
	add eax, 0x880
	lea esi, [eax+ebx]
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_150:
	mov eax, [ebp-0x30]
	movzx eax, byte [eax+0x7]
	mov [ebp-0x2c], eax
	mov edx, [ebp-0x30]
	movzx eax, word [edx+0x2]
	movzx edi, ax
	mov edx, [ecx+0x90]
	cmp edi, 0x1f
	jbe _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_100
	cmp ax, 0x20
	jz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_110
	lea ebx, [edx+0x400]
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_160:
	mov [esp+0x4], esi
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_120
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_80:
	add dword [ebp-0x30], 0x8
	add dword [ebp-0x1c], 0x1
	mov esi, [ebp-0x38]
	cmp [ebp-0x1c], esi
	jnz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_130
	add esp, 0x7c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_40:
	movzx ecx, word [ecx+0x2]
	lea eax, [esi+ecx*8+0xd0]
	mov [ebp-0x6c], eax
	mov ecx, [ebp-0x30]
	mov ecx, [ecx+0x4]
	mov [ebp-0x50], ecx
	movzx eax, dx
	movzx eax, word [ebx+eax*2+0xe30]
	mov [ebp-0x4c], eax
	mov edx, eax
	mov eax, [ebp-0x6c]
	xor edx, [eax+0xc]
	mov eax, ecx
	mov ecx, [ebp-0x6c]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	jmp _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_60
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_50:
	mov eax, 0x1
	jmp _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_140
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_120:
	mov eax, [esi]
	mov [ebx], eax
	mov eax, [esi+0x4]
	mov [ebx+0x4], eax
	mov eax, [esi+0x8]
	mov [ebx+0x8], eax
	mov eax, [esi+0xc]
	mov [ebx+0xc], eax
	mov eax, [esi+0x10]
	mov [ebx+0x10], eax
	mov eax, [esi+0x14]
	mov [ebx+0x14], eax
	mov eax, [esi+0x18]
	mov [ebx+0x18], eax
	mov eax, [esi+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [esi+0x20]
	mov [ebx+0x20], eax
	mov eax, [esi+0x24]
	mov [ebx+0x24], eax
	mov eax, [esi+0x28]
	mov [ebx+0x28], eax
	mov eax, [esi+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [esi+0x30]
	mov [ebx+0x30], eax
	mov eax, [esi+0x34]
	mov [ebx+0x34], eax
	mov eax, [esi+0x38]
	mov [ebx+0x38], eax
	mov eax, [esi+0x3c]
	mov [ebx+0x3c], eax
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_100:
	mov [esp+0xc], esi
	mov ebx, [ebp-0x2c]
	mov [esp+0x8], ebx
	mov [esp+0x4], edi
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_80
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_90:
	mov ebx, [ebp-0x5c]
	movzx eax, byte [ebx+0x2]
	mov [esp+0x8], eax
	movzx eax, di
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj
	mov esi, eax
	mov ecx, [ebp-0x20]
	jmp _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_150
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_110:
	lea ebx, [edx+0x3c0]
	jmp _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_160
_Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_20:
	mov edx, [ebp-0x24]
	mov eax, [edx]
	mov [esi+0x3c0], eax
	mov eax, [edx+0x4]
	mov [ebx+0x4], eax
	mov eax, [edx+0x8]
	mov [ebx+0x8], eax
	mov eax, [edx+0xc]
	mov [ebx+0xc], eax
	mov eax, [edx+0x10]
	mov [ebx+0x10], eax
	mov eax, [edx+0x14]
	mov [ebx+0x14], eax
	mov eax, [edx+0x18]
	mov [ebx+0x18], eax
	mov eax, [edx+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [edx+0x20]
	mov [ebx+0x20], eax
	mov eax, [edx+0x24]
	mov [ebx+0x24], eax
	mov eax, [edx+0x28]
	mov [ebx+0x28], eax
	mov eax, [edx+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [edx+0x30]
	mov [ebx+0x30], eax
	mov eax, [edx+0x34]
	mov [ebx+0x34], eax
	mov eax, [edx+0x38]
	mov [ebx+0x38], eax
	mov eax, [edx+0x3c]
	mov [ebx+0x3c], eax
	mov ecx, [ebp-0x40]
	mov [esp+0xc], ecx
	mov dword [esp+0x8], 0x4
	mov dword [esp+0x4], 0x20
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext_170
	nop



;R_SetupPassPerObjectArgs(GfxCmdBufContext)
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x9c
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov dword [ebp-0x60], 0x0
	mov dword [ebp-0x5c], 0x0
	mov dword [ebp-0x68], 0x0
	mov dword [ebp-0x64], 0x0
	mov ebx, [ebp+0xc]
	mov edx, [ebx+0xc4]
	movzx ecx, byte [edx+0xd]
	test cl, cl
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_10
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_130:
	add esp, 0x9c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_10:
	movzx eax, byte [edx+0xc]
	mov edx, [edx+0x10]
	lea eax, [edx+eax*8]
	mov [ebp-0x50], eax
	movzx ecx, cl
	mov [ebp-0x4c], ecx
	mov eax, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov [ebp-0x58], eax
	mov [ebp-0x54], edx
	mov [ebp-0x38], edx
	mov [ebp-0x34], eax
	mov esi, eax
	add esi, 0x40
	mov edi, [ebx+0x90]
	lea ebx, [edi+0x400]
	mov [esp+0x4], esi
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_20
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_200:
	mov dword [ebp-0x2c], 0x0
	mov esi, [ebp-0x4c]
	sub esi, [ebp-0x2c]
	mov ecx, [ebp-0x50]
	cmp word [ecx], 0x3
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_30
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_140:
	mov ebx, [ebp-0x38]
	mov [ebp-0x54], ebx
	mov eax, [ebp-0x34]
	mov [ebp-0x58], eax
	mov ebx, [ebp-0x58]
	mov esi, [ebp-0x54]
	mov edi, ebx
	mov [ebp-0x30], esi
	movzx edx, word [ecx+0x4]
	cmp dx, 0x39
	jbe _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_40
	movzx ecx, word [ecx+0x2]
	lea eax, [esi+ecx*8+0xd0]
	mov [ebp-0x7c], eax
	add eax, 0x8
	mov [ebp-0x40], eax
	mov ecx, [ebp-0x50]
	mov ecx, [ecx+0x4]
	mov [ebp-0x60], ecx
	movzx eax, dx
	sub eax, 0x3a
	sar eax, 0x2
	movzx eax, word [ebx+eax*2+0xee4]
	mov [ebp-0x5c], eax
	mov edx, eax
	mov eax, [ebp-0x40]
	xor edx, [eax+0x4]
	mov eax, ecx
	mov ecx, [ebp-0x7c]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x60]
	mov edx, [ebp-0x5c]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	mov edx, [ebp-0x50]
	movzx eax, byte [edx+0x7]
	sub eax, 0x1
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_60
	mov edx, [ebp-0x40]
	xor ecx, ecx
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_70:
	mov dword [edx+0x8], 0xffffffff
	mov dword [edx+0xc], 0xffffffff
	add ecx, 0x1
	add edx, 0x8
	cmp ecx, eax
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_70
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_60:
	xor eax, eax
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_170:
	movzx eax, al
	test eax, eax
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_80
	mov eax, [ebp-0x50]
	add eax, 0x4
	mov [ebp-0x6c], eax
	mov ebx, edi
	mov esi, [ebp-0x30]
	mov edx, edi
	mov eax, [ebp-0x50]
	movzx edi, word [eax+0x4]
	cmp di, 0x39
	ja _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_90
	mov ecx, esi
	movzx eax, di
	shl eax, 0x4
	add eax, 0x880
	lea esi, [eax+ebx]
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_180:
	mov eax, [ebp-0x50]
	movzx eax, byte [eax+0x7]
	mov [ebp-0x3c], eax
	mov edx, [ebp-0x50]
	movzx eax, word [edx+0x2]
	movzx edi, ax
	mov edx, [ecx+0x90]
	cmp edi, 0x1f
	jbe _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_100
	cmp ax, 0x20
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_110
	lea ebx, [edx+0x400]
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_190:
	mov [esp+0x4], esi
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_120
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_80:
	add dword [ebp-0x50], 0x8
	add dword [ebp-0x2c], 0x1
	mov eax, [ebp-0x4c]
	cmp [ebp-0x2c], eax
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_130
	mov esi, [ebp-0x4c]
	sub esi, [ebp-0x2c]
	mov ecx, [ebp-0x50]
	cmp word [ecx], 0x3
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_140
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_30:
	xor edi, edi
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_150
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_160:
	movzx eax, byte [ebp-0x19]
	mov ecx, [ebp-0x50]
	movzx edx, word [ecx+0x2]
	mov ecx, [ebp-0x38]
	mov [ebp-0x44], ecx
	mov ecx, [ebp-0x34]
	mov [ebp-0x48], ecx
	mov [esp+0x10], ebx
	mov [esp+0xc], eax
	mov [esp+0x8], edx
	mov eax, [ebp-0x48]
	mov edx, [ebp-0x44]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z12R_SetSampler16GfxCmdBufContextjhPK8GfxImage
	add dword [ebp-0x50], 0x8
	add edi, 0x1
	cmp esi, edi
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_130
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_150:
	mov edx, [ebp-0x50]
	cmp word [edx], 0x4
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_130
	mov ecx, edx
	lea edx, [ebp-0x19]
	mov [esp+0x8], edx
	mov eax, [ecx+0x4]
	mov [esp+0x4], eax
	mov ebx, [ebp-0x34]
	mov [esp], ebx
	call _Z20R_GetTextureFromCodeP20GfxCmdBufSourceStatejPh
	mov ebx, eax
	test eax, eax
	jnz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_160
	mov edx, [ebp-0x50]
	mov eax, [edx+0x4]
	mov [esp+0x4], eax
	mov ecx, [ebp-0x34]
	mov [esp], ecx
	call _Z22R_TextureFromCodeErrorP20GfxCmdBufSourceStatej
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_160
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_40:
	mov ecx, [ebp-0x50]
	movzx ecx, word [ecx+0x2]
	lea eax, [esi+ecx*8+0xd0]
	mov [ebp-0x7c], eax
	mov ecx, [ebp-0x50]
	mov ecx, [ecx+0x4]
	mov [ebp-0x68], ecx
	movzx eax, dx
	movzx eax, word [ebx+eax*2+0xe30]
	mov [ebp-0x64], eax
	mov edx, eax
	mov eax, [ebp-0x7c]
	xor edx, [eax+0xc]
	mov eax, ecx
	mov ecx, [ebp-0x7c]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x68]
	mov edx, [ebp-0x64]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_60
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_50:
	mov eax, 0x1
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_170
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_120:
	mov eax, [esi]
	mov [ebx], eax
	mov eax, [esi+0x4]
	mov [ebx+0x4], eax
	mov eax, [esi+0x8]
	mov [ebx+0x8], eax
	mov eax, [esi+0xc]
	mov [ebx+0xc], eax
	mov eax, [esi+0x10]
	mov [ebx+0x10], eax
	mov eax, [esi+0x14]
	mov [ebx+0x14], eax
	mov eax, [esi+0x18]
	mov [ebx+0x18], eax
	mov eax, [esi+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [esi+0x20]
	mov [ebx+0x20], eax
	mov eax, [esi+0x24]
	mov [ebx+0x24], eax
	mov eax, [esi+0x28]
	mov [ebx+0x28], eax
	mov eax, [esi+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [esi+0x30]
	mov [ebx+0x30], eax
	mov eax, [esi+0x34]
	mov [ebx+0x34], eax
	mov eax, [esi+0x38]
	mov [ebx+0x38], eax
	mov eax, [esi+0x3c]
	mov [ebx+0x3c], eax
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_100:
	mov [esp+0xc], esi
	mov ebx, [ebp-0x3c]
	mov [esp+0x8], ebx
	mov [esp+0x4], edi
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_80
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_90:
	mov ebx, [ebp-0x6c]
	movzx eax, byte [ebx+0x2]
	mov [esp+0x8], eax
	movzx eax, di
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj
	mov esi, eax
	mov ecx, [ebp-0x30]
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_180
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_110:
	lea ebx, [edx+0x3c0]
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_190
_Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_20:
	mov edx, [ebp-0x34]
	mov eax, [edx+0x40]
	mov [edi+0x400], eax
	mov eax, [esi+0x4]
	mov [ebx+0x4], eax
	mov eax, [esi+0x8]
	mov [ebx+0x8], eax
	mov eax, [esi+0xc]
	mov [ebx+0xc], eax
	mov eax, [esi+0x10]
	mov [ebx+0x10], eax
	mov eax, [esi+0x14]
	mov [ebx+0x14], eax
	mov eax, [esi+0x18]
	mov [ebx+0x18], eax
	mov eax, [esi+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [esi+0x20]
	mov [ebx+0x20], eax
	mov eax, [esi+0x24]
	mov [ebx+0x24], eax
	mov eax, [esi+0x28]
	mov [ebx+0x28], eax
	mov eax, [esi+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [esi+0x30]
	mov [ebx+0x30], eax
	mov eax, [esi+0x34]
	mov [ebx+0x34], eax
	mov eax, [esi+0x38]
	mov [ebx+0x38], eax
	mov eax, [esi+0x3c]
	mov [ebx+0x3c], eax
	mov [esp+0xc], esi
	mov dword [esp+0x8], 0x4
	mov dword [esp+0x4], 0x24
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext_200


;R_SetupPassVertexShaderArgs(GfxCmdBufContext)
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov eax, [ebp+0xc]
	mov ecx, [eax+0xc4]
	movzx ebx, byte [ecx+0xe]
	test bl, bl
	jz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_10
	movzx eax, byte [ecx+0xd]
	movzx edx, byte [ecx+0xc]
	add eax, edx
	mov edx, [ecx+0x10]
	lea edi, [edx+eax*8]
	movzx edx, bl
	xor eax, eax
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_30:
	mov ecx, edx
	sub ecx, eax
	mov [ebp-0x1c], ecx
	cmp word [edi], 0x2
	ja _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_20
	add edi, 0x8
	add eax, 0x1
	cmp edx, eax
	jnz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_30
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_10:
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_20:
	mov dword [ebp-0x20], 0x0
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_130:
	cmp word [edi], 0x3
	jnz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_10
	mov ebx, [ebp+0x8]
	mov eax, [ebp+0x8]
	mov [ebp-0x28], eax
	mov edx, [ebp+0xc]
	mov [ebp-0x2c], edx
	mov esi, edx
	mov [ebp-0x24], ebx
	movzx edx, word [edi+0x4]
	cmp dx, 0x39
	jbe _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_40
	movzx ecx, word [edi+0x2]
	lea ecx, [esi+ecx*8+0xd0]
	lea eax, [ecx+0x8]
	mov [ebp-0x3c], eax
	mov eax, [edi+0x4]
	mov [ebp-0x48], eax
	movzx eax, dx
	sub eax, 0x3a
	sar eax, 0x2
	movzx eax, word [ebx+eax*2+0xee4]
	mov [ebp-0x44], eax
	mov edx, eax
	mov eax, [ebp-0x3c]
	xor edx, [eax+0x4]
	mov eax, [ebp-0x48]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x48]
	mov edx, [ebp-0x44]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	movzx eax, byte [edi+0x7]
	sub eax, 0x1
	jz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_60
	mov edx, [ebp-0x3c]
	xor ecx, ecx
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_70:
	mov dword [edx+0x8], 0xffffffff
	mov dword [edx+0xc], 0xffffffff
	add ecx, 0x1
	add edx, 0x8
	cmp ecx, eax
	jnz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_70
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_60:
	xor eax, eax
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_140:
	movzx eax, al
	test eax, eax
	jnz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_80
	lea edx, [edi+0x4]
	mov [ebp-0x5c], edx
	mov ebx, [ebp-0x28]
	mov esi, [ebp-0x2c]
	mov edx, ebx
	movzx eax, word [edi+0x4]
	mov [ebp-0x36], ax
	cmp ax, 0x39
	ja _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_90
	mov ecx, esi
	movzx eax, word [ebp-0x36]
	shl eax, 0x4
	add eax, 0x880
	lea esi, [eax+ebx]
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_150:
	movzx eax, byte [edi+0x7]
	mov [ebp-0x34], eax
	movzx eax, word [edi+0x2]
	movzx edx, ax
	mov [ebp-0x30], edx
	mov edx, [ecx+0x90]
	cmp dword [ebp-0x30], 0x1f
	jbe _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_100
	cmp ax, 0x20
	jz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_110
	lea ebx, [edx+0x400]
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_160:
	mov [esp+0x4], esi
	mov [esp], ebx
	call _ZN14MacOpenGLUtils23AreMatricesDifferent4x4EPKvS1_
	test al, al
	jnz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_120
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_80:
	add edi, 0x8
	add dword [ebp-0x20], 0x1
	mov edx, [ebp-0x1c]
	cmp [ebp-0x20], edx
	jnz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_130
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_40:
	movzx ecx, word [edi+0x2]
	mov eax, [ebp-0x2c]
	lea ecx, [eax+ecx*8+0xd0]
	mov eax, [edi+0x4]
	mov [ebp-0x50], eax
	movzx eax, dx
	mov edx, [ebp-0x24]
	movzx eax, word [edx+eax*2+0xe30]
	mov [ebp-0x4c], eax
	mov edx, eax
	xor edx, [ecx+0xc]
	mov eax, [ebp-0x50]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	jmp _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_60
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_50:
	mov eax, 0x1
	jmp _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_140
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_120:
	mov eax, [esi]
	mov [ebx], eax
	mov eax, [esi+0x4]
	mov [ebx+0x4], eax
	mov eax, [esi+0x8]
	mov [ebx+0x8], eax
	mov eax, [esi+0xc]
	mov [ebx+0xc], eax
	mov eax, [esi+0x10]
	mov [ebx+0x10], eax
	mov eax, [esi+0x14]
	mov [ebx+0x14], eax
	mov eax, [esi+0x18]
	mov [ebx+0x18], eax
	mov eax, [esi+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [esi+0x20]
	mov [ebx+0x20], eax
	mov eax, [esi+0x24]
	mov [ebx+0x24], eax
	mov eax, [esi+0x28]
	mov [ebx+0x28], eax
	mov eax, [esi+0x2c]
	mov [ebx+0x2c], eax
	mov eax, [esi+0x30]
	mov [ebx+0x30], eax
	mov eax, [esi+0x34]
	mov [ebx+0x34], eax
	mov eax, [esi+0x38]
	mov [ebx+0x38], eax
	mov eax, [esi+0x3c]
	mov [ebx+0x3c], eax
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_100:
	mov [esp+0xc], esi
	mov ebx, [ebp-0x34]
	mov [esp+0x8], ebx
	mov eax, [ebp-0x30]
	mov [esp+0x4], eax
	mov dword [esp], 0x8620
	call glProgramEnvParameters4fvEXT
	jmp _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_80
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_90:
	mov ebx, [ebp-0x5c]
	movzx eax, byte [ebx+0x2]
	mov [esp+0x8], eax
	movzx eax, word [ebp-0x36]
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z15R_GetCodeMatrixP20GfxCmdBufSourceStatejj
	mov esi, eax
	mov ecx, [ebp-0x2c]
	jmp _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_150
_Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_110:
	lea ebx, [edx+0x3c0]
	jmp _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext_160



;R_SetPassPixelShaderStableArguments(GfxCmdBufContext, unsigned int, MaterialShaderArgument const*)
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov dword [ebp-0x40], 0x0
	mov dword [ebp-0x3c], 0x0
	mov edi, [ebp+0x8]
	mov [ebp-0x2c], eax
	mov [ebp-0x30], edx
	mov eax, [edx+0xb8]
	mov [ebp-0x34], eax
	xor eax, eax
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_20:
	mov edx, ecx
	sub edx, eax
	mov [ebp-0x1c], edx
	cmp word [edi], 0x4
	ja _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_10
	add edi, 0x8
	add eax, 0x1
	cmp ecx, eax
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_20
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_110:
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_10:
	mov dword [ebp-0x24], 0x0
	mov ecx, [ebp-0x1c]
	jmp _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_30
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_60:
	mov ecx, edx
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_30:
	sub ecx, [ebp-0x24]
	mov [ebp-0x20], ecx
	cmp word [edi], 0x5
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_40
	mov ebx, [ebp-0x2c]
	mov esi, [ebp-0x30]
	mov ecx, [edi+0x4]
	mov [ebp-0x40], ecx
	movzx eax, word [edi+0x4]
	movzx edx, word [ebx+eax*2+0xe30]
	mov [ebp-0x3c], edx
	movzx eax, word [edi+0x2]
	lea ecx, [esi+eax*8+0x1d0]
	mov edx, [ebp-0x3c]
	xor edx, [ecx+0xc]
	mov eax, [ebp-0x40]
	xor eax, [ecx+0x8]
	or edx, eax
	jz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_50
	mov eax, [ebp-0x40]
	mov edx, [ebp-0x3c]
	mov [ecx+0x8], eax
	mov [ecx+0xc], edx
	mov ebx, [ebp-0x2c]
	movzx eax, word [edi+0x4]
	shl eax, 0x4
	add eax, 0x880
	add eax, ebx
	mov [esp+0xc], eax
	movzx eax, byte [edi+0x7]
	mov [esp+0x8], eax
	movzx eax, word [edi+0x2]
	mov [esp+0x4], eax
	mov dword [esp], 0x8804
	call glProgramEnvParameters4fvEXT
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_50:
	add edi, 0x8
	add dword [ebp-0x24], 0x1
	mov edx, [ebp-0x1c]
	cmp [ebp-0x24], edx
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_60
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_40:
	mov eax, [ebp-0x34]
	mov esi, [eax+0x48]
	mov dword [ebp-0x28], 0x0
	mov ebx, [ebp-0x20]
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_120:
	sub ebx, [ebp-0x28]
	cmp word [edi], 0x6
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_70
	mov ebx, [edi+0x4]
	cmp ebx, [esi]
	jz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_80
	lea ecx, [esi+0x20]
	mov edx, ecx
	jmp _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_90
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_100:
	add ecx, 0x20
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_90:
	mov esi, ecx
	mov eax, [edx]
	add edx, 0x20
	cmp ebx, eax
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_100
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_80:
	movzx edx, word [edi+0x2]
	mov ecx, [ebp-0x30]
	mov dword [ecx+edx*8+0x1d8], 0xffffffff
	mov dword [ecx+edx*8+0x1dc], 0xffffffff
	lea eax, [esi+0x10]
	mov [esp+0xc], eax
	mov dword [esp+0x8], 0x1
	mov [esp+0x4], edx
	mov dword [esp], 0x8804
	call glProgramEnvParameters4fvEXT
	add edi, 0x8
	add dword [ebp-0x28], 0x1
	mov eax, [ebp-0x20]
	cmp [ebp-0x28], eax
	jz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_110
	mov ebx, eax
	jmp _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_120
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_70:
	xor esi, esi
_Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_130:
	cmp word [edi], 0x7
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_110
	mov edx, [edi+0x4]
	movzx eax, word [edi+0x2]
	mov ecx, [ebp-0x30]
	mov dword [ecx+eax*8+0x1d8], 0xffffffff
	mov dword [ecx+eax*8+0x1dc], 0xffffffff
	mov [esp+0xc], edx
	mov dword [esp+0x8], 0x1
	mov [esp+0x4], eax
	mov dword [esp], 0x8804
	call glProgramEnvParameters4fvEXT
	add edi, 0x8
	add esi, 0x1
	cmp ebx, esi
	jnz _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_130
	jmp _Z35R_SetPassPixelShaderStableArguments16GfxCmdBufContextjPK22MaterialShaderArgument_110
	nop



;R_TessStaticModelRigidDrawSurfList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xac
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov dword [ebp-0x58], 0x0
	mov dword [ebp-0x54], 0x0
	mov dword [ebp-0x60], 0x0
	mov dword [ebp-0x5c], 0x0
	mov dword [ebp-0x68], 0x0
	mov dword [ebp-0x64], 0x0
	mov dword [ebp-0x70], 0x0
	mov dword [ebp-0x6c], 0x0
	mov dword [ebp-0x78], 0x0
	mov dword [ebp-0x74], 0x0
	mov dword [ebp-0x80], 0x0
	mov dword [ebp-0x7c], 0x0
	mov dword [ebp-0x88], 0x0
	mov dword [ebp-0x84], 0x0
	mov ecx, [ebp+0xc]
	mov [ebp-0x2c], ecx
	mov ebx, [ebp+0x10]
	mov [ebp-0x30], ebx
	mov ecx, [ebp+0x8]
	mov ebx, [ecx]
	mov esi, [ecx+0x4]
	mov [ebp-0x90], ebx
	mov [ebp-0x8c], esi
	mov [ebp-0x34], esi
	mov edi, ebx
	mov ecx, [ecx+0xc]
	mov [ebp-0x38], ecx
	mov ecx, [ecx+0x8]
	mov [ebp-0x3c], ecx
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, s_manualObjectPlacement
	mov [ebx+0xf08], eax
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov eax, [ebp-0x34]
	mov dword [eax+0x98], 0x1
	mov [esp], esi
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov [ebp-0x8c], esi
	mov [ebp-0x90], ebx
	cmp dword [ebx+0xf34], 0x1
	sbb edx, edx
	cmp edx, [esi+0xcc]
	jz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], edx
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov esi, [ebp-0x30]
	test esi, esi
	jz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov ecx, [ebp+0xc]
	mov [ebp-0x88], ecx
	mov ebx, [ebp+0x10]
	mov [ebp-0x84], ebx
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov edx, [ebp-0x30]
	mov dword [edx+0x98], 0x1
	mov ecx, [ebp+0x10]
	mov [esp], ecx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ebx, [ebp-0x84]
	mov [ebp+0x10], ebx
	mov eax, [ebp+0xc]
	cmp dword [eax+0xf34], 0x1
	sbb eax, eax
	mov edx, [ebp-0x30]
	cmp eax, [edx+0xcc]
	jz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov ecx, [edi+0xca8]
	add ecx, 0x28000
	mov ebx, [ebp+0x8]
	mov edx, [ebx+0x8]
	mov ebx, [ebp-0x38]
	mov eax, [ebx]
	movzx eax, word [eax+edx*8]
	lea esi, [ecx+eax*4]
	cmp dword [ebp-0x3c], 0x7
	jz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov edx, [ebp-0x34]
	mov [ebp-0x4c], edx
	mov [ebp-0x50], edi
	mov ecx, [ebp-0x50]
	mov ebx, [ebp-0x4c]
	mov [esp], ecx
	mov [esp+0x4], ebx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov ebx, [ebp-0x34]
	mov [ebp-0x44], ebx
	mov [ebp-0x48], edi
	mov eax, [ebp-0x38]
	mov [esp+0xc], eax
	mov edx, [ebp-0x48]
	mov ecx, [ebp-0x44]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], esi
	call _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov eax, 0x1
	add esp, 0xac
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov eax, rgp
	mov eax, [eax+0x2008]
	mov [edi+0xc60], eax
	mov ebx, [ebp-0x30]
	test ebx, ebx
	jz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
	mov eax, [ebp-0x2c]
	mov [ebp-0x80], eax
	mov edx, [ebp-0x30]
	mov [ebp-0x7c], edx
	mov ecx, [ebp-0x80]
	mov ebx, [ebp-0x7c]
	mov [esp], ecx
	mov [esp+0x4], ebx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	mov ebx, [ebp-0x34]
	mov [ebp-0x74], ebx
	mov [ebp-0x78], edi
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebx+0xb8]
	mov eax, [eax+0x44]
	mov eax, [eax+0x8]
	mov dword [esp+0x4], _cstring_tree_chechnya_tr
	mov eax, [eax+0x20]
	mov [esp], eax
	call strstr
	test eax, eax
	jz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov dword [esp], 0x8037
	call glIsEnabled
	mov ebx, eax
	lea eax, [ebp-0x1c]
	mov [esp+0x4], eax
	mov dword [esp], 0x8038
	call glGetFloatv
	lea eax, [ebp-0x20]
	mov [esp+0x4], eax
	mov dword [esp], 0x2a00
	call glGetFloatv
	mov dword [esp], 0x8037
	call glEnable
	mov eax, [_ZZ34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContextE15sTreeTrunkUnits]
	mov [esp+0x4], eax
	mov eax, [_ZZ34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContextE16sTreeTrunkFactor]
	mov [esp], eax
	call glPolygonOffset
	mov edx, [ebp-0x2c]
	mov [ebp-0x70], edx
	mov ecx, [ebp-0x30]
	mov [ebp-0x6c], ecx
	mov eax, [ebp-0x34]
	mov [ebp-0x64], eax
	mov [ebp-0x68], edi
	mov edx, [ebp-0x38]
	mov [esp+0x14], edx
	mov eax, [ebp-0x70]
	mov edx, [ebp-0x6c]
	mov [esp+0xc], eax
	mov [esp+0x10], edx
	mov edx, [ebp-0x68]
	mov ecx, [ebp-0x64]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], esi
	call _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo
	mov eax, [ebp-0x20]
	mov [esp+0x4], eax
	mov eax, [ebp-0x1c]
	mov [esp], eax
	call glPolygonOffset
	test bl, bl
	jnz _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
	mov dword [esp], 0x8037
	call glDisable
	mov eax, 0x1
	add esp, 0xac
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov dword [esp], 0x8037
	call glEnable
	mov eax, 0x1
	add esp, 0xac
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov ecx, [ebp-0x2c]
	mov [ebp-0x60], ecx
	mov ebx, [ebp-0x30]
	mov [ebp-0x5c], ebx
	mov eax, [ebp-0x34]
	mov [ebp-0x54], eax
	mov [ebp-0x58], edi
	mov edx, [ebp-0x38]
	mov [esp+0x14], edx
	mov ecx, [ebp-0x60]
	mov ebx, [ebp-0x5c]
	mov [esp+0xc], ecx
	mov [esp+0x10], ebx
	mov eax, [ebp-0x58]
	mov edx, [ebp-0x54]
	mov [esp+0x4], eax
	mov [esp+0x8], edx
	mov [esp], esi
	call _Z24R_DrawStaticModelSurfLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo
	jmp _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
	nop
