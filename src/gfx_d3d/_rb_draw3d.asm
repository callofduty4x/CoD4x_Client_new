;Imports of rb_draw3d:
	extern _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	extern _Z18PIXBeginNamedEventiPKcz
	extern _Z7R_Set2DP20GfxCmdBufSourceState
	extern rgp
	extern backEndData
	extern r_dx
	extern _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	extern gfxCmdBufState
	extern memcpy
	extern memset
	extern gfxCmdBufSourceState
	extern _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	extern _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	extern _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	extern gfxCmdBufContext
	extern developer
	extern _Z12RB_DrawDebugPK12GfxViewParms
	extern _Z15R_GetClearColorPf
	extern _Z13R_ClearScreenP16IDirect3DDevice9hPKffhPK11GfxViewport
	extern gfxDrawMethod
	extern gfxCmdBufInput
	extern _Z28RB_ExecuteRenderCommandsLoopPKv
	extern _Z21RB_ProcessPostEffectsPK11GfxViewInfo
	extern r_showFbColorDebug
	extern r_showFloatZDebug
	extern gfxRenderTargets
	extern tess
	extern _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	extern _Z17RB_EndTessSurfacev
	extern _Z21RB_DrawSunPostEffectsi
	extern _Z25RB_UsingColorManipulationPK11GfxViewInfo
	extern _Z36RB_ApplyColorManipulationSplitscreenPK11GfxViewInfo
	extern sc_showDebug
	extern sc_showOverlay
	extern _Z22RB_ShadowCookieOverlayv
	extern r_depthPrepass
	extern _Z13R_InitContextPK14GfxBackEndDataP9GfxCmdBuf
	extern _Z9R_DrawLitPK11GfxViewInfoP9GfxCmdBufS3_
	extern _Z11R_DrawDecalPK11GfxViewInfoP9GfxCmdBufS3_
	extern _Z10RB_DrawSuni
	extern rg
	extern _Z10R_DrawCallPFvPKv16GfxCmdBufContextS1_ES0_P20GfxCmdBufSourceStatePK11GfxViewInfoPK19GfxDrawSurfListInfoPK12GfxViewParmsP9GfxCmdBufSG_
	extern colorWhite
	extern _Z29R_SetupViewProjectionMatricesP12GfxViewParms
	extern _Z17R_InitDynamicMeshP11GfxMeshDatajjj
	extern _Z13R_SetQuadMeshP15GfxQuadMeshDataffffffffm
	extern _Z14R_DepthPrepass17GfxRenderTargetIdPK11GfxViewInfoP9GfxCmdBuf
	extern _Z21R_ShutdownDynamicMeshP11GfxMeshData
	extern _Z20RB_DrawShadowCookiesPK11GfxViewInfo
	extern _Z17RB_SpotShadowMapsPK14GfxBackEndDataPK11GfxViewInfo
	extern _Z9R_Resolve16GfxCmdBufContextP8GfxImage
	extern _Z21R_ConvertColorToBytesPKfPh
	extern floorf
	extern ceilf
	extern _Z17R_SetQuadMeshDataP11GfxMeshDataffffffffm
	extern _Z16RB_SunShadowMapsPK14GfxBackEndDataPK11GfxViewInfo
	extern _Z32R_DrawFullbrightEmissiveCallbackPKv16GfxCmdBufContextS1_
	extern _Z22R_DrawEmissiveCallbackPKv16GfxCmdBufContextS1_
	extern _Z27R_DrawPointLitSurfsCallbackPKv16GfxCmdBufContextS1_
	extern _Z28R_DrawDebugShaderLitCallbackPKv16GfxCmdBufContextS1_
	extern _Z30R_DrawDebugShaderDecalCallbackPKv16GfxCmdBufContextS1_
	extern _Z33R_DrawDebugShaderEmissiveCallbackPKv16GfxCmdBufContextS1_
	extern _Z27R_DrawFullbrightLitCallbackPKv16GfxCmdBufContextS1_
	extern _Z29R_DrawFullbrightDecalCallbackPKv16GfxCmdBufContextS1_
	extern _Z20RB_EndSceneRendering16GfxCmdBufContextPK14GfxCmdBufInputPK11GfxViewInfo


;Exports of rb_draw3d:
	global _Z15RB_Draw3DCommonv

SECTION .text



;RB_Draw3DCommon()
_Z15RB_Draw3DCommonv:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x10c
	mov dword [ebp-0x78], 0x0
	mov dword [ebp-0x74], 0x0
	mov dword [ebp-0x88], 0x0
	mov dword [ebp-0x84], 0x0
	mov dword [ebp-0x98], 0x0
	mov dword [ebp-0x94], 0x0
	mov dword [ebp-0xa8], 0x0
	mov dword [ebp-0xa4], 0x0
	mov dword [ebp-0xb0], 0x0
	mov dword [ebp-0xac], 0x0
	mov eax, gfxDrawMethod
	mov eax, [eax]
	cmp eax, 0x1
	jz _Z15RB_Draw3DCommonv_10
	cmp eax, 0x2
	jz _Z15RB_Draw3DCommonv_20
	test eax, eax
	jnz _Z15RB_Draw3DCommonv_30
_Z15RB_Draw3DCommonv_40:
	add esp, 0x10c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z15RB_Draw3DCommonv_30:
	mov eax, backEndData
	mov eax, [eax]
	mov [ebp-0x80], eax
	mov eax, [eax+0x11e6c4]
	test eax, eax
	jz _Z15RB_Draw3DCommonv_40
	mov dword [esp+0x4], _cstring_post_effects
	mov dword [esp], 0xffffffff
	call _Z18PIXBeginNamedEventiPKcz
	mov eax, [ebp-0x80]
	mov ecx, [eax+0x11e6c4]
	test ecx, ecx
	jnz _Z15RB_Draw3DCommonv_50
_Z15RB_Draw3DCommonv_180:
	mov eax, backEndData
	mov eax, [eax]
	mov esi, [eax+0x11e6c8]
	mov dword [esp+0x8], 0x0
	lea eax, [esi+0x6380]
	mov [esp+0x4], eax
	mov ebx, gfxCmdBufSourceState
	mov [esp], ebx
	call _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	mov dword [esp+0x4], 0x1
	mov [esp], ebx
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov eax, gfxCmdBufContext
	mov edx, [eax+0x4]
	mov eax, [eax]
	mov dword [esp+0x8], 0x1
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov [esp+0x8], esi
	lea eax, [esi+0x140]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	lea eax, [esi+0x164]
	mov [esp+0x4], eax
	mov [esp], ebx
	call _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	mov [esp], ebx
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov ebx, gfxCmdBufState
	mov dword [esp+0x8], 0xa10
	mov [esp+0x4], ebx
	mov [esp], ebx
	call memcpy
	lea eax, [ebx+0xd8]
	mov dword [esp+0x8], 0x100
	mov dword [esp+0x4], 0x0
	mov [esp], eax
	call memset
	add ebx, 0x1d8
	mov dword [esp+0x8], 0x800
	mov dword [esp+0x4], 0x0
	mov [esp], ebx
	call memset
	cmp dword [esi+0x184], 0x1
	jz _Z15RB_Draw3DCommonv_60
_Z15RB_Draw3DCommonv_220:
	mov eax, gfxCmdBufState
	mov dword [esp+0x8], 0xa10
	mov [esp+0x4], eax
	mov [esp], eax
	call memcpy
	add esp, 0x10c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z15RB_Draw3DCommonv_10:
	mov eax, gfxCmdBufContext
	mov edx, [eax+0x4]
	mov [ebp-0x44], edx
	mov esi, [eax]
	mov eax, backEndData
	mov edi, [eax]
	mov eax, [edi+0x11e6c4]
	test eax, eax
	jz _Z15RB_Draw3DCommonv_40
	mov dword [ebp-0x9c], 0x0
	mov dword [ebp-0x3c], 0x0
	lea eax, [edx+0xd8]
	mov [ebp-0xbc], eax
	add edx, 0x1d8
	mov [ebp-0xc4], edx
_Z15RB_Draw3DCommonv_80:
	mov ebx, [ebp-0x3c]
	add ebx, [edi+0x11e6c8]
	mov [ebx+0x67a8], edi
	mov dword [esp+0x8], 0x0
	mov eax, gfxCmdBufInput
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	mov [esi+0xca8], edi
	mov dword [esp+0x8], 0xa10
	mov eax, gfxCmdBufState
	mov [esp+0x4], eax
	mov edx, [ebp-0x44]
	mov [esp], edx
	call memcpy
	mov dword [esp+0x8], 0x100
	mov dword [esp+0x4], 0x0
	mov eax, [ebp-0xbc]
	mov [esp], eax
	call memset
	mov dword [esp+0x8], 0x800
	mov dword [esp+0x4], 0x0
	mov edx, [ebp-0xc4]
	mov [esp], edx
	call memset
	mov eax, [ebp-0x44]
	mov [ebp-0xa4], eax
	mov [ebp-0xa8], esi
	mov dword [esp+0x4], 0x2
	mov [esp], esi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov edx, [ebp-0xa4]
	mov [ebp-0x94], edx
	mov [ebp-0x98], esi
	mov dword [esp+0x8], 0x2
	mov eax, [ebp-0x98]
	mov edx, [ebp-0x94]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov [esp+0x8], ebx
	lea eax, [ebx+0x140]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	lea eax, [ebx+0x164]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	mov eax, [ebx+0x5688]
	test eax, eax
	jz _Z15RB_Draw3DCommonv_70
	mov [esp], eax
	call _Z28RB_ExecuteRenderCommandsLoopPKv
_Z15RB_Draw3DCommonv_70:
	mov dword [esp+0x8], 0xa10
	mov edx, [ebp-0x44]
	mov [esp+0x4], edx
	mov eax, gfxCmdBufState
	mov [esp], eax
	call memcpy
	add dword [ebp-0x9c], 0x1
	add dword [ebp-0x3c], 0x67b0
	mov edx, [ebp-0x9c]
	cmp [edi+0x11e6c4], edx
	ja _Z15RB_Draw3DCommonv_80
	jmp _Z15RB_Draw3DCommonv_40
_Z15RB_Draw3DCommonv_20:
	mov eax, gfxCmdBufContext
	mov edx, [eax+0x4]
	mov [ebp-0x40], edx
	mov esi, [eax]
	mov eax, backEndData
	mov edi, [eax]
	mov ebx, [edi+0x11e6c4]
	test ebx, ebx
	jz _Z15RB_Draw3DCommonv_40
	mov dword [ebp-0x8c], 0x0
	mov dword [ebp-0x38], 0x0
	lea eax, [edx+0xd8]
	mov [ebp-0xb8], eax
	add edx, 0x1d8
	mov [ebp-0xc0], edx
_Z15RB_Draw3DCommonv_100:
	mov ebx, [ebp-0x38]
	add ebx, [edi+0x11e6c8]
	mov [ebx+0x67a8], edi
	mov dword [esp+0x8], 0x0
	mov eax, gfxCmdBufInput
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	mov [esi+0xca8], edi
	mov dword [esp+0x8], 0xa10
	mov eax, gfxCmdBufState
	mov [esp+0x4], eax
	mov edx, [ebp-0x40]
	mov [esp], edx
	call memcpy
	mov dword [esp+0x8], 0x100
	mov dword [esp+0x4], 0x0
	mov eax, [ebp-0xb8]
	mov [esp], eax
	call memset
	mov dword [esp+0x8], 0x800
	mov dword [esp+0x4], 0x0
	mov edx, [ebp-0xc0]
	mov [esp], edx
	call memset
	mov eax, [ebp-0x40]
	mov [ebp-0xac], eax
	mov [ebp-0xb0], esi
	mov dword [esp+0x4], 0x2
	mov [esp], esi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov edx, [ebp-0xac]
	mov [ebp-0x84], edx
	mov [ebp-0x88], esi
	mov dword [esp+0x8], 0x2
	mov eax, [ebp-0x88]
	mov edx, [ebp-0x84]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov [esp+0x8], ebx
	lea eax, [ebx+0x140]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	lea eax, [ebx+0x164]
	mov [esp+0x4], eax
	mov [esp], esi
	call _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	mov eax, [ebx+0x5688]
	test eax, eax
	jz _Z15RB_Draw3DCommonv_90
	mov [esp], eax
	call _Z28RB_ExecuteRenderCommandsLoopPKv
_Z15RB_Draw3DCommonv_90:
	mov dword [esp+0x8], 0xa10
	mov edx, [ebp-0x40]
	mov [esp+0x4], edx
	mov eax, gfxCmdBufState
	mov [esp], eax
	call memcpy
	add dword [ebp-0x8c], 0x1
	add dword [ebp-0x38], 0x67b0
	mov edx, [ebp-0x8c]
	cmp [edi+0x11e6c4], edx
	ja _Z15RB_Draw3DCommonv_100
	jmp _Z15RB_Draw3DCommonv_40
_Z15RB_Draw3DCommonv_50:
	mov dword [ebp-0x7c], 0x0
	mov dword [ebp-0x34], 0x0
	mov edi, gfxCmdBufSourceState
	mov edx, gfxCmdBufState
	add edx, 0x1d8
	mov [ebp-0xb4], edx
	mov eax, gfxCmdBufState
	mov [ebp-0xc8], eax
	mov edx, [ebp-0x80]
	jmp _Z15RB_Draw3DCommonv_110
_Z15RB_Draw3DCommonv_190:
	mov [esp], eax
	call _Z21RB_ProcessPostEffectsPK11GfxViewInfo
	mov dword [esp+0x4], 0x1
	mov [esp], edi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov dword [esp+0x8], 0x1
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov eax, r_showFbColorDebug
	mov eax, [eax]
	mov eax, [eax+0xc]
	cmp eax, 0x1
	jz _Z15RB_Draw3DCommonv_120
	cmp eax, 0x2
	jz _Z15RB_Draw3DCommonv_130
	mov eax, r_showFloatZDebug
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z15RB_Draw3DCommonv_140
	mov eax, gfxRenderTargets
	mov ebx, [eax+0x68]
	test ebx, ebx
	jz _Z15RB_Draw3DCommonv_150
	mov eax, tess
	mov ecx, [eax+0x22a948]
	test ecx, ecx
	jnz _Z15RB_Draw3DCommonv_160
_Z15RB_Draw3DCommonv_270:
	cvtsi2ss xmm1, dword [edi+0xf68]
	mulss xmm1, [_float_0_50000000]
	cvtsi2ss xmm0, dword [edi+0xf6c]
	mulss xmm0, [_float_0_50000000]
	mov [esp], edi
	movss [ebp-0xd8], xmm0
	movss [ebp-0xe8], xmm1
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f400000
	mov dword [esp+0x1c], 0x3f400000
	mov dword [esp+0x18], 0x3e800000
	mov dword [esp+0x14], 0x3e800000
	movss xmm0, dword [ebp-0xd8]
	movss [esp+0x10], xmm0
	movss xmm1, dword [ebp-0xe8]
	movss [esp+0xc], xmm1
	mulss xmm0, [_float_0_50000000]
	movss [esp+0x8], xmm0
	mulss xmm1, [_float_0_50000000]
	movss [esp+0x4], xmm1
	mov edx, rgp
	mov eax, [edx+0x208c]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
_Z15RB_Draw3DCommonv_150:
	mov dword [esp+0x4], 0x1
	mov [esp], edi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov eax, gfxCmdBufContext
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov dword [esp+0x8], 0x1
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov edx, [ebp-0x70]
	mov eax, [edx+0x13a0]
	mov [esp], eax
	call _Z21RB_DrawSunPostEffectsi
	mov dword [esp+0x8], 0xa10
	mov eax, [ebp-0xc8]
	mov [esp+0x4], eax
	mov [esp], eax
	call memcpy
	mov dword [esp+0x8], 0x0
	mov eax, gfxCmdBufInput
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	mov eax, backEndData
	mov eax, [eax]
	mov [edi+0xca8], eax
	mov dword [esp+0x8], 0xa10
	mov edx, [ebp-0xc8]
	mov [esp+0x4], edx
	mov [esp], edx
	call memcpy
	mov eax, [ebp-0xc8]
	add eax, 0xd8
	mov dword [esp+0x8], 0x100
	mov dword [esp+0x4], 0x0
	mov [esp], eax
	call memset
	mov eax, [ebp-0xc8]
	add eax, 0x1d8
	mov dword [esp+0x8], 0x800
	mov dword [esp+0x4], 0x0
	mov [esp], eax
	call memset
	mov dword [esp+0x4], 0x1
	mov [esp], edi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov dword [esp+0x8], 0x1
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov eax, [ebp-0x70]
	mov [esp+0x8], eax
	mov edx, [ebp-0x2c]
	mov [esp+0x4], edx
	mov [esp], edi
	call _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	mov eax, [ebp-0x30]
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	mov edx, [ebp-0x70]
	mov eax, [edx+0x5688]
	test eax, eax
	jz _Z15RB_Draw3DCommonv_170
	mov [esp], eax
	call _Z28RB_ExecuteRenderCommandsLoopPKv
_Z15RB_Draw3DCommonv_170:
	mov dword [esp+0x8], 0xa10
	mov eax, [ebp-0xc8]
	mov [esp+0x4], eax
	mov [esp], eax
	call memcpy
	add dword [ebp-0x7c], 0x1
	add dword [ebp-0x34], 0x67b0
	mov eax, [ebp-0x7c]
	mov edx, [ebp-0x80]
	cmp [edx+0x11e6c4], eax
	jbe _Z15RB_Draw3DCommonv_180
_Z15RB_Draw3DCommonv_110:
	mov eax, [ebp-0x34]
	add eax, [edx+0x11e6c8]
	mov [ebp-0x70], eax
	mov [eax+0x67a8], edx
	mov dword [esp+0x8], 0x0
	mov eax, [ebp-0x70]
	add eax, 0x6380
	mov [esp+0x4], eax
	mov [esp], edi
	call _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	mov dword [esp+0x8], 0xa10
	mov edx, gfxCmdBufState
	mov [esp+0x4], edx
	mov [esp], edx
	call memcpy
	mov eax, gfxCmdBufState
	add eax, 0xd8
	mov dword [esp+0x8], 0x100
	mov dword [esp+0x4], 0x0
	mov [esp], eax
	call memset
	mov dword [esp+0x8], 0x800
	mov dword [esp+0x4], 0x0
	mov eax, [ebp-0xb4]
	mov [esp], eax
	call memset
	mov eax, gfxCmdBufContext
	mov ebx, [eax]
	mov esi, [eax+0x4]
	mov dword [esp+0x4], 0x2
	mov [esp], ebx
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov [ebp-0x74], esi
	mov [ebp-0x78], ebx
	mov dword [esp+0x8], 0x2
	mov eax, [ebp-0x78]
	mov edx, [ebp-0x74]
	mov [esp], eax
	mov [esp+0x4], edx
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov edx, [ebp-0x70]
	add edx, 0x140
	mov [ebp-0x2c], edx
	mov eax, [ebp-0x70]
	mov [esp+0x8], eax
	mov [esp+0x4], edx
	mov [esp], edi
	call _Z11R_BeginViewP20GfxCmdBufSourceStatePK11GfxSceneDefPK12GfxViewParms
	mov edx, [ebp-0x70]
	add edx, 0x164
	mov [ebp-0x30], edx
	mov [esp+0x4], edx
	mov [esp], edi
	call _Z19R_SetViewportStructP20GfxCmdBufSourceStatePK11GfxViewport
	mov eax, [ebp-0x70]
	mov edx, [eax+0x13a4]
	test edx, edx
	jnz _Z15RB_Draw3DCommonv_190
	mov [esp], eax
	call _Z25RB_UsingColorManipulationPK11GfxViewInfo
	test al, al
	jz _Z15RB_Draw3DCommonv_150
	mov edx, [ebp-0x70]
	mov [esp], edx
	call _Z36RB_ApplyColorManipulationSplitscreenPK11GfxViewInfo
	jmp _Z15RB_Draw3DCommonv_150
_Z15RB_Draw3DCommonv_120:
	mov edx, tess
	mov eax, [edx+0x22a948]
	test eax, eax
	jnz _Z15RB_Draw3DCommonv_200
_Z15RB_Draw3DCommonv_250:
	mov [esp], edi
	call _Z7R_Set2DP20GfxCmdBufSourceState
	cvtsi2ss xmm0, dword [edi+0xf68]
	movss [ebp-0x6c], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x6c]
	movss [ebp-0x6c], xmm0
	cvtsi2ss xmm0, dword [edi+0xf6c]
	movss [ebp-0x68], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x68]
	movss [ebp-0x68], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x6c]
	movss [ebp-0x64], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x68]
	movss [ebp-0x60], xmm0
	mov dword [ebp-0x1c], 0xffff0000
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffff0000
	mov dword [esp+0x20], 0x3f800000
	mov dword [esp+0x1c], 0x3f800000
	mov dword [esp+0x18], 0x0
	mov dword [esp+0x14], 0x0
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x64]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x60]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x64]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2094]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	mov dword [ebp-0x1c], 0xff00ff00
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xff00ff00
	mov dword [esp+0x20], 0x3f800000
	mov dword [esp+0x1c], 0x3f800000
	mov dword [esp+0x18], 0x0
	mov dword [esp+0x14], 0x0
	movss xmm0, dword [ebp-0x60]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x64]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x60]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x6c]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2094]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	mov dword [ebp-0x1c], 0xff0000ff
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xff0000ff
	mov dword [esp+0x20], 0x3f800000
	mov dword [esp+0x1c], 0x3f800000
	mov dword [esp+0x18], 0x0
	mov dword [esp+0x14], 0x0
	movss xmm0, dword [ebp-0x60]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x64]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x68]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x64]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2094]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	mov dword [ebp-0x1c], 0xffffffff
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f800000
	mov dword [esp+0x1c], 0x3f800000
	mov dword [esp+0x18], 0x0
	mov dword [esp+0x14], 0x0
	movss xmm0, dword [ebp-0x60]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x64]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x68]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x6c]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2098]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
	jmp _Z15RB_Draw3DCommonv_150
_Z15RB_Draw3DCommonv_140:
	mov eax, sc_showDebug
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z15RB_Draw3DCommonv_150
	mov eax, tess
	mov edx, [eax+0x22a948]
	test edx, edx
	jnz _Z15RB_Draw3DCommonv_210
_Z15RB_Draw3DCommonv_280:
	cvtsi2ss xmm0, dword [edi+0xf68]
	movss [ebp-0x4c], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x4c]
	movss [ebp-0x4c], xmm0
	cvtsi2ss xmm0, dword [edi+0xf6c]
	movss [ebp-0x48], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x48]
	movss [ebp-0x48], xmm0
	mov dword [esp+0x4], 0x1
	mov [esp], edi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov dword [esp+0x8], 0x1
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov [esp], edi
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
	mov [edi+0xc44], eax
	mov dword [edi+0xa50], 0x3f800000
	mov dword [edi+0xa54], 0x0
	mov dword [edi+0xa58], 0x0
	mov dword [edi+0xa5c], 0x0
	add word [edi+0xe6a], 0x1
	mov dword [edi+0xa60], 0x0
	mov dword [edi+0xa64], 0x3f800000
	mov dword [edi+0xa68], 0x0
	mov dword [edi+0xa6c], 0x0
	add word [edi+0xe6c], 0x1
	mov dword [edi+0xa70], 0x0
	mov dword [edi+0xa74], 0x0
	mov dword [edi+0xa78], 0x3f800000
	mov dword [edi+0xa7c], 0x0
	add word [edi+0xe6e], 0x1
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f400000
	mov dword [esp+0x1c], 0x3f400000
	mov dword [esp+0x18], 0x3e800000
	mov dword [esp+0x14], 0x3e800000
	movss xmm0, dword [ebp-0x48]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x4c]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x48]
	mulss xmm0, [_float_0_50000000]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x4c]
	mulss xmm0, [_float_0_50000000]
_Z15RB_Draw3DCommonv_240:
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2090]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
	jmp _Z15RB_Draw3DCommonv_150
_Z15RB_Draw3DCommonv_60:
	mov eax, sc_showOverlay
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z15RB_Draw3DCommonv_220
	call _Z22RB_ShadowCookieOverlayv
	jmp _Z15RB_Draw3DCommonv_220
_Z15RB_Draw3DCommonv_130:
	mov eax, tess
	mov eax, [eax+0x22a948]
	test eax, eax
	jnz _Z15RB_Draw3DCommonv_230
_Z15RB_Draw3DCommonv_260:
	cvtsi2ss xmm0, dword [edi+0xf68]
	movss [ebp-0x5c], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x5c]
	movss [ebp-0x5c], xmm0
	cvtsi2ss xmm0, dword [edi+0xf6c]
	movss [ebp-0x58], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x58]
	movss [ebp-0x58], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x5c]
	movss [ebp-0x54], xmm0
	movss xmm0, dword [_float_0_50000000]
	mulss xmm0, [ebp-0x58]
	movss [ebp-0x50], xmm0
	mov eax, gfxRenderTargets
	mov eax, [eax+0x78]
	mov [edi+0xc44], eax
	mov dword [esp+0x4], 0x1
	mov [esp], edi
	call _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	mov dword [esp+0x8], 0x1
	mov [esp], ebx
	mov [esp+0x4], esi
	call _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	mov [esp], edi
	call _Z7R_Set2DP20GfxCmdBufSourceState
	mov dword [edi+0xa50], 0x3f800000
	mov dword [edi+0xa54], 0x0
	mov dword [edi+0xa58], 0x0
	mov dword [edi+0xa5c], 0x0
	add word [edi+0xe6a], 0x1
	mov dword [edi+0xa60], 0x0
	mov dword [edi+0xa64], 0x0
	mov dword [edi+0xa68], 0x0
	mov dword [edi+0xa6c], 0x0
	add word [edi+0xe6c], 0x1
	mov dword [edi+0xa70], 0x0
	mov dword [edi+0xa74], 0x0
	mov dword [edi+0xa78], 0x0
	mov dword [edi+0xa7c], 0x0
	add word [edi+0xe6e], 0x1
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f000000
	mov dword [esp+0x1c], 0x3f000000
	mov dword [esp+0x18], 0x3e800000
	mov dword [esp+0x14], 0x3e800000
	movss xmm0, dword [ebp-0x50]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x54]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x50]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x54]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2090]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
	mov dword [edi+0xa50], 0x0
	mov dword [edi+0xa54], 0x0
	mov dword [edi+0xa58], 0x0
	mov dword [edi+0xa5c], 0x0
	add word [edi+0xe6a], 0x1
	mov dword [edi+0xa60], 0x0
	mov dword [edi+0xa64], 0x3f800000
	mov dword [edi+0xa68], 0x0
	mov dword [edi+0xa6c], 0x0
	add word [edi+0xe6c], 0x1
	mov dword [edi+0xa70], 0x0
	mov dword [edi+0xa74], 0x0
	mov dword [edi+0xa78], 0x0
	mov dword [edi+0xa7c], 0x0
	add word [edi+0xe6e], 0x1
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f000000
	mov dword [esp+0x1c], 0x3f400000
	mov dword [esp+0x18], 0x3e800000
	mov dword [esp+0x14], 0x3f000000
	movss xmm0, dword [ebp-0x50]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x54]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x50]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x5c]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2090]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
	mov dword [edi+0xa50], 0x0
	mov dword [edi+0xa54], 0x0
	mov dword [edi+0xa58], 0x0
	mov dword [edi+0xa5c], 0x0
	add word [edi+0xe6a], 0x1
	mov dword [edi+0xa60], 0x0
	mov dword [edi+0xa64], 0x0
	mov dword [edi+0xa68], 0x0
	mov dword [edi+0xa6c], 0x0
	add word [edi+0xe6c], 0x1
	mov dword [edi+0xa70], 0x0
	mov dword [edi+0xa74], 0x0
	mov dword [edi+0xa78], 0x3f800000
	mov dword [edi+0xa7c], 0x0
	add word [edi+0xe6e], 0x1
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f400000
	mov dword [esp+0x1c], 0x3f000000
	mov dword [esp+0x18], 0x3f000000
	mov dword [esp+0x14], 0x3e800000
	movss xmm0, dword [ebp-0x50]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x54]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x58]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x54]
	movss [esp+0x4], xmm0
	mov edx, rgp
	mov eax, [edx+0x2090]
	mov [esp], eax
	call _Z17RB_DrawStretchPicPK8Materialffffffffm18GfxPrimStatsTarget
	call _Z17RB_EndTessSurfacev
	mov dword [edi+0xa50], 0x0
	mov dword [edi+0xa54], 0x0
	mov dword [edi+0xa58], 0x0
	mov dword [edi+0xa5c], 0x3f800000
	add word [edi+0xe6a], 0x1
	mov dword [edi+0xa60], 0x0
	mov dword [edi+0xa64], 0x0
	mov dword [edi+0xa68], 0x0
	mov dword [edi+0xa6c], 0x3f800000
	add word [edi+0xe6c], 0x1
	mov dword [edi+0xa70], 0x0
	mov dword [edi+0xa74], 0x0
	mov dword [edi+0xa78], 0x0
	mov dword [edi+0xa7c], 0x3f800000
	add word [edi+0xe6e], 0x1
	mov dword [esp+0x28], 0x9
	mov dword [esp+0x24], 0xffffffff
	mov dword [esp+0x20], 0x3f400000
	mov dword [esp+0x1c], 0x3f400000
	mov dword [esp+0x18], 0x3f000000
	mov dword [esp+0x14], 0x3f000000
	movss xmm0, dword [ebp-0x50]
	movss [esp+0x10], xmm0
	movss xmm0, dword [ebp-0x54]
	movss [esp+0xc], xmm0
	movss xmm0, dword [ebp-0x58]
	movss [esp+0x8], xmm0
	movss xmm0, dword [ebp-0x5c]
	jmp _Z15RB_Draw3DCommonv_240
_Z15RB_Draw3DCommonv_200:
	call _Z17RB_EndTessSurfacev
	jmp _Z15RB_Draw3DCommonv_250
_Z15RB_Draw3DCommonv_230:
	call _Z17RB_EndTessSurfacev
	jmp _Z15RB_Draw3DCommonv_260
_Z15RB_Draw3DCommonv_160:
	call _Z17RB_EndTessSurfacev
	jmp _Z15RB_Draw3DCommonv_270
_Z15RB_Draw3DCommonv_210:
	call _Z17RB_EndTessSurfacev
	jmp _Z15RB_Draw3DCommonv_280


;Initialized global or static variables of rb_draw3d:
SECTION .data


;Initialized constant data of rb_draw3d:
SECTION .rdata


;Zero initialized global or static variables of rb_draw3d:
SECTION .bss


;All cstrings:
SECTION .rdata
_cstring_post_effects:		db "Post Effects",0


;All constant floats and doubles:
SECTION .rdata
_float_0_50000000:		dd 0x3f000000	; 0.5
