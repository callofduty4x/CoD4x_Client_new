;Imports of rb_backend:
	extern _Z17RB_EndTessSurfacev
	extern gfxCmdBufSourceState
	extern gfxRenderTargets
	extern gfxCmdBufContext
	extern _Z16Image_GetSurfaceP8GfxImage
	extern rgp
	extern gfxCmdBufState
	extern _Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport
	extern _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	extern _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	extern _Z15RB_TessOverflowv
	extern sinf
	extern cosf
	extern r_dx
	extern _Z7R_Set2DP20GfxCmdBufSourceState
	extern pow
	extern floorf
	extern _Z13R_GetDeviceIDv
	extern _Z13R_GetVendorIDv
	extern _Z18R_GetIsAntialiasedv
	extern rg
	extern memcpy
	extern _Z13R_CmdBufSet3DP20GfxCmdBufSourceState
	extern _Z7R_Set3DP20GfxCmdBufSourceState
	extern _Z21CL_ScaledMillisecondsv
	extern _Z19R_GetCharacterGlyphP6Font_sj
	extern _Z18R_WarnOncePerFrame14GfxWarningTypez
	extern _Z22SEH_ReadCharFromStringPPKcPi
	extern _Z21R_FontGetRandomLetterP6Font_si
	extern _Z12RandWithSeedPi
	extern _Z10ColorIndexh
	extern _Z15SEH_PrintStrlenPKc
	extern gfxBuf
	extern r_gamma
	extern r_ignoreHwGamma
	extern _Z18Dvar_ClearModifiedPK6dvar_s
	extern _Z18R_SetColorMappingsv
	extern _Z9Com_Error11errorParm_tPKcz
	extern _Z29R_SetDrawSurfsShadowableLightP20GfxCmdBufSourceStatePK19GfxDrawSurfListInfo
	extern pixelCostMode
	extern _Z26R_SkipDrawSurfListMaterialPK11GfxDrawSurfj
	extern _Z25R_ChangeDepthHackNearClipP20GfxCmdBufSourceStatej
	extern _Z18R_ChangeDepthRangeP14GfxCmdBufState17GfxDepthRangeType
	extern _Z22R_PixelCost_EndSurface16GfxCmdBufContext
	extern _Z11R_SetupPass16GfxCmdBufContextj
	extern _Z20R_UpdateMaterialTimeP20GfxCmdBufSourceStatef
	extern _Z24R_PixelCost_BeginSurface16GfxCmdBufContext
	extern _Z13R_GetViewportP20GfxCmdBufSourceStateP11GfxViewport
	extern _Z21R_GetCachedSModelSurfj
	extern _Z34XModelGetStaticModelCacheVertCountP6XModelj
	extern _Z18R_LockVertexBufferP22IDirect3DVertexBuffer9iii
	extern Com_Memcpy
	extern _Z20R_UnlockVertexBufferP22IDirect3DVertexBuffer9
	extern _Z21RB_PatchModelLightingPK21GfxModelLightingPatchj
	extern _Z19RB_UploadShaderStepv
	extern r_texFilterAnisoMax
	extern _Z19R_CheckDvarModifiedPK6dvar_s
	extern _Z14R_SetTexFilterv
	extern r_showPixelCost
	extern r_aaAlpha
	extern gfxMetrics
	extern _Z27R_SetAlphaAntiAliasingStateP16IDirect3DDevice9i
	extern _Z29R_PixelCost_PrintColorCodeKeyv
	extern r_texFilterDisable
	extern r_texFilterAnisoMin
	extern r_texFilterMipMode
	extern r_texFilterMipBias
	extern _Z13Vec2NormalizePf
	extern gfxCmdBufInput
	extern _Z14R_RegisterFontPKci
	extern _Z20RB_InitSceneViewportv
	extern _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	extern memset
	extern _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	extern _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	extern _Z23R_ClearAllStreamSourcesP18GfxCmdBufPrimState
	extern _Z21RB_IsGpuFenceFinishedv
	extern _Z21R_ReleaseGpuFenceLockv
	extern msecPerRawTimerTick
	extern _Z17RB_Draw3DInternalPK11GfxViewInfo
	extern _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z26R_TessTrianglesPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z23R_TessParticleCloudListPK19GfxDrawSurfListArgs16GfxCmdBufContext
	extern _Z16RB_SaveScreenCmdP25GfxRenderCommandExecState
	extern _Z16RB_StretchRawCmdP25GfxRenderCommandExecState


;Exports of rb_backend:
	global _GLOBAL__I_backEndData
	global RB_RenderCommandTable
	global _Z22RB_SetMaterialColorCmdP25GfxRenderCommandExecState
	global _Z23RB_SaveScreenSectionCmdP25GfxRenderCommandExecState
	global _Z17RB_ClearScreenCmdP25GfxRenderCommandExecState
	global _Z17RB_SetViewportCmdP25GfxRenderCommandExecState
	global _Z16RB_StretchPicCmdP25GfxRenderCommandExecState
	global _Z22RB_StretchPicCmdFlipSTP25GfxRenderCommandExecState
	global _Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState
	global _Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState
	global _Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState
	global _Z31RB_DrawFullScreenColoredQuadCmdP25GfxRenderCommandExecState
	global _Z16RB_DrawText2DCmdP25GfxRenderCommandExecState
	global _Z16RB_DrawText3DCmdP25GfxRenderCommandExecState
	global _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState
	global _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState
	global _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState
	global _Z15RB_DrawLinesCmdP25GfxRenderCommandExecState
	global _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState
	global _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState
	global rb_tessTable
	global _ZZ14RB_LookupColorhPhE11color_table
	global _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	global _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm
	global _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E10MY_OFFSETS
	global _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E25MY_ALTCOLOR_TWO_CINEMATIC
	global _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E15MY_ALTCOLOR_TWO
	global _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_
	global _Z13R_SetVertex2dP9GfxVertexffffm
	global _Z14RB_DrawLines2DiiPK14GfxPointVertex
	global _Z14RB_DrawLines3DiiPK14GfxPointVertexh
	global _Z14RB_LookupColorhPh
	global _Z14RB_SetIdentityv
	global _Z15RB_SetBspImagesv
	global _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	global _Z17RB_InitCodeImagesv
	global _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m
	global _Z19RB_FullScreenFilterPK8Material
	global _Z20RB_InitCodeConstantsv
	global _Z20RB_SplitScreenFilterPK8MaterialPK11GfxViewInfo
	global _Z20R_ShowDirtyDiscErrorv
	global _Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget
	global _Z23R_SetVertex4dWithNormalP9GfxVertexfffffffffPKh
	global _Z24RB_RegisterBackendAssetsv
	global _Z26RB_FullScreenColoredFilterPK8Materialm
	global _Z28RB_CallExecuteRenderCommandsv
	global _Z28RB_DrawFullScreenColoredQuadPK8Materialffffm
	global _Z28RB_ExecuteRenderCommandsLoopPKv
	global backEnd
	global backEndData
	global tess


SECTION .text


;RB_SetMaterialColorCmd(GfxRenderCommandExecState*)
_Z22RB_SetMaterialColorCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	mov esi, [ebp+0x8]
	mov ebx, [esi]
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z22RB_SetMaterialColorCmdP25GfxRenderCommandExecState_10
	call _Z17RB_EndTessSurfacev
_Z22RB_SetMaterialColorCmdP25GfxRenderCommandExecState_10:
	lea ecx, [ebx+0x4]
	mov edx, gfxCmdBufSourceState
	mov eax, [ebx+0x4]
	mov [edx+0xb00], eax
	mov eax, [ecx+0x4]
	mov [edx+0xb04], eax
	mov eax, [ecx+0x8]
	mov [edx+0xb08], eax
	mov eax, [ecx+0xc]
	mov [edx+0xb0c], eax
	add word [edx+0xe80], 0x1
	mov edx, [esi]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [esi], eax
	pop ebx
	pop esi
	pop ebp
	ret
	nop



;RB_SaveScreenSectionCmd(GfxRenderCommandExecState*)
_Z23RB_SaveScreenSectionCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	mov esi, [ebp+0x8]
	mov ebx, [esi]
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z23RB_SaveScreenSectionCmdP25GfxRenderCommandExecState_10
	call _Z17RB_EndTessSurfacev
_Z23RB_SaveScreenSectionCmdP25GfxRenderCommandExecState_10:
	mov ecx, [ebx+0x14]
	mov eax, gfxCmdBufSourceState
	mov edx, [eax+0xf3c]
	mov eax, rgp
	mov [eax+ecx*4+0x2100], edx
	mov edx, [esi]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [esi], eax
	pop ebx
	pop esi
	pop ebp
	ret


;RB_ClearScreenCmd(GfxRenderCommandExecState*)
_Z17RB_ClearScreenCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x24
	mov ebx, [ebp+0x8]
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z17RB_ClearScreenCmdP25GfxRenderCommandExecState_10
	call _Z17RB_EndTessSurfacev
_Z17RB_ClearScreenCmdP25GfxRenderCommandExecState_10:
	mov edx, [ebx]
	mov dword [esp+0x14], 0x0
	movzx eax, byte [edx+0x5]
	mov [esp+0x10], eax
	mov eax, [edx+0x8]
	mov [esp+0xc], eax
	lea eax, [edx+0xc]
	mov [esp+0x8], eax
	movzx eax, byte [edx+0x4]
	mov [esp+0x4], eax
	mov eax, gfxCmdBufState
	mov eax, [eax+0x90]
	mov [esp], eax
	call _Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x24
	pop ebx
	pop ebp
	ret
	nop


;RB_SetViewportCmd(GfxRenderCommandExecState*)
_Z17RB_SetViewportCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z17RB_SetViewportCmdP25GfxRenderCommandExecState_10
	call _Z17RB_EndTessSurfacev
_Z17RB_SetViewportCmdP25GfxRenderCommandExecState_10:
	mov eax, [ebx]
	add eax, 0x4
	mov [esp+0x4], eax
	mov eax, gfxCmdBufSourceState
	mov [esp], eax
	call _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret


;RB_StretchPicCmd(GfxRenderCommandExecState*)
_Z16RB_StretchPicCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x34
	mov ebx, [ebp+0x8]
	mov edx, [ebx]
	mov dword [esp+0x28], 0x7
	mov eax, [edx+0x28]
	mov [esp+0x24], eax
	mov eax, [edx+0x24]
	mov [esp+0x20], eax
	mov eax, [edx+0x20]
	mov [esp+0x1c], eax
	mov eax, [edx+0x1c]
	mov [esp+0x18], eax
	mov eax, [edx+0x18]
	mov [esp+0x14], eax
	mov eax, [edx+0x14]
	mov [esp+0x10], eax
	mov eax, [edx+0x10]
	mov [esp+0xc], eax
	mov eax, [edx+0xc]
	mov [esp+0x8], eax
	mov eax, [edx+0x8]
	mov [esp+0x4], eax
	mov eax, [edx+0x4]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x34
	pop ebx
	pop ebp
	ret


;RB_StretchPicCmdFlipST(GfxRenderCommandExecState*)
_Z22RB_StretchPicCmdFlipSTP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x34
	mov ebx, [ebp+0x8]
	mov edx, [ebx]
	mov dword [esp+0x28], 0x7
	mov eax, [edx+0x28]
	mov [esp+0x24], eax
	mov eax, [edx+0x24]
	mov [esp+0x20], eax
	mov eax, [edx+0x20]
	mov [esp+0x1c], eax
	mov eax, [edx+0x1c]
	mov [esp+0x18], eax
	mov eax, [edx+0x18]
	mov [esp+0x14], eax
	mov eax, [edx+0x14]
	mov [esp+0x10], eax
	mov eax, [edx+0x10]
	mov [esp+0xc], eax
	mov eax, [edx+0xc]
	mov [esp+0x8], eax
	mov eax, [edx+0x8]
	mov [esp+0x4], eax
	mov eax, [edx+0x4]
	mov [esp], eax
	call _Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x34
	pop ebx
	pop ebp
	ret


;RB_StretchPicRotateXYCmd(GfxRenderCommandExecState*)
_Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov eax, [ebp+0x8]
	mov esi, [eax]
	mov dword [esp+0x4], 0x4
	mov eax, [esi+0x4]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ecx, [tess+0x22a94c]
	lea eax, [ecx+0x4]
	cmp eax, 0x154a
	jg _Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState_10
	mov edx, [tess+0x22a948]
	lea eax, [edx+0x6]
	cmp eax, 0x100000
	jle _Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState_20
_Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState_10:
	call _Z15RB_TessOverflowv
	mov ecx, [tess+0x22a94c]
	mov edx, [tess+0x22a948]
_Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState_20:
	mov ebx, ecx
	lea eax, [ecx+0x4]
	mov [tess+0x22a94c], eax
	lea eax, [edx+0x6]
	mov [tess+0x22a948], eax
	lea eax, [ebx+0x3]
	mov [edx+edx+tess+0x2a940], ax
	mov [edx+edx+tess+0x2a942], cx
	lea eax, [ebx+0x2]
	mov [edx+edx+tess+0x2a944], ax
	mov [edx+edx+tess+0x2a946], ax
	mov [edx+edx+tess+0x2a948], cx
	lea eax, [ebx+0x1]
	mov [edx+edx+tess+0x2a94a], ax
	movss xmm1, dword [_float_0_50000000]
	movss xmm0, dword [esi+0x10]
	mulss xmm0, xmm1
	movss [ebp-0x38], xmm0
	mulss xmm1, [esi+0x14]
	addss xmm0, [esi+0x8]
	movss [ebp-0x40], xmm0
	movaps xmm0, xmm1
	addss xmm0, [esi+0xc]
	movss [ebp-0x3c], xmm0
	cvtss2sd xmm0, [esi+0x2c]
	mulsd xmm0, [_double_0_01745329]
	cvtsd2ss xmm0, xmm0
	movss [ebp-0x34], xmm0
	movss [esp], xmm0
	movss [ebp-0x58], xmm1
	call sinf
	fstp dword [ebp-0x44]
	movss xmm0, dword [ebp-0x34]
	movss [esp], xmm0
	call cosf
	fstp dword [ebp-0x5c]
	movss xmm2, dword [ebp-0x5c]
	movss xmm4, dword [ebp-0x38]
	mulss xmm4, xmm2
	movss xmm6, dword [ebp-0x38]
	mulss xmm6, [ebp-0x44]
	movss xmm1, dword [ebp-0x58]
	movaps xmm3, xmm1
	xorps xmm3, [_data16_80000000]
	mulss xmm3, [ebp-0x44]
	mulss xmm2, xmm1
	mov edi, [esi+0x28]
	movss xmm0, dword [esi+0x1c]
	movss [ebp-0x30], xmm0
	mov edx, [esi+0x18]
	movss xmm5, dword [ebp-0x3c]
	subss xmm5, xmm6
	movss xmm1, dword [ebp-0x40]
	subss xmm1, xmm4
	movzx ebx, bx
	shl ebx, 0x5
	lea eax, [ebx+tess]
	movaps xmm0, xmm1
	subss xmm0, xmm3
	movss [ebx+tess], xmm0
	movaps xmm0, xmm5
	subss xmm0, xmm2
	movss [eax+0x4], xmm0
	mov dword [eax+0x8], 0x0
	mov ecx, 0x3f800000
	mov [eax+0xc], ecx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], edi
	mov [eax+0x14], edx
	movss xmm0, dword [ebp-0x30]
	movss [eax+0x18], xmm0
	mov eax, [esi+0x28]
	mov [ebp-0x20], eax
	movss xmm0, dword [esi+0x1c]
	movss [ebp-0x2c], xmm0
	mov edi, [esi+0x20]
	addss xmm6, [ebp-0x3c]
	addss xmm4, [ebp-0x40]
	lea edx, [ebx+0x20]
	lea eax, [edx+tess]
	movaps xmm0, xmm4
	subss xmm0, xmm3
	movss [edx+tess], xmm0
	movaps xmm0, xmm6
	subss xmm0, xmm2
	movss [eax+0x4], xmm0
	mov dword [eax+0x8], 0x0
	mov [eax+0xc], ecx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x20]
	mov [eax+0x10], edx
	mov [eax+0x14], edi
	movss xmm0, dword [ebp-0x2c]
	movss [eax+0x18], xmm0
	mov eax, [esi+0x28]
	mov [ebp-0x1c], eax
	movss xmm0, dword [esi+0x24]
	mov edi, [esi+0x20]
	lea edx, [ebx+0x40]
	lea eax, [edx+tess]
	addss xmm4, xmm3
	movss [edx+tess], xmm4
	addss xmm6, xmm2
	movss [eax+0x4], xmm6
	mov dword [eax+0x8], 0x0
	mov [eax+0xc], ecx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x1c]
	mov [eax+0x10], edx
	mov [eax+0x14], edi
	movss [eax+0x18], xmm0
	mov edi, [esi+0x28]
	movss xmm0, dword [esi+0x24]
	mov edx, [esi+0x18]
	add ebx, 0x60
	lea eax, [ebx+tess]
	addss xmm3, xmm1
	movss [ebx+tess], xmm3
	addss xmm2, xmm5
	movss [eax+0x4], xmm2
	mov dword [eax+0x8], 0x0
	mov [eax+0xc], ecx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], edi
	mov [eax+0x14], edx
	movss [eax+0x18], xmm0
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;RB_StretchPicRotateSTCmd(GfxRenderCommandExecState*)
_Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov eax, [ebp+0x8]
	mov edi, [eax]
	mov dword [esp+0x4], 0x4
	mov eax, [edi+0x4]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov edx, [tess+0x22a94c]
	mov esi, edx
	mov ebx, [tess+0x22a948]
	mov ecx, ebx
	lea eax, [edx+0x4]
	cmp eax, 0x154a
	jg _Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState_10
	lea eax, [ebx+0x6]
	cmp eax, 0x100000
	jle _Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState_20
_Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState_10:
	call _Z15RB_TessOverflowv
	mov edx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
_Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState_20:
	lea eax, [edx+0x4]
	mov [tess+0x22a94c], eax
	lea eax, [ecx+0x6]
	mov [tess+0x22a948], eax
	lea eax, [esi+0x3]
	mov [ebx+ebx+tess+0x2a940], ax
	mov [ebx+ebx+tess+0x2a942], si
	lea eax, [esi+0x2]
	mov [ebx+ebx+tess+0x2a944], ax
	mov [ebx+ebx+tess+0x2a946], ax
	mov [ebx+ebx+tess+0x2a948], si
	lea eax, [esi+0x1]
	mov [ebx+ebx+tess+0x2a94a], ax
	cvtss2sd xmm0, [edi+0x30]
	mulsd xmm0, [_double_0_01745329]
	cvtsd2ss xmm0, xmm0
	movss [ebp-0x20], xmm0
	movss [esp], xmm0
	call sinf
	fstp dword [ebp-0x28]
	movss xmm2, dword [edi+0x20]
	movss xmm0, dword [ebp-0x20]
	movss [esp], xmm0
	movss [ebp-0x38], xmm2
	call cosf
	fstp dword [ebp-0x3c]
	movss xmm4, dword [ebp-0x3c]
	movss xmm2, dword [ebp-0x38]
	mulss xmm4, xmm2
	movss xmm1, dword [edi+0x24]
	movaps xmm5, xmm4
	mulss xmm5, xmm1
	movss xmm0, dword [edi+0x28]
	movss xmm3, dword [ebp-0x28]
	mulss xmm3, xmm2
	mulss xmm3, xmm0
	xorps xmm2, [_data16_80000000]
	mulss xmm2, [ebp-0x28]
	mulss xmm2, xmm1
	mulss xmm4, xmm0
	movss xmm1, dword [edi+0x18]
	movaps xmm6, xmm1
	subss xmm6, xmm5
	movss xmm0, dword [edi+0x1c]
	movaps xmm7, xmm0
	subss xmm7, xmm3
	addss xmm5, xmm1
	addss xmm3, xmm0
	mov eax, [edi+0x2c]
	mov [ebp-0x24], eax
	mov ebx, [edi+0xc]
	movzx ecx, si
	shl ecx, 0x5
	lea edx, [ecx+tess]
	mov eax, [edi+0x8]
	mov [ecx+tess], eax
	mov [edx+0x4], ebx
	mov dword [edx+0x8], 0x0
	mov esi, 0x3f800000
	mov [edx+0xc], esi
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebp-0x24]
	mov [edx+0x10], eax
	movaps xmm0, xmm6
	subss xmm0, xmm2
	movss [edx+0x14], xmm0
	movaps xmm0, xmm7
	subss xmm0, xmm4
	movss [edx+0x18], xmm0
	mov edx, [edi+0x2c]
	mov [ebp-0x1c], edx
	mov ebx, [edi+0xc]
	lea edx, [ecx+0x20]
	lea eax, [edx+tess]
	movss xmm0, dword [edi+0x8]
	addss xmm0, [edi+0x10]
	movss [edx+tess], xmm0
	mov [eax+0x4], ebx
	mov dword [eax+0x8], 0x0
	mov [eax+0xc], esi
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x1c]
	mov [eax+0x10], edx
	movaps xmm0, xmm5
	subss xmm0, xmm2
	movss [eax+0x14], xmm0
	movaps xmm0, xmm3
	subss xmm0, xmm4
	movss [eax+0x18], xmm0
	mov ebx, [edi+0x2c]
	movss xmm1, dword [edi+0xc]
	addss xmm1, [edi+0x14]
	lea edx, [ecx+0x40]
	lea eax, [edx+tess]
	movss xmm0, dword [edi+0x8]
	addss xmm0, [edi+0x10]
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm1
	mov dword [eax+0x8], 0x0
	mov [eax+0xc], esi
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], ebx
	addss xmm5, xmm2
	movss [eax+0x14], xmm5
	addss xmm3, xmm4
	movss [eax+0x18], xmm3
	mov ebx, [edi+0x2c]
	movss xmm0, dword [edi+0xc]
	addss xmm0, [edi+0x14]
	add ecx, 0x60
	lea eax, [ecx+tess]
	mov edx, [edi+0x8]
	mov [ecx+tess], edx
	movss [eax+0x4], xmm0
	mov dword [eax+0x8], 0x0
	mov [eax+0xc], esi
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], ebx
	addss xmm2, xmm6
	movss [eax+0x14], xmm2
	addss xmm4, xmm7
	movss [eax+0x18], xmm4
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;RB_DrawQuadPicCmd(GfxRenderCommandExecState*)
_Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov eax, [ebp+0x8]
	mov edi, [eax]
	mov dword [esp+0x4], 0x4
	mov eax, [edi+0x4]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ecx, [tess+0x22a94c]
	lea eax, [ecx+0x4]
	cmp eax, 0x154a
	jg _Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState_10
	mov edx, [tess+0x22a948]
	lea eax, [edx+0x6]
	cmp eax, 0x100000
	jle _Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState_20
_Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState_10:
	call _Z15RB_TessOverflowv
	mov ecx, [tess+0x22a94c]
	mov edx, [tess+0x22a948]
_Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState_20:
	mov ebx, ecx
	lea eax, [ebx+0x4]
	mov [tess+0x22a94c], eax
	lea eax, [edx+0x6]
	mov [tess+0x22a948], eax
	lea eax, [ecx+0x3]
	mov [edx+edx+tess+0x2a940], ax
	mov [edx+edx+tess+0x2a942], bx
	lea eax, [ecx+0x2]
	mov [edx+edx+tess+0x2a944], ax
	mov [edx+edx+tess+0x2a946], ax
	mov [edx+edx+tess+0x2a948], bx
	lea eax, [ecx+0x1]
	mov [edx+edx+tess+0x2a94a], ax
	mov edx, [edi+0x28]
	mov [ebp-0x2c], edx
	mov ebx, [edi+0xc]
	movzx ecx, cx
	shl ecx, 0x5
	lea eax, [ecx+tess]
	mov edx, [edi+0x8]
	mov [ecx+tess], edx
	mov [eax+0x4], ebx
	mov dword [eax+0x8], 0x0
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x2c]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x0
	mov dword [eax+0x18], 0x0
	mov eax, [edi+0x28]
	mov [ebp-0x24], eax
	movss xmm0, dword [edi+0x14]
	lea ebx, [ecx+0x20]
	lea eax, [ebx+tess]
	mov edx, [edi+0x10]
	mov [ebx+tess], edx
	movss [eax+0x4], xmm0
	mov dword [eax+0x8], 0x0
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x24]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x3f800000
	mov dword [eax+0x18], 0x0
	mov eax, [edi+0x28]
	mov [ebp-0x20], eax
	mov esi, [edi+0x1c]
	lea ebx, [ecx+0x40]
	lea eax, [ebx+tess]
	mov edx, [edi+0x18]
	mov [ebx+tess], edx
	mov [eax+0x4], esi
	mov dword [eax+0x8], 0x0
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x20]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x3f800000
	mov dword [eax+0x18], 0x3f800000
	mov eax, [edi+0x28]
	mov [ebp-0x1c], eax
	mov ebx, [edi+0x24]
	add ecx, 0x60
	lea eax, [ecx+tess]
	mov edx, [edi+0x20]
	mov [ecx+tess], edx
	mov [eax+0x4], ebx
	mov dword [eax+0x8], 0x0
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp-0x1c]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x0
	mov dword [eax+0x18], 0x3f800000
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;RB_DrawFullScreenColoredQuadCmd(GfxRenderCommandExecState*)
_Z31RB_DrawFullScreenColoredQuadCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov edx, [ebp+0x8]
	mov eax, [edx]
	mov edx, [eax+0x18]
	mov [ebp-0x28], edx
	movss xmm0, dword [eax+0x14]
	movss [ebp-0x24], xmm0
	movss xmm0, dword [eax+0x10]
	movss [ebp-0x20], xmm0
	mov edi, [eax+0xc]
	mov esi, [eax+0x8]
	mov eax, [eax+0x4]
	mov [ebp-0x1c], eax
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z31RB_DrawFullScreenColoredQuadCmdP25GfxRenderCommandExecState_10
	call _Z17RB_EndTessSurfacev
_Z31RB_DrawFullScreenColoredQuadCmdP25GfxRenderCommandExecState_10:
	mov ebx, gfxCmdBufSourceState
	mov [esp], ebx
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov dword [esp+0x28], 0x9
	mov eax, [ebp-0x28]
	mov [esp+0x24], eax
	movss xmm0, dword [ebp-0x24]
	movss [esp+0x20], xmm0
	movss xmm0, dword [ebp-0x20]
	movss [esp+0x1c], xmm0
	mov [esp+0x18], edi
	mov [esp+0x14], esi
	cvtsi2ss xmm0, dword [ebx+0xf6c]
	movss [esp+0x10], xmm0
	cvtsi2ss xmm0, dword [ebx+0xf68]
	movss [esp+0xc], xmm0
	xor eax, eax
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov eax, [ebp-0x1c]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;RB_DrawText2DCmd(GfxRenderCommandExecState*)
_Z16RB_DrawText2DCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x9c
	mov eax, [ebp+0x8]
	mov ebx, [eax]
	cvtss2sd xmm0, [ebx+0xc]
	mulsd xmm0, [_double_0_01745329]
	cvtsd2ss xmm0, xmm0
	movss [ebp-0x1c], xmm0
	movss [esp], xmm0
	call sinf
	fstp dword [ebp-0x40]
	movss xmm0, dword [ebp-0x1c]
	movss [esp], xmm0
	call cosf
	mov edx, [ebx+0x44]
	mov ecx, [ebx+0x40]
	mov esi, [ebx+0x3c]
	mov edi, [ebx+0x38]
	mov eax, [ebx+0x34]
	mov [ebp-0x3c], eax
	mov eax, [ebx+0x30]
	mov [ebp-0x38], eax
	movss xmm0, dword [ebx+0x4c]
	movsx eax, byte [ebx+0x2c]
	mov [ebp-0x30], eax
	mov eax, [ebx+0x28]
	mov [ebp-0x2c], eax
	mov eax, [ebx+0x24]
	mov [ebp-0x28], eax
	mov eax, [ebx+0x20]
	mov [ebp-0x24], eax
	mov eax, [ebx+0x1c]
	mov [ebp-0x20], eax
	mov eax, [ebx+0x48]
	mov [esp+0x50], eax
	mov [esp+0x4c], edx
	mov [esp+0x48], ecx
	mov [esp+0x44], esi
	mov [esp+0x40], edi
	mov edx, [ebp-0x3c]
	mov [esp+0x3c], edx
	mov eax, [ebp-0x38]
	mov [esp+0x38], eax
	movss [esp+0x34], xmm0
	mov edx, [ebp-0x30]
	mov [esp+0x30], edx
	mov eax, [ebp-0x2c]
	mov [esp+0x2c], eax
	mov edx, [ebp-0x28]
	mov [esp+0x28], edx
	mov eax, [ebp-0x24]
	mov [esp+0x24], eax
	mov edx, [ebp-0x20]
	mov [esp+0x20], edx
	fstp dword [esp+0x1c]
	movss xmm0, dword [ebp-0x40]
	movss [esp+0x18], xmm0
	mov eax, [ebx+0x18]
	mov [esp+0x14], eax
	mov eax, [ebx+0x14]
	mov [esp+0x10], eax
	mov eax, [ebx+0x10]
	mov [esp+0xc], eax
	mov eax, [ebx+0x8]
	mov [esp+0x8], eax
	mov eax, [ebx+0x4]
	mov [esp+0x4], eax
	add ebx, 0x50
	mov [esp], ebx
	call _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x9c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop
	add [eax], al


;RB_DrawText3DCmd(GfxRenderCommandExecState*)
_Z16RB_DrawText3DCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x24
	mov ebx, [ebp+0x8]
	mov eax, [ebx]
	mov edx, [eax+0x2c]
	mov [esp+0x14], edx
	lea edx, [eax+0x20]
	mov [esp+0x10], edx
	lea edx, [eax+0x14]
	mov [esp+0xc], edx
	lea edx, [eax+0x4]
	mov [esp+0x8], edx
	mov edx, [eax+0x10]
	mov [esp+0x4], edx
	add eax, 0x30
	mov [esp], eax
	call _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x24
	pop ebx
	pop ebp
	ret


;RB_BlendSavedScreenBlurredCmd(GfxRenderCommandExecState*)
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov edi, [ebp+0x8]
	mov ebx, [edi]
	mov eax, [tess+0x22a948]
	test eax, eax
	jnz _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_10
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_60:
	mov esi, gfxCmdBufSourceState
	mov ecx, rgp
	mov edx, [ebx+0x18]
	mov eax, [esi+0xf3c]
	sub eax, [ecx+edx*4+0x2100]
	js _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_20
	mov edx, [ebx+0x4]
	cmp eax, edx
	jl _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_30
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_20:
	mov edx, [edi]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [edi], eax
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_30:
	cvtsi2ss xmm0, eax
	cvtsi2ss xmm1, edx
	divss xmm0, xmm1
	cvtss2sd xmm0, xmm0
	movsd [esp+0x8], xmm0
	mov dword [esp], 0x40000000
	mov dword [esp+0x4], 0x3f847ae1
	call pow
	fstp qword [ebp-0x38]
	cvtsd2ss xmm0, [ebp-0x38]
	ucomiss xmm0, [_float_0_99000001]
	jbe _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_40
	movss xmm0, dword [_float_252_44999695]
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_70:
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x3c]
	cvttss2si eax, [ebp-0x3c]
	shl eax, 0x18
	or eax, 0xffffff
	mov [ebp-0x1c], eax
	cvtsi2ss xmm0, dword [esi+0xf68]
	movss [ebp-0x30], xmm0
	mulss xmm0, [ebx+0x10]
	movss [ebp-0x30], xmm0
	cvtsi2ss xmm0, dword [esi+0xf6c]
	movss [ebp-0x2c], xmm0
	mulss xmm0, [ebx+0x14]
	movss [ebp-0x2c], xmm0
	mov eax, gfxRenderTargets
	mov eax, [eax]
	mov [esi+0xc44], eax
	call _Z13R_GetDeviceIDv
	mov esi, eax
	call _Z13R_GetVendorIDv
	cmp eax, 0x10de
	jz _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_50
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_90:
	movss xmm2, dword [ebx+0x8]
	movss xmm1, dword [ebx+0xc]
	mov dword [esp+0x28], 0x9
	mov eax, [ebp-0x1c]
	mov [esp+0x24], eax
	movss [esp+0x20], xmm1
	movaps xmm0, xmm2
	addss xmm0, [ebx+0x10]
	movss [esp+0x1c], xmm0
	addss xmm1, [ebx+0x14]
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_100:
	movss [esp+0x18], xmm1
	movss [esp+0x14], xmm2
	movss xmm0, dword [ebp-0x2c]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x30]
	movss [esp+0xc], xmm0
	xor eax, eax
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov eax, rgp
	mov eax, [eax+0x20f0]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	mov edx, [edi]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [edi], eax
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_10:
	call _Z17RB_EndTessSurfacev
	jmp _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_60
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_40:
	mulss xmm0, [_float_255_00000000]
	jmp _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_70
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_50:
	cmp esi, 0x393
	jz _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_80
	cmp esi, 0x395
	jz _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_80
	cmp esi, 0x391
	jnz _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_90
_Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_80:
	call _Z18R_GetIsAntialiasedv
	test al, al
	jz _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_90
	movss xmm1, dword [ebx+0xc]
	movss xmm2, dword [ebx+0x8]
	mov dword [esp+0x28], 0x9
	mov eax, [ebp-0x1c]
	mov [esp+0x24], eax
	movaps xmm0, xmm1
	addss xmm0, [ebx+0x14]
	movss [esp+0x20], xmm0
	movaps xmm0, xmm2
	addss xmm0, [ebx+0x10]
	movss [esp+0x1c], xmm0
	jmp _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState_100
	nop


;RB_BlendSavedScreenFlashedCmd(GfxRenderCommandExecState*)
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov edi, [ebp+0x8]
	mov esi, [edi]
	mov eax, [tess+0x22a948]
	test eax, eax
	jnz _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_10
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_30:
	movss xmm1, dword [_float_255_00000000]
	movss xmm0, dword [esi+0x4]
	mulss xmm0, xmm1
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	movss [ebp-0x48], xmm1
	call floorf
	fstp dword [ebp-0x34]
	cvttss2si eax, [ebp-0x34]
	movzx eax, al
	mov ebx, eax
	shl ebx, 0x10
	mov edx, eax
	shl edx, 0x8
	or ebx, edx
	or ebx, eax
	movss xmm1, dword [ebp-0x48]
	mulss xmm1, [esi+0x8]
	addss xmm1, [_float_0_50000000]
	movss [esp], xmm1
	call floorf
	fstp dword [ebp-0x38]
	cvttss2si eax, [ebp-0x38]
	shl eax, 0x18
	or ebx, eax
	mov [ebp-0x1c], ebx
	mov edx, gfxCmdBufSourceState
	cvtsi2ss xmm0, dword [edx+0xf68]
	movss [ebp-0x30], xmm0
	mulss xmm0, [esi+0x14]
	movss [ebp-0x30], xmm0
	cvtsi2ss xmm0, dword [edx+0xf6c]
	movss [ebp-0x2c], xmm0
	mulss xmm0, [esi+0x18]
	movss [ebp-0x2c], xmm0
	mov eax, gfxRenderTargets
	mov eax, [eax]
	mov [edx+0xc44], eax
	call _Z13R_GetDeviceIDv
	mov ebx, eax
	call _Z13R_GetVendorIDv
	cmp eax, 0x10de
	jz _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_20
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_50:
	movss xmm2, dword [esi+0xc]
	movss xmm1, dword [esi+0x10]
	mov dword [esp+0x28], 0x9
	mov eax, [ebp-0x1c]
	mov [esp+0x24], eax
	movss [esp+0x20], xmm1
	movaps xmm0, xmm2
	addss xmm0, [esi+0x14]
	movss [esp+0x1c], xmm0
	addss xmm1, [esi+0x18]
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_60:
	movss [esp+0x18], xmm1
	movss [esp+0x14], xmm2
	movss xmm0, dword [ebp-0x2c]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x30]
	movss [esp+0xc], xmm0
	xor eax, eax
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov eax, rgp
	mov eax, [eax+0x20f4]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	mov edx, [edi]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [edi], eax
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_10:
	call _Z17RB_EndTessSurfacev
	jmp _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_30
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_20:
	cmp ebx, 0x393
	jz _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_40
	cmp ebx, 0x395
	jz _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_40
	cmp ebx, 0x391
	jnz _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_50
_Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_40:
	call _Z18R_GetIsAntialiasedv
	test al, al
	jz _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_50
	movss xmm1, dword [esi+0x10]
	movss xmm2, dword [esi+0xc]
	mov dword [esp+0x28], 0x9
	mov eax, [ebp-0x1c]
	mov [esp+0x24], eax
	movaps xmm0, xmm1
	addss xmm0, [esi+0x18]
	movss [esp+0x20], xmm0
	movaps xmm0, xmm2
	addss xmm0, [esi+0x14]
	movss [esp+0x1c], xmm0
	jmp _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState_60


;RB_DrawPointsCmd(GfxRenderCommandExecState*)
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x8c
	mov eax, [ebp+0x8]
	mov eax, [eax]
	mov [ebp-0x38], eax
	cmp byte [eax+0x7], 0x2
	jz _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_10
	mov dword [esp+0x4], 0x4
	mov eax, rgp
	mov eax, [eax+0x203c]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ebx, gfxCmdBufSourceState
	cmp dword [ebx+0xf38], 0x3
	jz _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_20
	mov eax, [tess+0x22a948]
	test eax, eax
	jnz _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_30
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_130:
	mov dword [ebx+0xf38], 0x3
	lea edx, [ebx+0xcb0]
	mov dword [esp+0x8], 0x140
	mov eax, rg
	mov [esp+0x4], eax
	mov [esp], edx
	call memcpy
	xor eax, eax
	mov [ebx+0xef4], eax
	mov [ebx+0xef8], eax
	mov [ebx+0xefc], eax
	mov dword [ebx+0xf00], 0x3f800000
	mov [esp], ebx
	call _Z13R_CmdBufSet3DP20GfxCmdBufSourceState
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_20:
	mov edx, [ebx+0xf0c]
	lea eax, [edx+0x80]
	mov [ebp-0x30], eax
	mov ecx, [ebp-0x38]
	movzx eax, byte [ecx+0x6]
	cvtsi2ss xmm1, eax
	cvtsi2ss xmm0, dword [ebx+0xf68]
	movaps xmm2, xmm1
	divss xmm2, xmm0
	movss [ebp-0x2c], xmm2
	cvtsi2ss xmm0, dword [ebx+0xf6c]
	divss xmm1, xmm0
	movss [ebp-0x28], xmm1
	mov ebx, ecx
	add ebx, 0x8
	cmp word [ecx+0x4], 0x0
	jle _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_40
	lea eax, [edx+0x90]
	mov [ebp-0x1c], eax
	lea edi, [edx+0xa0]
	lea esi, [edx+0xb0]
	mov dword [ebp-0x34], 0x0
	mov edx, [tess+0x22a94c]
	jmp _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_50
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_80:
	mov eax, [ebp-0x1c]
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_50:
	movss xmm3, dword [ebx]
	movss xmm1, dword [ebx+0x4]
	movss xmm2, dword [ebx+0x8]
	movaps xmm7, xmm3
	mov ecx, [ebp-0x30]
	mulss xmm7, [ecx]
	movaps xmm0, xmm1
	mulss xmm0, [eax]
	addss xmm7, xmm0
	movaps xmm0, xmm2
	mulss xmm0, [edi]
	addss xmm7, xmm0
	addss xmm7, [esi]
	movaps xmm5, xmm3
	mulss xmm5, [ecx+0x4]
	movaps xmm0, xmm1
	mulss xmm0, [eax+0x4]
	addss xmm5, xmm0
	movaps xmm0, xmm2
	mulss xmm0, [edi+0x4]
	addss xmm5, xmm0
	addss xmm5, [esi+0x4]
	movaps xmm6, xmm3
	mulss xmm6, [ecx+0x8]
	movaps xmm0, xmm1
	mulss xmm0, [eax+0x8]
	addss xmm6, xmm0
	movaps xmm0, xmm2
	mulss xmm0, [edi+0x8]
	addss xmm6, xmm0
	addss xmm6, [esi+0x8]
	movaps xmm4, xmm3
	mulss xmm4, [ecx+0xc]
	mulss xmm1, [eax+0xc]
	addss xmm4, xmm1
	mulss xmm2, [edi+0xc]
	addss xmm4, xmm2
	addss xmm4, [esi+0xc]
	movss xmm0, dword [ebp-0x2c]
	mulss xmm0, xmm4
	movss [ebp-0x20], xmm0
	movss xmm2, dword [ebp-0x28]
	mulss xmm2, xmm4
	movss [ebp-0x24], xmm2
	movaps xmm0, xmm4
	mulss xmm0, [_float__0_00100000]
	addss xmm6, xmm0
	lea eax, [edx+0x4]
	cmp eax, 0x154a
	jg _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_60
	mov ecx, [tess+0x22a948]
	lea eax, [ecx+0x6]
	cmp eax, 0x100000
	jle _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_70
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_60:
	movss [ebp-0x58], xmm4
	movss [ebp-0x68], xmm5
	movss [ebp-0x78], xmm6
	movss [ebp-0x88], xmm7
	call _Z15RB_TessOverflowv
	mov edx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
	movss xmm7, dword [ebp-0x88]
	movss xmm6, dword [ebp-0x78]
	movss xmm5, dword [ebp-0x68]
	movss xmm4, dword [ebp-0x58]
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_70:
	lea eax, [edx+0x3]
	mov [ecx+ecx+tess+0x2a940], ax
	mov [ecx+ecx+tess+0x2a942], dx
	lea eax, [edx+0x2]
	mov [ecx+ecx+tess+0x2a944], ax
	mov [ecx+ecx+tess+0x2a946], ax
	mov [ecx+ecx+tess+0x2a948], dx
	lea eax, [edx+0x1]
	mov [ecx+ecx+tess+0x2a94a], ax
	lea eax, [ecx+0x6]
	mov [tess+0x22a948], eax
	movaps xmm2, xmm5
	subss xmm2, [ebp-0x24]
	movaps xmm0, xmm7
	subss xmm0, [ebp-0x20]
	shl edx, 0x5
	lea eax, [edx+tess]
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm2
	movss [eax+0x8], xmm6
	movss [eax+0xc], xmm4
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebx+0xc]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x0
	mov dword [eax+0x18], 0x0
	movss xmm1, dword [ebp-0x24]
	addss xmm1, xmm5
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x20
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	movss [edx+0x8], xmm6
	movss [edx+0xc], xmm4
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x0
	mov dword [edx+0x18], 0x3f800000
	movss xmm0, dword [ebp-0x20]
	addss xmm0, xmm7
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x40
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	movss [edx+0x8], xmm6
	movss [edx+0xc], xmm4
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x3f800000
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x60
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm2
	movss [edx+0x8], xmm6
	movss [edx+0xc], xmm4
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x0
	mov eax, [tess+0x22a94c]
	add eax, 0x4
	mov edx, eax
	mov [tess+0x22a94c], eax
	add dword [ebp-0x34], 0x1
	add ebx, 0x10
	mov ecx, [ebp-0x38]
	movsx eax, word [ecx+0x4]
	cmp eax, [ebp-0x34]
	jg _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_80
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_40:
	call _Z17RB_EndTessSurfacev
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_90:
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_10:
	mov dword [esp+0x4], 0x4
	mov eax, rgp
	mov eax, [eax+0x2034]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov edx, [ebp-0x38]
	movzx eax, byte [edx+0x6]
	cvtsi2ss xmm2, eax
	mulss xmm2, [_float_0_50000000]
	mov ebx, edx
	add ebx, 0x8
	cmp word [edx+0x4], 0x0
	jle _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_90
	xor esi, esi
	mov edx, [tess+0x22a94c]
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_120:
	lea eax, [edx+0x4]
	cmp eax, 0x154a
	jg _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_100
	mov ecx, [tess+0x22a948]
	lea eax, [ecx+0x6]
	cmp eax, 0x100000
	jle _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_110
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_100:
	movss [ebp-0x48], xmm2
	call _Z15RB_TessOverflowv
	mov edx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
	movss xmm2, dword [ebp-0x48]
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_110:
	lea eax, [edx+0x1]
	mov [ecx+ecx+tess+0x2a940], ax
	mov [ecx+ecx+tess+0x2a942], dx
	lea eax, [edx+0x2]
	mov [ecx+ecx+tess+0x2a944], ax
	mov [ecx+ecx+tess+0x2a946], ax
	mov [ecx+ecx+tess+0x2a948], dx
	lea eax, [edx+0x3]
	mov [ecx+ecx+tess+0x2a94a], ax
	lea eax, [ecx+0x6]
	mov [tess+0x22a948], eax
	mov ecx, [ebx+0x8]
	movss xmm1, dword [ebx+0x4]
	subss xmm1, xmm2
	shl edx, 0x5
	lea eax, [edx+tess]
	movss xmm0, dword [ebx]
	subss xmm0, xmm2
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm1
	mov [eax+0x8], ecx
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebx+0xc]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x0
	mov dword [eax+0x18], 0x0
	mov ecx, [ebx+0x8]
	movaps xmm1, xmm2
	addss xmm1, [ebx+0x4]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x20
	lea edx, [eax+tess]
	movss xmm0, dword [ebx]
	subss xmm0, xmm2
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ecx
	mov dword [edx+0xc], 0x3f800000
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x0
	mov dword [edx+0x18], 0x3f800000
	mov ecx, [ebx+0x8]
	movaps xmm1, xmm2
	addss xmm1, [ebx+0x4]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x40
	lea edx, [eax+tess]
	movaps xmm0, xmm2
	addss xmm0, [ebx]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ecx
	mov dword [edx+0xc], 0x3f800000
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x3f800000
	mov ecx, [ebx+0x8]
	movss xmm1, dword [ebx+0x4]
	subss xmm1, xmm2
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x60
	lea edx, [eax+tess]
	movaps xmm0, xmm2
	addss xmm0, [ebx]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ecx
	mov dword [edx+0xc], 0x3f800000
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x0
	mov edx, [tess+0x22a94c]
	add edx, 0x4
	mov [tess+0x22a94c], edx
	add esi, 0x1
	add ebx, 0x10
	mov ecx, [ebp-0x38]
	movsx eax, word [ecx+0x4]
	cmp eax, esi
	jg _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_120
	mov eax, [ebp+0x8]
	mov edx, [eax]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov edx, [ebp+0x8]
	mov [edx], eax
	add esp, 0x8c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_30:
	call _Z17RB_EndTessSurfacev
	jmp _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState_130
	nop


;RB_DrawLinesCmd(GfxRenderCommandExecState*)
_Z15RB_DrawLinesCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov edx, [ebx]
	cmp byte [edx+0x7], 0x2
	jz _Z15RB_DrawLinesCmdP25GfxRenderCommandExecState_10
	mov dword [esp+0xc], 0x1
	lea eax, [edx+0x8]
	mov [esp+0x8], eax
	movzx eax, byte [edx+0x6]
	mov [esp+0x4], eax
	movsx eax, word [edx+0x4]
	mov [esp], eax
	call _Z14RB_DrawLines3DiiPK14GfxPointVertexh
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z15RB_DrawLinesCmdP25GfxRenderCommandExecState_10:
	lea eax, [edx+0x8]
	mov [esp+0x8], eax
	movzx eax, byte [edx+0x6]
	mov [esp+0x4], eax
	movsx eax, word [edx+0x4]
	mov [esp], eax
	call _Z14RB_DrawLines2DiiPK14GfxPointVertex
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret


;RB_DrawTrianglesCmd(GfxRenderCommandExecState*)
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x5c
	mov edx, [ebp+0x8]
	mov eax, [edx]
	movsx ecx, word [eax+0xe]
	mov [ebp-0x38], ecx
	shl ecx, 0x4
	add ecx, 0x10
	mov ebx, [ebp-0x38]
	lea edx, [ebx+ebx*2]
	lea edx, [ecx+edx*4]
	lea ebx, [edx+ebx*4]
	lea esi, [eax+0x10]
	mov [ebp-0x30], esi
	lea ecx, [eax+ecx]
	mov [ebp-0x2c], ecx
	lea edx, [eax+edx]
	mov [ebp-0x28], edx
	lea edx, [eax+ebx]
	mov [ebp-0x24], edx
	mov ecx, [ebp-0x38]
	lea edx, [ebx+ecx*8]
	lea edi, [eax+edx]
	movsx ebx, word [eax+0xc]
	mov [ebp-0x34], ebx
	mov esi, [eax+0x8]
	mov ebx, [eax+0x4]
	mov ecx, [tess+0x22a948]
	test ecx, ecx
	jnz _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_10
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_70:
	mov eax, gfxCmdBufSourceState
	mov [esp], eax
	call _Z7R_Set3DP20GfxCmdBufSourceState
	mov [esp+0x4], esi
	mov [esp], ebx
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ecx, [tess+0x22a94c]
	mov eax, [ebp-0x38]
	add eax, ecx
	cmp eax, 0x154a
	jg _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_20
	mov eax, [ebp-0x34]
	add eax, [tess+0x22a948]
	cmp eax, 0x100000
	jg _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_20
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_60:
	mov edx, [ebp-0x34]
	test edx, edx
	jle _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_30
	xor ebx, ebx
	mov esi, [tess+0x22a948]
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_40:
	lea edx, [ebx+esi]
	movzx eax, word [edi+ebx*2]
	add eax, ecx
	mov [edx+edx+tess+0x2a940], ax
	add ebx, 0x1
	cmp [ebp-0x34], ebx
	jnz _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_40
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_30:
	mov eax, [ebp-0x38]
	test eax, eax
	jg _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_50
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_100:
	mov ebx, [ebp-0x34]
	add [tess+0x22a948], ebx
	mov eax, [ebp-0x38]
	add eax, ecx
	mov [tess+0x22a94c], eax
	call _Z17RB_EndTessSurfacev
	mov esi, [ebp+0x8]
	mov edx, [esi]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [esi], eax
	add esp, 0x5c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_20:
	call _Z15RB_TessOverflowv
	mov ecx, [tess+0x22a94c]
	jmp _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_60
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_10:
	call _Z17RB_EndTessSurfacev
	jmp _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_70
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_50:
	mov esi, [ebp-0x28]
	mov [ebp-0x20], esi
	mov edi, [ebp-0x24]
	mov esi, [ebp-0x2c]
	mov ebx, [ebp-0x30]
	mov dword [ebp-0x1c], 0x0
	jmp _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_80
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_90:
	mov ecx, [tess+0x22a94c]
_Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_80:
	mov eax, [ebp-0x20]
	mov [esp+0x28], eax
	mov eax, [edi+0x4]
	mov [esp+0x24], eax
	mov eax, [edi]
	mov [esp+0x20], eax
	mov eax, [esi+0x8]
	mov [esp+0x1c], eax
	mov eax, [esi+0x4]
	mov [esp+0x18], eax
	mov eax, [esi]
	mov [esp+0x14], eax
	mov eax, [ebx+0xc]
	mov [esp+0x10], eax
	mov eax, [ebx+0x8]
	mov [esp+0xc], eax
	mov eax, [ebx+0x4]
	mov [esp+0x8], eax
	mov eax, [ebx]
	mov [esp+0x4], eax
	mov eax, [ebp-0x1c]
	add eax, ecx
	shl eax, 0x5
	add eax, tess
	mov [esp], eax
	call _Z23R_SetVertex4dWithNormalP9GfxVertexfffffffffPKh
	add dword [ebp-0x1c], 0x1
	add dword [ebp-0x20], 0x4
	add edi, 0x8
	add esi, 0xc
	add ebx, 0x10
	mov edx, [ebp-0x1c]
	cmp [ebp-0x38], edx
	jnz _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_90
	mov ecx, [tess+0x22a94c]
	jmp _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState_100
	nop


;RB_ProjectionSetCmd(GfxRenderCommandExecState*)
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov edx, [ebx]
	mov eax, [edx+0x4]
	test eax, eax
	jz _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_10
	sub eax, 0x1
	jz _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_20
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_10:
	mov eax, [tess+0x22a948]
	test eax, eax
	jnz _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_30
	mov eax, gfxCmdBufSourceState
	mov [esp], eax
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov edx, [ebx]
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_40:
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_30:
	call _Z17RB_EndTessSurfacev
	mov eax, gfxCmdBufSourceState
	mov [esp], eax
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov edx, [ebx]
	jmp _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_40
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_20:
	mov eax, [tess+0x22a948]
	test eax, eax
	jnz _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_50
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_60:
	mov eax, gfxCmdBufSourceState
	mov [esp], eax
	call _Z7R_Set3DP20GfxCmdBufSourceState
	mov edx, [ebx]
	movzx eax, word [edx+0x2]
	add eax, edx
	mov [ebx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_50:
	call _Z17RB_EndTessSurfacev
	jmp _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState_60
	nop


;RB_DrawStretchPicRotate(Material const*, float, float, float, float, float, float, float, float, float, float, unsigned long, GfxPrimStatsTarget)
_Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x2c
	movss [ebp-0x1c], xmm0
	movss [ebp-0x20], xmm1
	movss [ebp-0x24], xmm2
	movss [ebp-0x28], xmm3
	mov edi, edx
	mov dword [esp+0x4], 0x4
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ecx, [tess+0x22a94c]
	lea eax, [ecx+0x4]
	cmp eax, 0x154a
	jg _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget_10
	mov edx, [tess+0x22a948]
	lea eax, [edx+0x6]
	cmp eax, 0x100000
	jle _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget_20
_Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget_10:
	call _Z15RB_TessOverflowv
	mov ecx, [tess+0x22a94c]
	mov edx, [tess+0x22a948]
_Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget_20:
	mov ebx, ecx
	lea eax, [ebx+0x4]
	mov [tess+0x22a94c], eax
	lea eax, [edx+0x6]
	mov [tess+0x22a948], eax
	lea eax, [ecx+0x3]
	mov [edx+edx+tess+0x2a940], ax
	mov [edx+edx+tess+0x2a942], bx
	lea eax, [ecx+0x2]
	mov [edx+edx+tess+0x2a944], ax
	mov [edx+edx+tess+0x2a946], ax
	mov [edx+edx+tess+0x2a948], bx
	lea eax, [ecx+0x1]
	mov [edx+edx+tess+0x2a94a], ax
	movss xmm2, dword [ebp-0x28]
	xorps xmm2, [_data16_80000000]
	mulss xmm2, [ebp+0x18]
	movss xmm3, dword [ebp+0x1c]
	mulss xmm3, [ebp-0x28]
	movzx ecx, cx
	shl ecx, 0x5
	lea eax, [ecx+tess]
	movss xmm0, dword [ebp-0x1c]
	movss [ecx+tess], xmm0
	movss xmm4, dword [ebp-0x20]
	movss [eax+0x4], xmm4
	xor esi, esi
	mov [eax+0x8], esi
	mov ebx, 0x3f800000
	mov [eax+0xc], ebx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], edi
	movss xmm0, dword [ebp+0x8]
	movss [eax+0x14], xmm0
	movss xmm4, dword [ebp+0xc]
	movss [eax+0x18], xmm4
	movss xmm1, dword [ebp-0x24]
	mulss xmm1, [ebp+0x18]
	addss xmm1, [ebp-0x20]
	movss xmm0, dword [ebp-0x24]
	mulss xmm0, [ebp+0x1c]
	addss xmm0, [ebp-0x1c]
	lea edx, [ecx+0x20]
	lea eax, [edx+tess]
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm1
	mov [eax+0x8], esi
	mov [eax+0xc], ebx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], edi
	movss xmm4, dword [ebp+0x10]
	movss [eax+0x14], xmm4
	movss xmm4, dword [ebp+0xc]
	movss [eax+0x18], xmm4
	lea edx, [ecx+0x40]
	lea eax, [edx+tess]
	addss xmm0, xmm2
	movss [edx+tess], xmm0
	addss xmm1, xmm3
	movss [eax+0x4], xmm1
	mov [eax+0x8], esi
	mov [eax+0xc], ebx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], edi
	movss xmm0, dword [ebp+0x10]
	movss [eax+0x14], xmm0
	movss xmm4, dword [ebp+0x14]
	movss [eax+0x18], xmm4
	add ecx, 0x60
	lea eax, [ecx+tess]
	addss xmm2, [ebp-0x1c]
	movss [ecx+tess], xmm2
	addss xmm3, [ebp-0x20]
	movss [eax+0x4], xmm3
	mov [eax+0x8], esi
	mov [eax+0xc], ebx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], edi
	movss xmm0, dword [ebp+0x8]
	movss [eax+0x14], xmm0
	movss [eax+0x18], xmm4
	add esp, 0x2c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;RB_DrawCursor(Material const*, unsigned char, float, float, float, float, Font_s*, float, float, unsigned long)
_Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov edi, eax
	movss [ebp-0x1c], xmm0
	movss [ebp-0x20], xmm1
	movss [ebp-0x24], xmm2
	movss [ebp-0x28], xmm3
	mov esi, ecx
	movss xmm0, dword [ebp+0x8]
	movss [ebp-0x2c], xmm0
	movss xmm0, dword [ebp+0xc]
	movss [ebp-0x30], xmm0
	mov eax, [ebp+0x10]
	mov [ebp-0x34], eax
	mov ebx, edx
	call _Z21CL_ScaledMillisecondsv
	lea edx, [eax+0xff]
	cmp eax, 0xffffffff
	cmovle eax, edx
	test ah, 0x1
	jnz _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_10
	movzx eax, bl
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z19R_GetCharacterGlyphP6Font_sj
	mov edx, eax
	movzx eax, byte [eax+0x6]
	cvtsi2ss xmm3, eax
	mulss xmm3, [ebp-0x30]
	movzx eax, byte [edx+0x5]
	cvtsi2ss xmm2, eax
	mulss xmm2, [ebp-0x2c]
	movsx eax, byte [edx+0x3]
	cvtsi2ss xmm1, eax
	mulss xmm1, [ebp-0x30]
	addss xmm1, [ebp-0x20]
	mov eax, [edi+0x40]
	mov eax, [eax+0x8]
	mov ecx, [eax+0x28]
	test ecx, ecx
	jz _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_20
_Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_40:
	mov eax, 0x1
_Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_50:
	test eax, eax
	jz _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_30
	mov eax, [edi]
	mov [ebp+0xc], eax
	mov dword [ebp+0x8], 0x26
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	jmp _Z18R_WarnOncePerFrame14GfxWarningTypez
_Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_30:
	movss xmm0, dword [ebp-0x28]
	movss [esp+0x14], xmm0
	movss xmm0, dword [ebp-0x24]
	movss [esp+0x10], xmm0
	mov eax, [edx+0x14]
	mov [esp+0xc], eax
	mov eax, [edx+0x10]
	mov [esp+0x8], eax
	mov eax, [edx+0xc]
	mov [esp+0x4], eax
	mov eax, [edx+0x8]
	mov [esp], eax
	mov ecx, 0x7
	mov edx, [ebp-0x34]
	movss xmm0, dword [ebp-0x1c]
	mov eax, edi
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
_Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_10:
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_20:
	mov eax, [eax+0x20]
	test eax, eax
	jnz _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_40
	xor eax, eax
	jmp _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm_50


;DrawText2D(char const*, float, float, Font_s*, float, float, float, float, GfxColor, int, int, int, char, float, GfxColor, int, int, int, int, Material const*, Material const*)
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x12c
	mov esi, [ebp+0x30]
	movzx eax, byte [ebp+0x38]
	mov [ebp-0xe9], al
	mov edx, [ebp+0x28]
	shr edx, 0x18
	mov [ebp-0xe8], dl
	mov eax, edx
	shl eax, 0x18
	mov [ebp-0xf0], eax
	mov edx, esi
	and dl, 0x1
	mov [ebp-0x85], dl
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__10
	pxor xmm0, xmm0
	movss [ebp-0xb4], xmm0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__790:
	mov eax, [ebp+0x14]
	mov eax, [eax+0xc]
	mov [ebp-0xb0], eax
	test esi, 0x40
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__20
	mov dword [ebp-0xa4], 0x1
	mov byte [ebp-0xa5], 0x0
	mov byte [ebp-0x9d], 0x0
	mov dword [ebp-0x9c], 0x0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__780:
	test esi, 0x10
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__30
	mov dword [ebp-0xac], 0x0
	mov dword [ebp-0x90], 0x1
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__320:
	movss xmm0, dword [_float__0_50000000]
	movss xmm1, dword [ebp+0x18]
	mulss xmm1, xmm0
	addss xmm1, [ebp+0xc]
	movss [ebp-0x98], xmm1
	movss xmm2, dword [ebp+0x1c]
	mulss xmm2, xmm0
	addss xmm2, [ebp+0x10]
	movss [ebp-0x94], xmm2
	mov edx, [ebp-0x90]
	test edx, edx
	jle _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__40
	mov eax, esi
	shr eax, 1
	and eax, 0x1
	mov [ebp-0xbc], eax
	mov edx, esi
	shr edx, 0x7
	and edx, 0x1
	mov [ebp-0xcc], edx
	movss xmm0, dword [ebp+0x18]
	mulss xmm0, [ebp+0x3c]
	movss [ebp-0xc8], xmm0
	movss xmm1, dword [ebp-0xb4]
	mulss xmm1, [ebp+0x18]
	movss [ebp-0xb8], xmm1
	mov eax, esi
	shr eax, 0x8
	and eax, 0x1
	mov [ebp-0xd4], eax
	mov edx, esi
	shr edx, 0x5
	and edx, 0x1
	mov [ebp-0x5c], edx
	shr esi, 0x2
	mov edi, esi
	and edi, 0x1
	mov [ebp-0xc4], edi
	shr esi, 1
	mov eax, esi
	and eax, 0x1
	mov [ebp-0xc0], eax
	cvtsi2ss xmm0, dword [ebp+0x50]
	divss xmm0, dword [_float_1000_00000000]
	mulss xmm0, [_float_30_00000000]
	cvttss2si edx, xmm0
	mov [ebp-0x68], edx
	shr esi, 0x6
	mov [ebp-0xd0], esi
	and dword [ebp-0xd0], 0x1
	mov dword [ebp-0x8c], 0x0
	movzx edi, byte [ebp-0xe9]
	mov [ebp-0xfc], edi
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__150:
	mov eax, [ebp-0xa4]
	mov [ebp-0x24], eax
	mov edx, [ebp+0x28]
	mov [ebp-0x20], edx
	mov eax, [ebp+0x8]
	mov [ebp-0x1c], eax
	movss xmm0, dword [ebp-0x98]
	movss [ebp-0x3c], xmm0
	movss xmm1, dword [ebp-0x94]
	movss [ebp-0x40], xmm1
	mov edx, [ebp+0x2c]
	mov [ebp-0x84], edx
	mov byte [ebp-0x7c], 0x0
	mov dword [ebp-0x80], 0x0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__310:
	cmp byte [eax], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__50
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__120:
	mov esi, [ebp-0x84]
	test esi, esi
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__50
	mov dword [esp+0x4], 0x0
	lea eax, [ebp-0x1c]
	mov [esp], eax
	call _Z22SEH_ReadCharFromStringPPKcPi
	mov ebx, eax
	cmp eax, 0x5e
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__60
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__430:
	cmp byte [ebp-0xa5], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__70
	cmp dword [ebp-0x84], 0x1
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__80
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__70:
	mov byte [ebp-0x7a], 0x0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__680:
	cmp ebx, 0x5e
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__90
	cmp ebx, 0xa
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__100
	cmp ebx, 0xd
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__110
	movss xmm1, dword [ebp-0x98]
	movss [ebp-0x3c], xmm1
	mov eax, [ebp-0x1c]
	cmp byte [eax], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__120
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__50:
	mov ebx, [ebp-0xbc]
	test ebx, ebx
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__130
	mov eax, [ebp-0x80]
	cmp [ebp+0x34], eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__140
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__130:
	add dword [ebp-0x8c], 0x1
	mov eax, [ebp-0x8c]
	cmp [ebp-0x90], eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__150
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__40:
	add esp, 0x12c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__80:
	mov eax, [ebp-0x24]
	mov [esp+0x4], eax
	mov eax, [ebp+0x14]
	mov [esp], eax
	call _Z21R_FontGetRandomLetterP6Font_si
	mov ebx, eax
	lea eax, [ebp-0x24]
	mov [esp], eax
	call _Z12RandWithSeedPi
	test al, 0x1
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__160
	mov byte [ebp-0x7a], 0xc0
	mov byte [ebp-0x79], 0x1
	mov ebx, 0x4f
	cmp byte [ebp-0x9d], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__170
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__330:
	mov esi, ebx
	mov byte [ebp-0x7b], 0x0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__550:
	cmp byte [ebp-0x79], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__180
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__360:
	mov dword [ebp-0x78], 0x0
	mov [esp+0x4], esi
	mov edx, [ebp+0x14]
	mov [esp], edx
	call _Z19R_GetCharacterGlyphP6Font_sj
	mov edi, eax
	cmp esi, ebx
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__190
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__370:
	mov [esp+0x4], ebx
	mov eax, [ebp+0x14]
	mov [esp], eax
	call _Z19R_GetCharacterGlyphP6Font_sj
	movzx edx, byte [eax+0x5]
	cvtsi2ss xmm1, edx
	mulss xmm1, [_float_0_50000000]
	movzx edx, byte [edi+0x5]
	cvtsi2ss xmm0, edx
	mulss xmm0, [_float__0_50000000]
	addss xmm1, xmm0
	movzx eax, byte [eax+0x4]
	cvtsi2ss xmm0, eax
	movss [ebp-0x74], xmm0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__380:
	movsx eax, byte [edi+0x2]
	cvtsi2ss xmm2, eax
	addss xmm2, xmm1
	mulss xmm2, [ebp+0x18]
	movsx eax, byte [edi+0x3]
	cvtsi2ss xmm3, eax
	mulss xmm3, [ebp+0x1c]
	mov ebx, [ebp-0x20]
	cmp byte [ebp-0x9d], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__200
	cmp byte [ebp-0xa5], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__210
	cmp dword [ebp-0x84], 0x1
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__200
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__210:
	cmp byte [ebp-0x7b], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220
	mov eax, [ebp-0x8c]
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__230
	mov eax, [ebp-0xc4]
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__240
	addss xmm2, [ebp-0x3c]
	movss [ebp-0x48], xmm2
	addss xmm3, [ebp-0x40]
	movss [ebp-0x44], xmm3
	movaps xmm1, xmm3
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__640:
	subss xmm2, [ebp-0x98]
	movss xmm4, dword [ebp+0x24]
	mulss xmm4, xmm2
	movss xmm0, dword [ebp-0x98]
	addss xmm0, xmm4
	movss [ebp-0x64], xmm0
	subss xmm1, [ebp-0x94]
	movss xmm0, dword [ebp+0x20]
	mulss xmm0, xmm1
	movss xmm5, dword [ebp-0x64]
	subss xmm5, xmm0
	mulss xmm2, [ebp+0x20]
	movss [ebp-0x60], xmm2
	movss xmm4, dword [ebp+0x24]
	mulss xmm4, xmm1
	addss xmm4, [ebp-0x94]
	addss xmm4, xmm2
	cmp byte [ebp-0x79], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__250
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm3, eax
	mulss xmm3, [ebp+0x1c]
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm2, eax
	mulss xmm2, [ebp+0x18]
	mov edx, [ebp-0xb0]
	mov eax, [edx+0x40]
	mov eax, [eax+0x8]
	mov edx, [eax+0x28]
	test edx, edx
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__260
	mov eax, [eax+0x20]
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__260
	xor eax, eax
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__270
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__580:
	mov edi, [ebp-0xb0]
	mov eax, [edi]
	mov [esp+0x4], eax
	mov dword [esp], 0x26
	call _Z18R_WarnOncePerFrame14GfxWarningTypez
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__590:
	mov edi, [ebp-0xbc]
	test edi, edi
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220
	mov eax, [ebp-0x80]
	cmp [ebp+0x34], eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__280
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220:
	cmp byte [ebp-0x85], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__290
	movss xmm2, dword [ebp-0x3c]
	addss xmm2, [ebp-0xb8]
	movss [ebp-0x3c], xmm2
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__470:
	mov edi, [ebp-0xcc]
	test edi, edi
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__300
	movss xmm1, dword [ebp-0x3c]
	addss xmm1, [ebp-0xc8]
	movss [ebp-0x3c], xmm1
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__300:
	add dword [ebp-0x80], 0x1
	sub dword [ebp-0x84], 0x1
	mov eax, [ebp-0x1c]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__310
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__30:
	mov edx, [ebp+0x14]
	mov edx, [edx+0x10]
	mov [ebp-0xac], edx
	mov dword [ebp-0x90], 0x2
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__320
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__110:
	mov byte [ebp-0x79], 0x0
	cmp byte [ebp-0x9d], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__330
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__170:
	movzx eax, byte [ebp-0x1d]
	mov [ebp-0x69], al
	lea eax, [ebp-0x24]
	mov [esp], eax
	call _Z12RandWithSeedPi
	mov ecx, eax
	mov eax, [ebp+0x50]
	cdq
	idiv dword [ebp-0x68]
	mov edi, eax
	mov eax, ecx
	cdq
	idiv dword [ebp-0x68]
	imul edi, edx
	cmp [ebp-0x9c], edi
	jl _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__340
	mov esi, ebx
	mov byte [ebp-0x7b], 0x1
	mov byte [ebp-0x79], 0x0
	movss xmm1, dword [_float_255_00000000]
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__570:
	addss xmm1, [_float_0_50000000]
	movss [esp], xmm1
	call floorf
	fstp dword [ebp-0xf8]
	cvttss2si edx, [ebp-0xf8]
	cmp edx, 0xfe
	jle _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__350
	mov eax, 0xffffffff
	mov [ebp-0x7a], al
	cmp byte [ebp-0x79], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__360
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__180:
	mov eax, [ebp-0x24]
	mov [ebp-0x2c], eax
	lea eax, [ebp-0x2c]
	mov [esp], eax
	call _Z12RandWithSeedPi
	mov [ebp-0x78], eax
	mov [esp+0x4], esi
	mov edx, [ebp+0x14]
	mov [esp], edx
	call _Z19R_GetCharacterGlyphP6Font_sj
	mov edi, eax
	cmp esi, ebx
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__370
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__190:
	movzx eax, byte [eax+0x4]
	cvtsi2ss xmm1, eax
	movss [ebp-0x74], xmm1
	pxor xmm1, xmm1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__380
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__90:
	mov esi, [ebp-0x1c]
	movzx ecx, byte [esi]
	lea eax, [ecx-0x1]
	cmp al, 0x1
	ja _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__110
	movss xmm0, dword [ebp-0x3c]
	subss xmm0, [ebp-0x98]
	movss xmm2, dword [ebp-0x40]
	subss xmm2, [ebp-0x94]
	movss xmm5, dword [ebp+0x24]
	mulss xmm5, xmm0
	addss xmm5, [ebp-0x98]
	movss xmm1, dword [ebp+0x20]
	mulss xmm1, xmm2
	subss xmm5, xmm1
	movss xmm1, dword [ebp+0x24]
	mulss xmm1, xmm2
	addss xmm1, [ebp-0x94]
	mulss xmm0, [ebp+0x20]
	addss xmm1, xmm0
	mov edx, [ebp-0x20]
	sub cl, 0x1
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__390
	movss xmm2, dword [_float_1_00000000]
	movss [ebp-0x70], xmm2
	xor edi, edi
	mov eax, [ebp+0x14]
	mov ebx, [eax+0x4]
	movsx eax, byte [esi+0x1]
	sub eax, 0x10
	imul eax, ebx
	mov ecx, eax
	add ecx, 0x10
	js _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__400
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__720:
	sar ecx, 0x5
	cvtsi2ss xmm4, ecx
	mulss xmm4, [ebp+0x18]
	movsx eax, byte [esi+0x2]
	sub eax, 0x10
	imul eax, ebx
	mov ecx, eax
	add ecx, 0x10
	js _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__410
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__730:
	sar ecx, 0x5
	cvtsi2ss xmm3, ecx
	mulss xmm3, [ebp+0x1c]
	cvtsi2ss xmm0, ebx
	mulss xmm0, [ebp+0x1c]
	addss xmm0, xmm3
	mulss xmm0, [_float__0_50000000]
	mov eax, [esi+0x3]
	movss xmm2, dword [ebp+0x24]
	movss [esp+0x14], xmm2
	movss xmm2, dword [ebp+0x20]
	movss [esp+0x10], xmm2
	mov dword [esp+0xc], 0x3f800000
	mov [esp+0x8], edi
	mov dword [esp+0x4], 0x0
	movss xmm2, dword [ebp-0x70]
	movss [esp], xmm2
	mov ecx, 0x7
	movaps xmm2, xmm4
	addss xmm1, xmm0
	movaps xmm0, xmm5
	movss [ebp-0x118], xmm4
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	movss xmm4, dword [ebp-0x118]
	addss xmm4, [ebp-0x3c]
	movss [ebp-0x3c], xmm4
	mov eax, [ebp-0xcc]
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__420
	addss xmm4, [ebp-0xc8]
	movss [ebp-0x3c], xmm4
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__420:
	mov eax, [ebp-0x1c]
	add eax, 0x7
	mov [ebp-0x1c], eax
	add dword [ebp-0x80], 0x1
	sub dword [ebp-0x84], 0x1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__310
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__60:
	mov eax, [ebp-0x1c]
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__430
	movzx eax, byte [eax]
	cmp al, 0x5e
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__430
	cmp al, 0x2f
	jle _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__430
	cmp al, 0x39
	jg _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__430
	movzx eax, al
	mov [esp], eax
	call _Z10ColorIndexh
	mov ebx, eax
	mov dword [esp], 0x37
	call _Z10ColorIndexh
	cmp bl, al
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__440
	mov eax, [ebp-0xd4]
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__450
	mov eax, [ebp-0x1c]
	movzx eax, byte [eax]
	mov [esp], eax
	call _Z10ColorIndexh
	cmp al, 0x2
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__460
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__450:
	lea eax, [ebp-0x28]
	mov [esp+0x4], eax
	mov eax, [ebp-0x1c]
	movzx eax, byte [eax]
	mov [esp], eax
	call _Z14RB_LookupColorhPh
	movzx edx, byte [ebp-0x28]
	shl edx, 0x10
	movzx eax, byte [ebp-0x27]
	shl eax, 0x8
	or edx, eax
	movzx eax, byte [ebp-0x26]
	or edx, eax
	movzx eax, byte [ebp-0xe8]
	shl eax, 0x18
	or edx, eax
	mov [ebp-0x20], edx
	mov byte [ebp-0x7c], 0x0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__800:
	mov eax, [ebp-0x1c]
	add eax, 0x1
	mov [ebp-0x1c], eax
	add dword [ebp-0x80], 0x2
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__310
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__200:
	mov eax, ebx
	shr eax, 0x18
	cvtsi2ss xmm1, eax
	divss xmm1, dword [_float_255_00000000]
	movzx eax, byte [ebp-0x7a]
	cvtsi2ss xmm0, eax
	divss xmm0, dword [_float_255_00000000]
	mulss xmm1, xmm0
	mulss xmm1, [_float_255_00000000]
	cvttss2si eax, xmm1
	shl eax, 0x18
	and ebx, 0xffffff
	or ebx, eax
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__210
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__290:
	movss xmm4, dword [ebp-0x74]
	mulss xmm4, [ebp+0x18]
	movss xmm0, dword [ebp-0x3c]
	addss xmm0, xmm4
	movss [ebp-0x3c], xmm0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__470
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__100:
	mov eax, [ebp+0x14]
	cvtsi2ss xmm0, dword [eax+0x4]
	mulss xmm0, [ebp+0x1c]
	addss xmm0, [ebp-0x40]
	movss [ebp-0x40], xmm0
	movss xmm0, dword [ebp-0x98]
	movss [ebp-0x3c], xmm0
	mov eax, [ebp-0x1c]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__310
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__230:
	cmp dword [ebp-0x8c], 0x1
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220
	mov esi, [ebp-0xd4]
	test esi, esi
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__480
	cmp byte [ebp-0x7c], 0x0
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__480:
	mov edx, ebx
	mov ecx, [ebp-0x5c]
	test ecx, ecx
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__490
	mov eax, [ebp+0x40]
	and eax, 0xff0000
	and ebx, 0xff00ffff
	or ebx, eax
	mov edx, [ebp+0x40]
	movzx eax, dh
	mov bh, al
	mov bl, [ebp+0x40]
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__750:
	addss xmm2, [ebp-0x3c]
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm0, eax
	mulss xmm0, [_float__0_75000000]
	movss xmm1, dword [_float_0_50000000]
	mulss xmm0, xmm1
	mulss xmm0, [ebp+0x18]
	addss xmm0, xmm2
	movss [ebp-0x50], xmm0
	addss xmm3, [ebp-0x40]
	movss [ebp-0x4c], xmm3
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm0, eax
	mulss xmm0, [_float__0_12500000]
	mulss xmm0, xmm1
	mulss xmm0, [ebp+0x1c]
	addss xmm0, xmm3
	movss [ebp-0x4c], xmm0
	mov eax, [ebp-0x78]
	and eax, 0x8000000f
	js _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__500
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__830:
	cvtsi2ss xmm0, eax
	movss xmm1, dword [_float_0_06250000]
	mulss xmm1, xmm0
	movss [ebp-0x58], xmm1
	movss xmm2, dword [_float_0_06250000]
	addss xmm2, xmm1
	movss [ebp-0x54], xmm2
	mov esi, _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E10MY_OFFSETS
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__540:
	movss xmm0, dword [esi]
	addss xmm0, xmm0
	mulss xmm0, [ebp+0x18]
	addss xmm0, [ebp-0x50]
	subss xmm0, [ebp-0x98]
	movss xmm1, dword [esi+0x4]
	addss xmm1, xmm1
	mulss xmm1, [ebp+0x1c]
	addss xmm1, [ebp-0x4c]
	subss xmm1, [ebp-0x94]
	movss xmm5, dword [ebp+0x24]
	mulss xmm5, xmm0
	addss xmm5, [ebp-0x98]
	movss xmm2, dword [ebp+0x20]
	mulss xmm2, xmm1
	subss xmm5, xmm2
	movss xmm4, dword [ebp+0x24]
	mulss xmm4, xmm1
	addss xmm4, [ebp-0x94]
	mulss xmm0, [ebp+0x20]
	addss xmm4, xmm0
	cmp byte [ebp-0x79], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__510
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm3, eax
	mulss xmm3, [ebp+0x1c]
	mulss xmm3, [_float_1_12500000]
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm2, eax
	mulss xmm2, [ebp+0x18]
	mulss xmm2, [_float_1_75000000]
	mov edx, [ebp-0xac]
	mov eax, [edx+0x40]
	mov eax, [eax+0x8]
	mov edx, [eax+0x28]
	test edx, edx
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__520
	mov eax, [eax+0x20]
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__520
	xor eax, eax
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__530
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__660:
	mov edx, [ebp-0xac]
	mov eax, [edx]
	mov [esp+0x4], eax
	mov dword [esp], 0x26
	call _Z18R_WarnOncePerFrame14GfxWarningTypez
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__670:
	add esi, 0x8
	cmp esi, _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E10MY_OFFSETS+0x20
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__540
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__350:
	xor eax, eax
	test edx, edx
	cmovg eax, edx
	mov [ebp-0x7a], al
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__550
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__340:
	mov eax, [ebp-0x9c]
	add eax, 0x3c
	cmp edi, eax
	jle _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__560
	mov esi, ebx
	mov byte [ebp-0x7b], 0x0
	mov byte [ebp-0x79], 0x0
	movss xmm1, dword [_float_255_00000000]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__570
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__260:
	mov eax, 0x1
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__580
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__270:
	movss xmm0, dword [ebp+0x24]
	movss [esp+0x14], xmm0
	movss xmm1, dword [ebp+0x20]
	movss [esp+0x10], xmm1
	mov eax, [edi+0x14]
	mov [esp+0xc], eax
	mov eax, [edi+0x10]
	mov [esp+0x8], eax
	mov eax, [edi+0xc]
	mov [esp+0x4], eax
	mov eax, [edi+0x8]
	mov [esp], eax
	mov ecx, 0x7
	mov edx, ebx
	movaps xmm1, xmm4
	movaps xmm0, xmm5
	mov eax, [ebp-0xb0]
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__590
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__240:
	mov eax, [ebp-0xc0]
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__600
	movss xmm1, dword [_float_2_00000000]
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__700:
	addss xmm2, [ebp-0x3c]
	movss [ebp-0x48], xmm2
	addss xmm3, [ebp-0x40]
	movss [ebp-0x44], xmm3
	addss xmm2, xmm1
	subss xmm2, [ebp-0x98]
	addss xmm1, xmm3
	subss xmm1, [ebp-0x94]
	movss xmm5, dword [ebp+0x24]
	mulss xmm5, xmm2
	addss xmm5, [ebp-0x98]
	movss xmm0, dword [ebp+0x20]
	mulss xmm0, xmm1
	subss xmm5, xmm0
	movss xmm4, dword [ebp+0x24]
	mulss xmm4, xmm1
	addss xmm4, [ebp-0x94]
	mulss xmm2, [ebp+0x20]
	addss xmm4, xmm2
	cmp byte [ebp-0x79], 0x0
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__610
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm3, eax
	mulss xmm3, [ebp+0x1c]
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm2, eax
	mulss xmm2, [ebp+0x18]
	mov edx, [ebp-0xb0]
	mov eax, [edx+0x40]
	mov eax, [eax+0x8]
	mov esi, [eax+0x28]
	test esi, esi
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__620
	mov ecx, [eax+0x20]
	test ecx, ecx
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__620
	xor eax, eax
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__630
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__650:
	movss xmm0, dword [ebp+0x24]
	movss [esp+0x14], xmm0
	movss xmm1, dword [ebp+0x20]
	movss [esp+0x10], xmm1
	mov eax, [edi+0x14]
	mov [esp+0xc], eax
	mov eax, [edi+0x10]
	mov [esp+0x8], eax
	mov eax, [edi+0xc]
	mov [esp+0x4], eax
	mov eax, [edi+0x8]
	mov [esp], eax
	mov ecx, 0x7
	mov edx, [ebp-0xf0]
	movaps xmm1, xmm4
	movaps xmm0, xmm5
	mov eax, [ebp-0xb0]
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	movss xmm2, dword [ebp-0x48]
	movss xmm1, dword [ebp-0x44]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__640
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__620:
	mov eax, 0x1
	test eax, eax
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__650
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__630:
	mov edx, [ebp-0xb0]
	mov eax, [edx]
	mov [esp+0x4], eax
	mov dword [esp], 0x26
	call _Z18R_WarnOncePerFrame14GfxWarningTypez
	movss xmm2, dword [ebp-0x48]
	movss xmm1, dword [ebp-0x44]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__640
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__520:
	mov eax, 0x1
	test eax, eax
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__660
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__530:
	movss xmm0, dword [ebp+0x24]
	movss [esp+0x14], xmm0
	movss xmm1, dword [ebp+0x20]
	movss [esp+0x10], xmm1
	mov eax, [edi+0x14]
	mov [esp+0xc], eax
	mov eax, [edi+0x10]
	mov [esp+0x8], eax
	mov eax, [edi+0xc]
	mov [esp+0x4], eax
	mov eax, [edi+0x8]
	mov [esp], eax
	mov ecx, 0x7
	mov edx, ebx
	movaps xmm1, xmm4
	movaps xmm0, xmm5
	mov eax, [ebp-0xac]
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__670
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__160:
	mov byte [ebp-0x7a], 0xc0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__680
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__250:
	mov eax, [ebp-0x78]
	and eax, 0x8000000f
	js _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__690
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__810:
	cvtsi2ss xmm1, eax
	mulss xmm1, [_float_0_06250000]
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm3, eax
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm2, eax
	movss xmm0, dword [ebp+0x24]
	movss [esp+0x14], xmm0
	movss xmm0, dword [ebp+0x20]
	movss [esp+0x10], xmm0
	mov dword [esp+0xc], 0x3f800000
	movaps xmm0, xmm1
	addss xmm0, [_float_0_06250000]
	movss [esp+0x8], xmm0
	mov dword [esp+0x4], 0x0
	movss [esp], xmm1
	mov ecx, 0x7
	mov edx, ebx
	mulss xmm3, [ebp+0x1c]
	mulss xmm2, [ebp+0x18]
	movaps xmm1, xmm4
	movaps xmm0, xmm5
	mov eax, [ebp+0x54]
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__590
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__510:
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm1, eax
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm0, eax
	movss xmm2, dword [ebp+0x24]
	movss [esp+0x14], xmm2
	movss xmm2, dword [ebp+0x20]
	movss [esp+0x10], xmm2
	mov dword [esp+0xc], 0x3f800000
	movss xmm2, dword [ebp-0x54]
	movss [esp+0x8], xmm2
	mov dword [esp+0x4], 0x0
	movss xmm2, dword [ebp-0x58]
	movss [esp], xmm2
	mov ecx, 0x7
	mov edx, ebx
	movss xmm3, dword [ebp+0x1c]
	mulss xmm3, xmm1
	movss xmm2, dword [ebp+0x18]
	mulss xmm2, xmm0
	movaps xmm1, xmm4
	movaps xmm0, xmm5
	mov eax, [ebp+0x58]
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__670
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__600:
	movss xmm1, dword [_float_1_00000000]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__700
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__560:
	mov edx, [ebp+0x44]
	lea eax, [ebx+edx]
	add eax, [ebp-0x9c]
	mov [ebp-0x2c], eax
	lea eax, [ebp-0x2c]
	mov [esp], eax
	call _Z12RandWithSeedPi
	test al, 0x1
	jz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__710
	mov esi, 0x4f
	mov byte [ebp-0x79], 0x1
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__820:
	mov eax, [ebp-0x9c]
	sub eax, edi
	add eax, 0x3c
	cvtsi2ss xmm0, eax
	divss xmm0, dword [_float_60_00000000]
	movss xmm1, dword [_float_1_00000000]
	subss xmm1, xmm0
	movzx eax, byte [ebp-0x69]
	cvtsi2ss xmm0, eax
	divss xmm0, dword [_float_255_00000000]
	mulss xmm1, xmm0
	mulss xmm1, [_float_255_00000000]
	mov byte [ebp-0x7b], 0x0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__570
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__390:
	pxor xmm0, xmm0
	movss [ebp-0x70], xmm0
	mov edi, 0x3f800000
	mov eax, [ebp+0x14]
	mov ebx, [eax+0x4]
	movsx eax, byte [esi+0x1]
	sub eax, 0x10
	imul eax, ebx
	mov ecx, eax
	add ecx, 0x10
	jns _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__720
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__400:
	lea ecx, [eax+0x2f]
	sar ecx, 0x5
	cvtsi2ss xmm4, ecx
	mulss xmm4, [ebp+0x18]
	movsx eax, byte [esi+0x2]
	sub eax, 0x10
	imul eax, ebx
	mov ecx, eax
	add ecx, 0x10
	jns _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__730
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__410:
	lea ecx, [eax+0x2f]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__730
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__610:
	mov eax, [ebp-0x78]
	and eax, 0x8000000f
	js _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__740
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__840:
	cvtsi2ss xmm1, eax
	mulss xmm1, [_float_0_06250000]
	movzx eax, byte [edi+0x6]
	cvtsi2ss xmm3, eax
	movzx eax, byte [edi+0x5]
	cvtsi2ss xmm2, eax
	movss xmm0, dword [ebp+0x24]
	movss [esp+0x14], xmm0
	movss xmm0, dword [ebp+0x20]
	movss [esp+0x10], xmm0
	mov dword [esp+0xc], 0x3f800000
	movaps xmm0, xmm1
	addss xmm0, [_float_0_06250000]
	movss [esp+0x8], xmm0
	mov dword [esp+0x4], 0x0
	movss [esp], xmm1
	mov ecx, 0x7
	mov edx, [ebp-0xf0]
	mulss xmm3, [ebp+0x1c]
	mulss xmm2, [ebp+0x18]
	movaps xmm1, xmm4
	movaps xmm0, xmm5
	mov eax, [ebp+0x54]
	call _Z23RB_DrawStretchPicRotatePK8Materialffffffffffm18GfxPrimStatsTarget
	movss xmm2, dword [ebp-0x48]
	movss xmm1, dword [ebp-0x44]
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__640
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__490:
	mov eax, ebx
	shr eax, 0x10
	movzx eax, al
	cvtsi2ss xmm0, eax
	movss xmm1, dword [_float_0_06000000]
	mulss xmm0, xmm1
	cvttss2si eax, xmm0
	movzx eax, al
	shl eax, 0x10
	and ebx, 0xff00ffff
	or ebx, eax
	movzx eax, dh
	cvtsi2ss xmm0, eax
	mulss xmm0, xmm1
	cvttss2si eax, xmm0
	mov bh, al
	movzx eax, dl
	cvtsi2ss xmm0, eax
	mulss xmm0, xmm1
	cvttss2si eax, xmm0
	mov bl, al
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__750
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__20:
	mov dword [ebp-0x24], 0x1
	mov eax, gfxCmdBufSourceState
	mov edi, [eax+0xf3c]
	sub edi, [ebp+0x44]
	mov edx, [ebp+0x8]
	mov [esp], edx
	call _Z15SEH_PrintStrlenPKc
	mov ecx, eax
	cmp [ebp+0x2c], eax
	cmovl ecx, [ebp+0x2c]
	mov edx, [ebp+0x48]
	imul edx, ecx
	mov eax, [ebp+0x4c]
	add eax, [ebp+0x50]
	cmp edi, eax
	jg _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__40
	cmp edi, edx
	jl _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__760
	cmp [ebp+0x4c], edi
	jl _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__770
	mov byte [ebp-0xa5], 0x0
	mov byte [ebp-0x9d], 0x0
	mov dword [ebp-0x9c], 0x0
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__860:
	mov eax, [ebp-0x24]
	mov [ebp-0xa4], eax
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__780
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__10:
	mov dword [esp+0x4], 0x6f
	mov eax, [ebp+0x14]
	mov [esp], eax
	call _Z19R_GetCharacterGlyphP6Font_sj
	movzx eax, byte [eax+0x4]
	cvtsi2ss xmm0, eax
	movss [ebp-0xb4], xmm0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__790
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__140:
	movss xmm0, dword [ebp-0x3c]
	subss xmm0, [ebp-0x98]
	movss xmm4, dword [ebp-0x40]
	subss xmm4, [ebp-0x94]
	movss xmm1, dword [ebp+0x24]
	mulss xmm1, xmm4
	addss xmm1, [ebp-0x94]
	movss xmm5, dword [ebp+0x20]
	mulss xmm5, xmm0
	mulss xmm0, [ebp+0x24]
	addss xmm0, [ebp-0x98]
	mulss xmm4, [ebp+0x20]
	mov edx, [ebp+0x28]
	mov [esp+0x8], edx
	movss xmm2, dword [ebp+0x1c]
	movss [esp+0x4], xmm2
	movss xmm2, dword [ebp+0x18]
	movss [esp], xmm2
	mov ecx, [ebp+0x14]
	movss xmm3, dword [ebp+0x24]
	movss xmm2, dword [ebp+0x20]
	addss xmm1, xmm5
	subss xmm0, xmm4
	mov edx, [ebp-0xfc]
	mov eax, [ebp-0xb0]
	call _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__130
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__280:
	movss xmm0, dword [ebp-0x40]
	subss xmm0, [ebp-0x94]
	movss xmm1, dword [ebp+0x24]
	mulss xmm1, xmm0
	addss xmm1, [ebp-0x94]
	mulss xmm0, [ebp+0x20]
	mov [esp+0x8], ebx
	movss xmm2, dword [ebp+0x1c]
	movss [esp+0x4], xmm2
	movss xmm4, dword [ebp+0x18]
	movss [esp], xmm4
	mov ecx, [ebp+0x14]
	movss xmm3, dword [ebp+0x24]
	movss xmm2, dword [ebp+0x20]
	addss xmm1, [ebp-0x60]
	movss xmm4, dword [ebp-0x64]
	subss xmm4, xmm0
	movaps xmm0, xmm4
	mov edx, [ebp-0xfc]
	mov eax, [ebp-0xb0]
	call _Z13RB_DrawCursorPK8MaterialhffffP6Font_sffm
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__220
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__440:
	mov edi, [ebp+0x28]
	mov [ebp-0x20], edi
	mov byte [ebp-0x7c], 0x0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__800
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__690:
	sub eax, 0x1
	or eax, 0xfffffff0
	add eax, 0x1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__810
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__710:
	mov eax, [ebp-0x2c]
	mov [esp+0x4], eax
	mov eax, [ebp+0x14]
	mov [esp], eax
	call _Z21R_FontGetRandomLetterP6Font_si
	mov esi, eax
	mov byte [ebp-0x79], 0x0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__820
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__500:
	sub eax, 0x1
	or eax, 0xfffffff0
	add eax, 0x1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__830
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__740:
	sub eax, 0x1
	or eax, 0xfffffff0
	add eax, 0x1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__840
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__460:
	mov ecx, _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E25MY_ALTCOLOR_TWO_CINEMATIC
	mov eax, [ebp-0xd0]
	test eax, eax
	mov eax, _ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E15MY_ALTCOLOR_TWO
	cmovz ecx, eax
	movzx edx, byte [ecx]
	shl edx, 0x10
	movzx eax, byte [ecx+0x1]
	shl eax, 0x8
	or edx, eax
	movzx eax, byte [ecx+0x2]
	or edx, eax
	movzx eax, byte [ecx+0x3]
	cvtsi2ss xmm1, eax
	divss xmm1, dword [_float_255_00000000]
	movzx eax, byte [ebp-0xe8]
	cvtsi2ss xmm0, eax
	divss xmm0, dword [_float_255_00000000]
	mulss xmm1, xmm0
	mulss xmm1, [_float_255_00000000]
	cvttss2si eax, xmm1
	shl eax, 0x18
	or edx, eax
	mov [ebp-0x20], edx
	mov byte [ebp-0x7c], 0x1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__800
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__760:
	mov eax, edi
	cdq
	idiv dword [ebp+0x48]
	mov [ebp-0xf4], eax
	mov eax, [ebp+0x48]
	imul eax, [ebp-0xf4]
	mov ebx, edi
	sub ebx, eax
	mov eax, [ebp+0x48]
	lea edx, [eax+0x3]
	cmp eax, 0xffffffff
	cmovle eax, edx
	mov edx, eax
	sar edx, 0x2
	jnz _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__850
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__870:
	mov edx, [ebp+0x44]
	lea eax, [ecx+edx]
	lea eax, [ebx+eax]
	add eax, [ebp-0xf4]
	mov [ebp-0x24], eax
	lea ebx, [ebp-0x24]
	mov [esp], ebx
	call _Z12RandWithSeedPi
	mov [esp], ebx
	call _Z12RandWithSeedPi
	mov edi, [ebp-0xf4]
	add edi, 0x1
	mov [ebp+0x2c], edi
	mov byte [ebp-0xa5], 0x1
	mov byte [ebp-0x9d], 0x0
	mov dword [ebp-0x9c], 0x0
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__860
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__850:
	mov eax, ebx
	mov edi, edx
	cdq
	idiv edi
	mov ebx, eax
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__870
_Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__770:
	mov edx, [ebp+0x44]
	lea eax, [ecx+edx]
	mov [ebp-0x24], eax
	lea ebx, [ebp-0x24]
	mov [esp], ebx
	call _Z12RandWithSeedPi
	mov [esp], ebx
	call _Z12RandWithSeedPi
	mov eax, [ebp+0x4c]
	sub edi, eax
	mov [ebp-0x9c], edi
	mov byte [ebp-0xa5], 0x0
	mov byte [ebp-0x9d], 0x1
	jmp _Z10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6__860
	nop



;R_SetVertex2d(GfxVertex*, float, float, float, float, unsigned long)
_Z13R_SetVertex2dP9GfxVertexffffm:
	push ebp
	mov ebp, esp
	mov eax, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov [eax], edx
	mov edx, [ebp+0x10]
	mov [eax+0x4], edx
	mov dword [eax+0x8], 0x0
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebp+0x1c]
	mov [eax+0x10], edx
	mov edx, [ebp+0x14]
	mov [eax+0x14], edx
	mov edx, [ebp+0x18]
	mov [eax+0x18], edx
	pop ebp
	ret


;RB_DrawLines2D(int, int, GfxPointVertex const*)
_Z14RB_DrawLines2DiiPK14GfxPointVertex:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x2c
	mov dword [esp+0x4], 0x4
	mov eax, rgp
	mov eax, [eax+0x2034]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov eax, [ebp+0x8]
	test eax, eax
	jg _Z14RB_DrawLines2DiiPK14GfxPointVertex_10
	add esp, 0x2c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z14RB_DrawLines2DiiPK14GfxPointVertex_10:
	xor edi, edi
	mov esi, [ebp+0x10]
	add esi, 0x10
	mov ebx, [ebp+0x10]
	add ebx, 0x4
_Z14RB_DrawLines2DiiPK14GfxPointVertex_40:
	movss xmm0, dword [esi+0x4]
	subss xmm0, [ebx]
	movss [ebp-0x20], xmm0
	movss xmm0, dword [ebx-0x4]
	subss xmm0, [esi]
	movss [ebp-0x1c], xmm0
	lea eax, [ebp-0x20]
	mov [esp], eax
	call _Z13Vec2NormalizePf
	fstp st0
	movss xmm0, dword [ebp-0x20]
	mulss xmm0, [_float_0_50000000]
	movss [ebp-0x20], xmm0
	movss xmm0, dword [ebp-0x1c]
	mulss xmm0, [_float_0_50000000]
	movss [ebp-0x1c], xmm0
	mov edx, [tess+0x22a94c]
	lea eax, [edx+0x4]
	cmp eax, 0x154a
	jg _Z14RB_DrawLines2DiiPK14GfxPointVertex_20
	mov ecx, [tess+0x22a948]
	lea eax, [ecx+0x6]
	cmp eax, 0x100000
	jle _Z14RB_DrawLines2DiiPK14GfxPointVertex_30
_Z14RB_DrawLines2DiiPK14GfxPointVertex_20:
	call _Z15RB_TessOverflowv
	mov edx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
_Z14RB_DrawLines2DiiPK14GfxPointVertex_30:
	lea eax, [edx+0x1]
	mov [ecx+ecx+tess+0x2a940], ax
	mov [ecx+ecx+tess+0x2a942], dx
	lea eax, [edx+0x2]
	mov [ecx+ecx+tess+0x2a944], ax
	mov [ecx+ecx+tess+0x2a946], ax
	mov [ecx+ecx+tess+0x2a948], dx
	lea eax, [edx+0x3]
	mov [ecx+ecx+tess+0x2a94a], ax
	lea eax, [ecx+0x6]
	mov [tess+0x22a948], eax
	mov ecx, [ebx+0x4]
	movss xmm1, dword [ebx]
	subss xmm1, [ebp-0x1c]
	shl edx, 0x5
	lea eax, [edx+tess]
	movss xmm0, dword [ebx-0x4]
	subss xmm0, [ebp-0x20]
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm1
	mov [eax+0x8], ecx
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov edx, [ebx+0x8]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x0
	mov dword [eax+0x18], 0x0
	mov ecx, [esi+0x8]
	movss xmm1, dword [esi+0x4]
	subss xmm1, [ebp-0x1c]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x20
	lea edx, [eax+tess]
	movss xmm0, dword [esi]
	subss xmm0, [ebp-0x20]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ecx
	mov dword [edx+0xc], 0x3f800000
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0x18]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x0
	mov dword [edx+0x18], 0x3f800000
	mov ecx, [esi+0x8]
	movss xmm1, dword [esi+0x4]
	addss xmm1, [ebp-0x1c]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x40
	lea edx, [eax+tess]
	movss xmm0, dword [esi]
	addss xmm0, [ebp-0x20]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ecx
	mov dword [edx+0xc], 0x3f800000
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0x18]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x3f800000
	mov ecx, [ebx+0x4]
	movss xmm1, dword [ebx]
	addss xmm1, [ebp-0x1c]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x60
	lea edx, [eax+tess]
	movss xmm0, dword [ebx-0x4]
	addss xmm0, [ebp-0x20]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ecx
	mov dword [edx+0xc], 0x3f800000
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0x8]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x0
	add dword [tess+0x22a94c], 0x4
	add edi, 0x1
	add ebx, 0x20
	add esi, 0x20
	cmp [ebp+0x8], edi
	jnz _Z14RB_DrawLines2DiiPK14GfxPointVertex_40
	add esp, 0x2c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;RB_DrawLines3D(int, int, GfxPointVertex const*, unsigned char)
_Z14RB_DrawLines3DiiPK14GfxPointVertexh:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xbc
	cmp byte [ebp+0x14], 0x0
	jz _Z14RB_DrawLines3DiiPK14GfxPointVertexh_10
	mov dword [esp+0x4], 0x4
	mov eax, rgp
	mov eax, [eax+0x2040]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_50:
	mov ebx, gfxCmdBufSourceState
	cmp dword [ebx+0xf38], 0x3
	jz _Z14RB_DrawLines3DiiPK14GfxPointVertexh_20
	mov edi, [tess+0x22a948]
	test edi, edi
	jnz _Z14RB_DrawLines3DiiPK14GfxPointVertexh_30
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_60:
	mov dword [ebx+0xf38], 0x3
	lea edx, [ebx+0xcb0]
	mov dword [esp+0x8], 0x140
	mov eax, rg
	mov [esp+0x4], eax
	mov [esp], edx
	call memcpy
	xor eax, eax
	mov [ebx+0xef4], eax
	mov [ebx+0xef8], eax
	mov [ebx+0xefc], eax
	mov dword [ebx+0xf00], 0x3f800000
	mov [esp], ebx
	call _Z13R_CmdBufSet3DP20GfxCmdBufSourceState
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_20:
	mov eax, [ebx+0xf0c]
	lea edi, [eax+0x80]
	cvtsi2ss xmm0, dword [ebp+0xc]
	cvtsi2ss xmm1, dword [ebx+0xf68]
	movaps xmm2, xmm0
	divss xmm2, xmm1
	movss [ebp-0x68], xmm2
	cvtsi2ss xmm1, dword [ebx+0xf6c]
	divss xmm0, xmm1
	movss [ebp-0x64], xmm0
	mov esi, [ebp+0x8]
	test esi, esi
	jg _Z14RB_DrawLines3DiiPK14GfxPointVertexh_40
	call _Z17RB_EndTessSurfacev
	add esp, 0xbc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_10:
	mov dword [esp+0x4], 0x4
	mov eax, rgp
	mov eax, [eax+0x2044]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	jmp _Z14RB_DrawLines3DiiPK14GfxPointVertexh_50
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_30:
	call _Z17RB_EndTessSurfacev
	jmp _Z14RB_DrawLines3DiiPK14GfxPointVertexh_60
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_40:
	lea edx, [eax+0x90]
	mov [ebp-0x48], edx
	lea ecx, [eax+0xa0]
	mov [ebp-0x44], ecx
	add eax, 0xb0
	mov [ebp-0x40], eax
	mov ebx, [ebp+0x10]
	add ebx, 0x10
	mov esi, ebx
	mov dword [ebp-0x6c], 0x0
	mov ecx, eax
	jmp _Z14RB_DrawLines3DiiPK14GfxPointVertexh_70
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_100:
	mov edx, [ebp-0x48]
	mov ecx, [ebp-0x40]
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_70:
	lea eax, [ebx-0x10]
	mov [ebp-0x3c], eax
	movss xmm6, dword [ebx-0x10]
	movss xmm1, dword [ebx-0xc]
	movss xmm0, dword [edx]
	movss [ebp-0x7c], xmm0
	movss xmm2, dword [ebx-0x8]
	mov eax, [ebp-0x44]
	movss xmm0, dword [eax]
	movss [ebp-0x78], xmm0
	mov eax, [ebp-0x40]
	movss xmm0, dword [eax]
	movss [ebp-0x98], xmm0
	movss xmm0, dword [edi]
	mulss xmm0, xmm6
	movss [ebp-0x4c], xmm0
	movss xmm0, dword [ebp-0x7c]
	mulss xmm0, xmm1
	addss xmm0, [ebp-0x4c]
	movss [ebp-0x4c], xmm0
	movss xmm0, dword [ebp-0x78]
	mulss xmm0, xmm2
	addss xmm0, [ebp-0x4c]
	addss xmm0, [ebp-0x98]
	movss [ebp-0x4c], xmm0
	movss xmm0, dword [edx+0x4]
	movss [ebp-0x74], xmm0
	mov eax, [ebp-0x44]
	movss xmm0, dword [eax+0x4]
	movss [ebp-0x70], xmm0
	mov eax, [ebp-0x40]
	movss xmm0, dword [eax+0x4]
	movss [ebp-0x94], xmm0
	movss xmm0, dword [edi+0x4]
	mulss xmm0, xmm6
	movss [ebp-0x50], xmm0
	movss xmm0, dword [ebp-0x74]
	mulss xmm0, xmm1
	addss xmm0, [ebp-0x50]
	movss [ebp-0x50], xmm0
	movss xmm0, dword [ebp-0x70]
	mulss xmm0, xmm2
	addss xmm0, [ebp-0x50]
	addss xmm0, [ebp-0x94]
	movss [ebp-0x50], xmm0
	movss xmm5, dword [edx+0x8]
	mov eax, [ebp-0x44]
	movss xmm7, dword [eax+0x8]
	mov edx, [ebp-0x40]
	movss xmm0, dword [edx+0x8]
	movss [ebp-0x90], xmm0
	movss xmm0, dword [edi+0x8]
	mulss xmm0, xmm6
	movss [ebp-0x54], xmm0
	movaps xmm0, xmm1
	mulss xmm0, xmm5
	addss xmm0, [ebp-0x54]
	movss [ebp-0x54], xmm0
	movaps xmm0, xmm2
	mulss xmm0, xmm7
	addss xmm0, [ebp-0x54]
	addss xmm0, [ebp-0x90]
	movss [ebp-0x54], xmm0
	mov eax, [ebp-0x48]
	movss xmm3, dword [eax+0xc]
	mov edx, [ebp-0x44]
	movss xmm4, dword [edx+0xc]
	movss xmm0, dword [ecx+0xc]
	movss [ebp-0x8c], xmm0
	mulss xmm6, [edi+0xc]
	mulss xmm1, xmm3
	addss xmm1, xmm6
	mulss xmm2, xmm4
	addss xmm2, xmm1
	addss xmm2, xmm0
	movss [ebp-0x58], xmm2
	movss xmm1, dword [esi+0x4]
	movss xmm2, dword [esi+0x8]
	movss xmm6, dword [edi]
	mulss xmm6, [esi]
	movss xmm0, dword [ebp-0x7c]
	mulss xmm0, xmm1
	addss xmm6, xmm0
	movss [ebp-0x5c], xmm6
	movss xmm6, dword [ebp-0x78]
	mulss xmm6, xmm2
	movss xmm0, dword [ebp-0x5c]
	addss xmm0, xmm6
	movss xmm6, dword [ebp-0x98]
	addss xmm6, xmm0
	movss [ebp-0x5c], xmm6
	movss xmm6, dword [edi+0x4]
	mulss xmm6, [esi]
	movss xmm0, dword [ebp-0x74]
	mulss xmm0, xmm1
	addss xmm6, xmm0
	movss xmm0, dword [ebp-0x70]
	mulss xmm0, xmm2
	addss xmm6, xmm0
	addss xmm6, [ebp-0x94]
	movss xmm0, dword [edi+0x8]
	mulss xmm0, [esi]
	mulss xmm5, xmm1
	addss xmm5, xmm0
	mulss xmm7, xmm2
	addss xmm7, xmm5
	movss xmm0, dword [ebp-0x90]
	addss xmm0, xmm7
	movss [ebp-0x60], xmm0
	movss xmm5, dword [edi+0xc]
	mulss xmm5, [esi]
	mulss xmm3, xmm1
	addss xmm5, xmm3
	mulss xmm4, xmm2
	addss xmm5, xmm4
	addss xmm5, [ebp-0x8c]
	movss xmm0, dword [ebp-0x58]
	mulss xmm0, xmm6
	movss xmm1, dword [ebp-0x50]
	mulss xmm1, xmm5
	subss xmm0, xmm1
	movss [ebp-0x20], xmm0
	movss xmm0, dword [ebp-0x4c]
	mulss xmm0, xmm5
	movss xmm1, dword [ebp-0x58]
	mulss xmm1, [ebp-0x5c]
	subss xmm0, xmm1
	movss [ebp-0x1c], xmm0
	lea eax, [ebp-0x20]
	mov [esp], eax
	movss [ebp-0xa8], xmm5
	movss [ebp-0xb8], xmm6
	call _Z13Vec2NormalizePf
	fstp st0
	movss xmm1, dword [ebp-0x68]
	mulss xmm1, [ebp-0x20]
	movss [ebp-0x20], xmm1
	movss xmm2, dword [ebp-0x64]
	mulss xmm2, [ebp-0x1c]
	movss [ebp-0x1c], xmm2
	movss xmm0, dword [ebp-0x58]
	mulss xmm0, xmm1
	movss [ebp-0x30], xmm0
	movss xmm0, dword [ebp-0x58]
	mulss xmm0, xmm2
	movss [ebp-0x2c], xmm0
	movss xmm5, dword [ebp-0xa8]
	mulss xmm1, xmm5
	movss [ebp-0x28], xmm1
	mulss xmm2, xmm5
	movss [ebp-0x24], xmm2
	mov edx, [tess+0x22a94c]
	lea eax, [edx+0x4]
	cmp eax, 0x154a
	movss xmm6, dword [ebp-0xb8]
	jg _Z14RB_DrawLines3DiiPK14GfxPointVertexh_80
	mov ecx, [tess+0x22a948]
	lea eax, [ecx+0x6]
	cmp eax, 0x100000
	jle _Z14RB_DrawLines3DiiPK14GfxPointVertexh_90
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_80:
	movss [ebp-0xa8], xmm5
	movss [ebp-0xb8], xmm6
	call _Z15RB_TessOverflowv
	mov edx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
	movss xmm6, dword [ebp-0xb8]
	movss xmm5, dword [ebp-0xa8]
_Z14RB_DrawLines3DiiPK14GfxPointVertexh_90:
	lea eax, [edx+0x3]
	mov [ecx+ecx+tess+0x2a940], ax
	mov [ecx+ecx+tess+0x2a942], dx
	lea eax, [edx+0x2]
	mov [ecx+ecx+tess+0x2a944], ax
	mov [ecx+ecx+tess+0x2a946], ax
	mov [ecx+ecx+tess+0x2a948], dx
	lea eax, [edx+0x1]
	mov [ecx+ecx+tess+0x2a94a], ax
	lea eax, [ecx+0x6]
	mov [tess+0x22a948], eax
	movss xmm1, dword [ebp-0x50]
	subss xmm1, [ebp-0x2c]
	shl edx, 0x5
	lea eax, [edx+tess]
	movss xmm0, dword [ebp-0x4c]
	subss xmm0, [ebp-0x30]
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm1
	movss xmm0, dword [ebp-0x54]
	movss [eax+0x8], xmm0
	movss xmm2, dword [ebp-0x58]
	movss [eax+0xc], xmm2
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov ecx, [ebp-0x3c]
	mov edx, [ecx+0xc]
	mov [eax+0x10], edx
	mov dword [eax+0x14], 0x0
	mov dword [eax+0x18], 0x0
	movaps xmm1, xmm6
	subss xmm1, [ebp-0x24]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x20
	lea edx, [eax+tess]
	movss xmm0, dword [ebp-0x5c]
	subss xmm0, [ebp-0x28]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	movss xmm0, dword [ebp-0x60]
	movss [edx+0x8], xmm0
	movss [edx+0xc], xmm5
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x0
	mov dword [edx+0x18], 0x3f800000
	addss xmm6, [ebp-0x24]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x40
	lea edx, [eax+tess]
	movss xmm2, dword [ebp-0x5c]
	addss xmm2, [ebp-0x28]
	movss [eax+tess], xmm2
	movss [edx+0x4], xmm6
	movss [edx+0x8], xmm0
	movss [edx+0xc], xmm5
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ebx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x3f800000
	movss xmm6, dword [ebp-0x50]
	addss xmm6, [ebp-0x2c]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x60
	lea edx, [eax+tess]
	movss xmm0, dword [ebp-0x4c]
	addss xmm0, [ebp-0x30]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm6
	movss xmm2, dword [ebp-0x54]
	movss [edx+0x8], xmm2
	movss xmm6, dword [ebp-0x58]
	movss [edx+0xc], xmm6
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov eax, [ecx+0xc]
	mov [edx+0x10], eax
	mov dword [edx+0x14], 0x3f800000
	mov dword [edx+0x18], 0x0
	add dword [tess+0x22a94c], 0x4
	add dword [ebp-0x6c], 0x1
	add esi, 0x20
	add ebx, 0x20
	mov eax, [ebp-0x6c]
	cmp [ebp+0x8], eax
	jnz _Z14RB_DrawLines3DiiPK14GfxPointVertexh_100
	call _Z17RB_EndTessSurfacev
	add esp, 0xbc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
	nop


;RB_LookupColor(unsigned char, unsigned char*)
_Z14RB_LookupColorhPh:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	movzx ebx, byte [ebp+0x8]
	movzx eax, bl
	mov [esp], eax
	call _Z10ColorIndexh
	movzx eax, al
	cmp eax, 0x7
	ja _Z14RB_LookupColorhPh_10
	mov eax, [eax*4+_ZZ14RB_LookupColorhPhE11color_table]
	mov edx, [ebp+0xc]
	mov [edx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z14RB_LookupColorhPh_10:
	cmp bl, 0x38
	jz _Z14RB_LookupColorhPh_20
	cmp bl, 0x39
	jz _Z14RB_LookupColorhPh_30
	mov eax, [ebp+0xc]
	mov dword [eax], 0xffffffff
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z14RB_LookupColorhPh_20:
	mov eax, rg
	cmp dword [eax+0x21d4], 0x2
	jz _Z14RB_LookupColorhPh_40
_Z14RB_LookupColorhPh_50:
	add eax, 0x21cc
_Z14RB_LookupColorhPh_60:
	mov eax, [eax]
	mov edx, [ebp+0xc]
	mov [edx], eax
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z14RB_LookupColorhPh_30:
	mov eax, rg
	cmp dword [eax+0x21d4], 0x2
	jz _Z14RB_LookupColorhPh_50
_Z14RB_LookupColorhPh_40:
	add eax, 0x21d0
	jmp _Z14RB_LookupColorhPh_60


;RB_SetIdentity()
_Z14RB_SetIdentityv:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, gfxCmdBufSourceState
	cmp dword [ebx+0xf38], 0x3
	jz _Z14RB_SetIdentityv_10
	mov eax, [tess+0x22a948]
	test eax, eax
	jnz _Z14RB_SetIdentityv_20
_Z14RB_SetIdentityv_30:
	mov dword [ebx+0xf38], 0x3
	lea edx, [ebx+0xcb0]
	mov dword [esp+0x8], 0x140
	mov eax, rg
	mov [esp+0x4], eax
	mov [esp], edx
	call memcpy
	xor eax, eax
	mov [ebx+0xef4], eax
	mov [ebx+0xef8], eax
	mov [ebx+0xefc], eax
	mov dword [ebx+0xf00], 0x3f800000
	mov [esp], ebx
	call _Z13R_CmdBufSet3DP20GfxCmdBufSourceState
_Z14RB_SetIdentityv_10:
	add esp, 0x14
	pop ebx
	pop ebp
	ret
_Z14RB_SetIdentityv_20:
	call _Z17RB_EndTessSurfacev
	jmp _Z14RB_SetIdentityv_30
	nop


;RB_SetBspImages()
_Z15RB_SetBspImagesv:
	push ebp
	mov ebp, esp
	mov eax, rgp
	mov edx, [eax+0x20a0]
	mov ecx, gfxCmdBufInput
	mov eax, [edx+0x21c]
	mov [ecx+0x3e4], eax
	mov eax, [edx+0x28]
	mov [ecx+0x3d8], eax
	movzx eax, byte [edx+0x2c]
	mov [ecx+0x41a], al
	pop ebp
	ret
	nop



;RB_DrawStretchPic(Material const*, float, float, float, float, float, float, float, float, unsigned long, GfxPrimStatsTarget)
_Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x1c
	mov edi, [ebp+0x20]
	mov esi, [ebp+0x2c]
	mov dword [esp+0x4], 0x4
	mov eax, [ebp+0x8]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ebx, [tess+0x22a94c]
	lea eax, [ebx+0x4]
	cmp eax, 0x154a
	jg _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget_10
	mov ecx, [tess+0x22a948]
	lea eax, [ecx+0x6]
	cmp eax, 0x100000
	jle _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget_20
_Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget_10:
	call _Z15RB_TessOverflowv
	mov ebx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
_Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget_20:
	mov edx, ebx
	lea eax, [edx+0x3]
	mov [ecx+ecx+tess+0x2a940], ax
	mov [ecx+ecx+tess+0x2a942], bx
	lea eax, [edx+0x2]
	mov [ecx+ecx+tess+0x2a944], ax
	mov [ecx+ecx+tess+0x2a946], ax
	mov [ecx+ecx+tess+0x2a948], bx
	add edx, 0x1
	mov [ecx+ecx+tess+0x2a94a], dx
	mov edx, ebx
	shl edx, 0x5
	lea eax, [edx+tess]
	movss xmm0, dword [ebp+0xc]
	movss [edx+tess], xmm0
	movss xmm1, dword [ebp+0x10]
	movss [eax+0x4], xmm1
	xor ebx, ebx
	mov [eax+0x8], ebx
	mov ecx, 0x3f800000
	mov [eax+0xc], ecx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], esi
	movss xmm0, dword [ebp+0x1c]
	movss [eax+0x14], xmm0
	mov [eax+0x18], edi
	movss xmm0, dword [ebp+0xc]
	addss xmm0, [ebp+0x14]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x20
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ebx
	mov [edx+0xc], ecx
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov [edx+0x10], esi
	movss xmm1, dword [ebp+0x24]
	movss [edx+0x14], xmm1
	mov [edx+0x18], edi
	movss xmm1, dword [ebp+0x10]
	addss xmm1, [ebp+0x18]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x40
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ebx
	mov [edx+0xc], ecx
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov [edx+0x10], esi
	movss xmm0, dword [ebp+0x24]
	movss [edx+0x14], xmm0
	movss xmm0, dword [ebp+0x28]
	movss [edx+0x18], xmm0
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x60
	lea edx, [eax+tess]
	movss xmm0, dword [ebp+0xc]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ebx
	mov [edx+0xc], ecx
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov [edx+0x10], esi
	movss xmm1, dword [ebp+0x1c]
	movss [edx+0x14], xmm1
	movss xmm0, dword [ebp+0x28]
	movss [edx+0x18], xmm0
	add dword [tess+0x22a94c], 0x4
	add dword [tess+0x22a948], 0x6
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;RB_InitCodeImages()
_Z17RB_InitCodeImagesv:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	mov eax, gfxCmdBufInput
	mov ebx, rgp
	mov edx, [ebx+0x200c]
	mov [eax+0x3a0], edx
	mov byte [eax+0x40c], 0x1
	mov ecx, rg
	mov dword [ecx+0x2270], 0x0
	mov edx, [ebx+0x2008]
	mov [eax+0x3a4], edx
	mov byte [eax+0x40d], 0x1
	mov dword [ecx+0x2274], 0x0
	mov edx, [ebx+0x201c]
	mov [eax+0x3a8], edx
	mov byte [eax+0x40e], 0x1
	mov dword [ecx+0x2278], 0x0
	mov dword [eax+0x3ac], 0x0
	mov byte [eax+0x40f], 0xe2
	mov dword [ecx+0x227c], 0x0
	mov esi, gfxRenderTargets
	mov edx, [esi+0xb4]
	mov [eax+0x3b8], edx
	mov byte [eax+0x412], 0x62
	mov dword [ecx+0x2288], _cstring_shadowcookiesamp
	mov edx, gfxMetrics
	movzx ebx, byte [edx+0x24]
	mov edx, [esi+0x104]
	mov [eax+0x3bc], edx
	mov [eax+0x413], bl
	mov dword [ecx+0x228c], _cstring_shadowmapsampler
	mov dword [eax+0x3c0], 0x0
	mov [eax+0x414], bl
	mov dword [ecx+0x2290], _cstring_shadowmapsampler1
	mov dword [eax+0x3c4], 0x0
	mov byte [eax+0x415], 0x62
	mov dword [ecx+0x2294], _cstring_feedbacksampler
	mov dword [eax+0x3c8], 0x0
	mov byte [eax+0x416], 0x62
	mov dword [ecx+0x2298], 0x0
	mov dword [eax+0x3cc], 0x0
	mov byte [eax+0x417], 0x62
	mov dword [ecx+0x229c], 0x0
	mov edx, [esi+0xdc]
	mov [eax+0x3d0], edx
	mov byte [eax+0x418], 0x62
	mov dword [ecx+0x22a0], _cstring_posteffect0
	mov edx, [esi+0xf0]
	mov [eax+0x3d4], edx
	mov byte [eax+0x419], 0x62
	mov dword [ecx+0x22a4], _cstring_posteffect1
	mov dword [eax+0x3d8], 0x0
	mov byte [eax+0x41a], 0x0
	mov dword [ecx+0x22a8], _cstring_samplersky
	mov dword [eax+0x3dc], 0x0
	mov byte [eax+0x41b], 0x0
	mov dword [ecx+0x22ac], _cstring_attenuationsampl
	mov dword [eax+0x3e0], 0x0
	mov byte [eax+0x41c], 0x62
	mov dword [ecx+0x22b0], 0x0
	mov dword [eax+0x3e4], 0x0
	mov byte [eax+0x41d], 0x62
	mov dword [ecx+0x22b4], 0x0
	mov edx, [esi+0x64]
	mov [eax+0x3e8], edx
	mov byte [eax+0x41e], 0x61
	mov dword [ecx+0x22b8], 0x0
	mov dword [eax+0x3f8], 0x0
	mov byte [eax+0x422], 0x62
	mov dword [ecx+0x22c8], _cstring_cinematicy
	mov dword [eax+0x3fc], 0x0
	mov byte [eax+0x423], 0x62
	mov dword [ecx+0x22cc], _cstring_cinematiccr
	mov dword [eax+0x400], 0x0
	mov byte [eax+0x424], 0x62
	mov dword [ecx+0x22d0], _cstring_cinematiccb
	mov dword [eax+0x404], 0x0
	mov byte [eax+0x425], 0x62
	mov dword [ecx+0x22d4], _cstring_cinematica
	pop ebx
	pop esi
	pop ebp
	ret


;RB_DrawTextInSpace(char const*, Font_s*, float const*, float const*, float const*, unsigned long)
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0xbc
	mov ebx, [ebp+0x10]
	mov eax, [ebp+0xc]
	mov eax, [eax+0xc]
	mov [ebp-0x60], eax
	mov ecx, [tess+0x22a948]
	test ecx, ecx
	jnz _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_10
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_70:
	mov eax, gfxCmdBufSourceState
	mov [esp], eax
	call _Z7R_Set3DP20GfxCmdBufSourceState
	movss xmm1, dword [_float__0_50000000]
	mov edx, [ebp+0x14]
	movss xmm0, dword [edx]
	mulss xmm0, xmm1
	movss [ebp-0x2c], xmm0
	addss xmm0, [ebx]
	movss [ebp-0x2c], xmm0
	add edx, 0x4
	mov [ebp-0x5c], edx
	mov eax, [ebp+0x14]
	movss xmm0, dword [eax+0x4]
	mulss xmm0, xmm1
	movss [ebp-0x30], xmm0
	addss xmm0, [ebx+0x4]
	movss [ebp-0x30], xmm0
	add eax, 0x8
	mov [ebp-0x58], eax
	mov eax, [ebp+0x14]
	movss xmm0, dword [eax+0x8]
	mulss xmm0, xmm1
	movss [ebp-0x34], xmm0
	addss xmm0, [ebx+0x8]
	movss [ebp-0x34], xmm0
	mov eax, [ebp+0x18]
	movss xmm0, dword [eax]
	mulss xmm0, xmm1
	addss xmm0, [ebp-0x2c]
	movss [ebp-0x2c], xmm0
	add eax, 0x4
	mov [ebp-0x54], eax
	mov edx, [ebp+0x18]
	movss xmm0, dword [edx+0x4]
	mulss xmm0, xmm1
	addss xmm0, [ebp-0x30]
	movss [ebp-0x30], xmm0
	add edx, 0x8
	mov [ebp-0x50], edx
	mov eax, [ebp+0x18]
	mulss xmm1, [eax+0x8]
	addss xmm1, [ebp-0x34]
	movss [ebp-0x34], xmm1
	mov eax, [ebp+0x8]
	cmp byte [eax], 0x0
	jnz _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_20
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_60:
	mov edx, [tess+0x22a948]
	test edx, edx
	jz _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_30
	call _Z17RB_EndTessSurfacev
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_30:
	add esp, 0xbc
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_20:
	mov dword [esp+0x4], 0x0
	lea edx, [ebp+0x8]
	mov [esp], edx
	call _Z22SEH_ReadCharFromStringPPKcPi
	mov [esp+0x4], eax
	mov eax, [ebp+0xc]
	mov [esp], eax
	call _Z19R_GetCharacterGlyphP6Font_sj
	mov [ebp-0x64], eax
	mov edx, eax
	movsx eax, byte [eax+0x2]
	cvtsi2ss xmm0, eax
	mov eax, [ebp+0x14]
	movss xmm1, dword [eax]
	movss [ebp-0x70], xmm1
	movaps xmm5, xmm1
	mulss xmm5, xmm0
	addss xmm5, [ebp-0x2c]
	mov eax, [ebp-0x5c]
	movss xmm1, dword [eax]
	movss [ebp-0x6c], xmm1
	movaps xmm6, xmm1
	mulss xmm6, xmm0
	addss xmm6, [ebp-0x30]
	mov eax, [ebp-0x58]
	movss xmm4, dword [eax]
	movaps xmm7, xmm0
	mulss xmm7, xmm4
	addss xmm7, [ebp-0x34]
	movsx eax, byte [edx+0x3]
	cvtsi2ss xmm0, eax
	mov edx, [ebp+0x18]
	movss xmm3, dword [edx]
	movaps xmm1, xmm0
	mulss xmm1, xmm3
	addss xmm5, xmm1
	mov eax, [ebp-0x54]
	movss xmm2, dword [eax]
	movaps xmm1, xmm0
	mulss xmm1, xmm2
	addss xmm6, xmm1
	mov edx, [ebp-0x50]
	movss xmm1, dword [edx]
	movss [ebp-0xac], xmm1
	mulss xmm0, xmm1
	addss xmm7, xmm0
	mov edx, [ebp-0x64]
	movzx eax, byte [edx+0x5]
	cvtsi2ss xmm0, eax
	movss xmm1, dword [ebp-0x70]
	mulss xmm1, xmm0
	movss [ebp-0x44], xmm1
	movss xmm1, dword [ebp-0x6c]
	mulss xmm1, xmm0
	movss [ebp-0x48], xmm1
	mulss xmm4, xmm0
	movss [ebp-0x4c], xmm4
	movzx eax, byte [edx+0x6]
	cvtsi2ss xmm0, eax
	mulss xmm3, xmm0
	movss [ebp-0x38], xmm3
	mulss xmm2, xmm0
	movss [ebp-0x3c], xmm2
	movss xmm1, dword [ebp-0xac]
	mulss xmm1, xmm0
	movss [ebp-0x40], xmm1
	mov dword [esp+0x4], 0x4
	mov eax, [ebp-0x60]
	mov [esp], eax
	movss [ebp-0x88], xmm5
	movss [ebp-0x98], xmm6
	movss [ebp-0xa8], xmm7
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov edx, [tess+0x22a94c]
	lea eax, [edx+0x4]
	cmp eax, 0x154a
	movss xmm5, dword [ebp-0x88]
	movss xmm6, dword [ebp-0x98]
	movss xmm7, dword [ebp-0xa8]
	jg _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_40
	mov esi, [tess+0x22a948]
	lea eax, [esi+0x6]
	cmp eax, 0x100000
	jle _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_50
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_40:
	movss [ebp-0x88], xmm5
	movss [ebp-0x98], xmm6
	movss [ebp-0xa8], xmm7
	call _Z15RB_TessOverflowv
	mov edx, [tess+0x22a94c]
	mov esi, [tess+0x22a948]
	movss xmm7, dword [ebp-0xa8]
	movss xmm6, dword [ebp-0x98]
	movss xmm5, dword [ebp-0x88]
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_50:
	mov ebx, edx
	movzx edx, si
	lea eax, [ebx+0x4]
	mov [tess+0x22a94c], eax
	lea eax, [esi+0x6]
	mov [tess+0x22a948], eax
	lea eax, [ebx+0x3]
	mov [edx+edx+tess+0x2a940], ax
	mov [edx+edx+tess+0x2a942], bx
	lea eax, [ebx+0x2]
	mov [edx+edx+tess+0x2a944], ax
	mov [edx+edx+tess+0x2a946], ax
	mov [edx+edx+tess+0x2a948], bx
	lea eax, [ebx+0x1]
	mov [edx+edx+tess+0x2a94a], ax
	mov edx, [ebp+0x1c]
	mov [ebp-0x1c], edx
	mov eax, [ebp-0x64]
	mov esi, [eax+0xc]
	mov edx, [eax+0x8]
	movzx ecx, bx
	shl ecx, 0x5
	lea eax, [ecx+tess]
	movss [ecx+tess], xmm5
	movss [eax+0x4], xmm6
	movss [eax+0x8], xmm7
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov ebx, [ebp-0x1c]
	mov [eax+0x10], ebx
	mov [eax+0x14], edx
	mov [eax+0x18], esi
	mov edx, [ebp-0x64]
	mov edi, [edx+0xc]
	mov esi, [edx+0x10]
	movss xmm2, dword [ebp-0x4c]
	addss xmm2, xmm7
	movss xmm1, dword [ebp-0x48]
	addss xmm1, xmm6
	movss xmm0, dword [ebp-0x44]
	addss xmm0, xmm5
	lea edx, [ecx+0x20]
	lea eax, [edx+tess]
	movss [edx+tess], xmm0
	movss [eax+0x4], xmm1
	movss [eax+0x8], xmm2
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], ebx
	mov [eax+0x14], esi
	mov [eax+0x18], edi
	mov eax, [ebp-0x64]
	mov edi, [eax+0x14]
	mov esi, [eax+0x10]
	lea edx, [ecx+0x40]
	lea eax, [edx+tess]
	addss xmm0, [ebp-0x38]
	movss [edx+tess], xmm0
	addss xmm1, [ebp-0x3c]
	movss [eax+0x4], xmm1
	addss xmm2, [ebp-0x40]
	movss [eax+0x8], xmm2
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], ebx
	mov [eax+0x14], esi
	mov [eax+0x18], edi
	mov edx, [ebp-0x64]
	mov esi, [edx+0x14]
	mov edx, [edx+0x8]
	add ecx, 0x60
	lea eax, [ecx+tess]
	addss xmm5, [ebp-0x38]
	movss [ecx+tess], xmm5
	addss xmm6, [ebp-0x3c]
	movss [eax+0x4], xmm6
	addss xmm7, [ebp-0x40]
	movss [eax+0x8], xmm7
	mov dword [eax+0xc], 0x3f800000
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], ebx
	mov [eax+0x14], edx
	mov [eax+0x18], esi
	mov edx, [ebp-0x64]
	movzx eax, byte [edx+0x4]
	cvtsi2ss xmm0, eax
	movaps xmm1, xmm0
	mov eax, [ebp+0x14]
	mulss xmm1, [eax]
	addss xmm1, [ebp-0x2c]
	movss [ebp-0x2c], xmm1
	movaps xmm1, xmm0
	mov edx, [ebp-0x5c]
	mulss xmm1, [edx]
	addss xmm1, [ebp-0x30]
	movss [ebp-0x30], xmm1
	mov eax, [ebp-0x58]
	mulss xmm0, [eax]
	addss xmm0, [ebp-0x34]
	movss [ebp-0x34], xmm0
	mov eax, [ebp+0x8]
	cmp byte [eax], 0x0
	jnz _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_20
	jmp _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_60
_Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_10:
	call _Z17RB_EndTessSurfacev
	jmp _Z18RB_DrawTextInSpacePKcP6Font_sPKfS4_S4_m_70
	nop


;RB_FullScreenFilter(Material const*)
_Z19RB_FullScreenFilterPK8Material:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x30
	mov esi, [ebp+0x8]
	mov ecx, [tess+0x22a948]
	test ecx, ecx
	jz _Z19RB_FullScreenFilterPK8Material_10
	call _Z17RB_EndTessSurfacev
_Z19RB_FullScreenFilterPK8Material_10:
	mov ebx, gfxCmdBufSourceState
	mov [esp], ebx
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov eax, 0x3f800000
	mov [esp+0x20], eax
	mov [esp+0x1c], eax
	xor eax, eax
	mov [esp+0x18], eax
	mov [esp+0x14], eax
	cvtsi2ss xmm0, dword [ebx+0xf6c]
	movss [esp+0x10], xmm0
	cvtsi2ss xmm0, dword [ebx+0xf68]
	movss [esp+0xc], xmm0
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	add esp, 0x30
	pop ebx
	pop esi
	pop ebp
	jmp _Z17RB_EndTessSurfacev


;RB_InitCodeConstants()
_Z20RB_InitCodeConstantsv:
	push ebp
	mov ebp, esp
	pop ebp
	ret
	nop


;RB_SplitScreenFilter(Material const*, GfxViewInfo const*)
_Z20RB_SplitScreenFilterPK8MaterialPK11GfxViewInfo:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov edi, [ebp+0x8]
	mov esi, [ebp+0xc]
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z20RB_SplitScreenFilterPK8MaterialPK11GfxViewInfo_10
	call _Z17RB_EndTessSurfacev
_Z20RB_SplitScreenFilterPK8MaterialPK11GfxViewInfo_10:
	mov ebx, gfxCmdBufSourceState
	mov [esp], ebx
	call _Z7R_Set2DP20GfxCmdBufSourceState
	cvtsi2ss xmm5, dword [esi+0x16c]
	cvtsi2ss xmm4, dword [esi+0x170]
	cvtsi2ss xmm3, dword [ebx+0xf68]
	cvtsi2ss xmm0, dword [ebx+0xf6c]
	cvtsi2ss xmm2, dword [esi+0x164]
	divss xmm2, xmm3
	cvtsi2ss xmm1, dword [esi+0x168]
	divss xmm1, xmm0
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	movaps xmm6, xmm4
	divss xmm6, xmm0
	movaps xmm0, xmm6
	addss xmm0, xmm1
	movss [esp+0x20], xmm0
	movaps xmm0, xmm5
	divss xmm0, xmm3
	addss xmm0, xmm2
	movss [esp+0x1c], xmm0
	movss [esp+0x18], xmm1
	movss [esp+0x14], xmm2
	movss [esp+0x10], xmm4
	movss [esp+0xc], xmm5
	xor eax, eax
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	jmp _Z17RB_EndTessSurfacev


;R_ShowDirtyDiscError()
_Z20R_ShowDirtyDiscErrorv:
	push ebp
	mov ebp, esp
	pop ebp
	ret
	nop


;RB_DrawStretchPicFlipST(Material const*, float, float, float, float, float, float, float, float, unsigned long, GfxPrimStatsTarget)
_Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x1c
	mov edi, [ebp+0x1c]
	mov esi, [ebp+0x2c]
	mov dword [esp+0x4], 0x4
	mov eax, [ebp+0x8]
	mov [esp], eax
	call _Z19RB_SetTessTechniquePK8Material21MaterialTechniqueType
	mov ebx, [tess+0x22a94c]
	lea eax, [ebx+0x4]
	cmp eax, 0x154a
	jg _Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget_10
	mov ecx, [tess+0x22a948]
	lea eax, [ecx+0x6]
	cmp eax, 0x100000
	jle _Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget_20
_Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget_10:
	call _Z15RB_TessOverflowv
	mov ebx, [tess+0x22a94c]
	mov ecx, [tess+0x22a948]
_Z23RB_DrawStretchPicFlipSTPK8Materialffffffffm18GfxPrimStatsTarget_20:
	mov edx, ebx
	lea eax, [edx+0x3]
	mov [ecx+ecx+tess+0x2a940], ax
	mov [ecx+ecx+tess+0x2a942], bx
	lea eax, [edx+0x2]
	mov [ecx+ecx+tess+0x2a944], ax
	mov [ecx+ecx+tess+0x2a946], ax
	mov [ecx+ecx+tess+0x2a948], bx
	add edx, 0x1
	mov [ecx+ecx+tess+0x2a94a], dx
	mov edx, ebx
	shl edx, 0x5
	lea eax, [edx+tess]
	movss xmm0, dword [ebp+0xc]
	movss [edx+tess], xmm0
	movss xmm1, dword [ebp+0x10]
	movss [eax+0x4], xmm1
	xor ebx, ebx
	mov [eax+0x8], ebx
	mov ecx, 0x3f800000
	mov [eax+0xc], ecx
	mov dword [eax+0x1c], 0x3ffe7f7f
	mov [eax+0x10], esi
	mov [eax+0x14], edi
	movss xmm0, dword [ebp+0x20]
	movss [eax+0x18], xmm0
	movss xmm0, dword [ebp+0xc]
	addss xmm0, [ebp+0x14]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x20
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ebx
	mov [edx+0xc], ecx
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov [edx+0x10], esi
	mov [edx+0x14], edi
	movss xmm1, dword [ebp+0x28]
	movss [edx+0x18], xmm1
	movss xmm1, dword [ebp+0x10]
	addss xmm1, [ebp+0x18]
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x40
	lea edx, [eax+tess]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ebx
	mov [edx+0xc], ecx
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov [edx+0x10], esi
	movss xmm0, dword [ebp+0x24]
	movss [edx+0x14], xmm0
	movss xmm0, dword [ebp+0x28]
	movss [edx+0x18], xmm0
	mov eax, [tess+0x22a94c]
	shl eax, 0x5
	add eax, 0x60
	lea edx, [eax+tess]
	movss xmm0, dword [ebp+0xc]
	movss [eax+tess], xmm0
	movss [edx+0x4], xmm1
	mov [edx+0x8], ebx
	mov [edx+0xc], ecx
	mov dword [edx+0x1c], 0x3ffe7f7f
	mov [edx+0x10], esi
	movss xmm1, dword [ebp+0x24]
	movss [edx+0x14], xmm1
	movss xmm0, dword [ebp+0x20]
	movss [edx+0x18], xmm0
	add dword [tess+0x22a94c], 0x4
	add dword [tess+0x22a948], 0x6
	add esp, 0x1c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret


;R_SetVertex4dWithNormal(GfxVertex*, float, float, float, float, float, float, float, float, float, unsigned char const*)
_Z23R_SetVertex4dWithNormalP9GfxVertexfffffffffPKh:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	xor edx, edx
	mov ecx, [ebp+0x8]
	mov eax, [ebp+0xc]
	mov [ecx], eax
	mov eax, [ebp+0x10]
	mov [ecx+0x4], eax
	mov eax, [ebp+0x14]
	mov [ecx+0x8], eax
	mov eax, [ebp+0x18]
	mov [ecx+0xc], eax
	movss xmm1, dword [_float_127_00000000]
	movss xmm0, dword [ebp+0x1c]
	mulss xmm0, xmm1
	movss xmm2, dword [_float_127_50000000]
	addss xmm0, xmm2
	cvttss2si eax, xmm0
	mov dl, al
	movss xmm0, dword [ebp+0x20]
	mulss xmm0, xmm1
	addss xmm0, xmm2
	cvttss2si eax, xmm0
	mov dh, al
	mulss xmm1, [ebp+0x24]
	addss xmm1, xmm2
	cvttss2si eax, xmm1
	movzx eax, al
	shl eax, 0x10
	and edx, 0xff00ffff
	or edx, eax
	and edx, 0xffffff
	or edx, 0x3f000000
	mov [ecx+0x1c], edx
	mov eax, [ebp+0x30]
	mov eax, [eax]
	mov [ecx+0x10], eax
	mov eax, [ebp+0x28]
	mov [ecx+0x14], eax
	mov eax, [ebp+0x2c]
	mov [ecx+0x18], eax
	leave
	ret


;RB_RegisterBackendAssets()
_Z24RB_RegisterBackendAssetsv:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	mov dword [esp+0x4], 0x1
	mov dword [esp], _cstring_fontssmalldevfon
	call _Z14R_RegisterFontPKci
	mov [backEnd+0x8], eax
	leave
	ret
	nop


;RB_FullScreenColoredFilter(Material const*, unsigned long)
_Z26RB_FullScreenColoredFilterPK8Materialm:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x3c
	mov edi, [ebp+0x8]
	mov esi, [ebp+0xc]
	mov ebx, [tess+0x22a948]
	test ebx, ebx
	jz _Z26RB_FullScreenColoredFilterPK8Materialm_10
	call _Z17RB_EndTessSurfacev
_Z26RB_FullScreenColoredFilterPK8Materialm_10:
	mov ebx, gfxCmdBufSourceState
	mov [esp], ebx
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov dword [esp+0x28], 0x9
	mov [esp+0x24], esi
	mov eax, 0x3f800000
	mov [esp+0x20], eax
	mov [esp+0x1c], eax
	xor eax, eax
	mov [esp+0x18], eax
	mov [esp+0x14], eax
	cvtsi2ss xmm0, dword [ebx+0xf6c]
	movss [esp+0x10], xmm0
	cvtsi2ss xmm0, dword [ebx+0xf68]
	movss [esp+0xc], xmm0
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	add esp, 0x3c
	pop ebx
	pop esi
	pop edi
	pop ebp
	jmp _Z17RB_EndTessSurfacev
	nop



;RB_DrawFullScreenColoredQuad(Material const*, float, float, float, float, unsigned long)
_Z28RB_DrawFullScreenColoredQuadPK8Materialffffm:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x4c
	mov eax, [ebp+0x8]
	mov [ebp-0x1c], eax
	movss xmm0, dword [ebp+0xc]
	movss [ebp-0x20], xmm0
	movss xmm0, dword [ebp+0x10]
	movss [ebp-0x24], xmm0
	movss xmm0, dword [ebp+0x14]
	movss [ebp-0x28], xmm0
	mov edi, [ebp+0x18]
	mov esi, [ebp+0x1c]
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z28RB_DrawFullScreenColoredQuadPK8Materialffffm_10
	call _Z17RB_EndTessSurfacev
_Z28RB_DrawFullScreenColoredQuadPK8Materialffffm_10:
	mov ebx, gfxCmdBufSourceState
	mov [esp], ebx
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov dword [esp+0x28], 0x9
	mov [esp+0x24], esi
	mov [esp+0x20], edi
	movss xmm0, dword [ebp-0x28]
	movss [esp+0x1c], xmm0
	movss xmm0, dword [ebp-0x24]
	movss [esp+0x18], xmm0
	movss xmm0, dword [ebp-0x20]
	movss [esp+0x14], xmm0
	cvtsi2ss xmm0, dword [ebx+0xf6c]
	movss [esp+0x10], xmm0
	cvtsi2ss xmm0, dword [ebx+0xf68]
	movss [esp+0xc], xmm0
	xor eax, eax
	mov [esp+0x8], eax
	mov [esp+0x4], eax
	mov eax, [ebp-0x1c]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	add esp, 0x4c
	pop ebx
	pop esi
	pop edi
	pop ebp
	jmp _Z17RB_EndTessSurfacev
	nop


;RB_ExecuteRenderCommandsLoop(void const*)
_Z28RB_ExecuteRenderCommandsLoopPKv:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x24
	mov eax, [ebp+0x8]
	mov [ebp-0xc], eax
	movzx eax, word [eax]
	test ax, ax
	jnz _Z28RB_ExecuteRenderCommandsLoopPKv_10
_Z28RB_ExecuteRenderCommandsLoopPKv_40:
	mov eax, [tess+0x22a948]
	test eax, eax
	jz _Z28RB_ExecuteRenderCommandsLoopPKv_20
	call _Z17RB_EndTessSurfacev
_Z28RB_ExecuteRenderCommandsLoopPKv_20:
	add esp, 0x24
	pop ebx
	pop ebp
	ret
_Z28RB_ExecuteRenderCommandsLoopPKv_10:
	lea ebx, [ebp-0xc]
_Z28RB_ExecuteRenderCommandsLoopPKv_30:
	movzx eax, ax
	mov [esp], ebx
	call dword [eax*4+RB_RenderCommandTable]
	mov eax, [ebp-0xc]
	movzx eax, word [eax]
	test ax, ax
	jnz _Z28RB_ExecuteRenderCommandsLoopPKv_30
	jmp _Z28RB_ExecuteRenderCommandsLoopPKv_40


;Initialized global or static variables of rb_backend:
SECTION .data


;Initialized constant data of rb_backend:
SECTION .rdata
RB_RenderCommandTable: dd 0x0, _Z22RB_SetMaterialColorCmdP25GfxRenderCommandExecState, _Z16RB_SaveScreenCmdP25GfxRenderCommandExecState, _Z23RB_SaveScreenSectionCmdP25GfxRenderCommandExecState, _Z17RB_ClearScreenCmdP25GfxRenderCommandExecState, _Z17RB_SetViewportCmdP25GfxRenderCommandExecState, _Z16RB_StretchPicCmdP25GfxRenderCommandExecState, _Z22RB_StretchPicCmdFlipSTP25GfxRenderCommandExecState, _Z24RB_StretchPicRotateXYCmdP25GfxRenderCommandExecState, _Z24RB_StretchPicRotateSTCmdP25GfxRenderCommandExecState, _Z16RB_StretchRawCmdP25GfxRenderCommandExecState, _Z17RB_DrawQuadPicCmdP25GfxRenderCommandExecState, _Z31RB_DrawFullScreenColoredQuadCmdP25GfxRenderCommandExecState, _Z16RB_DrawText2DCmdP25GfxRenderCommandExecState, _Z16RB_DrawText3DCmdP25GfxRenderCommandExecState, _Z29RB_BlendSavedScreenBlurredCmdP25GfxRenderCommandExecState, _Z29RB_BlendSavedScreenFlashedCmdP25GfxRenderCommandExecState, _Z16RB_DrawPointsCmdP25GfxRenderCommandExecState, _Z15RB_DrawLinesCmdP25GfxRenderCommandExecState, _Z19RB_DrawTrianglesCmdP25GfxRenderCommandExecState, _Z19RB_ProjectionSetCmdP25GfxRenderCommandExecState, 0x0, 0x0, 0x0
rb_tessTable: dd _Z19R_TessTrianglesListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z26R_TessTrianglesPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z34R_TessStaticModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z28R_TessStaticModelPreTessListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z27R_TessStaticModelCachedListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z36R_TessStaticModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z12R_TessBModelPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z29R_TessXModelRigidDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z36R_TessXModelRigidSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z31R_TessXModelSkinnedDrawSurfListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z18R_TessCodeMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z18R_TessMarkMeshListPK19GfxDrawSurfListArgs16GfxCmdBufContext, _Z23R_TessParticleCloudListPK19GfxDrawSurfListArgs16GfxCmdBufContext, 0x0, 0x0, 0x0
_ZZ14RB_LookupColorhPhE11color_table: dd 0xff000000, 0xff5c5cff, 0xff00ff00, 0xff00ffff, 0xffff0000, 0xffffff00, 0xffff5cff, 0xffffffff, 0x80000000, 0x0, 0x0, 0x0, 0x80000000, 0x0, 0x0, 0x0, 0x80000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
_ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E10MY_OFFSETS: dd 0xbf800000, 0xbf800000, 0xbf800000, 0x3f800000, 0x3f800000, 0xbf800000, 0x3f800000, 0x3f800000
		db 0x0
_ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E25MY_ALTCOLOR_TWO_CINEMATIC: dd 0xdce6ffe6
_ZZ10DrawText2DPKcffP6Font_sffff8GfxColoriiicfS3_iiiiPK8MaterialS6_E15MY_ALTCOLOR_TWO: dd 0xdce6ffe6, 0x0, 0x0, 0x0, 0x0, 0x0
		db 0x0, 0x0, 0x0


;Zero initialized global or static variables of rb_backend:
SECTION .bss
backEnd: resb 0xc
backEndData: resb 0x14
tess: resb 0x22a960


;All cstrings:
SECTION .rdata
_cstring_direct3ddevice9p:		db "Direct3DDevice9::Present failed: %s",0ah,0
_cstring_shadowcookiesamp:		db "shadowCookieSampler",0
_cstring_shadowmapsampler:		db "shadowmapSamplerSun",0
_cstring_shadowmapsampler1:		db "shadowmapSamplerSpot",0
_cstring_feedbacksampler:		db "feedbackSampler",0
_cstring_posteffect0:		db "postEffect0",0
_cstring_posteffect1:		db "postEffect1",0
_cstring_samplersky:		db "sampler.sky",0
_cstring_attenuationsampl:		db "attenuationSampler",0
_cstring_cinematicy:		db "cinematicY",0
_cstring_cinematiccr:		db "cinematicCr",0
_cstring_cinematiccb:		db "cinematicCb",0
_cstring_cinematica:		db "cinematicA",0
_cstring_fontssmalldevfon:		db "fonts/smalldevfont",0



;All constant floats and doubles:
SECTION .rdata
_float_0_50000000:		dd 0x3f000000	; 0.5
_double_0_01745329:		dq 0x3f91df46a2529d39	; 0.0174533
_float_0_99000001:		dd 0x3f7d70a4	; 0.99
_float_252_44999695:		dd 0x437c7333	; 252.45
_float_255_00000000:		dd 0x437f0000	; 255
_float__0_00100000:		dd 0xba83126f	; -0.001
_float__0_50000000:		dd 0xbf000000	; -0.5
_float_1000_00000000:		dd 0x447a0000	; 1000
_float_30_00000000:		dd 0x41f00000	; 30
_float_1_00000000:		dd 0x3f800000	; 1
_float__0_75000000:		dd 0xbf400000	; -0.75
_float__0_12500000:		dd 0xbe000000	; -0.125
_float_0_06250000:		dd 0x3d800000	; 0.0625
_float_1_12500000:		dd 0x3f900000	; 1.125
_float_1_75000000:		dd 0x3fe00000	; 1.75
_float_2_00000000:		dd 0x40000000	; 2
_float_60_00000000:		dd 0x42700000	; 60
_float_0_06000000:		dd 0x3d75c28f	; 0.06
_float_127_00000000:		dd 0x42fe0000	; 127
_float_127_50000000:		dd 0x42ff0000	; 127.5
_double_30_00000000:		dq 0x403e000000000000	; 30
_double_36854775808_00000000:		dq 0x43e0000000000000	; 9.22337e+18

alignb 16
_data16_80000000:		dd 0x80000000, 0x0, 0x0, 0x0	; OWORD
