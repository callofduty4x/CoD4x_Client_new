global X86_Benchmark

SECTION .text

;int64_t X86_Benchmark()
X86_Benchmark:

%define x -8
%define y -12
%define z -16
%define k -20
%define holdrand -36
%define a -24
%define b -28
%define c -32
%define initialX -36
%define initialY -40
%define initialtickcount -48
%define finaltickcount -56

                push    ebp
                mov     ebp, esp
                
                movss   xmm0, dword [_float_0_25]
                movss   [ebp+initialX], xmm0
                movss   xmm0, dword [_float_0_75]
                movss   [ebp+initialY], xmm0
                movss   xmm0, dword [_float_2_6]
                movss   [ebp+k], xmm0

                rdtsc
                mov     dword [ebp+initialtickcount], eax
                mov     dword [ebp+initialtickcount+4], edx
                mov     dword [ebp+holdrand], 0
                fld     dword [ebp+initialX]
                fstp    dword [ebp+x]
                fld     dword [ebp+initialY]
                fstp    dword [ebp+y]
                xor     ecx, ecx
                jmp     short do_inner_loop
update_inner_loop:                      
                                        
                inc     ecx
                cmp     ecx, 3E8h
                jnb     end_inner_loop

do_inner_loop:                             
                fld1
                fsub    dword   [ebp+x]
                fmul    dword   [ebp+x]
                fmul    dword   [ebp+k]
                fadd    dword   [ebp+x]
                fstp    dword   [ebp+x]
                fld1
                fsub    dword   [ebp+y]
                fmul    dword   [ebp+y]
                fmul    dword   [ebp+k]
                fadd    dword   [ebp+y]
                fstp    dword   [ebp+y]
                fld     dword   [ebp+y]
                fdiv    dword   [ebp+x]
                fstp    dword   [ebp+z]
                fld1
                fsub    dword   [ebp+x]
                fmul    dword   [ebp+x]
                fmul    dword   [ebp+k]
                fadd    dword   [ebp+x]
                fstp    dword   [ebp+x]
                fld1
                fsub    dword   [ebp+y]
                fmul    dword   [ebp+y]
                fmul    dword   [ebp+k]
                fadd    dword   [ebp+y]
                fstp    dword   [ebp+y]
                test    ecx, 1
                jz      short update_inner_loop
                mov     eax, [ebp+holdrand]
                mov     edx, 343FDh
                imul    edx
                add     eax, 269EC3h
                mov     [ebp+holdrand], eax
                shr     eax, 11h
                mov     [ebp+a], edx
                mov     eax, [ebp+holdrand]
                mov     edx, 343FDh
                imul    edx
                add     eax, 269EC3h
                mov     [ebp+holdrand], eax
                mov     [ebp+b], edx
                mov     eax, [ebp+holdrand]
                mov     edx, 343FDh
                imul    edx
                add     eax, 269EC3h
                mov     [ebp+holdrand], eax
                mov     [ebp+c], edx
                jmp     update_inner_loop
end_inner_loop: 
                rdtsc
                mov     dword [ebp+finaltickcount], eax
                mov     dword [ebp+finaltickcount+4], edx
                mov     ecx, dword [ebp+finaltickcount]
                sub     ecx, dword [ebp+initialtickcount]
                mov     eax, dword [ebp+finaltickcount+4]
                sbb     eax, dword [ebp+initialtickcount+4]

                mov     edx, eax
                mov     eax, ecx

                pop     ebp
                ret


;All constant floats and doubles:
SECTION .rdata
_float_0_25:		dd 0x3e800000
_float_0_75:		dd 0x3f400000
_float_2_6:		    dd 0x40266666