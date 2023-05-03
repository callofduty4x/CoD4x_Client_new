;Imports of win_shared:

;Exports of win_shared:
	global _Z14Sys_SnapVectorPf


SECTION .text


;Sys_SnapVector(float*)
_Z14Sys_SnapVectorPf:
	push ebp
	mov ebp, esp
	mov edx, [ebp+0x8]
	cvttss2si eax, [edx]
	cvtsi2ss xmm0, eax
	movss [edx], xmm0
	cvttss2si eax, [edx+0x4]
	cvtsi2ss xmm0, eax
	movss [edx+0x4], xmm0
	cvttss2si eax, [edx+0x8]
	cvtsi2ss xmm0, eax
	movss [edx+0x8], xmm0
	pop ebp
	ret


;Initialized global or static variables of win_shared:
SECTION .data


;Initialized constant data of win_shared:
SECTION .rdata


;Zero initialized global or static variables of win_shared:
SECTION .bss


;All cstrings:
SECTION .rdata



;All constant floats and doubles:
SECTION .rdata

