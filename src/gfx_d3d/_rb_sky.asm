;Imports of rb_sky:
	extern tess
	extern gfxCmdBufSourceState
	extern rgp
	extern r_drawSun
	extern _Z14RB_SetIdentityv
	extern _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	extern floorf
	extern _Z21R_ConvertColorToBytesPKfPh
	extern _Z28RB_DrawFullScreenColoredQuadPK8Materialffffm
	extern _Z14RB_SetTessQuad8GfxColor

;Exports of rb_sky:
	global _Z21RB_DrawSunPostEffectsi
	global sunFlareArray

SECTION .text



;RB_TessSunBillboard(float, float, GfxColor)
_Z19RB_TessSunBillboardff8GfxColor:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x50
	movss [ebp-0xc], xmm0
	movss [ebp-0x10], xmm1
	mov edx, gfxCmdBufSourceState
	mov ecx, [edx+0xf0c]
	lea esi, [ecx+0x80]
	mov edx, rgp
	mov edx, [edx+0x20a0]
	lea ebx, [edx+0x1d0]
	movss xmm1, dword [edx+0x1d0]
	movss xmm4, dword [ebx+0x4]
	lea edx, [ecx+0x90]
	movss xmm5, dword [ebx+0x8]
	lea ebx, [ecx+0xa0]
	movaps xmm6, xmm1
	mulss xmm6, [ecx+0x80]
	movaps xmm0, xmm4
	mulss xmm0, [ecx+0x90]
	addss xmm6, xmm0
	movaps xmm0, xmm5
	mulss xmm0, [ecx+0xa0]
	addss xmm6, xmm0
	movaps xmm3, xmm1
	mulss xmm3, [esi+0x4]
	movaps xmm0, xmm4
	mulss xmm0, [edx+0x4]
	addss xmm3, xmm0
	movaps xmm0, xmm5
	mulss xmm0, [ebx+0x4]
	addss xmm3, xmm0
	movaps xmm2, xmm1
	mulss xmm2, [esi+0x8]
	movaps xmm0, xmm4
	mulss xmm0, [edx+0x8]
	addss xmm2, xmm0
	movaps xmm0, xmm5
	mulss xmm0, [ebx+0x8]
	addss xmm2, xmm0
	mulss xmm1, [esi+0xc]
	mulss xmm4, [edx+0xc]
	addss xmm1, xmm4
	mulss xmm5, [ebx+0xc]
	addss xmm1, xmm5
	movss [ebp-0x28], xmm1
	movss [ebp-0x38], xmm2
	movss [ebp-0x48], xmm3
	movss [ebp-0x58], xmm6
	mov [esp], eax
	call _Z14RB_SetTessQuad8GfxColor
	movss xmm1, dword [ebp-0x28]
	movaps xmm5, xmm1
	mulss xmm5, [_float__0_00050000]
	movss xmm4, dword [ebp-0x10]
	mulss xmm4, xmm1
	movss xmm7, dword [ebp-0xc]
	mulss xmm7, xmm1
	movss xmm6, dword [ebp-0x58]
	movss [eax], xmm6
	movss xmm3, dword [ebp-0x48]
	movss [eax+0x4], xmm3
	movss xmm2, dword [ebp-0x38]
	movss [eax+0x8], xmm2
	movss [eax+0xc], xmm1
	lea edx, [eax+0x20]
	movss [eax+0x20], xmm6
	movss [edx+0x4], xmm3
	movss [edx+0x8], xmm2
	movss [edx+0xc], xmm1
	lea ecx, [eax+0x40]
	movss [eax+0x40], xmm6
	movss [ecx+0x4], xmm3
	movss [ecx+0x8], xmm2
	movss [ecx+0xc], xmm1
	lea ebx, [eax+0x60]
	movss [eax+0x60], xmm6
	movss [ebx+0x4], xmm3
	movss [ebx+0x8], xmm2
	movss [ebx+0xc], xmm1
	movaps xmm0, xmm7
	addss xmm0, [eax]
	movss [eax], xmm0
	movaps xmm0, xmm4
	addss xmm0, [eax+0x4]
	movss [eax+0x4], xmm0
	movaps xmm0, xmm5
	addss xmm0, [eax+0x8]
	movss [eax+0x8], xmm0
	movaps xmm0, xmm7
	addss xmm0, [eax+0x20]
	movss [eax+0x20], xmm0
	movss xmm0, dword [edx+0x4]
	subss xmm0, xmm4
	movss [edx+0x4], xmm0
	movaps xmm0, xmm5
	addss xmm0, [edx+0x8]
	movss [edx+0x8], xmm0
	movss xmm0, dword [eax+0x40]
	subss xmm0, xmm7
	movss [eax+0x40], xmm0
	movss xmm0, dword [ecx+0x4]
	subss xmm0, xmm4
	movss [ecx+0x4], xmm0
	movaps xmm0, xmm5
	addss xmm0, [ecx+0x8]
	movss [ecx+0x8], xmm0
	movss xmm0, dword [eax+0x60]
	subss xmm0, xmm7
	movss [eax+0x60], xmm0
	addss xmm4, [ebx+0x4]
	movss [ebx+0x4], xmm4
	addss xmm5, [ebx+0x8]
	movss [ebx+0x8], xmm5
	add esp, 0x50
	pop ebx
	pop esi
	pop ebp
	ret
	nop


;RB_DrawSunPostEffects(int)
_Z21RB_DrawSunPostEffectsi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov eax, [ebp+0x8]
	lea eax, [eax+eax*4]
	lea esi, [eax*8+sunFlareArray]
	mov eax, [esi+0xc]
	test eax, eax
	jz _Z21RB_DrawSunPostEffectsi_10
	mov ecx, gfxCmdBufSourceState
	mov edx, [ecx+0xf3c]
	cmp eax, edx
	jle _Z21RB_DrawSunPostEffectsi_20
_Z21RB_DrawSunPostEffectsi_170:
	mov edi, 0xa
_Z21RB_DrawSunPostEffectsi_180:
	mov eax, [ecx+0xf3c]
	mov [esi+0xc], eax
	mov eax, r_drawSun
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z21RB_DrawSunPostEffectsi_30
	mov edx, rgp
	mov eax, [edx+0x20a0]
	cmp byte [eax+0x17c], 0x0
	jz _Z21RB_DrawSunPostEffectsi_30
	mov ebx, [eax+0x184]
	test ebx, ebx
	jz _Z21RB_DrawSunPostEffectsi_40
	movss xmm0, dword [esi+0x14]
	movss xmm2, dword [eax+0x190]
	ucomiss xmm2, xmm0
	jae _Z21RB_DrawSunPostEffectsi_40
	movss xmm3, dword [eax+0x198]
	ucomiss xmm0, xmm3
	jb _Z21RB_DrawSunPostEffectsi_50
	movss xmm0, dword [_float_1_00000000]
_Z21RB_DrawSunPostEffectsi_270:
	movaps xmm1, xmm0
	mulss xmm1, [eax+0x19c]
	movss [ebp-0x40], xmm1
	mulss xmm0, [eax+0x194]
	movss [ebp-0x3c], xmm0
	addss xmm0, [eax+0x18c]
	movss [ebp-0x3c], xmm0
	mov ecx, [eax+0x1a4]
	mov edx, [eax+0x1a0]
	movss xmm2, dword [esi+0x10]
	movss xmm3, dword [esi]
	ucomiss xmm2, xmm3
	jbe _Z21RB_DrawSunPostEffectsi_60
	test edx, edx
	jle _Z21RB_DrawSunPostEffectsi_70
	cvtsi2ss xmm1, edi
	cvtsi2ss xmm0, edx
	divss xmm1, xmm0
	addss xmm1, xmm3
	ucomiss xmm1, xmm2
	jbe _Z21RB_DrawSunPostEffectsi_80
_Z21RB_DrawSunPostEffectsi_70:
	movss [esi], xmm2
	mov dword [esp+0x4], 0x4
	mov eax, [eax+0x184]
	mov [esp], eax
	movss [ebp-0x58], xmm2
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	movss xmm2, dword [ebp-0x58]
	mulss xmm2, [ebp-0x40]
	mulss xmm2, [_float_255_00000000]
	addss xmm2, [_float_0_50000000]
	movss [esp], xmm2
	call floorf
	fstp dword [ebp-0x44]
	cvttss2si eax, [ebp-0x44]
	movzx eax, al
	mov edx, eax
	shl edx, 0x10
	mov ecx, eax
	shl ecx, 0x8
	or edx, ecx
	or eax, edx
	or eax, 0xff000000
	mov [ebp-0x1c], eax
	call _Z14RB_SetIdentityv
	mov eax, [ebp-0x1c]
	movss xmm1, dword [ebp-0x3c]
	divss xmm1, dword [_float_480_00000000]
	movss xmm0, dword [ebp-0x3c]
	divss xmm0, dword [_float_640_00000000]
	call _Z19RB_TessSunBillboardff8GfxColor
	mov ecx, gfxCmdBufSourceState
	mov edx, rgp
_Z21RB_DrawSunPostEffectsi_40:
	mov eax, [ecx+0xf0c]
	lea ecx, [eax+0x110]
	mov ebx, [edx+0x20a0]
	lea edx, [ebx+0x1d0]
	movss xmm4, dword [ebx+0x1d0]
	mulss xmm4, [eax+0x110]
	movss xmm0, dword [edx+0x4]
	mulss xmm0, [ecx+0x4]
	addss xmm4, xmm0
	movss xmm0, dword [edx+0x8]
	mulss xmm0, [ecx+0x8]
	addss xmm4, xmm0
	pxor xmm5, xmm5
	ucomiss xmm5, [ebx+0x1b0]
	jae _Z21RB_DrawSunPostEffectsi_90
	movss xmm0, dword [ebx+0x1a8]
	ucomiss xmm0, xmm4
	jb _Z21RB_DrawSunPostEffectsi_100
	movaps xmm2, xmm5
_Z21RB_DrawSunPostEffectsi_200:
	mulss xmm2, [esi+0x10]
	mov edx, [ebx+0x1b8]
	mov eax, [ebx+0x1b4]
	movss xmm3, dword [esi+0x4]
	ucomiss xmm2, xmm3
	jbe _Z21RB_DrawSunPostEffectsi_110
	test eax, eax
	jle _Z21RB_DrawSunPostEffectsi_120
	cvtsi2ss xmm1, edi
	cvtsi2ss xmm0, eax
	divss xmm1, xmm0
	addss xmm1, xmm3
	ucomiss xmm1, xmm2
	ja _Z21RB_DrawSunPostEffectsi_120
	movaps xmm2, xmm1
_Z21RB_DrawSunPostEffectsi_120:
	movss [esi+0x4], xmm2
	movaps xmm6, xmm2
	mulss xmm6, [ebx+0x1b0]
_Z21RB_DrawSunPostEffectsi_250:
	movaps xmm0, xmm5
	ucomiss xmm5, [ebx+0x1c4]
	jae _Z21RB_DrawSunPostEffectsi_130
	movss xmm0, dword [ebx+0x1bc]
	ucomiss xmm0, xmm4
	jb _Z21RB_DrawSunPostEffectsi_140
	movaps xmm2, xmm5
_Z21RB_DrawSunPostEffectsi_230:
	mulss xmm2, [esi+0x10]
	mov edx, [ebx+0x1cc]
	mov eax, [ebx+0x1c8]
	movss xmm3, dword [esi+0x8]
	ucomiss xmm2, xmm3
	jbe _Z21RB_DrawSunPostEffectsi_150
	test eax, eax
	jle _Z21RB_DrawSunPostEffectsi_160
	cvtsi2ss xmm1, edi
	cvtsi2ss xmm0, eax
	divss xmm1, xmm0
	addss xmm1, xmm3
	ucomiss xmm1, xmm2
	ja _Z21RB_DrawSunPostEffectsi_160
	movaps xmm2, xmm1
_Z21RB_DrawSunPostEffectsi_160:
	movss [esi+0x8], xmm2
	movaps xmm0, xmm2
	mulss xmm0, [ebx+0x1c4]
_Z21RB_DrawSunPostEffectsi_130:
	movss [ebp-0x2c], xmm0
	movss [ebp-0x28], xmm0
	movss [ebp-0x24], xmm0
	movss [ebp-0x20], xmm6
	lea eax, [ebp-0x1c]
	mov [esp+0x4], eax
	lea eax, [ebp-0x2c]
	mov [esp], eax
	call _Z21R_ConvertColorToBytesPKfPh
	mov eax, [ebp-0x1c]
	mov [esp+0x14], eax
	mov eax, 0x3f800000
	mov [esp+0x10], eax
	mov [esp+0xc], eax
	xor eax, eax
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov eax, rgp
	mov eax, [eax+0x2064]
	mov [esp], eax
	call _Z28RB_DrawFullScreenColoredQuadPK8Materialffffm
_Z21RB_DrawSunPostEffectsi_30:
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z21RB_DrawSunPostEffectsi_10:
	mov ecx, gfxCmdBufSourceState
	jmp _Z21RB_DrawSunPostEffectsi_170
_Z21RB_DrawSunPostEffectsi_20:
	mov edi, edx
	sub edi, eax
	jmp _Z21RB_DrawSunPostEffectsi_180
_Z21RB_DrawSunPostEffectsi_100:
	movss xmm1, dword [ebx+0x1ac]
	ucomiss xmm4, xmm1
	jb _Z21RB_DrawSunPostEffectsi_190
	movss xmm2, dword [_float_1_00000000]
	jmp _Z21RB_DrawSunPostEffectsi_200
_Z21RB_DrawSunPostEffectsi_150:
	ucomiss xmm3, xmm2
	ja _Z21RB_DrawSunPostEffectsi_210
	movaps xmm2, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_160
_Z21RB_DrawSunPostEffectsi_140:
	movss xmm1, dword [ebx+0x1c0]
	ucomiss xmm4, xmm1
	jb _Z21RB_DrawSunPostEffectsi_220
	movss xmm2, dword [_float_1_00000000]
	jmp _Z21RB_DrawSunPostEffectsi_230
_Z21RB_DrawSunPostEffectsi_110:
	ucomiss xmm3, xmm2
	ja _Z21RB_DrawSunPostEffectsi_240
	movaps xmm2, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_120
_Z21RB_DrawSunPostEffectsi_90:
	movaps xmm6, xmm5
	jmp _Z21RB_DrawSunPostEffectsi_250
_Z21RB_DrawSunPostEffectsi_60:
	ucomiss xmm3, xmm2
	jbe _Z21RB_DrawSunPostEffectsi_260
	test ecx, ecx
	jle _Z21RB_DrawSunPostEffectsi_70
	cvtsi2ss xmm0, edi
	cvtsi2ss xmm1, ecx
	divss xmm0, xmm1
	subss xmm3, xmm0
	maxss xmm2, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_70
_Z21RB_DrawSunPostEffectsi_50:
	subss xmm0, xmm2
	subss xmm3, xmm2
	divss xmm0, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_270
_Z21RB_DrawSunPostEffectsi_210:
	test edx, edx
	jle _Z21RB_DrawSunPostEffectsi_160
	cvtsi2ss xmm0, edi
	cvtsi2ss xmm1, edx
	divss xmm0, xmm1
	subss xmm3, xmm0
	maxss xmm2, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_160
_Z21RB_DrawSunPostEffectsi_240:
	test edx, edx
	jle _Z21RB_DrawSunPostEffectsi_120
	cvtsi2ss xmm0, edi
	cvtsi2ss xmm1, edx
	divss xmm0, xmm1
	subss xmm3, xmm0
	maxss xmm2, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_120
_Z21RB_DrawSunPostEffectsi_190:
	movaps xmm2, xmm4
	subss xmm2, xmm0
	subss xmm1, xmm0
	divss xmm2, xmm1
	jmp _Z21RB_DrawSunPostEffectsi_200
_Z21RB_DrawSunPostEffectsi_220:
	movaps xmm2, xmm4
	subss xmm2, xmm0
	subss xmm1, xmm0
	divss xmm2, xmm1
	jmp _Z21RB_DrawSunPostEffectsi_230
_Z21RB_DrawSunPostEffectsi_260:
	movaps xmm2, xmm3
	jmp _Z21RB_DrawSunPostEffectsi_70
_Z21RB_DrawSunPostEffectsi_80:
	movaps xmm2, xmm1
	jmp _Z21RB_DrawSunPostEffectsi_70



;Initialized global or static variables of rb_sky:
SECTION .data


;Initialized constant data of rb_sky:
SECTION .rdata
g_fltMin__uint4: dd 0x800000, 0x800000, 0x800000, 0x800000


;Zero initialized global or static variables of rb_sky:
SECTION .bss
sunFlareArray: resb 0x100




;All constant floats and doubles:
SECTION .rdata
_float__0_00050000:		dd 0xba03126f	; -0.0005
_float_16_00000000:		dd 0x41800000	; 16
_float_1_00000000:		dd 0x3f800000	; 1
_float_0_00131109:		dd 0x3aabd8fb	; 0.00131109
_float_0_99000001:		dd 0x3f7d70a4	; 0.99
_float_0_50000000:		dd 0x3f000000	; 0.5
_float_262144_00000000:		dd 0x48800000	; 262144
_float_0_00390625:		dd 0x3b800000	; 0.00390625
_float_4294967296_00000000:		dd 0x4f800000	; 4.29497e+09
_float_255_00000000:		dd 0x437f0000	; 255
_float_480_00000000:		dd 0x43f00000	; 480
_float_640_00000000:		dd 0x44200000	; 640

