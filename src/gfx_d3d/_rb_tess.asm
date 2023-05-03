;Imports of rb_tess:
	extern _Z18XSurfaceGetNumTrisPK8XSurface
	extern _Z19XSurfaceGetNumVertsPK8XSurface
	extern _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	extern gfxBuf
	extern _Z15R_SetVertexDataP14GfxCmdBufStatePKvii
	extern _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	extern _Z24DB_GetIndexBufferAndBasehPvS_Pi
	extern _Z22R_OpenGL_SetBufferHintj
	extern _Z25R_OpenGL_ClearBufferHintsv
	extern _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	extern _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	extern _Z18R_UpdateVertexDeclP14GfxCmdBufState
	extern _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	extern _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	extern _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
	extern _Z25R_SetStreamsForBspSurfaceP18GfxCmdBufPrimStatePK14srfTriangles_t
	extern _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	extern rgp
	extern _Z13R_SetLightmap16GfxCmdBufContextj
	extern _Z20R_SetReflectionProbe16GfxCmdBufContextj
	extern sc_enable
	extern gfxRenderTargets
	extern rg
	extern _Z15R_SetMeshStreamP14GfxCmdBufStateP11GfxMeshData
	extern _Z39R_SetStaticModelLightingCoordsForSourcejP20GfxCmdBufSourceState
	extern _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	extern _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo
	extern _Z21R_DrawBspDrawSurfsLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo
	extern _Z24VecNCompareCustomEpsilonPKfS0_fi
	extern _Z19Vec3RotateTransposePKfPA3_S_Pf
	extern _Z25R_DrawBspDrawSurfsPreTessPKj16GfxCmdBufContext
	extern _Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext
	extern _Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext
	extern _Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext
	extern _Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext
	extern s_manualObjectPlacement
	extern _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	extern _Z24R_DrawXModelRigidSurfLitPK11GfxDrawSurfj16GfxCmdBufContextS2_PK19GfxDrawSurfListInfo
	extern _Z27R_DrawXModelRigidSurfCameraPK11GfxDrawSurfj16GfxCmdBufContextPK19GfxDrawSurfListInfo
	extern _Z21R_DrawXModelRigidSurfPK11GfxDrawSurfj16GfxCmdBufContextPK19GfxDrawSurfListInfo
	extern _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	extern _Z21R_DrawStaticModelSurfPKj16GfxCmdBufContextPK19GfxDrawSurfListInfo
	extern strstr
	extern _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext
	extern _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext
	extern _Z27R_DrawXModelSkinnedUncached16GfxCmdBufContextP8XSurfaceP15GfxPackedVertex
	extern _Z25R_DrawXModelSkinnedCached16GfxCmdBufContextPK22GfxModelSkinnedSurface


;Exports of rb_tess:
	global _GLOBAL__I__Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	global _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext


SECTION .text


;global constructors keyed to R_TessCodeMeshList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_GLOBAL__I__Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	mov edx, 0xffff
	mov eax, 0x1
	pop ebp
	jmp _Z41__static_initialization_and_destruction_0ii


;__static_initialization_and_destruction_0(int, int)
_Z41__static_initialization_and_destruction_0ii:
	push ebp
	mov ebp, esp
	cmp edx, 0xffff
	jz _Z41__static_initialization_and_destruction_0ii_10
_Z41__static_initialization_and_destruction_0ii_20:
	pop ebp
	ret
_Z41__static_initialization_and_destruction_0ii_10:
	sub eax, 0x1
	jnz _Z41__static_initialization_and_destruction_0ii_20
	mov eax, [g_fltMin__uint4]
	mov [g_fltMin], eax
	mov eax, [g_fltMin__uint4+0x4]
	mov [g_fltMin+0x4], eax
	mov eax, [g_fltMin__uint4+0x8]
	mov [g_fltMin+0x8], eax
	mov eax, [g_fltMin__uint4+0xc]
	mov [g_fltMin+0xc], eax
	mov eax, [g_negativeZero__uint4]
	mov [g_negativeZero], eax
	mov eax, [g_negativeZero__uint4+0x4]
	mov [g_negativeZero+0x4], eax
	mov eax, [g_negativeZero__uint4+0x8]
	mov [g_negativeZero+0x8], eax
	mov eax, [g_negativeZero__uint4+0xc]
	mov [g_negativeZero+0xc], eax
	mov eax, [g_inc__uint4]
	mov [g_inc], eax
	mov eax, [g_inc__uint4+0x4]
	mov [g_inc+0x4], eax
	mov eax, [g_inc__uint4+0x8]
	mov [g_inc+0x8], eax
	mov eax, [g_inc__uint4+0xc]
	mov [g_inc+0xc], eax
	mov eax, [g_swizzleXYZW__uint4]
	mov [g_swizzleXYZW], eax
	mov eax, [g_swizzleXYZW__uint4+0x4]
	mov [g_swizzleXYZW+0x4], eax
	mov eax, [g_swizzleXYZW__uint4+0x8]
	mov [g_swizzleXYZW+0x8], eax
	mov eax, [g_swizzleXYZW__uint4+0xc]
	mov [g_swizzleXYZW+0xc], eax
	mov eax, [g_swizzleYXZW__uint4]
	mov [g_swizzleYXZW], eax
	mov eax, [g_swizzleYXZW__uint4+0x4]
	mov [g_swizzleYXZW+0x4], eax
	mov eax, [g_swizzleYXZW__uint4+0x8]
	mov [g_swizzleYXZW+0x8], eax
	mov eax, [g_swizzleYXZW__uint4+0xc]
	mov [g_swizzleYXZW+0xc], eax
	mov eax, [g_swizzleXZYW__uint4]
	mov [g_swizzleXZYW], eax
	mov eax, [g_swizzleXZYW__uint4+0x4]
	mov [g_swizzleXZYW+0x4], eax
	mov eax, [g_swizzleXZYW__uint4+0x8]
	mov [g_swizzleXZYW+0x8], eax
	mov eax, [g_swizzleXZYW__uint4+0xc]
	mov [g_swizzleXZYW+0xc], eax
	mov eax, [g_swizzleYXWZ__uint4]
	mov [g_swizzleYXWZ], eax
	mov eax, [g_swizzleYXWZ__uint4+0x4]
	mov [g_swizzleYXWZ+0x4], eax
	mov eax, [g_swizzleYXWZ__uint4+0x8]
	mov [g_swizzleYXWZ+0x8], eax
	mov eax, [g_swizzleYXWZ__uint4+0xc]
	mov [g_swizzleYXWZ+0xc], eax
	mov eax, [g_swizzleXAZC__uint4]
	mov [g_swizzleXAZC], eax
	mov eax, [g_swizzleXAZC__uint4+0x4]
	mov [g_swizzleXAZC+0x4], eax
	mov eax, [g_swizzleXAZC__uint4+0x8]
	mov [g_swizzleXAZC+0x8], eax
	mov eax, [g_swizzleXAZC__uint4+0xc]
	mov [g_swizzleXAZC+0xc], eax
	mov eax, [g_swizzleYBWD__uint4]
	mov [g_swizzleYBWD], eax
	mov eax, [g_swizzleYBWD__uint4+0x4]
	mov [g_swizzleYBWD+0x4], eax
	mov eax, [g_swizzleYBWD__uint4+0x8]
	mov [g_swizzleYBWD+0x8], eax
	mov eax, [g_swizzleYBWD__uint4+0xc]
	mov [g_swizzleYBWD+0xc], eax
	mov eax, [g_swizzleXYAB__uint4]
	mov [g_swizzleXYAB], eax
	mov eax, [g_swizzleXYAB__uint4+0x4]
	mov [g_swizzleXYAB+0x4], eax
	mov eax, [g_swizzleXYAB__uint4+0x8]
	mov [g_swizzleXYAB+0x8], eax
	mov eax, [g_swizzleXYAB__uint4+0xc]
	mov [g_swizzleXYAB+0xc], eax
	mov eax, [g_swizzleZWCD__uint4]
	mov [g_swizzleZWCD], eax
	mov eax, [g_swizzleZWCD__uint4+0x4]
	mov [g_swizzleZWCD+0x4], eax
	mov eax, [g_swizzleZWCD__uint4+0x8]
	mov [g_swizzleZWCD+0x8], eax
	mov eax, [g_swizzleZWCD__uint4+0xc]
	mov [g_swizzleZWCD+0xc], eax
	mov eax, [g_swizzleXYZA__uint4]
	mov [g_swizzleXYZA], eax
	mov eax, [g_swizzleXYZA__uint4+0x4]
	mov [g_swizzleXYZA+0x4], eax
	mov eax, [g_swizzleXYZA__uint4+0x8]
	mov [g_swizzleXYZA+0x8], eax
	mov eax, [g_swizzleXYZA__uint4+0xc]
	mov [g_swizzleXYZA+0xc], eax
	mov eax, [g_swizzleYZXW__uint4]
	mov [g_swizzleYZXW], eax
	mov eax, [g_swizzleYZXW__uint4+0x4]
	mov [g_swizzleYZXW+0x4], eax
	mov eax, [g_swizzleYZXW__uint4+0x8]
	mov [g_swizzleYZXW+0x8], eax
	mov eax, [g_swizzleYZXW__uint4+0xc]
	mov [g_swizzleYZXW+0xc], eax
	mov eax, [g_swizzleZXYW__uint4]
	mov [g_swizzleZXYW], eax
	mov eax, [g_swizzleZXYW__uint4+0x4]
	mov [g_swizzleZXYW+0x4], eax
	mov eax, [g_swizzleZXYW__uint4+0x8]
	mov [g_swizzleZXYW+0x8], eax
	mov eax, [g_swizzleZXYW__uint4+0xc]
	mov [g_swizzleZXYW+0xc], eax
	mov eax, [g_swizzleWABW__uint4]
	mov [g_swizzleWABW], eax
	mov eax, [g_swizzleWABW__uint4+0x4]
	mov [g_swizzleWABW+0x4], eax
	mov eax, [g_swizzleWABW__uint4+0x8]
	mov [g_swizzleWABW+0x8], eax
	mov eax, [g_swizzleWABW__uint4+0xc]
	mov [g_swizzleWABW+0xc], eax
	mov eax, [g_swizzleZWAW__uint4]
	mov [g_swizzleZWAW], eax
	mov eax, [g_swizzleZWAW__uint4+0x4]
	mov [g_swizzleZWAW+0x4], eax
	mov eax, [g_swizzleZWAW__uint4+0x8]
	mov [g_swizzleZWAW+0x8], eax
	mov eax, [g_swizzleZWAW__uint4+0xc]
	mov [g_swizzleZWAW+0xc], eax
	mov eax, [g_swizzleYZWA__uint4]
	mov [g_swizzleYZWA], eax
	mov eax, [g_swizzleYZWA__uint4+0x4]
	mov [g_swizzleYZWA+0x4], eax
	mov eax, [g_swizzleYZWA__uint4+0x8]
	mov [g_swizzleYZWA+0x8], eax
	mov eax, [g_swizzleYZWA__uint4+0xc]
	mov [g_swizzleYZWA+0xc], eax
	mov eax, [g_swizzleXXXX__uint4]
	mov [g_swizzleXXXX], eax
	mov eax, [g_swizzleXXXX__uint4+0x4]
	mov [g_swizzleXXXX+0x4], eax
	mov eax, [g_swizzleXXXX__uint4+0x8]
	mov [g_swizzleXXXX+0x8], eax
	mov eax, [g_swizzleXXXX__uint4+0xc]
	mov [g_swizzleXXXX+0xc], eax
	mov eax, [g_swizzleYYYY__uint4]
	mov [g_swizzleYYYY], eax
	mov eax, [g_swizzleYYYY__uint4+0x4]
	mov [g_swizzleYYYY+0x4], eax
	mov eax, [g_swizzleYYYY__uint4+0x8]
	mov [g_swizzleYYYY+0x8], eax
	mov eax, [g_swizzleYYYY__uint4+0xc]
	mov [g_swizzleYYYY+0xc], eax
	mov eax, [g_swizzleZZZZ__uint4]
	mov [g_swizzleZZZZ], eax
	mov eax, [g_swizzleZZZZ__uint4+0x4]
	mov [g_swizzleZZZZ+0x4], eax
	mov eax, [g_swizzleZZZZ__uint4+0x8]
	mov [g_swizzleZZZZ+0x8], eax
	mov eax, [g_swizzleZZZZ__uint4+0xc]
	mov [g_swizzleZZZZ+0xc], eax
	mov eax, [g_swizzleWWWW__uint4]
	mov [g_swizzleWWWW], eax
	mov eax, [g_swizzleWWWW__uint4+0x4]
	mov [g_swizzleWWWW+0x4], eax
	mov eax, [g_swizzleWWWW__uint4+0x8]
	mov [g_swizzleWWWW+0x8], eax
	mov eax, [g_swizzleWWWW__uint4+0xc]
	mov [g_swizzleWWWW+0xc], eax
	mov eax, [g_selectX__uint4]
	mov [g_selectX], eax
	mov eax, [g_selectX__uint4+0x4]
	mov [g_selectX+0x4], eax
	mov eax, [g_selectX__uint4+0x8]
	mov [g_selectX+0x8], eax
	mov eax, [g_selectX__uint4+0xc]
	mov [g_selectX+0xc], eax
	mov eax, [g_selectY__uint4]
	mov [g_selectY], eax
	mov eax, [g_selectY__uint4+0x4]
	mov [g_selectY+0x4], eax
	mov eax, [g_selectY__uint4+0x8]
	mov [g_selectY+0x8], eax
	mov eax, [g_selectY__uint4+0xc]
	mov [g_selectY+0xc], eax
	mov eax, [g_selectZ__uint4]
	mov [g_selectZ], eax
	mov eax, [g_selectZ__uint4+0x4]
	mov [g_selectZ+0x4], eax
	mov eax, [g_selectZ__uint4+0x8]
	mov [g_selectZ+0x8], eax
	mov eax, [g_selectZ__uint4+0xc]
	mov [g_selectZ+0xc], eax
	mov eax, [g_selectW__uint4]
	mov [g_selectW], eax
	mov eax, [g_selectW__uint4+0x4]
	mov [g_selectW+0x4], eax
	mov eax, [g_selectW__uint4+0x8]
	mov [g_selectW+0x8], eax
	mov eax, [g_selectW__uint4+0xc]
	mov [g_selectW+0xc], eax
	mov eax, [g_keepYZW__uint4]
	mov [g_keepYZW], eax
	mov eax, [g_keepYZW__uint4+0x4]
	mov [g_keepYZW+0x4], eax
	mov eax, [g_keepYZW__uint4+0x8]
	mov [g_keepYZW+0x8], eax
	mov eax, [g_keepYZW__uint4+0xc]
	mov [g_keepYZW+0xc], eax
	mov eax, [g_keepXZW__uint4]
	mov [g_keepXZW], eax
	mov eax, [g_keepXZW__uint4+0x4]
	mov [g_keepXZW+0x4], eax
	mov eax, [g_keepXZW__uint4+0x8]
	mov [g_keepXZW+0x8], eax
	mov eax, [g_keepXZW__uint4+0xc]
	mov [g_keepXZW+0xc], eax
	mov eax, [g_keepXYW__uint4]
	mov [g_keepXYW], eax
	mov eax, [g_keepXYW__uint4+0x4]
	mov [g_keepXYW+0x4], eax
	mov eax, [g_keepXYW__uint4+0x8]
	mov [g_keepXYW+0x8], eax
	mov eax, [g_keepXYW__uint4+0xc]
	mov [g_keepXYW+0xc], eax
	mov eax, [g_keepXYZ__uint4]
	mov [g_keepXYZ], eax
	mov eax, [g_keepXYZ__uint4+0x4]
	mov [g_keepXYZ+0x4], eax
	mov eax, [g_keepXYZ__uint4+0x8]
	mov [g_keepXYZ+0x8], eax
	mov eax, [g_keepXYZ__uint4+0xc]
	mov [g_keepXYZ+0xc], eax
	mov eax, [g_keepXY__uint4]
	mov [g_keepXY], eax
	mov eax, [g_keepXY__uint4+0x4]
	mov [g_keepXY+0x4], eax
	mov eax, [g_keepXY__uint4+0x8]
	mov [g_keepXY+0x8], eax
	mov eax, [g_keepXY__uint4+0xc]
	mov [g_keepXY+0xc], eax
	mov eax, [g_keepZW__uint4]
	mov [g_keepZW], eax
	mov eax, [g_keepZW__uint4+0x4]
	mov [g_keepZW+0x4], eax
	mov eax, [g_keepZW__uint4+0x8]
	mov [g_keepZW+0x8], eax
	mov eax, [g_keepZW__uint4+0xc]
	mov [g_keepZW+0xc], eax
	mov eax, [g_keepX__uint4]
	mov [g_keepX], eax
	mov eax, [g_keepX__uint4+0x4]
	mov [g_keepX+0x4], eax
	mov eax, [g_keepX__uint4+0x8]
	mov [g_keepX+0x8], eax
	mov eax, [g_keepX__uint4+0xc]
	mov [g_keepX+0xc], eax
	mov eax, [g_keepZ__uint4]
	mov [g_keepZ], eax
	mov eax, [g_keepZ__uint4+0x4]
	mov [g_keepZ+0x4], eax
	mov eax, [g_keepZ__uint4+0x8]
	mov [g_keepZ+0x8], eax
	mov eax, [g_keepZ__uint4+0xc]
	mov [g_keepZ+0xc], eax
	pop ebp
	ret



;R_TessBModel(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xcc
	mov dword [ebp-0x70], 0x0
	mov dword [ebp-0x6c], 0x0
	mov dword [ebp-0x78], 0x0
	mov dword [ebp-0x74], 0x0
	mov dword [ebp-0x80], 0x0
	mov dword [ebp-0x7c], 0x0
	mov dword [ebp-0x88], 0x0
	mov dword [ebp-0x84], 0x0
	mov dword [ebp-0x90], 0x0
	mov dword [ebp-0x8c], 0x0
	mov dword [ebp-0x98], 0x0
	mov dword [ebp-0x94], 0x0
	mov dword [ebp-0xa0], 0x0
	mov dword [ebp-0x9c], 0x0
	mov dword [ebp-0xa8], 0x0
	mov dword [ebp-0xa4], 0x0
	mov eax, [ebp+0x8]
	mov ebx, [ebp+0xc]
	mov [ebp-0x30], ebx
	mov esi, [ebp+0x10]
	mov [ebp-0x34], esi
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov [ebp-0xb0], ebx
	mov [ebp-0xac], esi
	mov [ebp-0x3c], esi
	mov [ebp-0x38], ebx
	mov esi, [eax+0xc]
	mov ebx, [eax+0x8]
	mov eax, [esi]
	lea eax, [eax+ebx*8]
	mov [ebp-0x64], eax
	mov eax, [esi+0x4]
	sub eax, ebx
	mov [ebp-0x60], eax
	mov ecx, [ebp-0xac]
	mov edx, [ebp-0xb0]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov edx, [ebp-0x38]
	mov edx, [edx+0xca8]
	mov [ebp-0x48], edx
	mov esi, [esi+0x8]
	mov [ebp-0x44], esi
	cmp esi, 0x7
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_180:
	mov dword [esp+0x4], 0x0
	mov ebx, [ebp-0x38]
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov esi, [ebp-0x3c]
	mov eax, [esi+0xc0]
	test byte [eax+0x4], 0x8
	jnz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov eax, 0x2
	mov ecx, [ebp-0x3c]
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_140:
	add ecx, 0x90
	mov [ebp-0x40], ecx
	mov [ecx+0x8], eax
	mov ebx, [ebp-0x3c]
	mov [esp], ebx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov [ebp-0xac], ebx
	mov esi, [ebp-0x38]
	mov [ebp-0xb0], esi
	cmp dword [esi+0xf34], 0x1
	sbb edx, edx
	cmp edx, [ebx+0xcc]
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov [esp+0x4], edx
	mov [esp], ebx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov eax, [ebp-0x34]
	test eax, eax
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
	mov edx, [ebp-0x30]
	mov [ebp-0xa8], edx
	mov ecx, [ebp-0x34]
	mov [ebp-0xa4], ecx
	mov ebx, [ebp-0xa8]
	mov esi, [ebp-0xa4]
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov esi, [ebp-0x34]
	mov eax, [esi+0xc0]
	test byte [eax+0x4], 0x8
	jnz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov eax, 0x2
	mov ecx, [ebp-0x34]
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_150:
	mov [ecx+0x98], eax
	mov [esp], ecx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ebx, [ebp-0x30]
	mov [ebp+0xc], ebx
	mov esi, [ebp-0x34]
	mov [ebp+0x10], esi
	cmp dword [ebx+0xf34], 0x1
	sbb eax, eax
	cmp eax, [esi+0xcc]
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	mov eax, [ebp-0x30]
	mov edx, [ebp-0x34]
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_160:
	mov [ebp-0xa0], eax
	mov [ebp-0x9c], edx
	mov ecx, [ebp-0xa0]
	mov ebx, [ebp-0x9c]
	mov [esp], ecx
	mov [esp+0x4], ebx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	mov eax, [ebp-0x64]
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov dword [ebp-0xb8], 0xffffffff
	mov dword [ebp-0xb4], 0xffffffff
	mov word [ebp-0xb8], 0x0
	and dword [ebp-0xb8], 0xff00ffff
	and dword [ebp-0xb8], 0xe0ffffff
	mov dword [ebp-0xc0], 0xffffffff
	mov dword [ebp-0xbc], 0xffffffff
	mov word [ebp-0xc0], 0x0
	cmp dword [ebp-0x44], 0x7
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
	and dword [ebp-0xc0], 0xff00ffff
	and dword [ebp-0xc0], 0xe0ffffff
	mov edx, [ebp-0x3c]
	mov [ebp-0x94], edx
	mov ecx, [ebp-0x38]
	mov [ebp-0x98], ecx
	mov eax, [ebp-0x98]
	mov edx, [ebp-0x94]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov edx, [ebp-0xb8]
	and edx, ebx
	mov [ebp-0x58], edx
	mov ecx, [ebp-0xb4]
	and ecx, esi
	mov [ebp-0x54], ecx
	mov dword [ebp-0x5c], 0x0
	mov eax, [ebp-0x34]
	add eax, 0x90
	mov [ebp-0xc8], eax
	cmp dword [ebp-0x44], 0x7
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_130:
	mov edx, [ebp-0xc0]
	and edx, ebx
	mov [ebp-0x50], edx
	mov ecx, [ebp-0xbc]
	and ecx, esi
	mov [ebp-0x4c], ecx
	mov eax, [ebp-0x5c]
	mov edx, [ebp-0x64]
	lea edi, [edx+eax*8]
	mov [ebp-0x2c], eax
	mov ecx, [ebp-0x60]
	mov [ebp-0xc4], ecx
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_120:
	movzx eax, bx
	mov esi, [ebp-0x48]
	lea ebx, [esi+eax*4]
	mov eax, [ebx]
	mov edx, [ebp-0x38]
	cmp eax, [edx+0xf08]
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
	mov [esp+0x4], eax
	mov [esp], edx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	mov ebx, [ebx+0x4]
	movzx eax, word [ebx+0x8]
	mov [ebp-0x24], eax
	movzx eax, word [ebx+0xa]
	mov [ebp-0x20], eax
	mov [esp+0x4], ebx
	mov ecx, [ebp-0x40]
	mov [esp], ecx
	call _Z25R_SetStreamsForBspSurfaceP18GfxCmdBufPrimStatePK14srfTriangles_t
	mov esi, [ebp-0x3c]
	mov [ebp-0x74], esi
	mov eax, [ebp-0x38]
	mov [ebp-0x78], eax
	mov edx, [ebp-0x78]
	mov ecx, [ebp-0x74]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov ecx, rgp
	mov edx, [ecx+0x20a0]
	mov eax, [ebx+0xc]
	mov edx, [edx+0x14]
	lea eax, [edx+eax*2]
	mov [esp+0x4], eax
	mov esi, [ebp-0x40]
	mov [esp], esi
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	mov eax, [ebp-0x34]
	test eax, eax
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
	mov [esp+0x4], ebx
	mov edx, [ebp-0xc8]
	mov [esp], edx
	call _Z25R_SetStreamsForBspSurfaceP18GfxCmdBufPrimStatePK14srfTriangles_t
	mov ecx, [ebp-0x30]
	mov [ebp-0x70], ecx
	mov esi, [ebp-0x34]
	mov [ebp-0x6c], esi
	mov eax, [ebp-0x70]
	mov edx, [ebp-0x6c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov ecx, rgp
	mov edx, [ecx+0x20a0]
	mov eax, [ebx+0xc]
	mov edx, [edx+0x14]
	lea eax, [edx+eax*2]
	mov [esp+0x4], eax
	mov ebx, [ebp-0xc8]
	mov [esp], ebx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea esi, [ebp-0x24]
	mov [esp+0x4], esi
	mov [esp], ebx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	mov dword [ebp-0x20], 0x0
	add dword [ebp-0x2c], 0x1
	mov eax, [ebp-0xc4]
	cmp [ebp-0x2c], eax
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
	mov ebx, [edi+0x8]
	mov esi, [edi+0xc]
	add edi, 0x8
	mov eax, [ebp-0xc0]
	and eax, ebx
	mov edx, [ebp-0xbc]
	and edx, esi
	mov ecx, [ebp-0x4c]
	xor ecx, edx
	xor eax, [ebp-0x50]
	or ecx, eax
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
	mov eax, [ebp-0xb8]
	and eax, ebx
	mov edx, [ebp-0xb4]
	and edx, esi
	mov ecx, [ebp-0x54]
	xor ecx, edx
	xor eax, [ebp-0x58]
	or ecx, eax
	jnz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
	mov edx, [ebp-0x2c]
	mov [ebp-0x5c], edx
	cmp dword [ebp-0x44], 0x7
	jnz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_130
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	mov eax, ebx
	shr eax, 0x18
	and eax, 0x1f
	mov ecx, [ebp-0x3c]
	mov [ebp-0x8c], ecx
	mov ecx, [ebp-0x38]
	mov [ebp-0x90], ecx
	mov [esp+0x8], eax
	mov eax, [ebp-0x90]
	mov edx, [ebp-0x8c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z13R_SetLightmap16GfxCmdBufContextj
	mov ecx, ebx
	shr ecx, 0x10
	movzx eax, cl
	mov ecx, [ebp-0x3c]
	mov [ebp-0x84], ecx
	mov ecx, [ebp-0x38]
	mov [ebp-0x88], ecx
	mov [esp+0x8], eax
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x3c]
	mov [ebp-0x7c], edx
	mov ecx, [ebp-0x38]
	mov [ebp-0x80], ecx
	mov eax, [ebp-0x80]
	mov edx, [ebp-0x7c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	jmp _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_130
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov eax, [ebp-0x2c]
	add esp, 0xcc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov eax, [esi+0xb8]
	mov eax, [eax+0x40]
	movzx eax, byte [eax+0x4]
	add eax, 0x2
	mov ecx, esi
	jmp _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_140
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov eax, [esi+0xb8]
	mov eax, [eax+0x40]
	movzx eax, byte [eax+0x4]
	add eax, 0x2
	mov ecx, esi
	jmp _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_150
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov eax, ebx
	mov edx, esi
	jmp _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov eax, sc_enable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_170
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_190:
	mov ecx, [ebp-0x38]
	mov [ecx+0xc60], eax
	jmp _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_180
_Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_170:
	mov eax, rgp
	mov eax, [eax+0x2008]
	jmp _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext_190


;R_TessCodeMeshList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x9c
	mov dword [ebp-0x70], 0x0
	mov dword [ebp-0x6c], 0x0
	mov dword [ebp-0x78], 0x0
	mov dword [ebp-0x74], 0x0
	mov eax, [ebp+0x8]
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov [ebp-0x80], ebx
	mov [ebp-0x7c], esi
	mov [ebp-0x34], esi
	mov [ebp-0x2c], ebx
	mov ebx, [eax+0xc]
	mov esi, [eax+0x8]
	mov eax, [ebx+0x4]
	sub eax, esi
	mov [ebp-0x60], eax
	mov eax, [ebx]
	lea esi, [eax+esi*8]
	mov [ebp-0x64], esi
	mov ecx, [ebp-0x7c]
	mov edx, [ebp-0x80]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov edx, [ebp-0x64]
	mov esi, [edx]
	mov edi, [edx+0x4]
	mov eax, rg
	add eax, 0x2244
	mov ecx, [ebp-0x2c]
	cmp [ecx+0xf08], eax
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], eax
	mov ebx, [ebp-0x80]
	mov [esp], ebx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov dword [esp+0x4], 0x0
	mov eax, [ebp-0x80]
	mov [esp], eax
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov edx, [ebp-0x34]
	add edx, 0x90
	mov [ebp-0x40], edx
	mov dword [edx+0x8], 0x1
	mov ecx, [ebp-0x7c]
	mov [esp], ecx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ebx, [ebp-0x2c]
	cmp dword [ebx+0xf34], 0x1
	sbb eax, eax
	mov edx, [ebp-0x34]
	cmp eax, [edx+0xcc]
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov [esp+0x4], eax
	mov ecx, [ebp-0x7c]
	mov [esp], ecx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	mov ebx, [ebp-0x2c]
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov ebx, [ebx+0xca8]
	mov [ebp-0x4c], ebx
	mov eax, ebx
	add eax, 0xb0000
	mov [esp+0x4], eax
	mov eax, [ebp-0x7c]
	mov [esp], eax
	call _Z15R_SetMeshStreamP14GfxCmdBufStateP11GfxMeshData
	mov dword [ebp-0x1c], 0x0
	mov dword [ebp-0x24], 0x4000
	mov dword [ebp-0x20], 0x0
	mov dword [ebp-0x88], 0xffffffff
	mov dword [ebp-0x84], 0xffffffff
	mov word [ebp-0x88], 0x0
	and dword [ebp-0x88], 0xff00ffff
	and dword [ebp-0x88], 0xe0ffffff
	mov edx, [ebp-0x88]
	and edx, esi
	mov [ebp-0x58], edx
	mov ecx, [ebp-0x84]
	and ecx, edi
	mov [ebp-0x54], ecx
	mov dword [ebp-0x48], 0x0
	mov dword [ebp-0x44], 0x0
	mov dword [ebp-0x5c], 0x0
	xor ebx, ebx
	mov [ebp-0x8c], ebx
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	movzx eax, si
	shl eax, 0x4
	mov esi, [ebp-0x4c]
	lea eax, [eax+esi+0x20000]
	mov [ebp-0x68], eax
	mov edx, [ebp-0x44]
	test edx, edx
	jnz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	cmp word [eax+0xa], 0x0
	jnz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov edx, [ebp-0x8c]
	lea eax, [edx+edx*2]
	mov ecx, [ebp-0x48]
	lea eax, [ecx+eax*2]
	mov ebx, [ebp-0x68]
	cmp eax, [ebx+0x4]
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov eax, [ebp-0x8c]
	test eax, eax
	jnz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov ebx, [ebp-0x68]
	mov ebx, [ebx+0x4]
	mov [ebp-0x48], ebx
	mov esi, [ebp-0x68]
	movzx edx, word [esi+0x8]
	movzx eax, word [esi+0xa]
	movzx ecx, ax
	mov [ebp-0x3c], ecx
	test ax, ax
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
	mov ebx, [ebp-0x2c]
	mov [ebp-0x30], ebx
	mov dword [ebp-0x38], 0x0
	mov edi, ebx
	add edi, 0xbf0
	shl edx, 0x4
	mov eax, [ebp-0x4c]
	lea esi, [edx+eax+0x6b000]
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov ebx, [esi+0xc]
	mov ecx, [esi+0x8]
	mov edx, [esi+0x4]
	mov eax, [esi]
	mov [edi], eax
	mov [edi+0x4], edx
	mov [edi+0x8], ecx
	mov [edi+0xc], ebx
	mov edx, [ebp-0x30]
	add word [edx+0xe9e], 0x1
	add dword [ebp-0x38], 0x1
	add esi, 0x10
	add edi, 0x10
	add edx, 0x2
	mov [ebp-0x30], edx
	mov ecx, [ebp-0x38]
	cmp [ebp-0x3c], ecx
	jnz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov ebx, [ebp-0x34]
	mov [ebp-0x74], ebx
	mov esi, [ebp-0x2c]
	mov [ebp-0x78], esi
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov [ebp-0x6c], ebx
	mov [ebp-0x70], esi
	mov edx, [ebp-0x70]
	mov ecx, [ebp-0x6c]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov ecx, [ebp-0x20]
	mov [ebp-0x8c], ecx
	mov ebx, [ebp-0x68]
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	movzx ebx, word [ebx+0xa]
	mov [ebp-0x44], ebx
	mov ebx, [ebp-0x8c]
	mov esi, [ebp-0x68]
	add ebx, [esi]
	mov [ebp-0x8c], ebx
	mov [ebp-0x20], ebx
	add dword [ebp-0x5c], 0x1
	mov eax, [ebp-0x5c]
	cmp [ebp-0x60], eax
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
	mov ecx, [ebp-0x64]
	mov esi, [ecx+eax*8]
	mov edi, [ecx+eax*8+0x4]
	mov eax, [ebp-0x88]
	and eax, esi
	mov edx, [ebp-0x84]
	and edx, edi
	mov ecx, [ebp-0x54]
	xor ecx, edx
	xor eax, [ebp-0x58]
	or ecx, eax
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	test ebx, ebx
	jz _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
	mov [esp+0x8], ebx
	mov ebx, [ebp-0x48]
	mov [esp+0x4], ebx
	mov esi, [ebp-0x40]
	mov [esp], esi
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	mov eax, [ebp-0x5c]
	add esp, 0x9c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov esi, [ebp-0x8c]
	mov [esp+0x8], esi
	mov eax, [ebp-0x48]
	mov [esp+0x4], eax
	mov edx, [ebp-0x40]
	mov [esp], edx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov ecx, [ebp-0x40]
	mov [esp], ecx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	mov dword [ebp-0x20], 0x0
	jmp _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110


;R_TessMarkMeshList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xbc
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
	mov dword [ebp-0x90], 0x0
	mov dword [ebp-0x8c], 0x0
	mov dword [ebp-0x98], 0x0
	mov dword [ebp-0x94], 0x0
	mov eax, [ebp+0x8]
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov [ebp-0xa0], ebx
	mov [ebp-0x9c], esi
	mov [ebp-0x38], esi
	mov [ebp-0x34], ebx
	mov ebx, [eax+0xc]
	mov esi, [eax+0x8]
	mov eax, [ebx+0x4]
	sub eax, esi
	mov [ebp-0x58], eax
	mov eax, [ebx]
	lea esi, [eax+esi*8]
	mov [ebp-0x5c], esi
	mov ecx, [ebp-0x9c]
	mov edx, [ebp-0xa0]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov ebx, [ebx+0x8]
	mov [ebp-0x40], ebx
	cmp ebx, 0x7
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_200:
	mov ebx, [ebp-0x5c]
	mov ecx, [ebx]
	mov ebx, [ebx+0x4]
	mov [ebp-0xb8], ecx
	mov [ebp-0xb4], ebx
	mov eax, rg
	add eax, 0x2244
	mov esi, [ebp-0x34]
	cmp [esi+0xf08], eax
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
	mov eax, [ebp-0x34]
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180:
	mov dword [esp+0x4], 0x0
	mov [esp], eax
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov edx, [ebp-0x34]
	mov edx, [edx+0xca8]
	mov [ebp-0x48], edx
	movzx edi, word [ebp-0xb8]
	mov eax, edi
	shl eax, 0x4
	movzx eax, byte [eax+edx+0x11867a]
	and eax, 0xc0
	cmp eax, 0x40
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	cmp eax, 0xc0
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	xor eax, eax
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170:
	neg eax
	add eax, 0x2
	mov ecx, [ebp-0x38]
	add ecx, 0x90
	mov [ebp-0x3c], ecx
	mov [ecx+0x8], eax
	mov ebx, [ebp-0x38]
	mov [esp], ebx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov [ebp-0x9c], ebx
	mov esi, [ebp-0x34]
	mov [ebp-0xa0], esi
	cmp dword [esi+0xf34], 0x1
	sbb edx, edx
	cmp edx, [ebx+0xcc]
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
	mov [esp+0x4], edx
	mov [esp], ebx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	mov eax, [ebp-0x48]
	add eax, 0x11e670
	mov [esp+0x4], eax
	mov edx, [ebp-0x38]
	mov [esp], edx
	call _Z15R_SetMeshStreamP14GfxCmdBufStateP11GfxMeshData
	mov dword [ebp-0x1c], 0x0
	mov dword [ebp-0x24], 0x1800
	mov dword [ebp-0x20], 0x0
	mov dword [ebp-0xa8], 0xffffffff
	mov dword [ebp-0xa4], 0xffffffff
	mov word [ebp-0xa8], 0x0
	and dword [ebp-0xa8], 0xff00ffff
	and dword [ebp-0xa8], 0xe0ffffff
	mov dword [ebp-0xb0], 0xffffffff
	mov dword [ebp-0xac], 0xffffffff
	mov word [ebp-0xb0], 0x0
	cmp dword [ebp-0x40], 0x7
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	and dword [ebp-0xb0], 0xff00ffff
	and dword [ebp-0xb0], 0xe0ffffff
	mov ecx, [ebp-0x38]
	mov [ebp-0x94], ecx
	mov ebx, [ebp-0x34]
	mov [ebp-0x98], ebx
	mov eax, [ebp-0x98]
	mov edx, [ebp-0x94]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov edx, [ebp-0xb8]
	and edx, [ebp-0xa8]
	mov [ebp-0x50], edx
	mov ecx, [ebp-0xb4]
	and ecx, [ebp-0xa4]
	mov [ebp-0x4c], ecx
	mov dword [ebp-0x44], 0x0
	mov dword [ebp-0x54], 0x0
	cmp dword [ebp-0x40], 0x7
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120:
	mov ebx, [ebp-0xb8]
	and ebx, [ebp-0xb0]
	mov esi, [ebp-0xb4]
	and esi, [ebp-0xac]
	mov eax, [ebp-0x54]
	mov edx, [ebp-0x5c]
	lea eax, [edx+eax*8]
	mov [ebp-0x30], eax
	mov edx, [ebp-0x54]
	mov [ebp-0x2c], edx
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov ecx, [edi+0x4]
	mov [ebp-0x44], ecx
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	add edx, [edi]
	mov edi, edx
	mov [ebp-0x20], edx
	add dword [ebp-0x2c], 0x1
	mov eax, [ebp-0x58]
	cmp [ebp-0x2c], eax
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
	mov ecx, [ebp-0x30]
	mov edx, [ecx+0x8]
	mov ecx, [ecx+0xc]
	mov [ebp-0xb8], edx
	mov [ebp-0xb4], ecx
	add dword [ebp-0x30], 0x8
	mov eax, [ebp-0xb0]
	and eax, [ebp-0xb8]
	mov edx, [ebp-0xac]
	and edx, ecx
	mov ecx, esi
	xor ecx, edx
	xor eax, ebx
	or ecx, eax
	jnz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
	movzx edi, word [ebp-0xb8]
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	shl edi, 0x4
	mov ecx, [ebp-0x48]
	lea edi, [edi+ecx+0x118670]
	mov edx, [ebp-0x20]
	lea eax, [edx+edx*2]
	mov ecx, [ebp-0x44]
	lea eax, [ecx+eax*2]
	cmp eax, [edi+0x4]
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
	test edx, edx
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
	mov eax, [ebp-0x38]
	mov [ebp-0x6c], eax
	mov edx, [ebp-0x34]
	mov [ebp-0x70], edx
	mov eax, [ebp-0x70]
	mov edx, [ebp-0x6c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov edx, [ebp-0x44]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x3c]
	mov [esp], ecx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov edx, [ebp-0x3c]
	mov [esp], edx
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	mov dword [ebp-0x20], 0x0
	xor edx, edx
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	mov eax, [ebp-0xa8]
	and eax, [ebp-0xb8]
	mov edx, [ebp-0xa4]
	and edx, [ebp-0xb4]
	mov ecx, [ebp-0x4c]
	xor ecx, edx
	xor eax, [ebp-0x50]
	or ecx, eax
	jnz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
	mov eax, [ebp-0x2c]
	mov [ebp-0x54], eax
	movzx edi, word [ebp-0xb8]
	cmp dword [ebp-0x40], 0x7
	jnz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov ecx, [ebp-0x20]
	test ecx, ecx
	jnz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130
	mov eax, edi
	shl eax, 0x4
	mov ecx, [ebp-0x48]
	lea edx, [eax+ecx+0x118670]
	movzx eax, byte [edx+0xa]
	and eax, 0xc0
	cmp eax, 0x40
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_210:
	cmp eax, 0xc0
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150
	mov eax, [ebp-0xb8]
	shr eax, 0x18
	and eax, 0x1f
	mov ebx, [ebp-0x38]
	mov [ebp-0x84], ebx
	mov esi, [ebp-0x34]
	mov [ebp-0x88], esi
	mov [esp+0x8], eax
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z13R_SetLightmap16GfxCmdBufContextj
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220:
	mov ecx, [ebp-0xb8]
	shr ecx, 0x10
	movzx eax, cl
	mov ecx, [ebp-0x38]
	mov [ebp-0x7c], ecx
	mov ebx, [ebp-0x34]
	mov [ebp-0x80], ebx
	mov [esp+0x8], eax
	mov eax, [ebp-0x80]
	mov edx, [ebp-0x7c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x38]
	mov [ebp-0x74], edx
	mov [ebp-0x78], ebx
	mov ecx, [ebp-0x78]
	mov ebx, [ebp-0x74]
	mov [esp], ecx
	mov [esp+0x4], ebx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	test edi, edi
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	mov ebx, [ebp-0x38]
	mov [ebp-0x64], ebx
	mov esi, [ebp-0x34]
	mov [ebp-0x68], esi
	mov eax, [ebp-0x68]
	mov edx, [ebp-0x64]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov edx, [ebp-0x44]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x3c]
	mov [esp], ecx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea ebx, [ebp-0x24]
	mov [esp+0x4], ebx
	mov esi, [ebp-0x3c]
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160:
	mov eax, [ebp-0x2c]
	add esp, 0xbc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov eax, 0x1
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov eax, esi
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov eax, sc_enable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_190
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230:
	mov edx, [ebp-0x34]
	mov [edx+0xc60], eax
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_200
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130:
	mov ebx, [ebp-0x38]
	mov [ebp-0x8c], ebx
	mov esi, [ebp-0x34]
	mov [ebp-0x90], esi
	mov eax, [ebp-0x90]
	mov edx, [ebp-0x8c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov [esp+0x8], eax
	mov edx, [ebp-0x44]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x3c]
	mov [esp], ecx
	call _Z14R_SetIndexDataP18GfxCmdBufPrimStatePKti
	mov [ebp-0x1c], eax
	lea ebx, [ebp-0x24]
	mov [esp+0x4], ebx
	mov esi, [ebp-0x3c]
	mov [esp], esi
	call _Z22R_DrawIndexedPrimitiveP18GfxCmdBufPrimStatePK15GfxDrawPrimArgs
	mov dword [ebp-0x20], 0x0
	mov dword [ebp-0x44], 0x0
	mov eax, edi
	shl eax, 0x4
	mov ecx, [ebp-0x48]
	lea edx, [eax+ecx+0x118670]
	movzx eax, byte [edx+0xa]
	and eax, 0xc0
	cmp eax, 0x40
	jnz _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_210
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140:
	mov ebx, [ebp-0x34]
	mov [esp+0x4], ebx
	movzx eax, word [edx+0x8]
	mov [esp], eax
	call _Z39R_SetStaticModelLightingCoordsForSourcejP20GfxCmdBufSourceState
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150:
	mov esi, [ebp-0x34]
	mov [esp+0x4], esi
	movzx eax, word [edx+0x8]
	mov [esp], eax
	call _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220
_Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_190:
	mov eax, rgp
	mov eax, [eax+0x2008]
	jmp _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230
	nop


;R_TessTrianglesList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x8c
	mov dword [ebp-0x38], 0x0
	mov dword [ebp-0x34], 0x0
	mov dword [ebp-0x40], 0x0
	mov dword [ebp-0x3c], 0x0
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
	mov ecx, [ebp+0xc]
	mov [ebp-0x1c], ecx
	mov edi, [ebp+0x10]
	mov ecx, [ebp+0x8]
	mov ebx, [ecx]
	mov esi, [ecx+0x4]
	mov [ebp-0x24], esi
	mov [ebp-0x20], ebx
	mov ecx, [ecx+0xc]
	mov [ebp-0x28], ecx
	mov ecx, [ecx+0x8]
	mov [ebp-0x2c], ecx
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, rg
	add eax, 0x2244
	mov edx, [ebp-0x20]
	cmp [edx+0xf08], eax
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov ecx, [ebp-0x24]
	mov eax, [ecx+0xc0]
	test byte [eax+0x4], 0x8
	jnz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov eax, 0x2
	mov ecx, [ebp-0x24]
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov [ecx+0x98], eax
	mov [esp], ecx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov esi, [ebp-0x24]
	mov ebx, [ebp-0x20]
	cmp dword [ebx+0xf34], 0x1
	sbb edx, edx
	cmp edx, [esi+0xcc]
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov [esp+0x4], edx
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	test edi, edi
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
	mov ecx, [ebp-0x1c]
	mov [ebp-0x78], ecx
	mov [ebp-0x74], edi
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, [edi+0xc0]
	test byte [eax+0x4], 0x8
	jnz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov eax, 0x2
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	mov [edi+0x98], eax
	mov [esp], edi
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov edx, [ebp-0x1c]
	mov [ebp+0xc], edx
	mov [ebp+0x10], edi
	cmp dword [edx+0xf34], 0x1
	sbb eax, eax
	cmp eax, [edi+0xcc]
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	mov ebx, [ebp-0x20]
	mov ecx, [ebx+0xca8]
	add ecx, 0x28000
	mov eax, [ebp+0x8]
	mov edx, [eax+0x8]
	mov ebx, [ebp-0x28]
	mov eax, [ebx]
	movzx eax, word [eax+edx*8]
	lea ebx, [ecx+eax*4]
	cmp dword [ebp-0x2c], 0x7
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
	mov ecx, [ebp-0x24]
	mov [ebp-0x3c], ecx
	mov eax, [ebp-0x20]
	mov [ebp-0x40], eax
	mov edx, [ebp-0x40]
	mov ecx, [ebp-0x3c]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov ecx, [ebp-0x24]
	mov [ebp-0x34], ecx
	mov eax, [ebp-0x20]
	mov [ebp-0x38], eax
	mov edx, [ebp-0x38]
	mov ecx, [ebp-0x34]
	mov [esp], edx
	mov [esp+0x4], ecx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov ecx, [ebp-0x28]
	mov [esp+0x8], ecx
	mov eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z18R_DrawBspDrawSurfsPKjP14GfxCmdBufStatePK19GfxDrawSurfListInfo
	mov eax, 0x1
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov eax, [ecx+0xb8]
	mov eax, [eax+0x40]
	movzx eax, byte [eax+0x4]
	add eax, 0x2
	jmp _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov eax, [edi+0xb8]
	mov eax, [eax+0x40]
	movzx eax, byte [eax+0x4]
	add eax, 0x2
	jmp _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov eax, sc_enable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov edx, [ebp-0x20]
	mov [edx+0xc60], eax
	mov ecx, [ebp-0x24]
	mov [ebp-0x6c], ecx
	mov [ebp-0x70], edx
	mov eax, [ebp-0x70]
	mov edx, [ebp-0x6c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x24]
	mov [ebp-0x64], edx
	mov ecx, [ebp-0x20]
	mov [ebp-0x68], ecx
	mov eax, [ebp-0x68]
	mov edx, [ebp-0x64]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	test edi, edi
	jz _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
	mov edx, [ebp-0x1c]
	mov [ebp-0x60], edx
	mov [ebp-0x5c], edi
	mov eax, [ebp-0x60]
	mov edx, [ebp-0x5c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x1c]
	mov [ebp-0x58], edx
	mov [ebp-0x54], edi
	mov eax, [ebp-0x58]
	mov edx, [ebp-0x54]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	mov edx, [ebp-0x1c]
	mov [ebp-0x50], edx
	mov [ebp-0x4c], edi
	mov ecx, [ebp-0x24]
	mov [ebp-0x44], ecx
	mov eax, [ebp-0x20]
	mov [ebp-0x48], eax
	mov edx, [ebp-0x28]
	mov [esp+0x14], edx
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [esp+0xc], eax
	mov [esp+0x10], edx
	mov edx, [ebp-0x48]
	mov ecx, [ebp-0x44]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], ebx
	call _Z21R_DrawBspDrawSurfsLitPKj16GfxCmdBufContextS1_PK19GfxDrawSurfListInfo
	mov eax, 0x1
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	mov eax, rgp
	mov eax, [eax+0x2008]
	jmp _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110



;R_TessStaticModelCachedList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov dword [ebp-0x30], 0x0
	mov dword [ebp-0x2c], 0x0
	mov dword [ebp-0x38], 0x0
	mov dword [ebp-0x34], 0x0
	mov ecx, [ebp+0x8]
	mov ebx, [ecx]
	mov esi, [ecx+0x4]
	mov [ebp-0x1c], esi
	mov edi, ebx
	mov ecx, [ecx+0xc]
	mov [ebp-0x20], ecx
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov eax, [eax+0x8]
	mov [ebp-0x24], eax
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov eax, rg
	add eax, 0x2244
	cmp [ebx+0xf08], eax
	jz _Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
_Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov edx, [ebp-0x1c]
	mov dword [edx+0x98], 0xf
	mov [esp], esi
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	cmp dword [edi+0xf34], 0x1
	sbb eax, eax
	mov ecx, [ebp-0x1c]
	cmp eax, [ecx+0xcc]
	jz _Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov ecx, [edi+0xca8]
	add ecx, 0x28000
	mov edi, [ebp+0x8]
	mov edx, [edi+0x8]
	mov edi, [ebp-0x20]
	mov eax, [edi]
	movzx eax, word [eax+edx*8]
	lea eax, [ecx+eax*4]
	cmp dword [ebp-0x24], 0x7
	jz _Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov [ebp-0x2c], esi
	mov [ebp-0x30], ebx
	mov edx, [ebp-0x30]
	mov ecx, [ebp-0x2c]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], eax
	call _Z27R_DrawStaticModelCachedSurfPKj16GfxCmdBufContext
	mov eax, 0x1
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov [ebp-0x34], esi
	mov [ebp-0x38], ebx
	mov edx, [ebp-0x38]
	mov ecx, [ebp-0x34]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], eax
	call _Z30R_DrawStaticModelCachedSurfLitPKj16GfxCmdBufContext
	mov eax, 0x1
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;R_TessStaticModelPreTessList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov dword [ebp-0x30], 0x0
	mov dword [ebp-0x2c], 0x0
	mov dword [ebp-0x38], 0x0
	mov dword [ebp-0x34], 0x0
	mov ecx, [ebp+0x8]
	mov ebx, [ecx]
	mov esi, [ecx+0x4]
	mov [ebp-0x1c], esi
	mov edi, ebx
	mov ecx, [ecx+0xc]
	mov [ebp-0x20], ecx
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov eax, [eax+0x8]
	mov [ebp-0x24], eax
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov eax, rg
	add eax, 0x2244
	cmp [ebx+0xf08], eax
	jz _Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
_Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov edx, [ebp-0x1c]
	mov dword [edx+0x98], 0xf
	mov [esp], esi
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	cmp dword [edi+0xf34], 0x1
	sbb eax, eax
	mov ecx, [ebp-0x1c]
	cmp eax, [ecx+0xcc]
	jz _Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov ecx, [edi+0xca8]
	add ecx, 0x28000
	mov edi, [ebp+0x8]
	mov edx, [edi+0x8]
	mov edi, [ebp-0x20]
	mov eax, [edi]
	movzx eax, word [eax+edx*8]
	lea eax, [ecx+eax*4]
	cmp dword [ebp-0x24], 0x7
	jz _Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov [ebp-0x2c], esi
	mov [ebp-0x30], ebx
	mov edx, [ebp-0x30]
	mov ecx, [ebp-0x2c]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], eax
	call _Z28R_DrawStaticModelPreTessSurfPKj16GfxCmdBufContext
	mov eax, 0x1
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov [ebp-0x34], esi
	mov [ebp-0x38], ebx
	mov edx, [ebp-0x38]
	mov ecx, [ebp-0x34]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], eax
	call _Z31R_DrawStaticModelPreTessSurfLitPKj16GfxCmdBufContext
	mov eax, 0x1
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;R_TessXModelRigidDrawSurfList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xcc
	mov dword [ebp-0x40], 0x0
	mov dword [ebp-0x3c], 0x0
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
	mov dword [ebp-0x90], 0x0
	mov dword [ebp-0x8c], 0x0
	mov dword [ebp-0x98], 0x0
	mov dword [ebp-0x94], 0x0
	mov dword [ebp-0xa0], 0x0
	mov dword [ebp-0x9c], 0x0
	mov eax, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov [ebp-0x1c], edx
	mov ecx, [ebp+0x10]
	mov [ebp-0x20], ecx
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov [ebp-0x24], esi
	mov edi, ebx
	mov ecx, [ebx+0xca8]
	mov edx, [eax+0xc]
	mov [ebp-0x28], edx
	mov edx, [edx+0x8]
	mov [ebp-0x2c], edx
	mov edx, [eax+0x8]
	mov eax, [ebp-0x28]
	mov eax, [eax+0x4]
	sub eax, edx
	mov [ebp-0x30], eax
	mov eax, [ebp-0x28]
	mov eax, [eax]
	lea edx, [eax+edx*8]
	mov [ebp-0x34], edx
	mov eax, [edx]
	mov edx, [edx+0x4]
	mov [ebp-0xa8], eax
	mov [ebp-0xa4], edx
	mov eax, s_manualObjectPlacement
	mov [ebx+0xf08], eax
	mov eax, [ebp-0x28]
	mov eax, [eax+0x24]
	test eax, eax
	jz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	movzx eax, word [ebp-0xa8]
	movzx eax, word [ecx+eax*4+0xe]
	movzx edx, ax
	test ax, ax
	jnz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	xor ebx, ebx
	xor eax, eax
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	mov esi, eax
	mov edx, [ebp-0x24]
	mov [ebp-0x9c], edx
	mov [ebp-0xa0], edi
	mov eax, [ebp-0xa0]
	mov edx, [ebp-0x9c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	test esi, esi
	jnz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120:
	mov [esp+0x4], ebx
	mov [esp], edi
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov edx, [ebp-0x24]
	mov dword [edx+0x98], 0x1
	mov [esp], edx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ecx, [ebp-0x24]
	cmp ebx, [ecx+0xcc]
	jz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
	mov [esp+0x4], ebx
	mov [esp], ecx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	cmp dword [ebp-0x2c], 0x7
	jnz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov eax, sc_enable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jnz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130:
	mov eax, rgp
	mov eax, [eax+0x2008]
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140:
	mov [edi+0xc60], eax
	mov eax, [ebp-0x20]
	test eax, eax
	jz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
	mov eax, [ebp-0x1c]
	mov [ebp-0x90], eax
	mov edx, [ebp-0x20]
	mov [ebp-0x8c], edx
	mov eax, [ebp-0x90]
	mov edx, [ebp-0x8c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	test esi, esi
	jnz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160:
	mov edx, [ebp-0x20]
	mov dword [edx+0x98], 0x1
	mov [esp], edx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ecx, [ebp-0x20]
	cmp ebx, [ecx+0xcc]
	jz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
	mov [esp+0x4], ebx
	mov [esp], ecx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	mov edx, [ebp-0x20]
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150:
	mov eax, [ebp-0x1c]
	mov [ebp-0x80], eax
	mov [ebp-0x7c], edx
	mov eax, [ebp-0x80]
	mov edx, [ebp-0x7c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov edx, [ebp-0x24]
	mov [ebp-0x74], edx
	mov [ebp-0x78], edi
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x1c]
	mov [ebp-0x70], edx
	mov ecx, [ebp-0x20]
	mov [ebp-0x6c], ecx
	mov eax, [ebp-0x24]
	mov [ebp-0x64], eax
	mov [ebp-0x68], edi
	mov edx, [ebp-0x28]
	mov [esp+0x18], edx
	mov eax, [ebp-0x70]
	mov edx, [ebp-0x6c]
	mov [esp+0x10], eax
	mov [esp+0x14], edx
	mov edx, [ebp-0x68]
	mov ecx, [ebp-0x64]
	mov [esp+0x8], edx
	mov [esp+0xc], ecx
	mov ecx, [ebp-0x30]
	mov [esp+0x4], ecx
	mov eax, [ebp-0x34]
	mov [esp], eax
	call _Z24R_DrawXModelRigidSurfLitPK11GfxDrawSurfj16GfxCmdBufContextS2_PK19GfxDrawSurfListInfo
	add esp, 0xcc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	lea eax, [ecx+edx*8+0x118260]
	mov ebx, [eax]
	and ebx, 0x2
	mov eax, [eax+0x4]
	jmp _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov edx, [ebp-0x24]
	mov [ebp-0x5c], edx
	mov [ebp-0x60], edi
	mov eax, [ebp-0x60]
	mov edx, [ebp-0x5c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x24]
	mov [ebp-0x54], edx
	mov [ebp-0x58], edi
	mov ecx, [ebp-0x28]
	mov [esp+0x10], ecx
	mov eax, [ebp-0x58]
	mov edx, [ebp-0x54]
	mov [esp+0x8], eax
	mov [esp+0xc], edx
	mov edx, [ebp-0x30]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x34]
	mov [esp], ecx
	call _Z27R_DrawXModelRigidSurfCameraPK11GfxDrawSurfj16GfxCmdBufContextPK19GfxDrawSurfListInfo
	add esp, 0xcc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov [ebp-0x4c], esi
	mov [ebp-0x50], ebx
	mov eax, [ebp-0x50]
	mov edx, [ebp-0x4c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov edx, [ebp-0x24]
	mov dword [edx+0x98], 0x1
	mov [esp], esi
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ecx, [ebp-0x24]
	cmp dword [ecx+0xcc], 0xffffffff
	jz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
	mov dword [esp+0x4], 0xffffffff
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov [ebp-0x44], esi
	mov [ebp-0x48], ebx
	mov eax, [ebp-0x48]
	mov edx, [ebp-0x44]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov [ebp-0x3c], esi
	mov [ebp-0x40], ebx
	mov edx, [ebp-0x28]
	mov [esp+0x10], edx
	mov eax, [ebp-0x40]
	mov edx, [ebp-0x3c]
	mov [esp+0x8], eax
	mov [esp+0xc], edx
	mov edx, [ebp-0x30]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x34]
	mov [esp], ecx
	call _Z21R_DrawXModelRigidSurfPK11GfxDrawSurfj16GfxCmdBufContextPK19GfxDrawSurfListInfo
	add esp, 0xcc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov edx, [ebp-0x24]
	mov [ebp-0x94], edx
	mov [ebp-0x98], edi
	mov eax, [ebp-0x98]
	mov edx, [ebp-0x94]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	jmp _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	test dword [ebp-0xa8], 0x1f000000
	jz _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
	jmp _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	mov edx, ecx
	jmp _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150
_Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	mov edx, [ebp-0x1c]
	mov [ebp-0x88], edx
	mov ecx, [ebp-0x20]
	mov [ebp-0x84], ecx
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	jmp _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160


;R_TessXModelSkinnedDrawSurfList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x10c
	mov dword [ebp-0x80], 0x0
	mov dword [ebp-0x7c], 0x0
	mov dword [ebp-0x88], 0x0
	mov dword [ebp-0x84], 0x0
	mov dword [ebp-0x90], 0x0
	mov dword [ebp-0x8c], 0x0
	mov dword [ebp-0x98], 0x0
	mov dword [ebp-0x94], 0x0
	mov dword [ebp-0xa0], 0x0
	mov dword [ebp-0x9c], 0x0
	mov dword [ebp-0xa8], 0x0
	mov dword [ebp-0xa4], 0x0
	mov dword [ebp-0xb0], 0x0
	mov dword [ebp-0xac], 0x0
	mov dword [ebp-0xb8], 0x0
	mov dword [ebp-0xb4], 0x0
	mov dword [ebp-0xc0], 0x0
	mov dword [ebp-0xbc], 0x0
	mov dword [ebp-0xc8], 0x0
	mov dword [ebp-0xc4], 0x0
	mov dword [ebp-0xd0], 0x0
	mov dword [ebp-0xcc], 0x0
	mov dword [ebp-0xd8], 0x0
	mov dword [ebp-0xd4], 0x0
	mov dword [ebp-0xe0], 0x0
	mov dword [ebp-0xdc], 0x0
	mov dword [ebp-0xe8], 0x0
	mov dword [ebp-0xe4], 0x0
	mov dword [ebp-0xf0], 0x0
	mov dword [ebp-0xec], 0x0
	mov eax, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov [ebp-0x3c], edx
	mov ecx, [ebp+0x10]
	mov [ebp-0x40], ecx
	mov edx, [eax]
	mov ecx, [eax+0x4]
	mov [ebp-0xf8], edx
	mov [ebp-0xf4], ecx
	mov [ebp-0x48], ecx
	mov [ebp-0x44], edx
	mov ecx, [edx+0xca8]
	mov [ebp-0x54], ecx
	mov ebx, [eax+0xc]
	mov edx, [ebx+0x8]
	mov [ebp-0x50], edx
	mov edx, [eax+0x8]
	mov ecx, [ebx+0x4]
	sub ecx, edx
	mov [ebp-0x70], ecx
	mov eax, [ebx]
	lea edx, [eax+edx*8]
	mov [ebp-0x74], edx
	mov esi, [edx]
	mov edi, [edx+0x4]
	mov eax, [ebp-0x44]
	add eax, 0xf14
	mov edx, [ebp-0x44]
	cmp eax, [edx+0xf08]
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], eax
	mov ecx, [ebp-0xf8]
	mov [esp], ecx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov eax, [ebx+0x24]
	test eax, eax
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	movzx eax, si
	mov edx, [ebp-0x54]
	lea ebx, [edx+eax*4]
	movzx eax, word [ebx+0xe]
	movzx ecx, ax
	mov [ebp-0x20], ecx
	test ax, ax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
	mov dword [ebp-0x5c], 0x0
	pxor xmm0, xmm0
	movss [ebp-0x58], xmm0
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_290:
	movss [esp+0x4], xmm0
	mov eax, [ebp-0x44]
	mov [esp], eax
	call _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	mov [ebp-0x24], eax
	mov edx, [ebp-0x48]
	mov [ebp-0xec], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0xf0], ecx
	mov eax, [ebp-0xf0]
	mov edx, [ebp-0xec]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, [ebp-0x24]
	test eax, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_410:
	mov edx, [ebp-0x5c]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x44]
	mov [esp], ecx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov eax, [ebp-0x48]
	mov dword [eax+0x98], 0x1
	mov [esp], eax
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov ecx, [ebp-0x5c]
	mov edx, [ebp-0x48]
	cmp ecx, [edx+0xcc]
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov [esp+0x4], ecx
	mov [esp], edx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	cmp dword [ebp-0x50], 0x7
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
	mov eax, sc_enable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
	test esi, 0x1f000000
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_430:
	mov edx, [ebp-0x44]
	mov [edx+0xc60], eax
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_380:
	mov eax, [ebp-0x48]
	mov [ebp-0xdc], eax
	mov edx, [ebp-0x44]
	mov [ebp-0xe0], edx
	mov eax, [ebp-0xe0]
	mov edx, [ebp-0xdc]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov eax, [ebp-0x40]
	test eax, eax
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
	mov edx, [ebp-0x3c]
	mov [ebp-0xd8], edx
	mov ecx, [ebp-0x40]
	mov [ebp-0xd4], ecx
	mov eax, [ebp-0xd8]
	mov edx, [ebp-0xd4]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov ecx, [ebp-0x24]
	test ecx, ecx
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_440:
	mov edx, [ebp-0x40]
	mov dword [edx+0x98], 0x1
	mov [esp], edx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov eax, [ebp-0x5c]
	mov ecx, [ebp-0x40]
	cmp eax, [ecx+0xcc]
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
	mov [esp+0x4], eax
	mov [esp], ecx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	mov ecx, [ebp-0x40]
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov edx, [ebp-0x3c]
	mov [ebp-0xc8], edx
	mov [ebp-0xc4], ecx
	mov eax, [ebp-0xc8]
	mov edx, [ebp-0xc4]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x3c]
	mov [ebp-0xc0], edx
	mov ecx, [ebp-0x40]
	mov [ebp-0xbc], ecx
	mov eax, [ebp-0xc0]
	mov edx, [ebp-0xbc]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	mov dword [ebp-0x100], 0xffffffff
	mov dword [ebp-0xfc], 0xffffffff
	mov word [ebp-0x100], 0x0
	and dword [ebp-0x100], 0xff00ffff
	mov edx, [ebp-0x100]
	and edx, esi
	mov [ebp-0x30], edx
	mov ecx, [ebp-0xfc]
	and ecx, edi
	mov [ebp-0x2c], ecx
	mov dword [ebp-0x6c], 0x0
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170:
	mov edx, [ebp-0x40]
	test edx, edx
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
	mov eax, [ebp-0x3c]
	mov [ebp+0xc], eax
	mov edx, [ebp-0x40]
	mov [ebp+0x10], edx
	mov eax, [ebx]
	test eax, eax
	js _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130
	mov eax, [ebp+0xc]
	mov edx, [ebp+0x10]
	mov [esp+8], ebx
	mov [esp+4], edx
	mov [esp], eax
	call _Z25R_DrawXModelSkinnedCached16GfxCmdBufContextPK22GfxModelSkinnedSurface
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120:
	mov ecx, [ebp-0x44]
	mov [esp+0x4], ecx
	movzx eax, word [ebx+0x10]
	mov [esp], eax
	call _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	mov ecx, esi
	shr ecx, 0x10
	movzx eax, cl
	mov ecx, [ebp-0x48]
	mov [ebp-0xb4], ecx
	mov ecx, [ebp-0x44]
	mov [ebp-0xb8], ecx
	mov [esp+0x8], eax
	mov eax, [ebp-0xb8]
	mov edx, [ebp-0xb4]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	mov edx, [ebp-0x48]
	mov [ebp-0xac], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0xb0], ecx
	mov eax, [ebp-0xb0]
	mov edx, [ebp-0xac]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov edx, [ebp-0x48]
	mov [ebp-0xf4], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0xf8], ecx
	mov eax, [ebx]
	test eax, eax
	js _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140
	mov eax, [ebp-0xf8]
	mov edx, [ebp-0xf4]
	mov [esp+8], ebx
	mov [esp+4], edx
	mov [esp], eax
	call _Z25R_DrawXModelSkinnedCached16GfxCmdBufContextPK22GfxModelSkinnedSurface
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_400:
	add dword [ebp-0x6c], 0x1
	mov eax, [ebp-0x6c]
	cmp [ebp-0x70], eax
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150
	mov ecx, [ebp-0x74]
	mov esi, [ecx+eax*8]
	mov edi, [ecx+eax*8+0x4]
	mov eax, [ebp-0x100]
	and eax, esi
	mov edx, [ebp-0xfc]
	and edx, edi
	mov ecx, [ebp-0x2c]
	xor ecx, edx
	xor eax, [ebp-0x30]
	or ecx, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movzx eax, si
	mov edx, [ebp-0x54]
	lea ebx, [edx+eax*4]
	movzx eax, word [ebx+0xe]
	movzx edx, ax
	cmp [ebp-0x20], edx
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170
	test ax, ax
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180
	mov ecx, [ebp-0x54]
	lea edx, [ecx+edx*8+0x118260]
	mov eax, [edx]
	and eax, 0x2
	cmp [ebp-0x5c], eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movss xmm0, dword [ebp-0x58]
	ucomiss xmm0, [edx+0x4]
	jp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_390:
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160:
	mov eax, [ebp-0x6c]
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150:
	add esp, 0x10c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	movzx eax, si
	mov edx, [ebp-0x54]
	lea ebx, [edx+eax*4]
	movzx eax, word [ebx+0xe]
	movzx ecx, ax
	mov [ebp-0x60], ecx
	test ax, ax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_190
	pxor xmm0, xmm0
	movss [ebp-0x1c], xmm0
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_280:
	movss [esp+0x4], xmm0
	mov eax, [ebp-0x44]
	mov [esp], eax
	call _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	mov [ebp-0x4c], eax
	mov edx, [ebp-0x48]
	mov [ebp-0x94], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0x98], ecx
	mov eax, [ebp-0x98]
	mov edx, [ebp-0x94]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, [ebp-0x4c]
	test eax, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_200
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_420:
	mov dword [esp+0x4], 0x0
	mov edx, [ebp-0x44]
	mov [esp], edx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov ecx, [ebp-0x48]
	mov dword [ecx+0x98], 0x1
	mov [esp], ecx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov eax, [ebp-0x48]
	cmp dword [eax+0xcc], 0xffffffff
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_210
	mov dword [esp+0x4], 0xffffffff
	mov [esp], eax
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	mov edx, [ebp-0x48]
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_370:
	mov [ebp-0x84], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0x88], ecx
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x48]
	mov [ebp-0x7c], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0x80], ecx
	mov eax, [ebp-0x80]
	mov edx, [ebp-0x7c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov dword [ebp-0x100], 0xffffffff
	mov dword [ebp-0xfc], 0xffffffff
	mov word [ebp-0x100], 0x0
	and dword [ebp-0x100], 0xff00ffff
	and dword [ebp-0x100], 0xe0ffffff
	mov edx, [ebp-0x100]
	and edx, esi
	mov [ebp-0x68], edx
	mov ecx, [ebp-0xfc]
	and ecx, edi
	mov [ebp-0x64], ecx
	mov dword [ebp-0x6c], 0x0
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_240:
	mov eax, [ebp-0x48]
	mov [ebp-0xf4], eax
	mov edx, [ebp-0x44]
	mov [ebp-0xf8], edx
	mov edi, [ebx]
	test edi, edi
	js _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_260:
	mov eax, [ebp-0xf8]
	mov edx, [ebp-0xf4]
	mov [esp+8], ebx
	mov [esp+4], edx
	mov [esp], eax
	call _Z25R_DrawXModelSkinnedCached16GfxCmdBufContextPK22GfxModelSkinnedSurface
	add dword [ebp-0x6c], 0x1
	mov ecx, [ebp-0x6c]
	cmp [ebp-0x70], ecx
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_270:
	mov edx, [ebp-0x74]
	mov esi, [edx+ecx*8]
	mov edi, [edx+ecx*8+0x4]
	mov eax, [ebp-0x100]
	and eax, esi
	mov edx, [ebp-0xfc]
	and edx, edi
	mov ecx, [ebp-0x64]
	xor ecx, edx
	xor eax, [ebp-0x68]
	or ecx, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movzx eax, si
	mov ecx, [ebp-0x54]
	lea ebx, [ecx+eax*4]
	movzx eax, word [ebx+0xe]
	movzx edx, ax
	cmp [ebp-0x60], edx
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_240
	test ax, ax
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_250
	movss xmm0, dword [ebp-0x1c]
	ucomiss xmm0, [ecx+edx*8+0x118264]
	jp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_300:
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	mov eax, [ebp-0x48]
	mov [ebp-0xf4], eax
	mov edx, [ebp-0x44]
	mov [ebp-0xf8], edx
	mov edi, [ebx]
	test edi, edi
	jns _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_260
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220:
	mov eax, [ebx+0x14]
	mov ecx, [ebx+0x4]
	mov [esp+12], eax
	mov eax, [ebp-0xf8]
	mov edx, [ebp-0xf4]
	mov [esp+8], ecx
	mov [esp+4], edx
	mov [esp], eax
	call _Z27R_DrawXModelSkinnedUncached16GfxCmdBufContextP8XSurfaceP15GfxPackedVertex ;fixed
	add dword [ebp-0x6c], 0x1
	mov ecx, [ebp-0x6c]
	cmp [ebp-0x70], ecx
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_270
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230:
	mov eax, ecx
	add esp, 0x10c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_190:
	movss xmm0, dword [edx+ecx*8+0x118264]
	movss [ebp-0x1c], xmm0
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_280
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov edx, ecx
	mov ecx, [ebp-0x54]
	lea eax, [ecx+edx*8+0x118260]
	mov edx, [eax]
	and edx, 0x2
	mov [ebp-0x5c], edx
	movss xmm0, dword [eax+0x4]
	movss [ebp-0x58], xmm0
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_290
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_250:
	movss xmm0, dword [ebp-0x1c]
	ucomiss xmm0, [_float_0_00000000]
	jnp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_300
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov eax, [ebp-0x48]
	mov [ebp-0xa4], eax
	mov edx, [ebp-0x44]
	mov [ebp-0xa8], edx
	mov eax, [ebp-0xa8]
	mov edx, [ebp-0xa4]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x48]
	mov [ebp-0x9c], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0xa0], ecx
	mov eax, [ebp-0xa0]
	mov edx, [ebp-0x9c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov dword [ebp-0x100], 0xffffffff
	mov dword [ebp-0xfc], 0xffffffff
	mov word [ebp-0x100], 0x0
	and dword [ebp-0x100], 0xff00ffff
	and dword [ebp-0x100], 0xe0ffffff
	mov edx, [ebp-0x100]
	and edx, esi
	mov [ebp-0x38], edx
	mov ecx, [ebp-0xfc]
	and ecx, edi
	mov [ebp-0x34], ecx
	mov dword [ebp-0x6c], 0x0
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_320:
	mov eax, [ebp-0x48]
	mov [ebp-0xf4], eax
	mov edx, [ebp-0x44]
	mov [ebp-0xf8], edx
	mov eax, [ebx]
	test eax, eax
	js _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_310
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_340:
	mov eax, [ebp-0xf8]
	mov edx, [ebp-0xf4]
	mov [esp+8], ebx
	mov [esp+4], edx
	mov [esp], eax
	call _Z25R_DrawXModelSkinnedCached16GfxCmdBufContextPK22GfxModelSkinnedSurface
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_350:
	add dword [ebp-0x6c], 0x1
	mov ecx, [ebp-0x6c]
	cmp [ebp-0x70], ecx
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230
	mov edx, [ebp-0x74]
	mov esi, [edx+ecx*8]
	mov edi, [edx+ecx*8+0x4]
	mov eax, [ebp-0x100]
	and eax, esi
	mov edx, [ebp-0xfc]
	and edx, edi
	mov ecx, [ebp-0x34]
	xor ecx, edx
	xor eax, [ebp-0x38]
	or ecx, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movzx eax, si
	mov ecx, [ebp-0x54]
	lea ebx, [ecx+eax*4]
	movzx eax, word [ebx+0xe]
	movzx edx, ax
	cmp [ebp-0x20], edx
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_320
	test ax, ax
	jz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_330
	lea edx, [ecx+edx*8+0x118260]
	mov eax, [edx]
	and eax, 0x2
	cmp [ebp-0x5c], eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movss xmm0, dword [ebp-0x58]
	ucomiss xmm0, [edx+0x4]
	jp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_360:
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	mov eax, [ebp-0x48]
	mov [ebp-0xf4], eax
	mov edx, [ebp-0x44]
	mov [ebp-0xf8], edx
	mov eax, [ebx]
	test eax, eax
	jns _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_340
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_310:
	mov eax, [ebx+0x14]
	mov ecx, [ebx+0x4]
	mov [esp+12], eax
	mov eax, [ebp-0xf8]
	mov edx, [ebp-0xf4]
	mov [esp+8], ecx
	mov [esp+4], edx
	mov [esp], eax
	call _Z27R_DrawXModelSkinnedUncached16GfxCmdBufContextP8XSurfaceP15GfxPackedVertex
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_350
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_330:
	mov eax, [ebp-0x5c]
	test eax, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movss xmm0, dword [ebp-0x58]
	ucomiss xmm0, [_float_0_00000000]
	jnp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_360
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_210:
	mov edx, eax
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_370
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov eax, rgp
	mov eax, [eax+0x2008]
	mov ecx, [ebp-0x44]
	mov [ecx+0xc60], eax
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_380
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180:
	mov eax, [ebp-0x5c]
	test eax, eax
	jnz _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
	movss xmm0, dword [ebp-0x58]
	ucomiss xmm0, [_float_0_00000000]
	jnp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_390
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140:
	mov eax, [ebx+0x14]
	mov ecx, [ebx+0x4]
	mov [esp+12], eax
	mov eax, [ebp-0xf8]
	mov edx, [ebp-0xf4]
	mov [esp+8], ecx
	mov [esp+4], edx
	mov [esp], eax
	call _Z27R_DrawXModelSkinnedUncached16GfxCmdBufContextP8XSurfaceP15GfxPackedVertex
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_400
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130:
	mov eax, [ebx+0x14]
	mov ecx, [ebx+0x4]
	mov [esp+12], eax
	mov eax, [ebp+0xc]
	mov edx, [ebp+0x10]
	mov [esp+8], ecx
	mov [esp+4], edx
	mov [esp], eax
	call _Z27R_DrawXModelSkinnedUncached16GfxCmdBufContextP8XSurfaceP15GfxPackedVertex
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	mov edx, [ebp-0x48]
	mov [ebp-0xe4], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0xe8], ecx
	mov eax, [ebp-0xe8]
	mov edx, [ebp-0xe4]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_410
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_200:
	mov edx, [ebp-0x48]
	mov [ebp-0x8c], edx
	mov ecx, [ebp-0x44]
	mov [ebp-0x90], ecx
	mov eax, [ebp-0x90]
	mov edx, [ebp-0x8c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_420
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	mov eax, rgp
	mov eax, [eax+0x2008]
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_430
_Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	mov edx, [ebp-0x3c]
	mov [ebp-0xd0], edx
	mov ecx, [ebp-0x40]
	mov [ebp-0xcc], ecx
	mov eax, [ebp-0xd0]
	mov edx, [ebp-0xcc]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	jmp _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_440
	add [eax], al



;R_TessStaticModelSkinnedDrawSurfList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov dword [ebp-0x30], 0x0
	mov dword [ebp-0x2c], 0x0
	mov dword [ebp-0x38], 0x0
	mov dword [ebp-0x34], 0x0
	mov ecx, [ebp+0x8]
	mov esi, [ecx]
	mov edi, [ecx+0x4]
	mov [ebp-0x40], esi
	mov [ebp-0x3c], edi
	mov [ebp-0x1c], edi
	mov ebx, esi
	mov ecx, [ecx+0xc]
	mov [ebp-0x20], ecx
	mov [esp], esi
	mov [esp+0x4], edi
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov eax, [ebp-0x20]
	mov eax, [eax+0x8]
	mov [ebp-0x24], eax
	mov eax, s_manualObjectPlacement
	mov [esi+0xf08], eax
	mov dword [esp+0x4], 0x0
	mov [esp], esi
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov edx, [ebp-0x1c]
	mov dword [edx+0x98], 0x1
	mov [esp], edi
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov [ebp-0x3c], edi
	mov [ebp-0x40], esi
	cmp dword [esi+0xf34], 0x1
	sbb edx, edx
	cmp edx, [edi+0xcc]
	jz _Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov [esp+0x4], edx
	mov [esp], edi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov ecx, [ebx+0xca8]
	add ecx, 0x28000
	mov ebx, [ebp+0x8]
	mov edx, [ebx+0x8]
	mov ebx, [ebp-0x20]
	mov eax, [ebx]
	movzx eax, word [eax+edx*8]
	lea eax, [ecx+eax*4]
	cmp dword [ebp-0x24], 0x7
	jz _Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	mov [ebp-0x2c], edi
	mov [ebp-0x30], esi
	mov ecx, [ebp-0x30]
	mov ebx, [ebp-0x2c]
	mov [esp+0x4], ecx
	mov [esp+0x8], ebx
	mov [esp], eax
	call _Z28R_DrawStaticModelSkinnedSurfPKj16GfxCmdBufContext
	mov eax, 0x1
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov [ebp-0x34], edi
	mov [ebp-0x38], esi
	mov edx, [ebp-0x38]
	mov ecx, [ebp-0x34]
	mov [esp+0x4], edx
	mov [esp+0x8], ecx
	mov [esp], eax
	call _Z31R_DrawStaticModelSkinnedSurfLitPKj16GfxCmdBufContext
	mov eax, 0x1
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;R_TessXModelRigidSkinnedDrawSurfList(GfxDrawSurfListArgs const*, GfxCmdBufContext)
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xbc
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
	mov dword [ebp-0x90], 0x0
	mov dword [ebp-0x8c], 0x0
	mov dword [ebp-0x98], 0x0
	mov dword [ebp-0x94], 0x0
	mov eax, [ebp+0x8]
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov [ebp-0x28], esi
	mov [ebp-0x24], ebx
	mov edx, [ebx+0xca8]
	mov [ebp-0x38], edx
	mov ecx, [eax+0xc]
	mov [ebp-0x2c], ecx
	mov edx, [ecx+0x8]
	mov [ebp-0x34], edx
	mov edx, [eax+0x8]
	mov ecx, [ecx+0x4]
	sub ecx, edx
	mov [ebp-0x54], ecx
	mov ecx, [ebp-0x2c]
	mov eax, [ecx]
	lea edx, [eax+edx*8]
	mov [ebp-0x58], edx
	mov eax, [ecx+0x24]
	test eax, eax
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10
	mov ecx, esi
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230:
	mov dword [ecx+0x98], 0x1
	mov [esp], ecx
	call _Z18R_UpdateVertexDeclP14GfxCmdBufState
	mov dword [ebp-0xa0], 0xffffffff
	mov dword [ebp-0x9c], 0xffffffff
	mov word [ebp-0xa0], 0x0
	and dword [ebp-0xa0], 0xff00ffff
	and dword [ebp-0xa0], 0xe0ffffff
	mov dword [ebp-0xa8], 0xffffffff
	mov dword [ebp-0xa4], 0xffffffff
	mov word [ebp-0xa8], 0x0
	cmp dword [ebp-0x34], 0x7
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20
	and dword [ebp-0xa8], 0xff00ffff
	and dword [ebp-0xa8], 0xe0ffffff
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_20:
	mov eax, [ebp-0x58]
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov edx, [ebp-0xa0]
	and edx, ebx
	mov [ebp-0x50], edx
	mov ecx, [ebp-0x9c]
	and ecx, esi
	mov [ebp-0x4c], ecx
	mov dword [ebp-0x30], 0x1
	xor edx, edx
	cmp dword [ebp-0x34], 0x7
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180:
	mov eax, [ebp-0xa8]
	and eax, ebx
	mov [ebp-0x48], eax
	mov ecx, [ebp-0xa4]
	and ecx, esi
	mov [ebp-0x44], ecx
	mov eax, [ebp-0x58]
	lea eax, [eax+edx*8]
	mov [ebp-0x20], eax
	mov [ebp-0x1c], edx
	mov edx, [ebp-0x54]
	mov [ebp-0xac], edx
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130:
	mov [esp+0x4], eax
	mov [esp], ecx
	call _Z23R_ChangeObjectPlacementP20GfxCmdBufSourceStatePK18GfxScaledPlacement
	mov edx, [ebp-0x24]
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140:
	mov eax, [ebp-0x28]
	mov [ebp-0x74], eax
	mov [ebp-0x78], edx
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z24R_SetupPassPerObjectArgs16GfxCmdBufContext
	mov edx, [ebp-0x28]
	mov [ebp-0x6c], edx
	mov ecx, [ebp-0x24]
	mov [ebp-0x70], ecx
	mov eax, [ebp-0x70]
	mov edx, [ebp-0x6c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z22R_SetupPassPerPrimArgs16GfxCmdBufContext
	mov edx, [ebp-0x5c]
	mov ecx, [edx+0x4]
	mov eax, [ecx+0x1c]
	mov edx, [ebp-0x28]
	mov [ebp-0x64], edx
	mov edx, [ebp-0x24]
	mov [ebp-0x68], edx
	mov [esp+12], eax
	mov eax, [ebp-0x68]
	mov edx, [ebp-0x64]
	mov [esp+8], ecx
	mov [esp+4], edx
	mov [esp], eax
	call _Z27R_DrawXModelSkinnedUncached16GfxCmdBufContextP8XSurfaceP15GfxPackedVertex
	add dword [ebp-0x1c], 0x1
	mov ecx, [ebp-0xac]
	cmp [ebp-0x1c], ecx
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov eax, [ebp-0x20]
	mov ebx, [eax+0x8]
	mov esi, [eax+0xc]
	add eax, 0x8
	mov [ebp-0x20], eax
	mov eax, [ebp-0xa8]
	and eax, ebx
	mov edx, [ebp-0xa4]
	and edx, esi
	mov ecx, [ebp-0x44]
	xor ecx, edx
	xor eax, [ebp-0x48]
	or ecx, eax
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_40:
	movzx eax, bx
	mov ecx, [ebp-0x38]
	lea eax, [ecx+eax*4]
	mov [ebp-0x5c], eax
	mov eax, [ebp-0x2c]
	mov eax, [eax+0x24]
	test eax, eax
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70
	mov edx, [ebp-0x5c]
	movzx eax, word [edx+0xe]
	movzx edx, ax
	test ax, ax
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80
	mov dword [ebp-0x3c], 0x0
	xor eax, eax
	mov [esp+0x4], eax
	mov ecx, [ebp-0x24]
	mov [esp], ecx
	call _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	mov edi, eax
	mov eax, [ebp-0x30]
	or eax, edi
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150:
	test edi, edi
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160:
	mov edx, [ebp-0x3c]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x24]
	mov [esp], ecx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	cmp dword [ebp-0x34], 0x7
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170:
	mov ecx, [ebp-0x3c]
	mov edx, [ebp-0x28]
	cmp ecx, [edx+0xcc]
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120
	mov [esp+0x4], ecx
	mov [esp], edx
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_120:
	mov dword [ebp-0x30], 0x0
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_70:
	mov eax, [ebp-0x5c]
	add eax, 0x18
	mov ecx, [ebp-0x24]
	cmp eax, [ecx+0xf08]
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_130
	mov edx, ecx
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_140
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_80:
	mov ecx, [ebp-0x38]
	lea eax, [ecx+edx*8+0x118260]
	mov edx, [eax]
	and edx, 0x2
	mov [ebp-0x3c], edx
	mov eax, [eax+0x4]
	mov [esp+0x4], eax
	mov ecx, [ebp-0x24]
	mov [esp], ecx
	call _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	mov edi, eax
	mov eax, [ebp-0x30]
	or eax, edi
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_150
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_90:
	mov edx, [ebp-0x28]
	mov [ebp-0x8c], edx
	mov ecx, [ebp-0x24]
	mov [ebp-0x90], ecx
	mov eax, [ebp-0x90]
	mov edx, [ebp-0x8c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	test edi, edi
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_160
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_100:
	mov edx, [ebp-0x28]
	mov [ebp-0x84], edx
	mov ecx, [ebp-0x24]
	mov [ebp-0x88], ecx
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z27R_SetupPassVertexShaderArgs16GfxCmdBufContext
	mov edx, [ebp-0x3c]
	mov [esp+0x4], edx
	mov ecx, [ebp-0x24]
	mov [esp], ecx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	cmp dword [ebp-0x34], 0x7
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_110:
	mov eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov edx, [ebp-0x5c]
	movzx eax, word [edx+0x10]
	mov [esp], eax
	call _Z33R_SetModelLightingCoordsForSourcetP20GfxCmdBufSourceState
	mov ecx, ebx
	shr ecx, 0x10
	movzx eax, cl
	mov ecx, [ebp-0x28]
	mov [ebp-0x7c], ecx
	mov ecx, [ebp-0x24]
	mov [ebp-0x80], ecx
	mov [esp+0x8], eax
	mov eax, [ebp-0x80]
	mov edx, [ebp-0x7c]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z20R_SetReflectionProbe16GfxCmdBufContextj
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_170
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_60:
	mov eax, [ebp-0xa0]
	and eax, ebx
	mov edx, [ebp-0x9c]
	and edx, esi
	mov ecx, [ebp-0x4c]
	xor ecx, edx
	xor eax, [ebp-0x50]
	or ecx, eax
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50
	mov edx, [ebp-0x1c]
	cmp dword [ebp-0x34], 0x7
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_30:
	mov eax, sc_enable
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jnz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_190
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_200:
	mov eax, rgp
	mov eax, [eax+0x2008]
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_210:
	mov ecx, [ebp-0x24]
	mov [ecx+0xc60], eax
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_180
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_50:
	mov eax, [ebp-0x1c]
	add esp, 0xbc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_190:
	test ebx, 0x1f000000
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_200
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_210
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_10:
	mov [ebp-0x94], esi
	mov [ebp-0x98], ebx
	mov eax, [ebp-0x98]
	mov edx, [ebp-0x94]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z26R_SetupPassPixelShaderArgs16GfxCmdBufContext
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	mov edx, [ebp-0x28]
	cmp dword [edx+0xcc], 0xffffffff
	jz _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220
	mov dword [esp+0x4], 0xffffffff
	mov [esp], esi
	call _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	mov ecx, [ebp-0x28]
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230
_Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_220:
	mov ecx, edx
	jmp _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext_230
	nop


;Initialized global or static variables of rb_tess:
SECTION .data


;Initialized constant data of rb_tess:
SECTION .rdata
g_keepZ__uint4: dd 0x0, 0x0, 0xffffffff, 0x0
g_keepX__uint4: dd 0xffffffff, 0x0, 0x0, 0x0
g_keepZW__uint4: dd 0x0, 0x0, 0xffffffff, 0xffffffff
g_keepXY__uint4: dd 0xffffffff, 0xffffffff, 0x0, 0x0
g_keepXYZ__uint4: dd 0xffffffff, 0xffffffff, 0xffffffff, 0x0
g_keepXYW__uint4: dd 0xffffffff, 0xffffffff, 0x0, 0xffffffff
g_keepXZW__uint4: dd 0xffffffff, 0x0, 0xffffffff, 0xffffffff
g_keepYZW__uint4: dd 0x0, 0xffffffff, 0xffffffff, 0xffffffff
g_selectW__uint4: dd 0x10203, 0x4050607, 0x8090a0b, 0x1c1d1e1f
g_selectZ__uint4: dd 0x10203, 0x4050607, 0x18191a1b, 0xc0d0e0f
g_selectY__uint4: dd 0x10203, 0x14151617, 0x8090a0b, 0xc0d0e0f
g_selectX__uint4: dd 0x10111213, 0x4050607, 0x8090a0b, 0xc0d0e0f
g_swizzleWWWW__uint4: dd 0xc0d0e0f, 0xc0d0e0f, 0xc0d0e0f, 0xc0d0e0f
g_swizzleZZZZ__uint4: dd 0x8090a0b, 0x8090a0b, 0x8090a0b, 0x8090a0b
g_swizzleYYYY__uint4: dd 0x4050607, 0x4050607, 0x4050607, 0x4050607
g_swizzleXXXX__uint4: dd 0x10203, 0x10203, 0x10203, 0x10203
g_swizzleYZWA__uint4: dd 0x4050607, 0x8090a0b, 0xc0d0e0f, 0x10111213
g_swizzleZWAW__uint4: dd 0x8090a0b, 0xc0d0e0f, 0x10111213, 0xc0d0e0f
g_swizzleWABW__uint4: dd 0xc0d0e0f, 0x10111213, 0x14151617, 0xc0d0e0f
g_swizzleZXYW__uint4: dd 0x8090a0b, 0x10203, 0x4050607, 0xc0d0e0f
g_swizzleYZXW__uint4: dd 0x4050607, 0x8090a0b, 0x10203, 0xc0d0e0f
g_swizzleXYZA__uint4: dd 0x10203, 0x4050607, 0x8090a0b, 0x10111213
g_swizzleZWCD__uint4: dd 0x8090a0b, 0xc0d0e0f, 0x18191a1b, 0x1c1d1e1f
g_swizzleXYAB__uint4: dd 0x10203, 0x4050607, 0x10111213, 0x14151617
g_swizzleYBWD__uint4: dd 0x4050607, 0x14151617, 0xc0d0e0f, 0x1c1d1e1f
g_swizzleXAZC__uint4: dd 0x10203, 0x10111213, 0x8090a0b, 0x18191a1b
g_swizzleYXWZ__uint4: dd 0x4050607, 0x10203, 0xc0d0e0f, 0x8090a0b
g_swizzleXZYW__uint4: dd 0x10203, 0x8090a0b, 0x4050607, 0xc0d0e0f
g_swizzleYXZW__uint4: dd 0x4050607, 0x10203, 0x8090a0b, 0xc0d0e0f
g_swizzleXYZW__uint4: dd 0x10203, 0x4050607, 0x8090a0b, 0xc0d0e0f
g_inc__uint4: dd 0x1, 0x1, 0x1, 0x1
g_negativeZero__uint4: dd 0x80000000, 0x80000000, 0x80000000, 0x80000000
g_fltMin__uint4: dd 0x800000, 0x800000, 0x800000, 0x800000


;Zero initialized global or static variables of rb_tess:
SECTION .bss
g_keepZ: resb 0x10
g_keepX: resb 0x10
g_keepZW: resb 0x10
g_keepXY: resb 0x10
g_keepXYZ: resb 0x10
g_keepXYW: resb 0x10
g_keepXZW: resb 0x10
g_keepYZW: resb 0x10
g_selectW: resb 0x10
g_selectZ: resb 0x10
g_selectY: resb 0x10
g_selectX: resb 0x10
g_swizzleWWWW: resb 0x10
g_swizzleZZZZ: resb 0x10
g_swizzleYYYY: resb 0x10
g_swizzleXXXX: resb 0x10
g_swizzleYZWA: resb 0x10
g_swizzleZWAW: resb 0x10
g_swizzleWABW: resb 0x10
g_swizzleZXYW: resb 0x10
g_swizzleYZXW: resb 0x10
g_swizzleXYZA: resb 0x10
g_swizzleZWCD: resb 0x10
g_swizzleXYAB: resb 0x10
g_swizzleYBWD: resb 0x10
g_swizzleXAZC: resb 0x10
g_swizzleYXWZ: resb 0x10
g_swizzleXZYW: resb 0x10
g_swizzleYXZW: resb 0x10
g_swizzleXYZW: resb 0x10
g_inc: resb 0x10
g_negativeZero: resb 0x10
g_fltMin: resb 0x10


;All cstrings:
SECTION .rdata
_cstring_tree_chechnya_tr:		db "tree_chechnya_trunk_nml",0



;All constant floats and doubles:
SECTION .rdata
_float_0_00392157:		dd 0x3b808081	; 0.00392157
_float_0_00000000:		dd 0x0	; 0
_float_1_00000000:		dd 0x3f800000	; 1
_float_0_00100000:		dd 0x3a83126f	; 0.001

alignb 16
_data16_80000000:		dd 0x80000000, 0x0, 0x0, 0x0	; OWORD
