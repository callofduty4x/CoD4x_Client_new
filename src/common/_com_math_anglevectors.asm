;Imports of com_math_anglevectors:
	extern sinf
	extern cosf

;Exports of com_math_anglevectors:
	global _Z12AngleVectorsPKfPfS1_S1_
	global _Z13Vec4NormalizePf


SECTION .text


;AngleVectors(float const*, float*, float*, float*)
_Z12AngleVectorsPKfPfS1_S1_:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov esi, [ebp+0x8]
	mov ebx, [ebp+0xc]
	mov edi, [ebp+0x10]
	cvtss2sd xmm0, [esi+0x4]
	mulsd xmm0, [_double_0_01745329]
	cvtsd2ss xmm0, xmm0
	movss [ebp-0x38], xmm0
	movss [esp], xmm0
	call sinf
	fstp dword [ebp-0x2c]
	movss xmm0, dword [ebp-0x38]
	movss [esp], xmm0
	call cosf
	fstp dword [ebp-0x24]
	cvtss2sd xmm0, [esi]
	mulsd xmm0, [_double_0_01745329]
	cvtsd2ss xmm0, xmm0
	movss [ebp-0x20], xmm0
	movss [esp], xmm0
	call sinf
	fstp dword [ebp-0x30]
	movss xmm0, dword [ebp-0x20]
	movss [esp], xmm0
	call cosf
	fstp dword [ebp-0x28]
	test ebx, ebx
	jz _Z12AngleVectorsPKfPfS1_S1__10
	movss xmm0, dword [ebp-0x24]
	mulss xmm0, [ebp-0x28]
	movss [ebx], xmm0
	movss xmm0, dword [ebp-0x2c]
	mulss xmm0, [ebp-0x28]
	movss [ebx+0x4], xmm0
	movss xmm0, dword [ebp-0x30]
	xorps xmm0, [_data16_80000000]
	movss [ebp-0x3c], xmm0
	mov eax, [ebp-0x3c]
	mov [ebx+0x8], eax
_Z12AngleVectorsPKfPfS1_S1__10:
	test edi, edi
	jz _Z12AngleVectorsPKfPfS1_S1__20
_Z12AngleVectorsPKfPfS1_S1__50:
	cvtss2sd xmm0, [esi+0x8]
	mulsd xmm0, [_double_0_01745329]
	cvtsd2ss xmm0, xmm0
	movss [ebp-0x1c], xmm0
	movss [esp], xmm0
	call sinf
	fstp dword [ebp-0x34]
	movss xmm0, dword [ebp-0x1c]
	movss [esp], xmm0
	call cosf
	fstp dword [ebp-0x3c]
	movss xmm4, dword [ebp-0x3c]
	test edi, edi
	jz _Z12AngleVectorsPKfPfS1_S1__30
	movss xmm3, dword [ebp-0x34]
	xorps xmm3, [_data16_80000000]
	movss xmm2, dword [ebp-0x30]
	mulss xmm2, xmm3
	movss xmm0, dword [ebp-0x24]
	mulss xmm0, xmm2
	movss xmm1, dword [ebp-0x2c]
	mulss xmm1, xmm4
	addss xmm0, xmm1
	movss [edi], xmm0
	mulss xmm2, [ebp-0x2c]
	movss xmm0, dword [ebp-0x24]
	mulss xmm0, xmm4
	subss xmm2, xmm0
	movss [edi+0x4], xmm2
	mulss xmm3, [ebp-0x28]
	movss [edi+0x8], xmm3
_Z12AngleVectorsPKfPfS1_S1__30:
	mov eax, [ebp+0x14]
	test eax, eax
	jz _Z12AngleVectorsPKfPfS1_S1__40
	movss xmm1, dword [ebp-0x30]
	mulss xmm1, xmm4
	movss xmm0, dword [ebp-0x24]
	mulss xmm0, xmm1
	movss xmm2, dword [ebp-0x2c]
	mulss xmm2, [ebp-0x34]
	addss xmm0, xmm2
	mov eax, [ebp+0x14]
	movss [eax], xmm0
	mulss xmm1, [ebp-0x2c]
	movss xmm0, dword [ebp-0x34]
	mulss xmm0, [ebp-0x24]
	subss xmm1, xmm0
	movss [eax+0x4], xmm1
	movss xmm0, dword [ebp-0x28]
	mulss xmm0, xmm4
	movss [eax+0x8], xmm0
_Z12AngleVectorsPKfPfS1_S1__40:
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z12AngleVectorsPKfPfS1_S1__20:
	mov edx, [ebp+0x14]
	test edx, edx
	jnz _Z12AngleVectorsPKfPfS1_S1__50
	jmp _Z12AngleVectorsPKfPfS1_S1__40
	add [eax], al

;Vec4Normalize(float*)
_Z13Vec4NormalizePf:
	push ebp
	mov ebp, esp
	sub esp, 0x4
	mov eax, [ebp+0x8]
	movss xmm4, dword [eax]
	movss xmm1, dword [eax+0x4]
	movss xmm2, dword [eax+0x8]
	movss xmm3, dword [eax+0xc]
	movaps xmm0, xmm4
	mulss xmm0, xmm4
	mulss xmm1, xmm1
	addss xmm0, xmm1
	mulss xmm2, xmm2
	addss xmm0, xmm2
	mulss xmm3, xmm3
	addss xmm0, xmm3
	sqrtss xmm2, xmm0
	ucomiss xmm2, [_float_0_00000000]
	jp _Z13Vec4NormalizePf_10
	jz _Z13Vec4NormalizePf_20
_Z13Vec4NormalizePf_10:
	movss xmm0, dword [_float_1_00000000]
	divss xmm0, xmm2
	mulss xmm4, xmm0
	movss [eax], xmm4
	movaps xmm1, xmm0
	mulss xmm1, [eax+0x4]
	movss [eax+0x4], xmm1
	movaps xmm1, xmm0
	mulss xmm1, [eax+0x8]
	movss [eax+0x8], xmm1
	mulss xmm0, [eax+0xc]
	movss [eax+0xc], xmm0
_Z13Vec4NormalizePf_20:
	movss [ebp-0x4], xmm2
	fld dword [ebp-0x4]
	leave
	ret


;Initialized global or static variables of com_math_anglevectors:
SECTION .data


;Initialized constant data of com_math_anglevectors:
SECTION .rdata


;Zero initialized global or static variables of com_math_anglevectors:
SECTION .bss


;All cstrings:
SECTION .rdata



;All constant floats and doubles:
SECTION .rdata
_double_0_01745329:		dq 0x3f91df46a2529d39	; 0.0174533
_float_0_00000000:		dd 0x0	; 0
_float_1_00000000:		dd 0x3f800000	; 1

alignb 16
_data16_80000000:		dd 0x80000000, 0x0, 0x0, 0x0	; OWORD
