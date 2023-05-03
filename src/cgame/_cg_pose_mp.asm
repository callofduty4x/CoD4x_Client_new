;Imports of cg_pose_mp:
	extern _Z25CL_DObjCreateSkelForBonesPK6DObj_sPiPP11DObjAnimMat
	extern _Z25DObjCompleteHierarchyBitsPK6DObj_sPi
	extern _Z12DObjCalcSkelPK6DObj_sPi
	extern _Z15DObjGetSetBonesPK6DObj_sPi
	extern _Z20DObjGetRootBoneCountPK6DObj_s
	extern _Z20DObjGetRotTransArrayPK6DObj_s
	extern _Z12AnglesToQuatPKfPf
	extern _Z19R_GetLocalClientNumv
	extern cgArray
	extern _Z20DObjSetRotTransIndexPK6DObj_sPKii
	extern _Z12DObjSetTransP11DObjAnimMatPKf
	extern _Z21Ragdoll_DoControllersPK7cpose_tPK6DObj_sPi
	extern _Z23DObjSetControlTagAnglesPK6DObj_sPijPf
	extern _Z15DObjSetLocalTagPK6DObj_sPijPKfS4_
	extern floorf
	extern vec3_origin
	extern _Z12AnglesToAxisPKfPA3_f
	extern _Z12DObjGetModelPK6DObj_si
	extern _Z14XModelNumBonesPK6XModel
	extern _Z17XModelGetBasePosePK6XModel
	extern _Z23DObjSetLocalTagInternalPK6DObj_sPKfS3_i

;Exports of cg_pose_mp:
	global _Z15CG_DObjCalcPosePK7cpose_tPK6DObj_sPi
	global _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi
	global _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi
	global _Z23BG_Player_DoControllersPK14CEntPlayerInfoPK6DObj_sPi


SECTION .text


;CG_DObjCalcPose(cpose_t const*, DObj_s const*, int*)
_Z15CG_DObjCalcPosePK7cpose_tPK6DObj_sPi:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x20
	mov esi, [ebp+0xc]
	mov ebx, [ebp+0x10]
	lea eax, [ebp-0xc]
	mov [esp+0x8], eax
	mov [esp+0x4], ebx
	mov [esp], esi
	call _Z25CL_DObjCreateSkelForBonesPK6DObj_sPiPP11DObjAnimMat
	test eax, eax
	jz _Z15CG_DObjCalcPosePK7cpose_tPK6DObj_sPi_10
	mov eax, [ebp-0xc]
	add esp, 0x20
	pop ebx
	pop esi
	pop ebp
	ret
_Z15CG_DObjCalcPosePK7cpose_tPK6DObj_sPi_10:
	mov [esp+0x4], ebx
	mov [esp], esi
	call _Z25DObjCompleteHierarchyBitsPK6DObj_sPi
	mov [esp+0x8], ebx
	mov [esp+0x4], esi
	mov eax, [ebp+0x8]
	mov [esp], eax
	call _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi
	mov [esp+0x4], ebx
	mov [esp], esi
	call _Z12DObjCalcSkelPK6DObj_sPi
	mov eax, [ebp-0xc]
	add esp, 0x20
	pop ebx
	pop esi
	pop ebp
	ret


;CG_DoControllers(cpose_t const*, DObj_s const*, int*)
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xfc
	lea eax, [ebp-0x34]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z15DObjGetSetBonesPK6DObj_sPi
	mov edx, [ebp+0x8]
	movzx eax, byte [edx+0x2]
	cmp al, 0xb
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_10
	ja _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_20
	sub al, 0x1
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_30
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_130:
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z20DObjGetRootBoneCountPK6DObj_s
	lea edi, [eax-0x1]
	mov edx, edi
	sar edx, 0x5
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_40
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_140:
	cmp dword [ebp-0x34], 0xffffffff
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_50
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_150:
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z20DObjGetRotTransArrayPK6DObj_s
	mov ebx, eax
	test eax, eax
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_60
	lea eax, [ebp-0x44]
	mov [esp+0x4], eax
	mov eax, [ebp+0x8]
	add eax, 0x28
	mov [esp], eax
	call _Z12AnglesToQuatPKfPf
	mov dword [ebp-0x60], 0x0
	mov dword [ebp-0x5c], 0x0
	mov dword [ebp-0x58], 0x0
	mov dword [ebp-0x54], 0x80000000
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov dword [ebp-0x48], 0x0
	call _Z19R_GetLocalClientNumv
	mov eax, cgArray
	movss xmm0, dword [eax+0x49310]
	movss [ebp-0x8c], xmm0
	movss xmm6, dword [eax+0x49314]
	movss [ebp-0x90], xmm6
	movss xmm0, dword [eax+0x49318]
	movss [ebp-0x94], xmm0
	test edi, edi
	js _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_60
	xor esi, esi
	mov eax, [ebp-0x54]
	mov edx, [ebp+0x8]
	add edx, 0x1c
	mov [ebp-0xac], edx
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_70
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_80:
	add esi, 0x1
	ror eax, 1
	mov [ebp-0x54], eax
	add ebx, 0x20
	cmp edi, esi
	jl _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_60
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_70:
	mov edx, esi
	sar edx, 0x5
	test [ebp+edx*4-0x34], eax
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_80
	mov [esp+0x8], esi
	mov eax, 0x3
	sub eax, edx
	lea eax, [ebp+eax*4-0x60]
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z20DObjSetRotTransIndexPK6DObj_sPKii
	test eax, eax
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_90
	mov eax, [ebp-0x44]
	mov [ebx], eax
	mov eax, [ebp-0x40]
	mov [ebx+0x4], eax
	mov eax, [ebp-0x3c]
	mov [ebx+0x8], eax
	mov eax, [ebp-0x38]
	mov [ebx+0xc], eax
	mov edx, [ebp+0x8]
	mov eax, [edx+0x1c]
	mov [ebp-0x24], eax
	mov edx, [ebp-0xac]
	mov eax, [edx+0x4]
	mov [ebp-0x20], eax
	mov eax, [edx+0x8]
	mov [ebp-0x1c], eax
	movss xmm0, dword [ebp-0x24]
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_190:
	subss xmm0, [ebp-0x8c]
	movss [ebp-0x24], xmm0
	movss xmm0, dword [ebp-0x20]
	subss xmm0, [ebp-0x90]
	movss [ebp-0x20], xmm0
	movss xmm0, dword [ebp-0x1c]
	subss xmm0, [ebp-0x94]
	movss [ebp-0x1c], xmm0
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z12DObjSetTransP11DObjAnimMatPKf
	mov eax, [ebp-0x54]
	add esi, 0x1
	ror eax, 1
	mov [ebp-0x54], eax
	add ebx, 0x20
	cmp edi, esi
	jge _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_70
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_60:
	mov eax, [ebp+0x8]
	cmp byte [eax+0xc], 0x0
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_100
	mov edx, [eax+0x10]
	test edx, edx
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_110
	mov eax, [eax+0x14]
	test eax, eax
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_100
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_110:
	mov edx, [ebp+0x10]
	mov [esp+0x8], edx
	mov eax, [ebp+0xc]
	mov [esp+0x4], eax
	mov edx, [ebp+0x8]
	mov [esp], edx
	call _Z21Ragdoll_DoControllersPK7cpose_tPK6DObj_sPi
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_100:
	add esp, 0xfc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_20:
	cmp al, 0xc
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_120
	cmp al, 0xe
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_130
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_120:
	mov eax, [ebp+0x10]
	mov [esp+0x8], eax
	mov edx, [ebp+0xc]
	mov [esp+0x4], edx
	mov eax, [ebp+0x8]
	mov [esp], eax
	call _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z20DObjGetRootBoneCountPK6DObj_s
	lea edi, [eax-0x1]
	mov edx, edi
	sar edx, 0x5
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_140
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_40:
	mov ecx, edi
	and ecx, 0x1f
	add ecx, 0x1
	mov eax, 0xffffffff
	shr eax, cl
	or eax, [ebp+edx*4-0x34]
	add eax, 0x1
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_150
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_60
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_10:
	cmp byte [edx+0x4c], 0x0
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_160
	mov eax, [edx+0x40]
	mov [ebp-0x24], eax
	mov eax, [edx+0x44]
	mov [ebp-0x20], eax
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_240:
	xor esi, esi
	mov [ebp-0x1c], esi
	lea ebx, [ebp-0x24]
	mov [esp+0xc], ebx
	movzx eax, byte [edx+0x4d]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z23DObjSetControlTagAnglesPK6DObj_sPijPf
	mov [esp+0xc], ebx
	mov edx, [ebp+0x8]
	movzx eax, byte [edx+0x4e]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z23DObjSetControlTagAnglesPK6DObj_sPijPf
	mov edx, [ebp+0x8]
	mov eax, [edx+0x48]
	mov [ebp-0x24], eax
	mov [ebp-0x20], esi
	mov [esp+0xc], ebx
	movzx eax, byte [edx+0x4f]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z23DObjSetControlTagAnglesPK6DObj_sPijPf
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_130
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_90:
	mov eax, [ebp-0x44]
	mov [ebp-0x80], eax
	mov eax, [ebp-0x40]
	mov [ebp-0x7c], eax
	mov eax, [ebp-0x3c]
	mov [ebp-0x78], eax
	mov eax, [ebp-0x38]
	mov [ebp-0x74], eax
	mov eax, [ebp-0xac]
	mov [esp+0x4], eax
	lea eax, [ebp-0x80]
	mov [esp], eax
	call _Z12DObjSetTransP11DObjAnimMatPKf
	movss xmm3, dword [ebp-0x80]
	movss xmm0, dword [ebp-0x7c]
	movss xmm1, dword [ebp-0x78]
	movss xmm2, dword [ebp-0x74]
	mulss xmm3, xmm3
	mulss xmm0, xmm0
	addss xmm3, xmm0
	mulss xmm1, xmm1
	addss xmm3, xmm1
	mulss xmm2, xmm2
	addss xmm3, xmm2
	ucomiss xmm3, [_float_0_00000000]
	jp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_170
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_180
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_170:
	movss xmm0, dword [_float_2_00000000]
	divss xmm0, xmm3
	movss [ebp-0x64], xmm0
	movss xmm0, dword [_float_1_00000000]
	movss [ebp-0xbc], xmm0
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_200:
	movss xmm4, dword [ebx]
	movss xmm2, dword [ebp-0x38]
	movss xmm5, dword [ebx+0xc]
	movss xmm3, dword [ebp-0x44]
	movss xmm7, dword [ebx+0x8]
	movss xmm0, dword [ebp-0x40]
	movss [ebp-0xa8], xmm0
	movss xmm6, dword [ebx+0x4]
	movss xmm0, dword [ebp-0x3c]
	movss [ebp-0xa4], xmm0
	movaps xmm0, xmm2
	mulss xmm0, xmm5
	movaps xmm1, xmm4
	mulss xmm1, xmm3
	subss xmm0, xmm1
	movss xmm1, dword [ebp-0xa8]
	mulss xmm1, xmm6
	subss xmm0, xmm1
	movss xmm1, dword [ebp-0xa4]
	mulss xmm1, xmm7
	subss xmm0, xmm1
	movss [ebx+0xc], xmm0
	movaps xmm0, xmm4
	mulss xmm0, xmm2
	movaps xmm1, xmm5
	mulss xmm1, xmm3
	addss xmm0, xmm1
	movss xmm1, dword [ebp-0xa8]
	mulss xmm1, xmm7
	addss xmm0, xmm1
	movss xmm1, dword [ebp-0xa4]
	mulss xmm1, xmm6
	subss xmm0, xmm1
	movss [ebx], xmm0
	movaps xmm0, xmm2
	mulss xmm0, xmm6
	movaps xmm1, xmm3
	mulss xmm1, xmm7
	subss xmm0, xmm1
	movss xmm1, dword [ebp-0xa8]
	mulss xmm1, xmm5
	addss xmm0, xmm1
	movss xmm1, dword [ebp-0xa4]
	mulss xmm1, xmm4
	addss xmm0, xmm1
	movss [ebx+0x4], xmm0
	mulss xmm2, xmm7
	mulss xmm3, xmm6
	addss xmm2, xmm3
	mulss xmm4, [ebp-0xa8]
	subss xmm2, xmm4
	mulss xmm5, [ebp-0xa4]
	addss xmm2, xmm5
	movss [ebx+0x8], xmm2
	movss xmm3, dword [ebp-0x64]
	movaps xmm5, xmm3
	mulss xmm5, [ebp-0x80]
	movaps xmm7, xmm3
	mulss xmm7, [ebp-0x7c]
	mulss xmm3, [ebp-0x78]
	movaps xmm6, xmm5
	mulss xmm6, [ebp-0x80]
	movss [ebp-0xa0], xmm6
	movss xmm6, dword [ebp-0x7c]
	movaps xmm2, xmm5
	mulss xmm2, xmm6
	movss xmm1, dword [ebp-0x78]
	movaps xmm4, xmm5
	mulss xmm4, xmm1
	movss xmm0, dword [ebp-0x74]
	mulss xmm5, xmm0
	mulss xmm6, xmm7
	movss [ebp-0x9c], xmm6
	movaps xmm6, xmm7
	mulss xmm6, xmm1
	movss [ebp-0x98], xmm6
	mulss xmm7, xmm0
	movaps xmm6, xmm3
	mulss xmm6, xmm1
	mulss xmm3, xmm0
	movss xmm0, dword [ebp-0x9c]
	addss xmm0, xmm6
	movss xmm1, dword [ebp-0xbc]
	subss xmm1, xmm0
	mulss xmm1, [ebx+0x10]
	movaps xmm0, xmm2
	subss xmm0, xmm3
	mulss xmm0, [ebx+0x14]
	addss xmm1, xmm0
	movaps xmm0, xmm4
	addss xmm0, xmm7
	mulss xmm0, [ebx+0x18]
	addss xmm1, xmm0
	addss xmm1, [ebp-0x70]
	movss [ebp-0x24], xmm1
	addss xmm2, xmm3
	mulss xmm2, [ebx+0x10]
	addss xmm6, [ebp-0xa0]
	movss xmm0, dword [ebp-0xbc]
	subss xmm0, xmm6
	mulss xmm0, [ebx+0x14]
	addss xmm2, xmm0
	movss xmm0, dword [ebp-0x98]
	subss xmm0, xmm5
	mulss xmm0, [ebx+0x18]
	addss xmm2, xmm0
	addss xmm2, [ebp-0x6c]
	movss [ebp-0x20], xmm2
	subss xmm4, xmm7
	mulss xmm4, [ebx+0x10]
	addss xmm5, [ebp-0x98]
	mulss xmm5, [ebx+0x14]
	addss xmm4, xmm5
	movss xmm0, dword [ebp-0xa0]
	addss xmm0, [ebp-0x9c]
	movss xmm6, dword [ebp-0xbc]
	subss xmm6, xmm0
	movss [ebp-0xbc], xmm6
	mulss xmm6, [ebx+0x18]
	addss xmm4, xmm6
	addss xmm4, [ebp-0x68]
	movss [ebp-0x1c], xmm4
	movaps xmm0, xmm1
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_190
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_180:
	movss xmm6, dword [_float_1_00000000]
	movss [ebp-0xbc], xmm6
	movss [ebp-0x74], xmm6
	mov dword [ebp-0x64], 0x40000000
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_200
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_50:
	xor eax, eax
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_210
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_220:
	cmp dword [ebp+eax*4-0x34], 0xffffffff
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_150
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_210:
	add eax, 0x1
	cmp edx, eax
	ja _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_220
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_40
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_30:
	mov eax, [ebp+0x8]
	mov ecx, [eax+0x40]
	test ecx, ecx
	jz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_130
	mov edx, [eax+0x40]
	mov [ebp-0xb0], edx
	lea esi, [eax+0x40]
	xor edi, edi
	mov ebx, edx
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_230:
	mov [esp+0xc], ebx
	movzx eax, byte [esi+0x4]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z23DObjSetControlTagAnglesPK6DObj_sPijPf
	add edi, 0x1
	add ebx, 0xc
	add esi, 0x1
	cmp edi, 0x6
	jnz _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_230
	mov eax, [ebp-0xb0]
	add eax, 0x48
	mov [esp+0x10], eax
	mov eax, [ebp-0xb0]
	add eax, 0x54
	mov [esp+0xc], eax
	mov dword [esp+0x8], 0x0
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z15DObjSetLocalTagPK6DObj_sPijPKfS4_
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_130
_Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_160:
	mov ebx, [edx+0x40]
	movss xmm0, dword [ebx]
	subss xmm0, [edx+0x28]
	mulss xmm0, [_float_0_00277778]
	movss xmm2, dword [_float_0_50000000]
	movaps xmm1, xmm0
	addss xmm1, xmm2
	movss [esp], xmm1
	movss [ebp-0xd8], xmm0
	movss [ebp-0xe8], xmm2
	call floorf
	fstp dword [ebp-0xb4]
	movss xmm0, dword [ebp-0xd8]
	subss xmm0, [ebp-0xb4]
	mulss xmm0, [_float_360_00000000]
	movss [ebp-0x24], xmm0
	movss xmm0, dword [ebx+0x4]
	mov eax, [ebp+0x8]
	subss xmm0, [eax+0x2c]
	mulss xmm0, [_float_0_00277778]
	movss xmm2, dword [ebp-0xe8]
	addss xmm2, xmm0
	movss [esp], xmm2
	movss [ebp-0xd8], xmm0
	call floorf
	fstp dword [ebp-0xb8]
	movss xmm0, dword [ebp-0xd8]
	subss xmm0, [ebp-0xb8]
	mulss xmm0, [_float_360_00000000]
	movss [ebp-0x20], xmm0
	mov edx, [ebp+0x8]
	jmp _Z16CG_DoControllersPK7cpose_tPK6DObj_sPi_240
	nop


;CG_VehPoseControllers(cpose_t const*, DObj_s const*, int*)
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x20c
	mov edi, [ebp+0x8]
	xor esi, esi
	mov [ebp-0x24], esi
	mov [ebp-0x20], esi
	mov [ebp-0x1c], esi
	mov [ebp-0x2c], esi
	mov [ebp-0x28], esi
	mov [ebp-0x38], esi
	mov [ebp-0x48], esi
	mov [ebp-0x44], esi
	mov [ebp-0x40], esi
	movsx eax, word [edi+0x40]
	cvtsi2ss xmm0, eax
	movss xmm1, dword [_float_0_00549316]
	mulss xmm0, xmm1
	movss [ebp-0x3c], xmm0
	movsx eax, word [edi+0x44]
	cvtsi2ss xmm0, eax
	mulss xmm0, xmm1
	movss [ebp-0x34], xmm0
	movsx eax, word [edi+0x46]
	cvtsi2ss xmm0, eax
	mulss xmm0, xmm1
	movss [ebp-0x30], xmm0
	cmp byte [edi+0x2], 0xc
	jz _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_10
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_80:
	movsx eax, word [edi+0x42]
	cvtsi2ss xmm0, eax
	mulss xmm0, xmm1
	movss [ebp-0x20], xmm0
	movsx eax, word [edi+0x4c]
	cvtsi2ss xmm0, eax
	mulss xmm0, xmm1
	movss [ebp-0x44], xmm0
	lea eax, [ebp-0x3c]
	mov [esp+0x10], eax
	mov ebx, vec3_origin
	mov [esp+0xc], ebx
	movzx eax, byte [edi+0x60]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z15DObjSetLocalTagPK6DObj_sPijPKfS4_
	lea eax, [ebp-0x24]
	mov [esp+0x10], eax
	mov [esp+0xc], ebx
	movzx eax, byte [edi+0x61]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z15DObjSetLocalTagPK6DObj_sPijPKfS4_
	lea eax, [ebp-0x30]
	mov [esp+0x10], eax
	mov [esp+0xc], ebx
	movzx eax, byte [edi+0x62]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z15DObjSetLocalTagPK6DObj_sPijPKfS4_
	movss xmm0, dword [edi+0x50]
	movss [ebp-0x1bc], xmm0
	lea eax, [ebp-0xd8]
	mov [esp+0x4], eax
	lea eax, [edi+0x28]
	mov [esp], eax
	call _Z12AnglesToAxisPKfPA3_f
	lea eax, [edi+0x1c]
	mov ebx, [edi+0x1c]
	mov [ebp-0xb4], ebx
	mov ecx, [eax+0x4]
	mov [ebp-0xb0], ecx
	mov edx, [eax+0x8]
	mov [ebp-0xac], edx
	movss xmm1, dword [ebp-0xd8]
	movss [ebp-0x1c4], xmm1
	movss [ebp-0x158], xmm1
	movss xmm2, dword [ebp-0xd4]
	movss [ebp-0x1c8], xmm2
	movss [ebp-0x154], xmm2
	movss xmm0, dword [ebp-0xd0]
	movss [ebp-0x1cc], xmm0
	movss [ebp-0x150], xmm0
	mov [ebp-0x14c], esi
	movss xmm1, dword [ebp-0xcc]
	movss [ebp-0x1d0], xmm1
	movss [ebp-0x148], xmm1
	movss xmm2, dword [ebp-0xc8]
	movss [ebp-0x1d4], xmm2
	movss [ebp-0x144], xmm2
	movss xmm0, dword [ebp-0xc4]
	movss [ebp-0x1d8], xmm0
	movss [ebp-0x140], xmm0
	mov [ebp-0x13c], esi
	movss xmm1, dword [ebp-0xc0]
	movss [ebp-0x1dc], xmm1
	movss [ebp-0x138], xmm1
	movss xmm2, dword [ebp-0xbc]
	movss [ebp-0x1e0], xmm2
	movss [ebp-0x134], xmm2
	movss xmm0, dword [ebp-0xb8]
	movss [ebp-0x1e4], xmm0
	movss [ebp-0x130], xmm0
	mov [ebp-0x12c], esi
	mov [ebp-0x128], ebx
	mov [ebp-0x124], ecx
	mov [ebp-0x120], edx
	mov eax, 0x3f800000
	mov [ebp-0x11c], eax
	movss [ebp-0xa8], xmm1
	movss [ebp-0xa4], xmm2
	movss [ebp-0xa0], xmm0
	mov [ebp-0x9c], esi
	mov [ebp-0x78], ebx
	mov [ebp-0x74], ecx
	mov [ebp-0x70], edx
	mov [ebp-0x6c], esi
	movss xmm1, dword [ebp-0x1c4]
	movss [ebp-0x118], xmm1
	movss xmm2, dword [ebp-0x1d0]
	movss [ebp-0x114], xmm2
	movss xmm0, dword [ebp-0x1dc]
	movss [ebp-0x110], xmm0
	mov [ebp-0x10c], eax
	movss xmm1, dword [ebp-0x1c8]
	movss [ebp-0x108], xmm1
	movss xmm2, dword [ebp-0x1d4]
	movss [ebp-0x104], xmm2
	movss xmm0, dword [ebp-0x1e0]
	movss [ebp-0x100], xmm0
	mov [ebp-0xfc], eax
	movss xmm1, dword [ebp-0x1cc]
	movss [ebp-0xf8], xmm1
	movss xmm2, dword [ebp-0x1d8]
	movss [ebp-0xf4], xmm2
	movss xmm0, dword [ebp-0x1e4]
	movss [ebp-0xf0], xmm0
	mov [ebp-0xec], eax
	mov dword [esp+0x4], 0x0
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z12DObjGetModelPK6DObj_si
	mov ebx, eax
	mov [esp], eax
	call _Z14XModelNumBonesPK6XModel
	mov [esp], ebx
	call _Z17XModelGetBasePosePK6XModel
	mov [ebp-0x1c0], eax
	movss xmm0, dword [ebp-0x128]
	movss [ebp-0x1b4], xmm0
	movss xmm1, dword [ebp-0x124]
	movss [ebp-0x1b0], xmm1
	movss xmm2, dword [ebp-0x120]
	movss [ebp-0x1ac], xmm2
	movss xmm0, dword [ebp-0xa8]
	movss [ebp-0x1a8], xmm0
	movss xmm0, dword [_float_40_00000000]
	movss xmm1, dword [ebp-0x1a8]
	mulss xmm1, xmm0
	movss [ebp-0x1a4], xmm1
	movss xmm2, dword [ebp-0xa4]
	movss [ebp-0x1a0], xmm2
	mulss xmm2, xmm0
	movss [ebp-0x19c], xmm2
	movss xmm1, dword [ebp-0xa0]
	movss [ebp-0x198], xmm1
	mulss xmm1, xmm0
	movss [ebp-0x194], xmm1
	movss xmm2, dword [ebp-0x78]
	movss [ebp-0x190], xmm2
	movss xmm1, dword [ebp-0x74]
	movss [ebp-0x18c], xmm1
	movss xmm2, dword [ebp-0x70]
	movss [ebp-0x188], xmm2
	movss xmm1, dword [ebp-0x118]
	movss [ebp-0x184], xmm1
	movss xmm2, dword [ebp-0x108]
	movss [ebp-0x180], xmm2
	movss xmm1, dword [ebp-0xf8]
	movss [ebp-0x17c], xmm1
	movss xmm2, dword [ebp-0x114]
	movss [ebp-0x178], xmm2
	movss xmm1, dword [ebp-0x104]
	movss [ebp-0x174], xmm1
	movss xmm2, dword [ebp-0xf4]
	movss [ebp-0x170], xmm2
	movss xmm1, dword [ebp-0x110]
	movss [ebp-0x16c], xmm1
	movss xmm2, dword [ebp-0x100]
	movss [ebp-0x168], xmm2
	movss xmm1, dword [ebp-0xf0]
	movss [ebp-0x164], xmm1
	movss xmm2, dword [ebp-0x10c]
	movss [ebp-0x160], xmm2
	movss xmm1, dword [ebp-0xfc]
	movss [ebp-0x15c], xmm1
	mov ebx, edi
	mov dword [ebp-0x1b8], 0x0
	movaps xmm2, xmm0
	subss xmm2, [ebp-0x1bc]
	movss [ebp-0x1f4], xmm2
	movss xmm1, dword [ebp-0x1bc]
	addss xmm1, xmm0
	movss [ebp-0x1f0], xmm1
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_30:
	movzx esi, byte [ebx+0x5c]
	cmp esi, 0xfd
	jbe _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_20
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_40:
	add dword [ebp-0x1b8], 0x1
	add ebx, 0x1
	add edi, 0x2
	cmp dword [ebp-0x1b8], 0x4
	jnz _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_30
	add esp, 0x20c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_20:
	mov [esp+0x8], esi
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z20DObjSetRotTransIndexPK6DObj_sPKii
	test eax, eax
	jz _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_40
	mov eax, esi
	shl eax, 0x5
	add eax, [ebp-0x1c0]
	lea edx, [eax+0x10]
	movss xmm7, dword [eax+0x10]
	movss [ebp-0x58], xmm7
	movss xmm0, dword [edx+0x4]
	movss [ebp-0x1e8], xmm0
	movss [ebp-0x54], xmm0
	movss xmm1, dword [edx+0x8]
	movss [ebp-0x1ec], xmm1
	movss [ebp-0x50], xmm1
	mov dword [ebp-0x4c], 0x0
	movss xmm3, dword [ebp-0x1c4]
	mulss xmm3, xmm7
	movss xmm0, dword [ebp-0x1d0]
	mulss xmm0, [ebp-0x1e8]
	addss xmm3, xmm0
	movss xmm0, dword [ebp-0x1dc]
	mulss xmm0, xmm1
	addss xmm3, xmm0
	addss xmm3, [ebp-0x1b4]
	movss xmm2, dword [ebp-0x1c8]
	mulss xmm2, xmm7
	movss xmm0, dword [ebp-0x1d4]
	mulss xmm0, [ebp-0x1e8]
	addss xmm2, xmm0
	movss xmm0, dword [ebp-0x1e0]
	mulss xmm0, xmm1
	addss xmm2, xmm0
	addss xmm2, [ebp-0x1b0]
	movss xmm0, dword [ebp-0x1cc]
	mulss xmm0, xmm7
	movss xmm1, dword [ebp-0x1d8]
	mulss xmm1, [ebp-0x1e8]
	addss xmm0, xmm1
	movss xmm1, dword [ebp-0x1e4]
	mulss xmm1, [ebp-0x1ec]
	addss xmm0, xmm1
	addss xmm0, [ebp-0x1ac]
	movss [ebp-0x68], xmm3
	movss [ebp-0x64], xmm2
	movss [ebp-0x60], xmm0
	movzx eax, word [edi+0x54]
	cvtsi2ss xmm0, eax
	mulss xmm0, [_float_0_00001526]
	mulss xmm0, [ebp-0x1f0]
	movaps xmm1, xmm0
	subss xmm1, [ebp-0x1f4]
	pxor xmm2, xmm2
	cmpss xmm2, xmm1, 0x2
	movaps xmm1, xmm2
	andps xmm0, xmm2
	movss xmm2, dword [ebp-0x1f4]
	andnps xmm1, xmm2
	orps xmm1, xmm0
	movss xmm0, dword [ebp-0x1a4]
	addss xmm0, xmm3
	movss [ebp-0x68], xmm0
	movss xmm0, dword [ebp-0x19c]
	addss xmm0, [ebp-0x64]
	movss [ebp-0x64], xmm0
	movss xmm0, dword [ebp-0x194]
	addss xmm0, [ebp-0x60]
	xorps xmm1, [_data16_80000000]
	movss xmm2, dword [ebp-0x1a8]
	mulss xmm2, xmm1
	addss xmm2, [ebp-0x68]
	movss xmm5, dword [ebp-0x1a0]
	mulss xmm5, xmm1
	addss xmm5, [ebp-0x64]
	mulss xmm1, [ebp-0x198]
	addss xmm1, xmm0
	subss xmm2, [ebp-0x190]
	subss xmm5, [ebp-0x18c]
	subss xmm1, [ebp-0x188]
	movss xmm6, dword [ebp-0x184]
	mulss xmm6, xmm2
	movss xmm0, dword [ebp-0x180]
	mulss xmm0, xmm5
	addss xmm6, xmm0
	movss xmm0, dword [ebp-0x17c]
	mulss xmm0, xmm1
	addss xmm6, xmm0
	movss [ebp-0x98], xmm6
	movss xmm4, dword [ebp-0x178]
	mulss xmm4, xmm2
	movss xmm0, dword [ebp-0x174]
	mulss xmm0, xmm5
	addss xmm4, xmm0
	movss xmm0, dword [ebp-0x170]
	mulss xmm0, xmm1
	addss xmm4, xmm0
	movss [ebp-0x94], xmm4
	movss xmm3, dword [ebp-0x16c]
	mulss xmm3, xmm2
	movss xmm0, dword [ebp-0x168]
	mulss xmm0, xmm5
	addss xmm3, xmm0
	movss xmm0, dword [ebp-0x164]
	mulss xmm0, xmm1
	addss xmm3, xmm0
	movss [ebp-0x90], xmm3
	mulss xmm2, [ebp-0x160]
	mulss xmm5, [ebp-0x15c]
	addss xmm2, xmm5
	addss xmm2, xmm1
	movss [ebp-0x8c], xmm2
	movss [ebp-0x5c], xmm2
	subss xmm6, xmm7
	movss [ebp-0x68], xmm6
	subss xmm4, [ebp-0x1e8]
	movss [ebp-0x64], xmm4
	subss xmm3, [ebp-0x1ec]
	movss [ebp-0x60], xmm3
	mov eax, [ebp-0x68]
	mov [ebp-0x88], eax
	mov eax, [ebp-0x64]
	mov [ebp-0x84], eax
	mov eax, [ebp-0x60]
	mov [ebp-0x80], eax
	mov eax, [ebp-0x5c]
	mov [ebp-0x7c], eax
	pxor xmm0, xmm0
	ucomiss xmm0, [ebp-0x44]
	jp _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_50
	jz _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_60
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_50:
	cmp dword [ebp-0x1b8], 0x1
	jbe _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_70
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_60:
	mov [esp+0xc], esi
	mov dword [esp+0x8], 0x0
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_90:
	lea eax, [ebp-0x88]
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z23DObjSetLocalTagInternalPK6DObj_sPKfS3_i
	jmp _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_40
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_10:
	mov eax, [edi+0x48]
	mov [ebp-0x28], eax
	jmp _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_80
_Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_70:
	mov [esp+0xc], esi
	lea eax, [ebp-0x48]
	mov [esp+0x8], eax
	jmp _Z21CG_VehPoseControllersPK7cpose_tPK6DObj_sPi_90
	nop


;BG_Player_DoControllers(CEntPlayerInfo const*, DObj_s const*, int*)
_Z23BG_Player_DoControllersPK14CEntPlayerInfoPK6DObj_sPi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov eax, [ebp+0x8]
	mov edx, [eax]
	mov [ebp-0x1c], edx
	mov esi, eax
	xor edi, edi
	mov ebx, edx
_Z23BG_Player_DoControllersPK14CEntPlayerInfoPK6DObj_sPi_10:
	mov [esp+0xc], ebx
	movzx eax, byte [esi+0x4]
	mov [esp+0x8], eax
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z23DObjSetControlTagAnglesPK6DObj_sPijPf
	add edi, 0x1
	add ebx, 0xc
	add esi, 0x1
	cmp edi, 0x6
	jnz _Z23BG_Player_DoControllersPK14CEntPlayerInfoPK6DObj_sPi_10
	mov eax, [ebp-0x1c]
	add eax, 0x48
	mov [esp+0x10], eax
	mov eax, [ebp-0x1c]
	add eax, 0x54
	mov [esp+0xc], eax
	mov dword [esp+0x8], 0x0
	mov eax, [ebp+0x10]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call _Z15DObjSetLocalTagPK6DObj_sPijPKfS4_
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;Initialized global or static variables of cg_pose_mp:
SECTION .data


;Initialized constant data of cg_pose_mp:
SECTION .rdata


;Zero initialized global or static variables of cg_pose_mp:
SECTION .bss


;All cstrings:
SECTION .rdata



;All constant floats and doubles:
SECTION .rdata
_float_0_00000000:		dd 0x0	; 0
_float_2_00000000:		dd 0x40000000	; 2
_float_1_00000000:		dd 0x3f800000	; 1
_float_0_00277778:		dd 0x3b360b61	; 0.00277778
_float_0_50000000:		dd 0x3f000000	; 0.5
_float_360_00000000:		dd 0x43b40000	; 360
_float_0_00549316:		dd 0x3bb40000	; 0.00549316
_float_40_00000000:		dd 0x42200000	; 40
_float_0_00001526:		dd 0x37800080	; 1.5259e-05

alignb 16
_data16_80000000:		dd 0x80000000, 0x0, 0x0, 0x0	; OWORD
