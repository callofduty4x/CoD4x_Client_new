;Imports of phys_contacts:
	extern phys_drawcontacts
	extern physGlob
	extern _Z10Com_PrintfiPKcz
	extern _Z15Vec3NormalizeToPKfPf
	extern colorYellow
	extern _Z11CG_DebugBoxPKfS0_S0_fS0_ii
	extern _Z12CG_DebugLinePKfS0_S0_ii
	extern phys_contact_cfm
	extern phys_contact_erp
	extern ODE_BodyGetFirstGeom
	extern dBodyGetData
	extern phys_noIslands
	extern _Z19dJointCreateContactP7dxWorldP12dxJointGroupPK18dSurfaceParametersPK12dContactGeom
	extern dJointAttach
	extern dBodyGetPointVel
	extern dNormalize3
	extern colorRed
	extern phys_jitterMaxMass
	extern g_phys_msecStep
	extern _Z7randomfv
	extern _Z16Phys_ObjAddForce9PhysWorldiPKfS1_
	extern dBodyGetPosition
	extern _Z16Com_PrintWarningiPKcz

;Exports of phys_contacts:
	global _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList
	global _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1_
	global _Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii
	global _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld


SECTION .text


;Phys_RemoveOpposingNormalContacts(float const*, ContactList*)
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x14
	mov [ebp-0x20], eax
	mov esi, edx
	xor edx, edx
	mov ecx, [esi+0x1800]
	pxor xmm7, xmm7
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_20:
	lea eax, [ecx-0x1]
	cmp edx, eax
	jge _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_10
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_60:
	lea eax, [edx+edx*2]
	shl eax, 0x4
	lea ebx, [esi+eax]
	lea eax, [ebx+0x10]
	mov [ebp-0x1c], eax
	movss xmm5, dword [ebx+0x10]
	lea eax, [ebx+0x14]
	mov [ebp-0x18], eax
	movss xmm4, dword [ebx+0x14]
	lea eax, [ebx+0x18]
	mov [ebp-0x14], eax
	movss xmm3, dword [ebx+0x18]
	add edx, 0x1
	mov [ebp-0x10], edx
	cmp ecx, edx
	jle _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_20
	mov edi, edx
	movss xmm6, dword [_float__0_99000001]
	lea eax, [edx+edx*2]
	shl eax, 0x4
	lea ecx, [eax+esi]
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_50:
	movaps xmm0, xmm5
	mulss xmm0, [ecx+0x10]
	movaps xmm1, xmm4
	mulss xmm1, [ecx+0x14]
	addss xmm0, xmm1
	movaps xmm1, xmm3
	mulss xmm1, [ecx+0x18]
	addss xmm0, xmm1
	ucomiss xmm6, xmm0
	jbe _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_30
	movaps xmm2, xmm5
	mov edx, [ebp-0x20]
	mulss xmm2, [edx]
	movaps xmm0, xmm4
	mulss xmm0, [edx+0x4]
	addss xmm2, xmm0
	movaps xmm0, xmm3
	mulss xmm0, [edx+0x8]
	addss xmm2, xmm0
	mov eax, [ebp-0x1c]
	movss xmm1, dword [eax]
	mulss xmm1, [ebx]
	mov edx, [ebp-0x18]
	movss xmm0, dword [edx]
	mulss xmm0, [ebx+0x4]
	addss xmm1, xmm0
	mov eax, [ebp-0x14]
	movss xmm0, dword [eax]
	mulss xmm0, [ebx+0x8]
	addss xmm1, xmm0
	subss xmm2, xmm1
	ucomiss xmm7, xmm2
	ja _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_40
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_70:
	mov eax, [esi+0x1800]
	lea eax, [eax+eax*2]
	shl eax, 0x4
	add eax, esi
	lea edx, [eax-0x30]
	mov eax, [eax-0x30]
	mov [ecx], eax
	mov eax, [edx+0x4]
	mov [ecx+0x4], eax
	mov eax, [edx+0x8]
	mov [ecx+0x8], eax
	mov eax, [edx+0xc]
	mov [ecx+0xc], eax
	mov eax, [edx+0x10]
	mov [ecx+0x10], eax
	mov eax, [edx+0x14]
	mov [ecx+0x14], eax
	mov eax, [edx+0x18]
	mov [ecx+0x18], eax
	mov eax, [edx+0x1c]
	mov [ecx+0x1c], eax
	mov eax, [edx+0x20]
	mov [ecx+0x20], eax
	mov eax, [edx+0x24]
	mov [ecx+0x24], eax
	mov eax, [edx+0x28]
	mov [ecx+0x28], eax
	mov eax, [edx+0x2c]
	mov [ecx+0x2c], eax
	sub dword [esi+0x1800], 0x1
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_30:
	add edi, 0x1
	add ecx, 0x30
	cmp edi, [esi+0x1800]
	jl _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_50
	mov ecx, [esi+0x1800]
	mov edx, [ebp-0x10]
	lea eax, [ecx-0x1]
	cmp edx, eax
	jl _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_60
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_10:
	add esp, 0x14
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_40:
	mov eax, [ecx]
	mov [ebx], eax
	mov eax, [ecx+0x4]
	mov [ebx+0x4], eax
	mov eax, [ecx+0x8]
	mov [ebx+0x8], eax
	mov eax, [ecx+0xc]
	mov [ebx+0xc], eax
	mov eax, [ecx+0x10]
	mov [ebx+0x10], eax
	mov eax, [ecx+0x14]
	mov [ebx+0x14], eax
	mov eax, [ecx+0x18]
	mov [ebx+0x18], eax
	mov eax, [ecx+0x1c]
	mov [ebx+0x1c], eax
	mov eax, [ecx+0x20]
	mov [ebx+0x20], eax
	mov eax, [ecx+0x24]
	mov [ebx+0x24], eax
	mov eax, [ecx+0x28]
	mov [ebx+0x28], eax
	mov eax, [ecx+0x2c]
	mov [ebx+0x2c], eax
	mov edx, [ebp-0x1c]
	movss xmm5, dword [edx]
	mov eax, [ebp-0x18]
	movss xmm4, dword [eax]
	mov edx, [ebp-0x14]
	movss xmm3, dword [edx]
	jmp _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList_70


;Phys_ReduceContacts(dxBody*, ContactList const*, ContactList*)
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1_:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x37c
	mov eax, phys_drawcontacts
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__10
	mov ecx, [ebp+0xc]
	mov ebx, [ecx+0x1800]
	test ebx, ebx
	jg _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__20
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__10:
	mov ebx, [ebp+0xc]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__680:
	mov eax, 0x19919
	cdq
	idiv dword [ebx+0x1800]
	mov ecx, edx
	lea eax, [edx+edx*2]
	shl eax, 0x4
	lea eax, [eax+ebx+0x10]
	mov edx, [eax]
	mov [ebp-0x64], edx
	mov edx, [eax+0x4]
	mov [ebp-0x60], edx
	mov eax, [eax+0x8]
	mov [ebp-0x5c], eax
	mov eax, [ebx+0x1800]
	test eax, eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__30
	mov eax, ebx
	movss xmm2, dword [_float_3402823466385288598117041]
	xor edx, edx
	mov ebx, 0xffffffff
	add eax, 0x10
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__50:
	mov dword [ebp+edx*4-0x288], 0xffffffff
	movss xmm1, dword [ebp-0x64]
	mulss xmm1, [eax]
	movss xmm0, dword [ebp-0x60]
	mulss xmm0, [eax+0x4]
	addss xmm1, xmm0
	movss xmm0, dword [ebp-0x5c]
	mulss xmm0, [eax+0x8]
	addss xmm1, xmm0
	ucomiss xmm2, xmm1
	jbe _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__40
	movaps xmm2, xmm1
	mov ebx, edx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__40:
	add edx, 0x1
	add eax, 0x30
	mov esi, [ebp+0xc]
	cmp edx, [esi+0x1800]
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__50
	mov eax, ebx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__640:
	mov dword [ebp+ecx*4-0x288], 0x0
	mov dword [ebp+eax*4-0x288], 0x1
	lea eax, [ebx+ebx*2]
	shl eax, 0x4
	mov edx, [ebp+0xc]
	lea eax, [eax+edx+0x10]
	movss xmm0, dword [eax]
	movss [ebp-0x2c8], xmm0
	movss [ebp-0x58], xmm0
	movss xmm2, dword [eax+0x4]
	movss [ebp-0x2cc], xmm2
	movss [ebp-0x54], xmm2
	movss xmm7, dword [eax+0x8]
	movss [ebp-0x50], xmm7
	mov ecx, [edx+0x1800]
	test ecx, ecx
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__60
	mov eax, edx
	movss xmm0, dword [ebp-0x64]
	movss [ebp-0x2c0], xmm0
	movss xmm6, dword [ebp-0x60]
	movss xmm5, dword [ebp-0x5c]
	movss xmm2, dword [_float_3402823466385288598117041]
	movss [ebp-0x29c], xmm2
	xor edx, edx
	mov ebx, 0xffffffff
	add eax, 0x10
	movaps xmm4, xmm0
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__70
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__90:
	movss xmm4, dword [ebp-0x2c0]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__70:
	movss xmm1, dword [eax]
	movss xmm2, dword [eax+0x4]
	movss xmm3, dword [eax+0x8]
	mulss xmm4, xmm1
	movaps xmm0, xmm6
	mulss xmm0, xmm2
	addss xmm4, xmm0
	movaps xmm0, xmm5
	mulss xmm0, xmm3
	addss xmm4, xmm0
	mulss xmm1, [ebp-0x2c8]
	mulss xmm2, [ebp-0x2cc]
	addss xmm1, xmm2
	mulss xmm3, xmm7
	addss xmm1, xmm3
	movaps xmm0, xmm4
	subss xmm0, xmm1
	pxor xmm2, xmm2
	cmpss xmm2, xmm0, 0x2
	movaps xmm0, xmm2
	movaps xmm2, xmm4
	andps xmm2, xmm0
	movaps xmm4, xmm0
	andnps xmm4, xmm1
	orps xmm4, xmm2
	movss xmm0, dword [ebp-0x29c]
	ucomiss xmm0, xmm4
	jbe _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__80
	movss [ebp-0x29c], xmm4
	mov ebx, edx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__80:
	add edx, 0x1
	add eax, 0x30
	cmp ecx, edx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__90
	mov eax, ebx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__650:
	mov dword [ebp+eax*4-0x288], 0x2
	xor edi, edi
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__170:
	lea eax, [ebp-0x88]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__100:
	mov dword [eax], 0x0
	mov dword [eax+0x4], 0x0
	mov dword [eax+0x8], 0x0
	add eax, 0xc
	lea edx, [ebp-0x64]
	cmp edx, eax
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__100
	mov ecx, [ebp+0xc]
	mov eax, [ecx+0x1800]
	test eax, eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__110
	xor ecx, ecx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__130:
	mov eax, [ebp+ecx*4-0x288]
	cmp eax, 0xffffffff
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__120
	lea edx, [ecx+ecx*2]
	shl edx, 0x4
	mov ebx, [ebp+0xc]
	lea edx, [edx+ebx+0x10]
	lea eax, [eax+eax*2]
	lea eax, [ebp+eax*4-0x88]
	movss xmm0, dword [eax]
	addss xmm0, [edx]
	movss [eax], xmm0
	movss xmm0, dword [eax+0x4]
	addss xmm0, [edx+0x4]
	movss [eax+0x4], xmm0
	movss xmm0, dword [eax+0x8]
	addss xmm0, [edx+0x8]
	movss [eax+0x8], xmm0
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__120:
	add ecx, 0x1
	mov esi, [ebp+0xc]
	cmp [esi+0x1800], ecx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__130
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__110:
	lea edx, [ebp-0x88]
	lea eax, [ebp-0x80]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__150:
	movss xmm3, dword [eax-0x8]
	movss xmm0, dword [eax-0x4]
	movss xmm2, dword [eax]
	movaps xmm1, xmm3
	mulss xmm1, xmm3
	mulss xmm0, xmm0
	addss xmm1, xmm0
	mulss xmm2, xmm2
	addss xmm1, xmm2
	sqrtss xmm1, xmm1
	movaps xmm0, xmm1
	xorps xmm0, [_data16_80000000]
	pxor xmm2, xmm2
	ucomiss xmm0, xmm2
	jb _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__140
	movss xmm1, dword [_float_1_00000000]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__220:
	mulss xmm3, xmm1
	movss [eax-0x8], xmm3
	movaps xmm0, xmm1
	mulss xmm0, [eax-0x4]
	movss [eax-0x4], xmm0
	mulss xmm1, [eax]
	movss [eax], xmm1
	add edx, 0xc
	add eax, 0xc
	lea ecx, [ebp-0x64]
	cmp ecx, edx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__150
	cmp edi, 0x5
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__160
	add edi, 0x1
	mov ebx, [ebp+0xc]
	mov eax, [ebx+0x1800]
	test eax, eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__170
	mov ecx, ebx
	xor ebx, ebx
	movss xmm6, dword [_float__340282346638528859811704]
	add ecx, 0x10
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__200:
	movss xmm4, dword [ecx]
	movss xmm3, dword [ecx+0x4]
	movss xmm2, dword [ecx+0x8]
	xor edx, edx
	mov esi, 0xffffffff
	movaps xmm5, xmm6
	lea eax, [ebp-0x88]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__190:
	movaps xmm1, xmm4
	mulss xmm1, [eax]
	movaps xmm0, xmm3
	mulss xmm0, [eax+0x4]
	addss xmm1, xmm0
	movaps xmm0, xmm2
	mulss xmm0, [eax+0x8]
	addss xmm1, xmm0
	movaps xmm0, xmm5
	subss xmm0, xmm1
	pxor xmm7, xmm7
	ucomiss xmm0, xmm7
	jb _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__180
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__210:
	add edx, 0x1
	add eax, 0xc
	cmp edx, 0x3
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__190
	mov [ebp+ebx*4-0x288], esi
	add ebx, 0x1
	add ecx, 0x30
	mov eax, [ebp+0xc]
	cmp [eax+0x1800], ebx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__200
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__170
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__180:
	movaps xmm5, xmm1
	mov esi, edx
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__210
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__140:
	movss xmm7, dword [_float_1_00000000]
	divss xmm7, xmm1
	movaps xmm1, xmm7
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__220
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__160:
	mov eax, physGlob
	cmp byte [eax+0xbaa8], 0x0
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__230
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__620:
	mov dword [ebp-0x298], 0x0
	mov dword [ebp-0x2a4], 0xc
	lea edi, [ebp-0x88]
	add edi, 0xc
	mov ebx, [ebp-0x298]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__310:
	add ebx, 0x1
	mov [ebp-0x294], ebx
	cmp ebx, 0x3
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__240
	mov esi, [ebp-0x2a4]
	mov [ebp-0x2ec], esi
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__290:
	lea eax, [ebp-0x88]
	add eax, [ebp-0x2ec]
	movss xmm1, dword [edi-0xc]
	mulss xmm1, [eax]
	movss xmm0, dword [edi-0x8]
	mulss xmm0, [eax+0x4]
	addss xmm1, xmm0
	movss xmm0, dword [edi-0x4]
	mulss xmm0, [eax+0x8]
	addss xmm1, xmm0
	ucomiss xmm1, [_float_0_99900001]
	jbe _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__250
	mov eax, physGlob
	cmp byte [eax+0xbaa8], 0x0
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__260
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__320:
	mov edx, [ebp+0xc]
	mov eax, [edx+0x1800]
	test eax, eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__250
	mov ecx, 0x1
	lea edx, [ebp-0x288]
	add edx, 0x4
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__270
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__280:
	mov eax, ecx
	add ecx, 0x1
	add edx, 0x4
	mov esi, [ebp+0xc]
	cmp [esi+0x1800], eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__250
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__270:
	cmp ebx, [edx-0x4]
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__280
	mov esi, [ebp-0x298]
	mov [edx-0x4], esi
	mov eax, ecx
	add ecx, 0x1
	add edx, 0x4
	mov esi, [ebp+0xc]
	cmp [esi+0x1800], eax
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__270
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__250:
	add ebx, 0x1
	add dword [ebp-0x2ec], 0xc
	cmp ebx, 0x3
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__290
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__240:
	add dword [ebp-0x2a4], 0xc
	add edi, 0xc
	cmp dword [ebp-0x294], 0x2
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__300
	mov eax, [ebp-0x294]
	mov [ebp-0x298], eax
	mov ebx, eax
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__310
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__260:
	mov eax, [ebp-0x298]
	mov [esp+0xc], eax
	mov [esp+0x8], ebx
	mov dword [esp+0x4], _cstring_group_i_merged_i
	mov dword [esp], 0x0
	call _Z10Com_PrintfiPKcz
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__320
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__300:
	mov edx, [ebp+0x10]
	mov dword [edx+0x1800], 0x0
	lea eax, [ebp-0x88]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__330:
	mov dword [eax], 0x0
	mov dword [eax+0x4], 0x0
	mov dword [eax+0x8], 0x0
	add eax, 0xc
	lea ecx, [ebp-0x64]
	cmp eax, ecx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__330
	mov ebx, [ebp+0xc]
	mov eax, [ebx+0x1800]
	test eax, eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__340
	xor ecx, ecx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__350:
	lea edx, [ecx+ecx*2]
	shl edx, 0x4
	mov esi, [ebp+0xc]
	lea edx, [edx+esi+0x10]
	mov eax, [ebp+ecx*4-0x288]
	lea eax, [eax+eax*2]
	lea eax, [ebp+eax*4-0x88]
	movss xmm0, dword [eax]
	addss xmm0, [edx]
	movss [eax], xmm0
	movss xmm0, dword [eax+0x4]
	addss xmm0, [edx+0x4]
	movss [eax+0x4], xmm0
	movss xmm0, dword [eax+0x8]
	addss xmm0, [edx+0x8]
	movss [eax+0x8], xmm0
	add ecx, 0x1
	cmp [esi+0x1800], ecx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__350
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__340:
	mov dword [ebp-0x28c], 0x0
	lea eax, [ebp-0x88]
	mov [ebp-0x2a8], eax
	mov ecx, eax
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__570:
	lea edx, [ebp-0x34]
	mov [esp+0x4], edx
	mov [esp], ecx
	call _Z15Vec3NormalizeToPKfPf
	fstp st0
	movss xmm5, dword [ebp-0x2c]
	movaps xmm0, xmm5
	andps xmm0, [_data16_7fffffff]
	ucomiss xmm0, [_float_0_50000000]
	jb _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__360
	pxor xmm1, xmm1
	movss xmm4, dword [_float_1_00000000]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__580:
	movaps xmm3, xmm1
	mulss xmm3, [ebp-0x30]
	movaps xmm0, xmm5
	mulss xmm0, xmm4
	subss xmm3, xmm0
	movss [ebp-0x64], xmm3
	pxor xmm2, xmm2
	mulss xmm2, xmm5
	mulss xmm1, [ebp-0x34]
	subss xmm2, xmm1
	movss [ebp-0x60], xmm2
	movaps xmm0, xmm4
	mulss xmm0, [ebp-0x34]
	movss xmm4, dword [ebp-0x30]
	pxor xmm1, xmm1
	mulss xmm1, xmm4
	subss xmm0, xmm1
	movss [ebp-0x5c], xmm0
	movaps xmm1, xmm3
	mulss xmm1, xmm3
	mulss xmm2, xmm2
	addss xmm1, xmm2
	mulss xmm0, xmm0
	addss xmm1, xmm0
	sqrtss xmm1, xmm1
	movaps xmm0, xmm1
	xorps xmm0, [_data16_80000000]
	pxor xmm2, xmm2
	ucomiss xmm0, xmm2
	jb _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__370
	movss xmm1, dword [_float_1_00000000]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__600:
	mulss xmm3, xmm1
	movss [ebp-0x64], xmm3
	movaps xmm0, xmm1
	mulss xmm0, [ebp-0x60]
	movss [ebp-0x60], xmm0
	mulss xmm1, [ebp-0x5c]
	movss [ebp-0x5c], xmm1
	movaps xmm3, xmm4
	mulss xmm3, xmm1
	movaps xmm0, xmm5
	mulss xmm0, [ebp-0x60]
	subss xmm3, xmm0
	movss [ebp-0x58], xmm3
	movaps xmm2, xmm5
	mulss xmm2, [ebp-0x64]
	movss xmm0, dword [ebp-0x34]
	movaps xmm1, xmm0
	mulss xmm1, [ebp-0x5c]
	subss xmm2, xmm1
	movss [ebp-0x54], xmm2
	mulss xmm0, [ebp-0x60]
	mulss xmm4, [ebp-0x64]
	subss xmm0, xmm4
	movss [ebp-0x50], xmm0
	movaps xmm1, xmm3
	mulss xmm1, xmm3
	mulss xmm2, xmm2
	addss xmm1, xmm2
	mulss xmm0, xmm0
	addss xmm1, xmm0
	sqrtss xmm1, xmm1
	movaps xmm0, xmm1
	xorps xmm0, [_data16_80000000]
	pxor xmm2, xmm2
	ucomiss xmm0, xmm2
	jb _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__380
	movss xmm1, dword [_float_1_00000000]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__590:
	mulss xmm3, xmm1
	movss [ebp-0x58], xmm3
	movaps xmm0, xmm1
	mulss xmm0, [ebp-0x54]
	movss [ebp-0x54], xmm0
	mulss xmm1, [ebp-0x50]
	movss [ebp-0x50], xmm1
	mov edx, 0x1
	movss xmm6, dword [_float__340282346638528859811704]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__390:
	lea eax, [edx*4]
	mov dword [ebp+eax-0x44], 0x7f7fffff
	mov dword [ebp+eax-0x2c], 0xffffffff
	mov dword [ebp+eax-0x50], 0xff7fffff
	mov dword [ebp+eax-0x24], 0xffffffff
	add edx, 0x1
	cmp edx, 0x3
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__390
	mov eax, [ebp+0xc]
	mov edi, [eax+0x1800]
	test edi, edi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400
	mov dword [ebp-0x2b4], 0x0
	movaps xmm5, xmm6
	mov dword [ebp-0x290], 0xffffffff
	mov dword [ebp-0x2b0], 0x0
	mov edx, [ebp-0x2b4]
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__410
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__430:
	mov edi, edx
	add edi, 0x1
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__510:
	mov ebx, [ebp+0xc]
	cmp [ebx+0x1800], edi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__420
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__520:
	mov [ebp-0x2b4], edi
	mov edx, edi
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__410:
	mov ecx, [ebp-0x28c]
	cmp [ebp+edx*4-0x288], ecx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__430
	mov edi, edx
	add edi, 0x1
	mov ebx, [ebp+0xc]
	cmp [ebx+0x1800], edi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__440
	lea ebx, [edi*4]
	mov ecx, edi
	mov esi, [ebp-0x2b4]
	lea eax, [esi+esi*2]
	shl eax, 0x4
	add eax, [ebp+0xc]
	mov [ebp-0x2ac], eax
	movss xmm3, dword [_float_0_01000000]
	lea eax, [edi+edi*2]
	shl eax, 0x4
	mov esi, [ebp+0xc]
	lea edx, [eax+esi]
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__450
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__470:
	add ecx, 0x1
	add edx, 0x30
	add ebx, 0x4
	mov esi, [ebp+0xc]
	cmp [esi+0x1800], ecx
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__460
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__450:
	lea esi, [ebp-0x288]
	add esi, ebx
	mov eax, [ebp-0x28c]
	cmp [esi], eax
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__470
	movss xmm0, dword [edx]
	mov eax, [ebp-0x2ac]
	subss xmm0, [eax]
	movss xmm1, dword [edx+0x4]
	subss xmm1, [eax+0x4]
	movss xmm2, dword [edx+0x8]
	subss xmm2, [eax+0x8]
	mulss xmm0, xmm0
	mulss xmm1, xmm1
	addss xmm0, xmm1
	mulss xmm2, xmm2
	addss xmm0, xmm2
	ucomiss xmm3, xmm0
	mov eax, 0xffffffff
	cmovbe eax, [ebp-0x28c]
	mov [esi], eax
	add ecx, 0x1
	add edx, 0x30
	add ebx, 0x4
	mov esi, [ebp+0xc]
	cmp [esi+0x1800], ecx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__450
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__460:
	add dword [ebp-0x2b0], 0x1
	mov edx, [ebp-0x2b4]
	lea eax, [edx+edx*2]
	shl eax, 0x4
	add esi, eax
	movss xmm4, dword [esi]
	movss xmm3, dword [esi+0x4]
	movss xmm2, dword [esi+0x8]
	xor ebx, ebx
	lea ecx, [ebp-0x64]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__500:
	movaps xmm1, xmm4
	mulss xmm1, [ecx]
	movaps xmm0, xmm3
	mulss xmm0, [ecx+0x4]
	addss xmm1, xmm0
	movaps xmm0, xmm2
	mulss xmm0, [ecx+0x8]
	addss xmm1, xmm0
	lea eax, [ebx*4]
	lea edx, [ebp-0x40]
	add edx, eax
	movss xmm0, dword [edx]
	ucomiss xmm0, xmm1
	jbe _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__480
	movss [edx], xmm1
	mov edx, [ebp-0x2b4]
	mov [ebp+eax-0x28], edx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__480:
	lea edx, [ebp-0x4c]
	add edx, eax
	ucomiss xmm1, [edx]
	jbe _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__490
	movss [edx], xmm1
	mov edx, [ebp-0x2b4]
	mov [ebp+eax-0x20], edx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__490:
	add ebx, 0x1
	add ecx, 0xc
	cmp ebx, 0x2
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__500
	movss xmm0, dword [esi+0x20]
	ucomiss xmm0, xmm5
	jbe _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__510
	mov ecx, [ebp-0x2b4]
	mov [ebp-0x290], ecx
	movaps xmm5, xmm0
	mov ebx, [ebp+0xc]
	cmp [ebx+0x1800], edi
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__520
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__420:
	mov esi, [ebp-0x2b0]
	test esi, esi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400
	mov esi, [ebp-0x28]
	mov [ebp-0x2bc], esi
	mov eax, [ebp+0x10]
	mov ebx, [eax+0x1800]
	lea ecx, [ebx+ebx*2]
	shl ecx, 0x4
	lea edx, [esi+esi*2]
	shl edx, 0x4
	mov esi, [ebp+0xc]
	mov eax, [esi+edx]
	mov esi, [ebp+0x10]
	mov [ecx+esi], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x4]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x4], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x8]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x8], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0xc]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0xc], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x10]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x10], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x14]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x14], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x18]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x18], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x1c]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x1c], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x20]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x20], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x24]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x24], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x28]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x28], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x2c]
	mov edx, [ebp+0x10]
	mov [ecx+edx+0x2c], eax
	lea eax, [ebx+0x1]
	mov [edx+0x1800], eax
	mov ecx, [ebp-0x24]
	mov [ebp-0x2b8], ecx
	cmp [ebp-0x2bc], ecx
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__530
	mov esi, ecx
	lea ecx, [eax+eax*2]
	shl ecx, 0x4
	lea edx, [esi+esi*2]
	shl edx, 0x4
	mov esi, [ebp+0xc]
	mov eax, [esi+edx]
	mov esi, [ebp+0x10]
	mov [ecx+esi], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x4]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x4], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x8]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x8], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0xc]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0xc], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x10]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x10], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x14]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x14], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x18]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x18], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x1c]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x1c], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x20]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x20], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x24]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x24], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x28]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x28], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x2c]
	mov edx, [ebp+0x10]
	mov [ecx+edx+0x2c], eax
	lea eax, [ebx+0x2]
	mov [edx+0x1800], eax
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__530:
	mov edi, [ebp-0x20]
	cmp [ebp-0x2b8], edi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__540
	cmp [ebp-0x2bc], edi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__540
	mov ecx, [ebp+0x10]
	mov ebx, [ecx+0x1800]
	lea ecx, [ebx+ebx*2]
	shl ecx, 0x4
	lea edx, [edi+edi*2]
	shl edx, 0x4
	mov esi, [ebp+0xc]
	mov eax, [esi+edx]
	mov esi, [ebp+0x10]
	mov [ecx+esi], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x4]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x4], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x8]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x8], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0xc]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0xc], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x10]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x10], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x14]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x14], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x18]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x18], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x1c]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x1c], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x20]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x20], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x24]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x24], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x28]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x28], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x2c]
	mov edx, [ebp+0x10]
	mov [ecx+edx+0x2c], eax
	add ebx, 0x1
	mov [edx+0x1800], ebx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__540:
	mov esi, [ebp-0x1c]
	cmp edi, esi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__550
	cmp [ebp-0x2b8], esi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__550
	cmp [ebp-0x2bc], esi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__550
	mov ecx, [ebp+0x10]
	mov ecx, [ecx+0x1800]
	mov [ebp-0x32c], ecx
	lea ecx, [ecx+ecx*2]
	shl ecx, 0x4
	lea edx, [esi+esi*2]
	shl edx, 0x4
	mov eax, [ebp+0xc]
	mov eax, [eax+edx]
	mov ebx, [ebp+0x10]
	mov [ecx+ebx], eax
	mov eax, [ebp+0xc]
	mov eax, [eax+edx+0x4]
	mov [ecx+ebx+0x4], eax
	mov ebx, [ebp+0xc]
	mov ebx, [ebx+edx+0x8]
	mov eax, [ebp+0x10]
	mov [ecx+eax+0x8], ebx
	mov ebx, [ebp+0xc]
	mov ebx, [ebx+edx+0xc]
	mov [ecx+eax+0xc], ebx
	mov eax, [ebp+0xc]
	mov eax, [eax+edx+0x10]
	mov ebx, [ebp+0x10]
	mov [ecx+ebx+0x10], eax
	mov eax, [ebp+0xc]
	mov eax, [eax+edx+0x14]
	mov [ecx+ebx+0x14], eax
	mov ebx, [ebp+0xc]
	mov ebx, [ebx+edx+0x18]
	mov eax, [ebp+0x10]
	mov [ecx+eax+0x18], ebx
	mov ebx, [ebp+0xc]
	mov ebx, [ebx+edx+0x1c]
	mov [ecx+eax+0x1c], ebx
	mov eax, [ebp+0xc]
	mov eax, [eax+edx+0x20]
	mov ebx, [ebp+0x10]
	mov [ecx+ebx+0x20], eax
	mov eax, [ebp+0xc]
	mov eax, [eax+edx+0x24]
	mov [ecx+ebx+0x24], eax
	mov ebx, [ebp+0xc]
	mov ebx, [ebx+edx+0x28]
	mov eax, [ebp+0x10]
	mov [ecx+eax+0x28], ebx
	mov ebx, [ebp+0xc]
	mov edx, [ebx+edx+0x2c]
	mov [ecx+eax+0x2c], edx
	mov ebx, [ebp-0x32c]
	add ebx, 0x1
	mov [eax+0x1800], ebx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__550:
	cmp [ebp-0x290], esi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400
	cmp [ebp-0x290], edi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400
	mov esi, [ebp-0x2b8]
	cmp [ebp-0x290], esi
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400
	mov eax, [ebp-0x2bc]
	cmp [ebp-0x290], eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400
	mov edx, [ebp+0x10]
	mov ebx, [edx+0x1800]
	lea ecx, [ebx+ebx*2]
	shl ecx, 0x4
	mov esi, [ebp-0x290]
	lea edx, [esi+esi*2]
	shl edx, 0x4
	mov esi, [ebp+0xc]
	mov eax, [esi+edx]
	mov esi, [ebp+0x10]
	mov [ecx+esi], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x4]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x4], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x8]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x8], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0xc]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0xc], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x10]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x10], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x14]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x14], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x18]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x18], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x1c]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x1c], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x20]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x20], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x24]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x24], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x28]
	mov esi, [ebp+0x10]
	mov [ecx+esi+0x28], eax
	mov esi, [ebp+0xc]
	mov eax, [esi+edx+0x2c]
	mov edx, [ebp+0x10]
	mov [ecx+edx+0x2c], eax
	add ebx, 0x1
	mov [edx+0x1800], ebx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__400:
	add dword [ebp-0x28c], 0x1
	add dword [ebp-0x2a8], 0xc
	cmp dword [ebp-0x28c], 0x3
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__560
	mov ecx, [ebp-0x2a8]
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__570
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__440:
	mov esi, ebx
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__460
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__360:
	movss xmm1, dword [_float_1_00000000]
	pxor xmm4, xmm4
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__580
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__560:
	add esp, 0x37c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__380:
	movss xmm7, dword [_float_1_00000000]
	divss xmm7, xmm1
	movaps xmm1, xmm7
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__590
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__370:
	movss xmm7, dword [_float_1_00000000]
	divss xmm7, xmm1
	movaps xmm1, xmm7
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__600
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__230:
	xor esi, esi
	lea ebx, [ebp-0x80]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__610:
	cvtss2sd xmm0, [ebx]
	movsd [esp+0x1c], xmm0
	cvtss2sd xmm0, [ebx-0x4]
	movsd [esp+0x14], xmm0
	cvtss2sd xmm0, [ebx-0x8]
	movsd [esp+0xc], xmm0
	mov [esp+0x8], esi
	mov dword [esp+0x4], _cstring_group_i_ng_g_g
	mov dword [esp], 0x0
	call _Z10Com_PrintfiPKcz
	add esi, 0x1
	add ebx, 0xc
	cmp esi, 0x3
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__610
	mov edx, [ebp+0xc]
	mov eax, [edx+0x1800]
	test eax, eax
	jz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__620
	xor ebx, ebx
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__630:
	lea eax, [ebx+ebx*2]
	shl eax, 0x4
	add eax, [ebp+0xc]
	cvtss2sd xmm0, [eax+0x20]
	movsd [esp+0x40], xmm0
	cvtss2sd xmm0, [eax+0x18]
	movsd [esp+0x38], xmm0
	cvtss2sd xmm0, [eax+0x14]
	movsd [esp+0x30], xmm0
	cvtss2sd xmm0, [eax+0x10]
	movsd [esp+0x28], xmm0
	cvtss2sd xmm0, [eax+0x8]
	movsd [esp+0x20], xmm0
	cvtss2sd xmm0, [eax+0x4]
	movsd [esp+0x18], xmm0
	cvtss2sd xmm0, [eax]
	movsd [esp+0x10], xmm0
	mov eax, [ebp+ebx*4-0x288]
	mov [esp+0xc], eax
	mov [esp+0x8], ebx
	mov dword [esp+0x4], _cstring_contact_i_gi_pg_
	mov dword [esp], 0x0
	call _Z10Com_PrintfiPKcz
	add ebx, 0x1
	mov ecx, [ebp+0xc]
	cmp [ecx+0x1800], ebx
	jnz _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__630
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__620
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__30:
	mov ebx, 0xffffffff
	mov eax, 0xffffffff
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__640
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__60:
	mov eax, 0xffffffff
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__650
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__20:
	mov [ebp-0x2a0], ecx
	mov dword [ebp-0x2c4], 0x0
	mov eax, ecx
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__660
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__670:
	mov eax, [ebp-0x2a0]
_Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__660:
	movss xmm1, dword [eax+0x20]
	mov edx, [ebp-0x2c4]
	lea ebx, [edx+edx*2]
	shl ebx, 0x4
	mov ecx, [ebp+0xc]
	lea esi, [ebx+ecx+0x10]
	add ebx, ecx
	mov eax, 0xbf800000
	mov [ebp-0x40], eax
	mov [ebp-0x3c], eax
	mov [ebp-0x38], eax
	mov eax, 0x3f800000
	mov [ebp-0x4c], eax
	mov [ebp-0x48], eax
	mov [ebp-0x44], eax
	mov dword [esp+0x18], 0x3
	mov dword [esp+0x14], 0x0
	mov edi, colorYellow
	mov [esp+0x10], edi
	mov dword [esp+0xc], 0x0
	lea eax, [ebp-0x4c]
	mov [esp+0x8], eax
	lea edx, [ebp-0x40]
	mov [esp+0x4], edx
	mov [esp], ebx
	movss [ebp-0x2e8], xmm1
	call _Z11CG_DebugBoxPKfS0_S0_fS0_ii
	movss xmm1, dword [ebp-0x2e8]
	mulss xmm1, [_float_10_00000000]
	movaps xmm0, xmm1
	mulss xmm0, [esi]
	addss xmm0, [ebx]
	movss [ebp-0x34], xmm0
	movaps xmm0, xmm1
	mulss xmm0, [esi+0x4]
	addss xmm0, [ebx+0x4]
	movss [ebp-0x30], xmm0
	mulss xmm1, [esi+0x8]
	addss xmm1, [ebx+0x8]
	movss [ebp-0x2c], xmm1
	mov dword [esp+0x10], 0x3
	mov dword [esp+0xc], 0x0
	mov [esp+0x8], edi
	lea ecx, [ebp-0x34]
	mov [esp+0x4], ecx
	mov [esp], ebx
	call _Z12CG_DebugLinePKfS0_S0_ii
	add dword [ebp-0x2c4], 0x1
	add dword [ebp-0x2a0], 0x30
	mov ebx, [ebp-0x2c4]
	mov esi, [ebp+0xc]
	cmp ebx, [esi+0x1800]
	jl _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__670
	mov ebx, esi
	jmp _Z19Phys_ReduceContactsP6dxBodyPK11ContactListPS1__680
	add [eax], al


;Phys_AddCollisionContact(PhysWorld, PhysContact const*, int, int)
_Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x186c
	mov ebx, [ebp+0xc]
	mov edi, [ebp+0x10]
	mov esi, [ebp+0x14]
	test edi, edi
	jnz _Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_10
	mov dword [ebp-0x1850], 0x0
_Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_40:
	test esi, esi
	jnz _Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_20
	mov dword [ebp-0x184c], 0x0
_Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_30:
	mov dword [ebp-0x44], 0x301c
	mov eax, phys_contact_cfm
	mov eax, [eax]
	mov eax, [eax+0xc]
	mov [ebp-0x2c], eax
	mov eax, phys_contact_erp
	mov eax, [eax]
	mov eax, [eax+0xc]
	mov [ebp-0x30], eax
	mov eax, [ebx+0x1c]
	mov [ebp-0x40], eax
	xor ecx, ecx
	mov [ebp-0x3c], ecx
	mov eax, [ebx+0x20]
	mov [ebp-0x38], eax
	mov dword [ebp-0x34], 0x3dcccccd
	mov dword [ebp-0x48], 0x1
	mov eax, [ebx+0x18]
	mov [ebp-0x1828], eax
	lea edx, [ebx+0xc]
	mov eax, [ebx+0xc]
	mov [ebp-0x1838], eax
	mov eax, [edx+0x4]
	mov [ebp-0x1834], eax
	mov eax, [edx+0x8]
	mov [ebp-0x1830], eax
	mov [ebp-0x182c], ecx
	mov eax, [ebx]
	mov [ebp-0x1848], eax
	mov eax, [ebx+0x4]
	mov [ebp-0x1844], eax
	mov eax, [ebx+0x8]
	mov [ebp-0x1840], eax
	mov [ebp-0x183c], ecx
	mov eax, [ebp-0x1850]
	mov [ebp-0x1824], eax
	mov eax, [ebp-0x184c]
	mov [ebp-0x1820], eax
	mov dword [ebp-0x181c], 0x0
	mov eax, [ebp+0x8]
	mov [esp+0x10], eax
	lea eax, [ebp-0x44]
	mov [esp+0xc], eax
	mov [esp+0x8], esi
	mov [esp+0x4], edi
	lea eax, [ebp-0x1848]
	mov [esp], eax
	call _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld
	add esp, 0x186c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_20:
	mov [esp], esi
	call ODE_BodyGetFirstGeom
	mov [ebp-0x184c], eax
	jmp _Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_30
_Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_10:
	mov [esp], edi
	call ODE_BodyGetFirstGeom
	mov [ebp-0x1850], eax
	jmp _Z24Phys_AddCollisionContact9PhysWorldPK11PhysContactii_40
	nop


;Phys_CreateJointForEachContact(ContactList*, dxBody*, dxBody*, dSurfaceParameters const*, PhysWorld)
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xfc
	mov eax, [ebp+0x8]
	mov ebx, [eax+0x1800]
	lea edx, [ebx-0x1]
	mov [ebp-0xb0], edx
	xor eax, eax
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_210:
	cmp eax, [ebp-0xb0]
	jge _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_10
	lea esi, [eax+0x1]
	cmp ebx, esi
	jle _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_20
	lea eax, [eax+eax*2]
	shl eax, 0x4
	mov edi, [ebp+0x8]
	lea ecx, [eax+edi+0x10]
	lea eax, [esi+esi*2]
	shl eax, 0x4
	lea eax, [eax+edi+0x10]
	movss xmm4, dword [ecx+0x4]
	movss xmm3, dword [ecx+0x8]
	movaps xmm2, xmm3
	mulss xmm2, [eax+0x8]
	movaps xmm1, xmm4
	mulss xmm1, [eax+0x4]
	movss xmm0, dword [eax]
	mulss xmm0, [ecx]
	addss xmm1, xmm0
	addss xmm2, xmm1
	movss xmm5, dword [_float__0_99000001]
	ucomiss xmm5, xmm2
	ja _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_30
	mov edx, esi
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_40:
	add edx, 0x1
	cmp edx, ebx
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_20
	lea eax, [edx+edx*2]
	shl eax, 0x4
	mov edi, [ebp+0x8]
	lea eax, [eax+edi+0x10]
	movaps xmm2, xmm3
	mulss xmm2, [eax+0x8]
	movaps xmm1, xmm4
	mulss xmm1, [eax+0x4]
	movss xmm0, dword [ecx]
	mulss xmm0, [eax]
	addss xmm1, xmm0
	addss xmm2, xmm1
	ucomiss xmm5, xmm2
	jbe _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_40
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_30:
	mov edx, [ebp+0xc]
	test edx, edx
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_50
	mov eax, [ebp+0xc]
	mov [esp], eax
	call dBodyGetData
	mov dword [eax+0x4c], 0x1
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_50:
	mov eax, [ebp+0x10]
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_10
	mov edx, [ebp+0x10]
	mov [esp], edx
	call dBodyGetData
	mov dword [eax+0x4c], 0x1
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_10:
	mov ecx, [ebp+0x18]
	lea eax, [ecx+ecx*2]
	mov edx, eax
	shl edx, 0x4
	add eax, edx
	shl eax, 0x2
	add eax, physGlob
	movzx eax, byte [eax+0x20]
	mov [ebp-0x7d], al
	mov ebx, [ebp+0xc]
	mov dword [ebp-0x84], 0x0
	lea edi, [ebp-0x68]
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_80:
	lea esi, [ebp-0x1a]
	add esi, [ebp-0x84]
	mov byte [esi], 0x0
	test ebx, ebx
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_60
	mov [esp], ebx
	call dBodyGetData
	cmp dword [eax+0x4c], 0x1
	setz byte [esi]
	cmp byte [ebp-0x7d], 0x0
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_70
	lea edx, [eax+0x50]
	mov eax, [eax+0x50]
	mov [edi], eax
	mov eax, [edx+0x4]
	mov [edi+0x4], eax
	mov eax, [edx+0x8]
	mov [edi+0x8], eax
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_60:
	add dword [ebp-0x84], 0x1
	add edi, 0xc
	mov ebx, [ebp+0x10]
	cmp dword [ebp-0x84], 0x2
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_80
	movzx eax, byte [ebp-0x1a]
	mov [ebp-0x8a], al
	test al, al
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_90
	cmp byte [ebp-0x19], 0x0
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_100
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_290:
	mov edx, [ebp+0x8]
	mov eax, [edx+0x1800]
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_110
	movzx ecx, byte [ebp-0x19]
	mov [ebp-0x89], cl
	mov dword [ebp-0x88], 0x0
	mov edi, [ebp+0x18]
	lea eax, [edi+edi*2]
	mov ebx, edx
	mov edx, eax
	shl edx, 0x4
	add eax, edx
	shl eax, 0x2
	mov [ebp-0x90], eax
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_120
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_190:
	cmp byte [ebp-0x89], 0x0
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_130
	mov eax, [ebp+0xc]
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_140
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_220:
	mov eax, [ebp+0x10]
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_140
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_230:
	mov esi, physGlob
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_240:
	cmp byte [esi+0xbaa8], 0x0
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_150
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_280:
	mov eax, phys_noIslands
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_160
	mov edi, [ebp+0xc]
	test edi, edi
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_160
	mov ecx, [ebp+0x10]
	test ecx, ecx
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_160
	mov [esp+0xc], ebx
	mov edi, [ebp+0x14]
	mov [esp+0x8], edi
	mov edx, [ebp+0x18]
	mov eax, [esi+edx*4+0x27c]
	mov [esp+0x4], eax
	mov eax, [esi+edx*4]
	mov [esp], eax
	call _Z19dJointCreateContactP7dxWorldP12dxJointGroupPK18dSurfaceParametersPK12dContactGeom
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_170
	mov dword [esp+0x8], 0x0
	mov ecx, [ebp+0xc]
	mov [esp+0x4], ecx
	mov [esp], eax
	call dJointAttach
	mov [esp+0xc], ebx
	mov edi, [ebp+0x14]
	mov [esp+0x8], edi
	mov edx, [ebp+0x18]
	mov eax, [esi+edx*4+0x27c]
	mov [esp+0x4], eax
	mov eax, [esi+edx*4]
	mov [esp], eax
	call _Z19dJointCreateContactP7dxWorldP12dxJointGroupPK18dSurfaceParametersPK12dContactGeom
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_170
	mov ecx, [ebp+0x10]
	mov [esp+0x8], ecx
	mov dword [esp+0x4], 0x0
	mov [esp], eax
	call dJointAttach
	mov eax, phys_drawcontacts
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_180
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_200:
	add dword [ebp-0x88], 0x1
	add ebx, 0x30
	mov edx, [ebp-0x88]
	mov eax, [ebp+0x8]
	cmp edx, [eax+0x1800]
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_110
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_120:
	cmp byte [ebp-0x8a], 0x0
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_190
	lea eax, [ebp-0x50]
	mov [esp+0x10], eax
	mov eax, [ebx+0x8]
	mov [esp+0xc], eax
	mov eax, [ebx+0x4]
	mov [esp+0x8], eax
	mov eax, [ebx]
	mov [esp+0x4], eax
	mov edx, [ebp+0xc]
	mov [esp], edx
	call dBodyGetPointVel
	lea ecx, [ebp-0x50]
	mov [esp], ecx
	call dNormalize3
	movss xmm1, dword [ebp-0x50]
	mulss xmm1, [ebx+0x10]
	movss xmm0, dword [ebp-0x4c]
	mulss xmm0, [ebx+0x14]
	addss xmm1, xmm0
	movss xmm0, dword [ebp-0x48]
	mulss xmm0, [ebx+0x18]
	addss xmm1, xmm0
	ucomiss xmm1, [_float_0_010000001]
	jbe _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_190
	add dword [ebp-0x88], 0x1
	add ebx, 0x30
	mov edx, [ebp-0x88]
	mov eax, [ebp+0x8]
	cmp edx, [eax+0x1800]
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_120
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_110:
	add esp, 0xfc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_160:
	mov [esp+0xc], ebx
	mov edi, [ebp+0x14]
	mov [esp+0x8], edi
	mov eax, physGlob
	mov ecx, [ebp+0x18]
	mov edx, [eax+ecx*4+0x27c]
	mov [esp+0x4], edx
	mov eax, [eax+ecx*4]
	mov [esp], eax
	call _Z19dJointCreateContactP7dxWorldP12dxJointGroupPK18dSurfaceParametersPK12dContactGeom
	test eax, eax
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_170
	mov edi, [ebp+0x10]
	mov [esp+0x8], edi
	mov edx, [ebp+0xc]
	mov [esp+0x4], edx
	mov [esp], eax
	call dJointAttach
	mov eax, phys_drawcontacts
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_200
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_180:
	movss xmm1, dword [ebx+0x20]
	mov eax, 0xbf800000
	mov [ebp-0x28], eax
	mov [ebp-0x24], eax
	mov [ebp-0x20], eax
	mov eax, 0x3f800000
	mov [ebp-0x34], eax
	mov [ebp-0x30], eax
	mov [ebp-0x2c], eax
	mov dword [esp+0x18], 0x3
	mov dword [esp+0x14], 0x0
	mov ecx, colorRed
	mov [esp+0x10], ecx
	mov dword [esp+0xc], 0x0
	lea eax, [ebp-0x34]
	mov [esp+0x8], eax
	lea eax, [ebp-0x28]
	mov [esp+0x4], eax
	mov [esp], ebx
	movss [ebp-0xa8], xmm1
	call _Z11CG_DebugBoxPKfS0_S0_fS0_ii
	movss xmm1, dword [ebp-0xa8]
	mulss xmm1, [_float_10_00000000]
	movaps xmm0, xmm1
	mulss xmm0, [ebx+0x10]
	addss xmm0, [ebx]
	movss [ebp-0x40], xmm0
	movaps xmm0, xmm1
	mulss xmm0, [ebx+0x14]
	addss xmm0, [ebx+0x4]
	movss [ebp-0x3c], xmm0
	mulss xmm1, [ebx+0x18]
	addss xmm1, [ebx+0x8]
	movss [ebp-0x38], xmm1
	mov dword [esp+0x10], 0x3
	mov dword [esp+0xc], 0x0
	mov edi, colorRed
	mov [esp+0x8], edi
	lea eax, [ebp-0x40]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z12CG_DebugLinePKfS0_S0_ii
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_200
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_20:
	mov eax, esi
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_210
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_130:
	lea edi, [ebp-0x50]
	mov [esp+0x10], edi
	mov eax, [ebx+0x8]
	mov [esp+0xc], eax
	mov eax, [ebx+0x4]
	mov [esp+0x8], eax
	mov eax, [ebx]
	mov [esp+0x4], eax
	mov eax, [ebp+0x10]
	mov [esp], eax
	call dBodyGetPointVel
	mov [esp], edi
	call dNormalize3
	movss xmm1, dword [ebp-0x50]
	mulss xmm1, [ebx+0x10]
	movss xmm0, dword [ebp-0x4c]
	mulss xmm0, [ebx+0x14]
	addss xmm1, xmm0
	movss xmm0, dword [ebp-0x48]
	mulss xmm0, [ebx+0x18]
	addss xmm1, xmm0
	ucomiss xmm1, [_float_0_010000001]
	ja _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_200
	mov eax, [ebp+0xc]
	test eax, eax
	jnz _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_220
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_140:
	movss xmm0, dword [_float_0_69999999]
	ucomiss xmm0, [ebx+0x18]
	ja _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_230
	mov eax, [ebp+0xc]
	test eax, eax
	mov ecx, [ebp+0xc]
	cmovz ecx, [ebp+0x10]
	mov [ebp-0x6c], ecx
	mov esi, physGlob
	mov eax, [ebp-0x90]
	lea edi, [eax+esi+0xc]
	mov eax, phys_jitterMaxMass
	mov eax, [eax]
	movss xmm1, dword [eax+0xc]
	movss xmm3, dword [ecx+0x20]
	movaps xmm0, xmm1
	subss xmm0, xmm3
	pxor xmm4, xmm4
	movaps xmm2, xmm4
	cmpss xmm2, xmm0, 0x2
	movaps xmm0, xmm2
	movaps xmm2, xmm3
	andps xmm2, xmm0
	movaps xmm3, xmm0
	andnps xmm3, xmm1
	orps xmm3, xmm2
	movaps xmm0, xmm3
	divss xmm0, xmm1
	movaps xmm1, xmm0
	mulss xmm1, xmm0
	mulss xmm0, xmm1
	movss xmm5, dword [_float_1_00000000]
	subss xmm5, xmm0
	mulss xmm3, xmm5
	movss [ebp-0x70], xmm3
	mov eax, g_phys_msecStep
	mov edx, [ebp+0x18]
	cvtsi2ss xmm0, dword [eax+edx*4]
	movss xmm1, dword [_float_1000_00000000]
	divss xmm1, xmm0
	movss [ebp-0x74], xmm1
	mov eax, [edi+0x10]
	test eax, eax
	jle _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_240
	xor esi, esi
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_250
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_260:
	add esi, 0x1
	cmp esi, [edi+0x10]
	jge _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_230
	pxor xmm4, xmm4
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_250:
	lea eax, [esi+esi*8]
	lea eax, [edi+eax*4+0x10]
	lea edx, [eax+0x8]
	movss xmm1, dword [ebx]
	subss xmm1, [eax+0x8]
	movss xmm0, dword [ebx+0x4]
	subss xmm0, [edx+0x4]
	mulss xmm1, xmm1
	mulss xmm0, xmm0
	addss xmm1, xmm0
	addss xmm1, xmm4
	ucomiss xmm1, [edx+0x10]
	jae _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_260
	sqrtss xmm3, xmm1
	movss xmm2, dword [edx+0x18]
	movss xmm1, dword [edx+0x14]
	movaps xmm0, xmm2
	subss xmm0, xmm1
	movss xmm4, dword [_float_1_00000000]
	movaps xmm5, xmm4
	divss xmm5, xmm0
	ucomiss xmm3, xmm1
	ja _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_270
	movaps xmm1, xmm4
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_300:
	movss xmm0, dword [edx+0x1c]
	movss [ebp-0x7c], xmm0
	movss xmm2, dword [edx+0x20]
	subss xmm2, xmm0
	movss [ebp-0x78], xmm2
	movss [ebp-0xa8], xmm1
	call _Z7randomfv
	fstp dword [ebp-0xac]
	movss xmm0, dword [ebp-0xac]
	mulss xmm0, [ebp-0x78]
	addss xmm0, [ebp-0x7c]
	movss xmm1, dword [ebp-0xa8]
	mulss xmm0, xmm1
	mulss xmm0, [ebp-0x70]
	mulss xmm0, [ebp-0x74]
	movaps xmm1, xmm0
	mulss xmm1, [_float_0_00000000]
	movss [ebp-0x28], xmm1
	movss [ebp-0x24], xmm1
	movss [ebp-0x20], xmm0
	lea eax, [ebp-0x28]
	mov [esp+0xc], eax
	mov [esp+0x8], ebx
	mov eax, [ebp-0x6c]
	mov [esp+0x4], eax
	mov edx, [ebp+0x18]
	mov [esp], edx
	call _Z16Phys_ObjAddForce9PhysWorldiPKfS1_
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_260
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_150:
	cvtss2sd xmm0, [ebx+0x20]
	movsd [esp+0x3c], xmm0
	cvtss2sd xmm0, [ebx+0x18]
	movsd [esp+0x34], xmm0
	cvtss2sd xmm0, [ebx+0x14]
	movsd [esp+0x2c], xmm0
	cvtss2sd xmm0, [ebx+0x10]
	movsd [esp+0x24], xmm0
	cvtss2sd xmm0, [ebx+0x8]
	movsd [esp+0x1c], xmm0
	cvtss2sd xmm0, [ebx+0x4]
	movsd [esp+0x14], xmm0
	cvtss2sd xmm0, [ebx]
	movsd [esp+0xc], xmm0
	mov ecx, [ebp-0x88]
	mov [esp+0x8], ecx
	mov dword [esp+0x4], _cstring_contact_i_pg_g_g
	mov dword [esp], 0x0
	call _Z10Com_PrintfiPKcz
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_280
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_100:
	lea eax, [ebp-0x5c]
	mov edx, [ebp+0x8]
	call _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_290
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_270:
	movaps xmm1, xmm2
	subss xmm1, xmm3
	mulss xmm1, xmm5
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_300
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_70:
	mov [esp], ebx
	call dBodyGetPosition
	mov edx, [eax]
	mov [edi], edx
	mov edx, [eax+0x4]
	mov [edi+0x4], edx
	mov eax, [eax+0x8]
	mov [edi+0x8], eax
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_60
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_90:
	lea eax, [ebp-0x68]
	mov edx, [ebp+0x8]
	call _Z33Phys_RemoveOpposingNormalContactsPKfP11ContactList
	jmp _Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_290
_Z30Phys_CreateJointForEachContactP11ContactListP6dxBodyS2_PK18dSurfaceParameters9PhysWorld_170:
	mov dword [esp+0x4], _cstring_maximum_number_o
	mov dword [esp], 0x15
	call _Z16Com_PrintWarningiPKcz
	add esp, 0xfc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;Initialized global or static variables of phys_contacts:
SECTION .data


;Initialized constant data of phys_contacts:
SECTION .rdata


;Zero initialized global or static variables of phys_contacts:
SECTION .bss


;All cstrings:
SECTION .rdata
_cstring_group_i_merged_i:		db "Group %i merged into %i.",0ah,0
_cstring_group_i_ng_g_g:		db "Group %i: N:%g %g %g",0ah,0
_cstring_contact_i_gi_pg_:		db "Contact %i: G:%i, P:(%g %g %g), N:(%g %g %g), D:%g",0ah,0
_cstring_contact_i_pg_g_g:		db "Contact %i: P:(%g %g %g), N:(%g %g %g), D:%g",0ah,0
_cstring_maximum_number_o:		db "Maximum number of ODE physics contact points exceeded.",0ah,0



;All constant floats and doubles:
SECTION .rdata
_float__0_99000001:		dd 0xbf7d70a4	; -0.99
_float_3402823466385288598117041:		dd 0x7f7fffff	; 3.40282e+38
_float_1_00000000:		dd 0x3f800000	; 1
_float__340282346638528859811704:		dd 0xff7fffff	; -3.40282e+38
_float_0_99900001:		dd 0x3f7fbe77	; 0.999
_float_0_50000000:		dd 0x3f000000	; 0.5
_float_0_01000000:		dd 0x3c23d70b	; 0.01
_float_10_00000000:		dd 0x41200000	; 10
_float_0_010000001:		dd 0x3c23d70a	; 0.01
_float_0_69999999:		dd 0x3f333333	; 0.7
_float_1000_00000000:		dd 0x447a0000	; 1000
_float_0_00000000:		dd 0x0	; 0

alignb 16
_data16_80000000:		dd 0x80000000, 0x0, 0x0, 0x0	; OWORD
_data16_7fffffff:		dd 0x7fffffff, 0x0, 0x0, 0x0	; OWORD
