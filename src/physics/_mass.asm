;Imports of mass:
	extern dSetZero
	extern dMassTranslate

;Exports of mass:
	global _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4_

SECTION .text


;Phys_ComputeMassProperties(float const*, float const*, unsigned char (*)(float const*, float const*, void*), void*, float*, float*, float*)
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4_:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xfc
	mov ebx, [ebp+0x8]
	mov esi, [ebp+0xc]
	xor edi, edi
	mov [ebp-0x74], edi
	mov dword [esp+0x4], 0x4
	lea eax, [ebp-0x70]
	mov [esp], eax
	call dSetZero
	mov dword [esp+0x4], 0xc
	lea edx, [ebp-0x60]
	mov [esp], edx
	call dSetZero
	movss xmm0, dword [esi]
	movss [ebp-0xb8], xmm0
	subss xmm0, [ebx]
	movss [ebp-0xb8], xmm0
	movss xmm0, dword [_float_0_03125000]
	movss xmm1, dword [ebp-0xb8]
	mulss xmm1, xmm0
	movss [ebp-0xb8], xmm1
	lea eax, [ebx+0x4]
	mov [ebp-0xc0], eax
	movss xmm7, dword [esi+0x4]
	subss xmm7, [ebx+0x4]
	mulss xmm7, xmm0
	lea edx, [ebx+0x8]
	mov [ebp-0xbc], edx
	movss xmm6, dword [esi+0x8]
	subss xmm6, [ebx+0x8]
	mulss xmm6, xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm1, xmm0
	movss [ebp-0x24], xmm1
	movaps xmm1, xmm7
	mulss xmm1, xmm0
	movss [ebp-0x20], xmm1
	mulss xmm0, xmm6
	movss [ebp-0x1c], xmm0
	movss xmm0, dword [ebx]
	addss xmm0, [ebp-0x24]
	movss [ebp-0x30], xmm0
	xor esi, esi
	mov [ebp-0xb0], edi
	movss xmm0, dword [ebp-0xb0]
	movss [ebp-0xac], xmm0
	movss [ebp-0xa8], xmm0
	movss [ebp-0xa4], xmm0
	movss [ebp-0xa0], xmm0
	movss [ebp-0x9c], xmm0
	mov dword [ebp-0xb4], 0x0
	movss [ebp-0x88], xmm0
	movss [ebp-0x84], xmm0
	movss [ebp-0x80], xmm0
	lea edi, [ebp-0x30]
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__50:
	movss xmm0, dword [eax]
	addss xmm0, [ebp-0x20]
	movss [ebp-0x2c], xmm0
	mov dword [ebp-0x7c], 0x20
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__30:
	mov edx, [ebp-0xbc]
	movss xmm0, dword [edx]
	addss xmm0, [ebp-0x1c]
	movss [ebp-0x28], xmm0
	mov ebx, 0x20
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__20:
	mov eax, [ebp+0x14]
	mov [esp+0x8], eax
	lea edx, [ebp-0x24]
	mov [esp+0x4], edx
	mov [esp], edi
	movss [ebp-0xe8], xmm6
	movss [ebp-0xf8], xmm7
	call dword [ebp+0x10]
	test al, al
	movss xmm6, dword [ebp-0xe8]
	movss xmm7, dword [ebp-0xf8]
	jz _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__10
	add esi, 0x1
	movss xmm0, dword [ebp-0x80]
	addss xmm0, [ebp-0x30]
	movss [ebp-0x80], xmm0
	movss xmm1, dword [ebp-0x84]
	addss xmm1, [ebp-0x2c]
	movss [ebp-0x84], xmm1
	movss xmm0, dword [ebp-0x88]
	addss xmm0, [ebp-0x28]
	movss [ebp-0x88], xmm0
	movss xmm4, dword [ebp-0x30]
	movaps xmm1, xmm4
	mulss xmm1, xmm4
	movss xmm5, dword [ebp-0x2c]
	movaps xmm2, xmm5
	mulss xmm2, xmm5
	movaps xmm0, xmm1
	addss xmm0, xmm2
	addss xmm0, [ebp-0xb0]
	movss [ebp-0xb0], xmm0
	movss xmm3, dword [ebp-0x28]
	movaps xmm0, xmm3
	mulss xmm0, xmm3
	addss xmm1, xmm0
	addss xmm1, [ebp-0xac]
	movss [ebp-0xac], xmm1
	addss xmm2, xmm0
	addss xmm2, [ebp-0xa8]
	movss [ebp-0xa8], xmm2
	movaps xmm0, xmm4
	mulss xmm0, xmm5
	addss xmm0, [ebp-0xa4]
	movss [ebp-0xa4], xmm0
	mulss xmm4, xmm3
	addss xmm4, [ebp-0xa0]
	movss [ebp-0xa0], xmm4
	mulss xmm5, xmm3
	addss xmm5, [ebp-0x9c]
	movss [ebp-0x9c], xmm5
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__10:
	movaps xmm0, xmm6
	addss xmm0, [ebp-0x28]
	movss [ebp-0x28], xmm0
	sub ebx, 0x1
	jnz _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__20
	movaps xmm0, xmm7
	addss xmm0, [ebp-0x2c]
	movss [ebp-0x2c], xmm0
	sub dword [ebp-0x7c], 0x1
	jnz _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__30
	movss xmm0, dword [ebp-0xb8]
	addss xmm0, [ebp-0x30]
	movss [ebp-0x30], xmm0
	add dword [ebp-0xb4], 0x1
	cmp dword [ebp-0xb4], 0x20
	jz _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__40
	mov eax, [ebp-0xc0]
	jmp _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__50
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__40:
	cmp esi, 0x0
	jnz _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__60
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__80:
	add esp, 0xfc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__60:
	jl _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__70
	cvtsi2ss xmm0, esi
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__90:
	movss xmm1, dword [_float_1_00000000]
	divss xmm1, xmm0
	movaps xmm0, xmm1
	movss xmm1, dword [ebp-0x80]
	mulss xmm1, xmm0
	movss [ebp-0xc4], xmm1
	mov eax, [ebp+0x18]
	movss [eax], xmm1
	movss xmm1, dword [ebp-0x84]
	mulss xmm1, xmm0
	movss [ebp-0xc8], xmm1
	movss [eax+0x4], xmm1
	movss xmm1, dword [ebp-0x88]
	mulss xmm1, xmm0
	movss [ebp-0x98], xmm1
	movss [eax+0x8], xmm1
	movss xmm1, dword [ebp-0x9c]
	xorps xmm1, [_data16_80000000]
	mulss xmm1, xmm0
	movss [ebp-0x94], xmm1
	movss xmm1, dword [ebp-0xa0]
	xorps xmm1, [_data16_80000000]
	mulss xmm1, xmm0
	movss [ebp-0x90], xmm1
	movss xmm1, dword [ebp-0xa4]
	xorps xmm1, [_data16_80000000]
	mulss xmm1, xmm0
	movss [ebp-0x8c], xmm1
	mov dword [ebp-0x74], 0x0
	mov dword [esp+0x4], 0x4
	lea ebx, [ebp-0x74]
	lea eax, [ebp-0x70]
	mov [esp], eax
	movss [ebp-0xd8], xmm0
	call dSetZero
	mov dword [esp+0x4], 0xc
	lea edx, [ebp-0x60]
	mov [esp], edx
	call dSetZero
	mov dword [ebp-0x74], 0x3f800000
	movss xmm1, dword [ebp-0xc4]
	movss [ebp-0x70], xmm1
	movss xmm1, dword [ebp-0xc8]
	movss [ebp-0x6c], xmm1
	movss xmm1, dword [ebp-0x98]
	movss [ebp-0x68], xmm1
	movss xmm0, dword [ebp-0xd8]
	movss xmm1, dword [ebp-0xa8]
	mulss xmm1, xmm0
	movss [ebp-0x60], xmm1
	movss xmm1, dword [ebp-0xac]
	mulss xmm1, xmm0
	movss [ebp-0x4c], xmm1
	mulss xmm0, [ebp-0xb0]
	movss [ebp-0x38], xmm0
	movss xmm0, dword [ebp-0x8c]
	movss [ebp-0x5c], xmm0
	movss xmm1, dword [ebp-0x90]
	movss [ebp-0x58], xmm1
	movss xmm0, dword [ebp-0x94]
	movss [ebp-0x48], xmm0
	movss xmm1, dword [ebp-0x8c]
	movss [ebp-0x50], xmm1
	movss xmm0, dword [ebp-0x90]
	movss [ebp-0x40], xmm0
	movss xmm1, dword [ebp-0x94]
	movss [ebp-0x3c], xmm1
	mov eax, [ebp+0x18]
	movss xmm0, dword [eax+0x8]
	xorps xmm0, [_data16_80000000]
	movss [esp+0xc], xmm0
	movss xmm0, dword [eax+0x4]
	xorps xmm0, [_data16_80000000]
	movss [esp+0x8], xmm0
	movss xmm0, dword [eax]
	xorps xmm0, [_data16_80000000]
	movss [esp+0x4], xmm0
	mov [esp], ebx
	call dMassTranslate
	mov eax, [ebp-0x60]
	mov edx, [ebp+0x1c]
	mov [edx], eax
	mov eax, [ebp-0x4c]
	mov [edx+0x4], eax
	mov eax, [ebp-0x38]
	mov [edx+0x8], eax
	mov eax, [ebp-0x5c]
	mov edx, [ebp+0x20]
	mov [edx], eax
	mov eax, [ebp-0x58]
	mov [edx+0x4], eax
	mov eax, [ebp-0x48]
	mov [edx+0x8], eax
	jmp _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__80
_Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__70:
	mov eax, esi
	shr eax, 1
	and esi, 0x1
	or eax, esi
	cvtsi2ss xmm0, eax
	addss xmm0, xmm0
	jmp _Z26Phys_ComputeMassPropertiesPKfS0_PFhS0_S0_PvES1_PfS4_S4__90
	add [eax], al


;All constant floats and doubles:
SECTION .rdata
_float_0_03125000:		dd 0x3d000000	; 0.03125
_float_0_50000000:		dd 0x3f000000	; 0.5
_float_1_00000000:		dd 0x3f800000	; 1

alignb 16
_data16_80000000:		dd 0x80000000, 0x0, 0x0, 0x0	; OWORD