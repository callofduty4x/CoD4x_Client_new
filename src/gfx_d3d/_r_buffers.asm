;Imports of r_buffers:
	extern Z_VirtualAllocInternal
	extern Z_VirtualFreeInternal
	extern _Z7ms_randv
	extern _Z25R_AllocStaticVertexBufferPP22IDirect3DVertexBuffer9iPKc
	extern _Z25R_FinishStaticIndexBufferP21IDirect3DIndexBuffer9
	extern _Z26R_FinishStaticVertexBufferP22IDirect3DVertexBuffer9
	extern _Z24R_AllocStaticIndexBufferPP21IDirect3DIndexBuffer9iPKc

;Exports of r_buffers:
	global _Z20R_InitDynamicIndicesP17GfxDynamicIndicesi
	global _Z24R_ShutdownDynamicIndicesP17GfxDynamicIndices
	global _Z27R_CreateParticleCloudBufferv
	global gfxBuf


SECTION .text



;R_InitDynamicIndices(GfxDynamicIndices*, int)
_Z20R_InitDynamicIndicesP17GfxDynamicIndicesi:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov eax, [ebp+0xc]
	mov dword [ebx], 0x0
	mov [ebx+0x4], eax
	add eax, eax
	mov [esp], eax
	call Z_VirtualAllocInternal
	mov [ebx+0x8], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
	nop


;R_ShutdownDynamicIndices(GfxDynamicIndices*)
_Z24R_ShutdownDynamicIndicesP17GfxDynamicIndices:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov eax, [ebx+0x8]
	mov [esp], eax
	call Z_VirtualFreeInternal
	mov dword [ebx+0x8], 0x0
	add esp, 0x14
	pop ebx
	pop ebp
	ret


;R_CreateParticleCloudBuffer()
_Z27R_CreateParticleCloudBufferv:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x8c
	mov dword [esp+0x8], _cstring_particle_cloud_v
	mov dword [esp+0x4], 0x14000
	mov dword [esp], gfxBuf+0x74
	call _Z25R_AllocStaticVertexBufferPP22IDirect3DVertexBuffer9iPKc
	mov ebx, eax
	mov dword [esp+0x8], _cstring_particle_cloud_i
	mov dword [esp+0x4], 0x3000
	mov dword [esp], gfxBuf+0x78
	call _Z24R_AllocStaticIndexBufferPP21IDirect3DIndexBuffer9iPKc
	mov [ebp-0x30], eax
	mov [ebp-0x2c], ebx
	mov dword [ebp-0x54], 0x0
_Z27R_CreateParticleCloudBufferv_80:
	cvtsi2ss xmm0, dword [ebp-0x54]
	movss [ebp-0x48], xmm0
	movzx eax, word [ebp-0x54]
	shl eax, 0x7
	mov [ebp-0x3a], ax
	mov eax, [ebp-0x2c]
	mov [ebp-0x38], eax
	mov eax, [ebp-0x30]
	mov [ebp-0x34], eax
	mov dword [ebp-0x50], 0x0
_Z27R_CreateParticleCloudBufferv_70:
	cvtsi2ss xmm0, dword [ebp-0x50]
	movss [ebp-0x44], xmm0
	mov [ebp-0x40], eax
	mov edi, [ebp-0x38]
	mov dword [ebp-0x4c], 0x0
	mov esi, eax
_Z27R_CreateParticleCloudBufferv_50:
	mov ebx, edi
	call _Z7ms_randv
	cvtsi2ss xmm3, eax
	divss xmm3, dword [_float_32767_00000000]
	addss xmm3, [ebp-0x48]
	mulss xmm3, [_float_0_25000000]
	subss xmm3, [_float_1_00000000]
	movss [ebp-0x78], xmm3
	call _Z7ms_randv
	cvtsi2ss xmm2, eax
	divss xmm2, dword [_float_32767_00000000]
	addss xmm2, [ebp-0x44]
	mulss xmm2, [_float_0_25000000]
	subss xmm2, [_float_1_00000000]
	movss [ebp-0x68], xmm2
	call _Z7ms_randv
	cvtsi2ss xmm1, eax
	divss xmm1, dword [_float_32767_00000000]
	cvtsi2ss xmm0, dword [ebp-0x4c]
	addss xmm1, xmm0
	mulss xmm1, [_float_0_12500000]
	subss xmm1, [_float_1_00000000]
	xor ecx, ecx
	xor edx, edx
	movss xmm3, dword [ebp-0x78]
	movss xmm2, dword [ebp-0x68]
_Z27R_CreateParticleCloudBufferv_20:
	movss [ebx], xmm3
	movss [ebx+0x4], xmm2
	movss [ebx+0x8], xmm1
	mov eax, [edx+cornerTexCoords]
	mov [ebx+0xc], eax
	mov eax, [edx+cornerTexCoords+0x4]
	mov [ebx+0x10], eax
	add ebx, 0x14
	add ecx, 0x1
	add edx, 0x8
	cmp ecx, 0x4
	jnz _Z27R_CreateParticleCloudBufferv_20
	movzx eax, word [ebp-0x3a]
	add ax, [ebp-0x4c]
	lea ecx, [eax*4]
	mov edx, quadIndices
_Z27R_CreateParticleCloudBufferv_30:
	mov eax, ecx
	add ax, [edx]
	mov [esi], ax
	add esi, 0x2
	add edx, 0x2
	cmp edx, quadIndices + 12
	jnz _Z27R_CreateParticleCloudBufferv_30
	add dword [ebp-0x4c], 0x1
	add dword [ebp-0x40], 0xc
	add edi, 0x50
	cmp dword [ebp-0x4c], 0x10
	jz _Z27R_CreateParticleCloudBufferv_40
	mov esi, [ebp-0x40]
	jmp _Z27R_CreateParticleCloudBufferv_50
_Z27R_CreateParticleCloudBufferv_40:
	add dword [ebp-0x50], 0x1
	add word [ebp-0x3a], 0x10
	add dword [ebp-0x38], 0x500
	add dword [ebp-0x34], 0xc0
	cmp dword [ebp-0x50], 0x8
	jz _Z27R_CreateParticleCloudBufferv_60
	mov eax, [ebp-0x34]
	jmp _Z27R_CreateParticleCloudBufferv_70
_Z27R_CreateParticleCloudBufferv_60:
	add dword [ebp-0x54], 0x1
	add dword [ebp-0x30], 0x600
	add dword [ebp-0x2c], 0x2800
	cmp dword [ebp-0x54], 0x8
	jnz _Z27R_CreateParticleCloudBufferv_80
	mov eax, [gfxBuf+0x78]
	mov [esp], eax
	call _Z25R_FinishStaticIndexBufferP21IDirect3DIndexBuffer9
	mov eax, [gfxBuf+0x74]
	mov [esp], eax
	call _Z26R_FinishStaticVertexBufferP22IDirect3DVertexBuffer9
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;Initialized global or static variables of r_buffers:
SECTION .data


;Initialized constant data of r_buffers:
SECTION .rdata
quadIndices: dd 0x10000, 0x20002, 0x30001, 0x0, 0x0, 0x0, 0x0, 0x0
cornerTexCoords: dd 0x0, 0x0, 0x0, 0x3f800000, 0x3f800000, 0x0, 0x3f800000, 0x3f800000, 0x80000000, 0x0, 0x0, 0x0


;Zero initialized global or static variables of r_buffers:
SECTION .bss
gfxBuf: resb 0x2400e0


;All cstrings:
SECTION .rdata
_cstring_particle_cloud_v:		db "Particle Cloud Verts",0
_cstring_particle_cloud_i:		db "Particle Cloud Indices",0


;All constant floats and doubles:
SECTION .rdata
_float_32767_00000000:		dd 0x46fffe00	; 32767
_float_0_25000000:		dd 0x3e800000	; 0.25
_float_1_00000000:		dd 0x3f800000	; 1
_float_0_12500000:		dd 0x3e000000	; 0.125

