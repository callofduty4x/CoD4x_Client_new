;Imports of r_init:
	extern r_reflectionProbeGenerate
	extern r_vsync
	extern _Z10Com_PrintfiPKcz
	extern _Z12R_InitImagesv
	extern _Z13Material_Initv
	extern _Z11R_InitFontsv
	extern _Z15R_InitLoadWaterv
	extern _Z15R_InitLightDefsv
	extern _Z11R_ClearFogsv
	extern _Z11R_InitDebugv
	extern alwaysfails
	extern _Z23R_ShutdownRenderTargetsv
	extern _Z28R_ShutdownModelLightingImagev
	extern _Z26R_ShutdownStaticModelCachev
	extern _Z23R_DestroyDynamicBuffersv
	extern _Z28R_DestroyParticleCloudBufferv
	extern _Z23RB_FreeSunSpriteQueriesv
	extern _Z19R_InitRenderTargetsv
	extern _Z22R_CreateDynamicBuffersv
	extern _Z24RB_AllocSunSpriteQueriesv
	extern _Z27R_CreateParticleCloudBufferv
	extern _Z19R_InitRenderBuffersv
	extern _Z24R_InitModelLightingImagev
	extern _Z22R_InitStaticModelCachev
	extern _Z9Sys_Sleepi
	extern _Z22R_GetMonitorDimensionsPiS_
	extern _Z18R_SyncRenderThreadv
	extern _Z15R_ShutdownDebugv
	extern _Z21R_SaveLightVisHistoryv
	extern _Z19R_ShutdownLightDefsv
	extern _Z15R_ShutdownWorldv
	extern useFastFile
	extern _Z20R_ResetModelLightingv
	extern _Z20R_UnlockSkinnedCachev
	extern _Z23R_FlushStaticModelCachev
	extern _Z20R_Cinematic_Shutdownv
	extern _Z24R_ShutdownRenderCommandsv
	extern _Z16R_UnregisterCmdsv
	extern _Z18DB_ShutdownXAssetsv
	extern _Z19R_ShutdownLoadWaterv
	extern _Z15R_ShutdownFontsv
	extern _Z17Material_Shutdownv
	extern _Z16R_ShutdownImagesv
	extern gfxCmdBufState
	extern _Z23R_ClearAllStreamSourcesP18GfxCmdBufPrimState
	extern _Z9Sys_ErrorPKcz
	extern r_gamma
	extern pow
	extern floorf
	extern r_loadForRenderer
	extern _Z12Dvar_SetBoolPK6dvar_sb
	extern _Z28Dvar_MakeLatchedValueCurrentPK6dvar_s
	extern _Z14DB_LoadXAssetsP9XZoneInfoji
	extern _Z14DB_SyncXAssetsv
	extern _Z15R_RegisterDvarsv
	extern _Z21Sys_DirectXFatalErrorv
	extern _Z16Sys_IsMainThreadv
	extern _Z27R_Cinematic_BeginLostDevicev
	extern _Z25DB_BeginRecoverLostDevicev
	extern _Z19R_ReleaseLostImagesv
	extern _Z19Material_ReleaseAllv
	extern _Z14R_ReleaseWorldv
	extern r_aaSamples
	extern gfxCmdBufInput
	extern gfxCmdBufSourceState
	extern _Z23R_InitCmdBufSourceStateP20GfxCmdBufSourceStatePK14GfxCmdBufInputi
	extern _Z20RB_InitSceneViewportv
	extern _Z21R_SetRenderTargetSizeP20GfxCmdBufSourceState17GfxRenderTargetId
	extern gfxCmdBufContext
	extern _Z17R_SetRenderTarget16GfxCmdBufContext17GfxRenderTargetId
	extern _Z13R_ReloadWorldv
	extern _Z18Material_ReloadAllv
	extern _Z18R_ReloadLostImagesv
	extern _Z23DB_EndRecoverLostDevicev
	extern _Z25R_Cinematic_EndLostDevicev
	extern _Z2vaPKcz
	extern _Z21R_AbortRenderCommandsv
	extern _Z22Material_FinishLoadingv
	extern _Z17RB_TouchAllImagesv
	extern _Z15RB_SetGammaRampPK12GfxGammaRamp
	extern _Z14R_RegisterCmdsv
	extern memset
	extern _Z16MatrixIdentity44PA4_f
	extern _Z16R_InitDrawMethodv
	extern _Z24RB_RegisterBackendAssetsv
	extern _Z11R_InitWaterv
	extern _Z13R_CheckDxCapsPK9_D3DCAPS9
	extern r_rendererPreference
	extern r_rendererInUse
	extern _Z11Dvar_SetIntPK6dvar_si
	extern qsort
	extern _Z17Dvar_RegisterEnumPKcPS0_itS0_
	extern r_mode
	extern r_displayRefresh
	extern _Z12Dvar_GetBoolPKc
	extern r_customMode
	extern sscanf
	extern _Z17Dvar_EnumToStringPK6dvar_s
	extern _Z11Dvar_GetIntPKc
	extern _Z14R_CreateWindowP14GfxWindowParms
	extern _Z23R_GetDepthStencilFormat10_D3DFORMAT
	extern r_multiGpu
	extern r_aspectRatio
	extern _Z20RB_InitCodeConstantsv
	extern r_gpuSync
	extern _Z18RB_SetInitialStatev
	extern _Z16Dvar_SetModifiedPK6dvar_s
	extern _Z11R_InitScenev
	extern _Z20Sys_HideSplashWindowv
	extern sprintf
	extern _Z9Com_Error11errorParm_tPKcz
	extern iDirect3DCreate9
	extern _Z20R_InitRenderCommandsv
	extern _Z21R_AcquireGpuFenceLockv
	extern _Z21RB_IsGpuFenceFinishedv
	extern _Z21R_ReleaseGpuFenceLockv
	extern _Z22R_CreateForInitOrResetv
	extern _Z27R_ReleaseForShutdownOrResetv

;Exports of r_init:
	global _Z13R_InitSystemsv
	global _Z21R_CompareDisplayModesPKvS0_
	global _Z21R_CompareRefreshRatesPKvS0_
	global _Z10R_InitOncev
	global _Z13R_UnloadWorldv
	global _Z14R_GammaCorrectPhi
	global _Z15R_MakeDedicatedPK16GfxConfiguration
	global _Z16R_FatalInitErrorPKc
	global _Z16R_FatalLockErrorl
	global _Z17R_CheckLostDevicev
	global _Z17R_EndRegistrationv
	global _Z17R_TrackStatisticsP14trStatistics_t
	global _Z18R_SetColorMappingsv
	global _Z18R_UpdateTeamColorsiPKfS0_
	global _Z19R_ConfigureRendererPK16GfxConfiguration
	global _Z24R_IsUsingAdaptiveGpuSyncv
	global _Z9R_SyncGpuPFiyE
	global r_dx
	global rgp
	global rg
	global gfxCfg
	global gfxMetrics
	global g_allocateMinimalResources
	global g_disableRendering
	global gfxAssets
	global vidConfig


SECTION .text



;R_InitSystems()
_Z13R_InitSystemsv:
	push ebp
	mov ebp, esp
	sub esp, 0x8
	call _Z12R_InitImagesv
	call _Z13Material_Initv
	call _Z11R_InitFontsv
	call _Z15R_InitLoadWaterv
	call _Z15R_InitLightDefsv
	call _Z11R_ClearFogsv
	call _Z11R_InitDebugv
	mov byte [rg+0x140], 0x1
	leave
	ret


;R_CompareDisplayModes(void const*, void const*)
_Z21R_CompareDisplayModesPKvS0_:
	push ebp
	mov ebp, esp
	mov ecx, [ebp+0x8]
	mov edx, [ebp+0xc]
	mov eax, [ecx]
	sub eax, [edx]
	jnz _Z21R_CompareDisplayModesPKvS0__10
	mov eax, [ecx+0x4]
	sub eax, [edx+0x4]
	jnz _Z21R_CompareDisplayModesPKvS0__10
	mov eax, [ecx+0x8]
	sub eax, [edx+0x8]
_Z21R_CompareDisplayModesPKvS0__10:
	pop ebp
	ret
	nop


;R_CompareRefreshRates(void const*, void const*)
_Z21R_CompareRefreshRatesPKvS0_:
	push ebp
	mov ebp, esp
	mov eax, [ebp+0x8]
	mov eax, [eax]
	mov edx, [ebp+0xc]
	sub eax, [edx]
	pop ebp
	ret
	nop


;R_InitOnce()
_Z10R_InitOncev:
	push ebp
	mov ebp, esp
	pop ebp
	ret
	nop


;R_UnloadWorld()
_Z13R_UnloadWorldv:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	mov edx, [rgp+0x20a0]
	test edx, edx
	jz _Z13R_UnloadWorldv_10
	mov dword [esp], _cstring_cannot_unload_bs
	call _Z9Sys_ErrorPKcz
_Z13R_UnloadWorldv_10:
	leave
	ret


;R_GammaCorrect(unsigned char*, int)
_Z14R_GammaCorrectPhi:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x23c
	mov edi, [ebp+0x8]
	mov eax, r_gamma
	mov eax, [eax]
	movss xmm1, dword [_float_1_00000000]
	movaps xmm0, xmm1
	divss xmm0, dword [eax+0xc]
	xor ebx, ebx
	cvtss2sd xmm2, xmm0
	movsd [ebp-0x220], xmm2
	ucomiss xmm0, xmm1
	jp _Z14R_GammaCorrectPhi_10
	jnz _Z14R_GammaCorrectPhi_10
_Z14R_GammaCorrectPhi_20:
	mov eax, ebx
	shl eax, 0x8
	add eax, ebx
	mov [ebp+ebx*2-0x218], ax
	add ebx, 0x1
	cmp ebx, 0x100
	jnz _Z14R_GammaCorrectPhi_20
_Z14R_GammaCorrectPhi_50:
	mov ebx, [ebp+0xc]
	test ebx, ebx
	jle _Z14R_GammaCorrectPhi_30
	xor ebx, ebx
	mov esi, 0x7f807f81
_Z14R_GammaCorrectPhi_40:
	lea ecx, [ebx+edi]
	movzx eax, byte [ecx]
	movzx edx, word [ebp+eax*2-0x218]
	mov eax, edx
	imul esi
	shr edx, 0x7
	mov [ecx], dl
	add ebx, 0x1
	cmp [ebp+0xc], ebx
	jnz _Z14R_GammaCorrectPhi_40
_Z14R_GammaCorrectPhi_30:
	add esp, 0x23c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z14R_GammaCorrectPhi_10:
	cvtsi2ss xmm0, ebx
	divss xmm0, dword [_float_255_00000000]
	movsd xmm1, qword [ebp-0x220]
	movsd [esp+0x8], xmm1
	cvtss2sd xmm0, xmm0
	movsd [esp], xmm0
	call pow
	fstp qword [ebp-0x228]
	cvtsd2ss xmm0, [ebp-0x228]
	mulss xmm0, [_float_65535_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x22c]
	cvttss2si eax, [ebp-0x22c]
	mov [ebp+ebx*2-0x218], ax
	add ebx, 0x1
	cmp ebx, 0x100
	jnz _Z14R_GammaCorrectPhi_10
	jmp _Z14R_GammaCorrectPhi_50
	nop


;R_MakeDedicated(GfxConfiguration const*)
_Z15R_MakeDedicatedPK16GfxConfiguration:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx
	sub esp, 0x6c
	mov edx, [ebp+0x8]
	mov eax, [edx]
	mov [gfxCfg], eax
	mov eax, [edx+0x4]
	mov [gfxCfg+0x4], eax
	mov eax, [edx+0x8]
	mov [gfxCfg+0x8], eax
	mov eax, [edx+0xc]
	mov [gfxCfg+0xc], eax
	mov eax, [edx+0x10]
	mov [gfxCfg+0x10], eax
	mov eax, [edx+0x14]
	mov [gfxCfg+0x14], eax
	mov eax, [edx+0x18]
	mov [gfxCfg+0x18], eax
	mov eax, [edx+0x1c]
	mov [gfxCfg+0x1c], eax
	mov eax, [edx+0x20]
	mov [gfxCfg+0x20], eax
	mov eax, [edx+0x24]
	mov [gfxCfg+0x24], eax
	mov eax, [edx+0x28]
	mov [gfxCfg+0x28], eax
	mov eax, [edx+0x2c]
	mov [gfxCfg+0x2c], eax
	mov ebx, r_loadForRenderer
	mov ecx, [ebx]
	test ecx, ecx
	jz _Z15R_MakeDedicatedPK16GfxConfiguration_10
_Z15R_MakeDedicatedPK16GfxConfiguration_90:
	mov dword [esp+0x4], 0x0
	mov eax, [ebx]
	mov [esp], eax
	call _Z12Dvar_SetBoolPK6dvar_sb
	mov eax, [ebx]
	mov [esp], eax
	call _Z28Dvar_MakeLatchedValueCurrentPK6dvar_s
	mov eax, [gfxCfg+0x18]
	mov [ebp-0x60], eax
	mov dword [ebp-0x5c], 0x2
	mov dword [ebp-0x58], 0x0
	mov eax, [gfxCfg+0x24]
	test eax, eax
	jz _Z15R_MakeDedicatedPK16GfxConfiguration_20
	mov [ebp-0x54], eax
	mov dword [ebp-0x50], 0x0
	mov dword [ebp-0x4c], 0x0
	mov eax, 0x2
	mov ebx, 0x3
_Z15R_MakeDedicatedPK16GfxConfiguration_80:
	mov ecx, [gfxCfg+0x2c]
	test ecx, ecx
	jz _Z15R_MakeDedicatedPK16GfxConfiguration_30
	lea eax, [eax+eax*2]
	lea eax, [ebp+eax*4-0x18]
	lea edx, [eax-0x48]
	mov [eax-0x48], ecx
	mov dword [edx+0x4], 0x10
	mov dword [edx+0x8], 0x0
	mov dword [esp+0x8], 0x0
	mov [esp+0x4], ebx
	lea edi, [ebp-0x60]
	mov [esp], edi
	call _Z14DB_LoadXAssetsP9XZoneInfoji
	call _Z14DB_SyncXAssetsv
	xor eax, eax
	mov esi, 0x1
	mov ecx, [gfxCfg+0x1c]
	test ecx, ecx
	jz _Z15R_MakeDedicatedPK16GfxConfiguration_40
_Z15R_MakeDedicatedPK16GfxConfiguration_60:
	lea eax, [eax+eax*2]
	lea eax, [ebp+eax*4-0x18]
	lea edx, [eax-0x48]
	mov [eax-0x48], ecx
	mov dword [edx+0x4], 0x8
	mov dword [edx+0x8], 0x0
	lea ebx, [esi+0x1]
_Z15R_MakeDedicatedPK16GfxConfiguration_70:
	lea eax, [esi+esi*2]
	lea eax, [ebp+eax*4-0x18]
	lea ecx, [eax-0x48]
	mov edx, [gfxCfg+0x20]
	mov [eax-0x48], edx
	mov dword [ecx+0x4], 0x4
	mov dword [ecx+0x8], 0x0
	mov ecx, [gfxCfg+0x28]
	test ecx, ecx
	jz _Z15R_MakeDedicatedPK16GfxConfiguration_50
	lea eax, [ebx+ebx*2]
	lea eax, [ebp+eax*4-0x18]
	lea edx, [eax-0x48]
	mov [eax-0x48], ecx
	mov dword [edx+0x4], 0x1
	mov dword [edx+0x8], 0x0
	lea ebx, [esi+0x2]
_Z15R_MakeDedicatedPK16GfxConfiguration_50:
	mov dword [esp+0x8], 0x0
	mov [esp+0x4], ebx
	mov [esp], edi
	call _Z14DB_LoadXAssetsP9XZoneInfoji
	add esp, 0x6c
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
_Z15R_MakeDedicatedPK16GfxConfiguration_30:
	lea esi, [eax+0x1]
	lea edi, [ebp-0x60]
	mov ecx, [gfxCfg+0x1c]
	test ecx, ecx
	jnz _Z15R_MakeDedicatedPK16GfxConfiguration_60
_Z15R_MakeDedicatedPK16GfxConfiguration_40:
	mov ebx, esi
	mov esi, eax
	jmp _Z15R_MakeDedicatedPK16GfxConfiguration_70
_Z15R_MakeDedicatedPK16GfxConfiguration_20:
	mov al, 0x1
	mov ebx, 0x2
	jmp _Z15R_MakeDedicatedPK16GfxConfiguration_80
_Z15R_MakeDedicatedPK16GfxConfiguration_10:
	call _Z15R_RegisterDvarsv
	jmp _Z15R_MakeDedicatedPK16GfxConfiguration_90


;R_FatalInitError(char const*)
_Z16R_FatalInitErrorPKc:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x14
	mov ebx, [ebp+0x8]
	mov dword [esp+0x4], _cstring__directx_returne
	mov dword [esp], 0x8
	call _Z10Com_PrintfiPKcz
	mov dword [esp+0x4], _cstring__initialization_
	mov dword [esp], 0x8
	call _Z10Com_PrintfiPKcz
	mov dword [esp+0x4], _cstring__consult_the_rea
	mov dword [esp], 0x8
	call _Z10Com_PrintfiPKcz
	mov [esp+0x8], ebx
	mov dword [esp+0x4], _cstring_s
	mov dword [esp], 0x8
	call _Z10Com_PrintfiPKcz
	add esp, 0x14
	pop ebx
	pop ebp
	jmp _Z21Sys_DirectXFatalErrorv


;R_FatalLockError(long)
_Z16R_FatalLockErrorl:
	push ebp
	mov ebp, esp
	sub esp, 0x18
	mov dword [esp+0x4], _cstring__directx_failed_
	mov dword [esp], 0x8
	call _Z10Com_PrintfiPKcz
	mov dword [esp+0x8], 0x0
	mov dword [esp+0x4], _cstring__error_informati
	mov dword [esp], 0x8
	call _Z10Com_PrintfiPKcz
	leave
	jmp _Z21Sys_DirectXFatalErrorv




;R_EndRegistration()
_Z17R_EndRegistrationv:
	push ebp
	mov ebp, esp
	sub esp, 0x8
	call _Z22Material_FinishLoadingv
	mov eax, useFastFile
	mov eax, [eax]
	cmp byte [eax+0xc], 0x0
	jz _Z17R_EndRegistrationv_10
	leave
	ret
_Z17R_EndRegistrationv_10:
	call _Z18R_SyncRenderThreadv
	leave
	jmp _Z17RB_TouchAllImagesv
	nop



;R_TrackStatistics(trStatistics_t*)
_Z17R_TrackStatisticsP14trStatistics_t:
	push ebp
	mov ebp, esp
	mov eax, [ebp+0x8]
	mov [rg+0x21d8], eax
	pop ebp
	ret
	nop

;R_SetColorMappings()
_Z18R_SetColorMappingsv:
	push ebp
	mov ebp, esp
	push ebx
	sub esp, 0x234
	cmp byte [vidConfig+0x2c], 0x0
	jz _Z18R_SetColorMappingsv_10
	mov eax, r_gamma
	mov eax, [eax]
	movss xmm1, dword [_float_1_00000000]
	movaps xmm0, xmm1
	divss xmm0, dword [eax+0xc]
	xor ebx, ebx
	cvtss2sd xmm2, xmm0
	movsd [ebp-0x210], xmm2
	ucomiss xmm0, xmm1
	jp _Z18R_SetColorMappingsv_20
	jnz _Z18R_SetColorMappingsv_20
_Z18R_SetColorMappingsv_30:
	mov eax, ebx
	shl eax, 0x8
	add eax, ebx
	mov [ebp+ebx*2-0x208], ax
	add ebx, 0x1
	cmp ebx, 0x100
	jnz _Z18R_SetColorMappingsv_30
_Z18R_SetColorMappingsv_40:
	lea eax, [ebp-0x208]
	mov [esp], eax
	call _Z15RB_SetGammaRampPK12GfxGammaRamp
_Z18R_SetColorMappingsv_10:
	add esp, 0x234
	pop ebx
	pop ebp
	ret
_Z18R_SetColorMappingsv_20:
	cvtsi2ss xmm0, ebx
	divss xmm0, dword [_float_255_00000000]
	movsd xmm1, qword [ebp-0x210]
	movsd [esp+0x8], xmm1
	cvtss2sd xmm0, xmm0
	movsd [esp], xmm0
	call pow
	fstp qword [ebp-0x218]
	cvtsd2ss xmm0, [ebp-0x218]
	mulss xmm0, [_float_65535_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x21c]
	cvttss2si eax, [ebp-0x21c]
	mov [ebp+ebx*2-0x208], ax
	add ebx, 0x1
	cmp ebx, 0x100
	jnz _Z18R_SetColorMappingsv_20
	jmp _Z18R_SetColorMappingsv_40


;R_UpdateTeamColors(int, float const*, float const*)
_Z18R_UpdateTeamColorsiPKfS0_:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x30
	mov ebx, [ebp+0xc]
	mov esi, [ebp+0x10]
	mov eax, [ebp+0x8]
	mov [rg+0x21d4], eax
	movss xmm0, dword [ebx]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0xc]
	cvttss2si eax, [ebp-0xc]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__10
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__90:
	mov [rg+0x21d0], dl
	movss xmm0, dword [ebx+0x4]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x10]
	cvttss2si eax, [ebp-0x10]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__20
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__150:
	mov [rg+0x21d1], dl
	movss xmm0, dword [ebx+0x8]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x14]
	cvttss2si eax, [ebp-0x14]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__30
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__140:
	mov [rg+0x21d2], dl
	movss xmm0, dword [ebx+0xc]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x18]
	cvttss2si eax, [ebp-0x18]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__40
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__130:
	mov [rg+0x21d3], dl
	movss xmm0, dword [esi]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x1c]
	cvttss2si eax, [ebp-0x1c]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__50
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__120:
	mov [rg+0x21cc], dl
	movss xmm0, dword [esi+0x4]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x20]
	cvttss2si eax, [ebp-0x20]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__60
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__110:
	mov [rg+0x21cd], dl
	movss xmm0, dword [esi+0x8]
	mulss xmm0, [_float_255_00000000]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x24]
	cvttss2si eax, [ebp-0x24]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__70
	mov edx, 0xffffffff
_Z18R_UpdateTeamColorsiPKfS0__100:
	mov [rg+0x21ce], dl
	movss xmm0, dword [_float_255_00000000]
	mulss xmm0, [esi+0xc]
	addss xmm0, [_float_0_50000000]
	movss [esp], xmm0
	call floorf
	fstp dword [ebp-0x28]
	cvttss2si eax, [ebp-0x28]
	cmp eax, 0xfe
	jle _Z18R_UpdateTeamColorsiPKfS0__80
	mov edx, 0xffffffff
	mov [rg+0x21cf], dl
	add esp, 0x30
	pop ebx
	pop esi
	pop ebp
	ret
_Z18R_UpdateTeamColorsiPKfS0__10:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__90
_Z18R_UpdateTeamColorsiPKfS0__80:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	mov [rg+0x21cf], dl
	add esp, 0x30
	pop ebx
	pop esi
	pop ebp
	ret
_Z18R_UpdateTeamColorsiPKfS0__70:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__100
_Z18R_UpdateTeamColorsiPKfS0__60:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__110
_Z18R_UpdateTeamColorsiPKfS0__50:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__120
_Z18R_UpdateTeamColorsiPKfS0__40:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__130
_Z18R_UpdateTeamColorsiPKfS0__30:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__140
_Z18R_UpdateTeamColorsiPKfS0__20:
	xor edx, edx
	test eax, eax
	cmovg edx, eax
	jmp _Z18R_UpdateTeamColorsiPKfS0__150



;R_ConfigureRenderer(GfxConfiguration const*)
_Z19R_ConfigureRendererPK16GfxConfiguration:
	push ebp
	mov ebp, esp
	mov edx, [ebp+0x8]
	mov eax, [edx]
	mov [gfxCfg], eax
	mov eax, [edx+0x4]
	mov [gfxCfg+0x4], eax
	mov eax, [edx+0x8]
	mov [gfxCfg+0x8], eax
	mov eax, [edx+0xc]
	mov [gfxCfg+0xc], eax
	mov eax, [edx+0x10]
	mov [gfxCfg+0x10], eax
	mov eax, [edx+0x14]
	mov [gfxCfg+0x14], eax
	mov eax, [edx+0x18]
	mov [gfxCfg+0x18], eax
	mov eax, [edx+0x1c]
	mov [gfxCfg+0x1c], eax
	mov eax, [edx+0x20]
	mov [gfxCfg+0x20], eax
	mov eax, [edx+0x24]
	mov [gfxCfg+0x24], eax
	mov eax, [edx+0x28]
	mov [gfxCfg+0x28], eax
	mov eax, [edx+0x2c]
	mov [gfxCfg+0x2c], eax
	pop ebp
	jmp _Z20R_InitRenderCommandsv
	nop


;R_IsUsingAdaptiveGpuSync()
_Z24R_IsUsingAdaptiveGpuSyncv:
	push ebp
	mov ebp, esp
	xor eax, eax
	cmp dword [r_dx+0x2c58], 0x1
	setz al
	pop ebp
	ret
	nop


;R_SyncGpu(int (*)(unsigned long long))
_Z9R_SyncGpuPFiyE:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x10
	mov ebx, [ebp+0x8]
	mov ecx, [r_dx+0x2c58]
	test ecx, ecx
	jnz _Z9R_SyncGpuPFiyE_10
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
_Z9R_SyncGpuPFiyE_10:
	test ebx, ebx
	setnz al
	movzx esi, al
	rdtsc
	mov [r_dx+0x2c94], eax
	mov dword [r_dx+0x2c98], 0x0
	call _Z21R_AcquireGpuFenceLockv
_Z9R_SyncGpuPFiyE_60:
	call _Z21RB_IsGpuFenceFinishedv
	test al, al
	jnz _Z9R_SyncGpuPFiyE_20
_Z9R_SyncGpuPFiyE_50:
	rdtsc
	xor edx, edx
	mov [r_dx+0x2c9c], eax
	mov [r_dx+0x2ca0], edx
	sub eax, [r_dx+0x2c94]
	sbb edx, [r_dx+0x2c98]
	cmp edx, [r_dx+0x2c90]
	jb _Z9R_SyncGpuPFiyE_30
	ja _Z9R_SyncGpuPFiyE_20
	cmp eax, [r_dx+0x2c8c]
	jae _Z9R_SyncGpuPFiyE_20
_Z9R_SyncGpuPFiyE_30:
	test esi, esi
	jz _Z9R_SyncGpuPFiyE_40
	call _Z21R_ReleaseGpuFenceLockv
	mov eax, [r_dx+0x2c9c]
	mov edx, [r_dx+0x2ca0]
	mov [esp], eax
	mov [esp+0x4], edx
	call ebx
	mov esi, eax
	call _Z21R_AcquireGpuFenceLockv
	call _Z21RB_IsGpuFenceFinishedv
	test al, al
	jz _Z9R_SyncGpuPFiyE_50
_Z9R_SyncGpuPFiyE_20:
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	jmp _Z21R_ReleaseGpuFenceLockv
_Z9R_SyncGpuPFiyE_40:
	mov dword [esp], 0x1
	call _Z9Sys_Sleepi
	jmp _Z9R_SyncGpuPFiyE_60


;Initialized global or static variables of r_init:
SECTION .data
g_allocateMinimalResources: dd 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0


;Initialized constant data of r_init:
SECTION .rdata
formats: dd 0x4b, 0x17, 0x4b, 0x16, 0x4b, 0x14, 0x0, 0x0, 0x80000000, 0x0, 0x0, 0x0, 0x7fffffff, 0x0, 0x0, 0x0


;Zero initialized global or static variables of r_init:
SECTION .bss
r_dx: resb 0x2ce0
rgp: resb 0x2180
rg: resb 0x2340
gfxCfg: resb 0x30
gfxMetrics: resb 0x28
g_disableRendering: resb 0x18
gfxAssets: resb 0x10
vidConfig: resb 0x40


;All cstrings:
SECTION .rdata
_cstring_using_ix_antiali:		db "Using %ix anti-aliasing",0ah,0
_cstring_initializing_ren:		db "Initializing render targets...",0ah,0
_cstring_initializing_dyn:		db "Initializing dynamic buffers...",0ah,0
_cstring_creating_direct3:		db "Creating Direct3D queries...",0ah,0
_cstring_event_query_crea:		db "Event query creation failed: %s (0x%08x)",0ah,0
_cstring_initializing_par:		db "Initializing particle cloud buffer...",0ah,0
_cstring_initializing_sta:		db "Initializing static model cache...",0ah,0
_cstring_occlusion_query_:		db "Occlusion query creation failed: %s (0x%08x)",0ah,0
_cstring_creating_direct31:		db "Creating Direct3D device...",0ah,0
_cstring_cannot_unload_bs:		db "Cannot unload bsp while it is in use",0
_cstring__directx_returne:		db "********** DirectX returned an unrecoverable error code during initialization  **********",0ah,0
_cstring__initialization_:		db "********** Initialization also happens while playing if DirectX loses a device **********",0ah,0
_cstring__consult_the_rea:		db "********** Consult the readme for how to continue from this problem            **********",0ah,0
_cstring_s:		db 0ah,"%s",0ah,0
_cstring__directx_failed_:		db "********** DirectX failed a call to lock a vertex buffer or an index buffer **********",0ah,0
_cstring__error_informati:		db "********** error information:  %s",0ah,0
_cstring_recovering_lost_:		db "Recovering lost device...",0ah,0
_cstring_finished_recover:		db "Finished recovering lost device.",0ah,0
_cstring_couldnt_reinitia:		db "Couldn",27h,"t reinitialize after a lost Direct3D device",0
_cstring_couldnt_reset_a_:		db "Couldn",27h,"t reset a lost Direct3D device - IDirect3DDevice9::Reset returned 0x%08x (%s)",0
_cstring__r_init_:		db "----- R_Init -----",0ah,0
_cstring_sun_sprite_occlu:		db "Sun sprite occlusion query calibration failed; reverting to low-quality sun visibility test",0
_cstring_pixel_shader_ver:		db "Pixel shader version is %i.%i",0ah,0
_cstring_vertex_shader_ve:		db "Vertex shader version is %i.%i",0ah,0
_cstring_shader_model_30:		db "Shader model 3.0",0
_cstring_shader_model_20:		db "Shader model 2.0",0
_cstring_s_code_path_is_a:		db "%s code path is available.",0ah,0
_cstring_using_s_code_pat:		db "Using %s code path because the requested %s code path is unavailable.",0ah,0
_cstring_no_valid_resolut:		db "No valid resolutions of %i x %i or above found",0
_cstring_direct_x_resolut:		db "Direct X resolution mode",0
_cstring_r_mode:		db "r_mode",0
_cstring_refresh_rate:		db "Refresh rate",0
_cstring_r_displayrefresh:		db "r_displayRefresh",0
_cstring_r_fullscreen:		db "r_fullscreen",0
_cstring_ixi:		db "%ix%i",0
_cstring_vid_xpos:		db "vid_xpos",0
_cstring_vid_ypos:		db "vid_ypos",0
_cstring_using_s_code_pat1:		db "Using %s code path because r_rendererPreference is set to %s.",0ah,0
_cstring_i_hz:		db "%i Hz",0
_cstring_couldnt_initiali:		db "Couldn",27h,"t initialize renderer",0
_cstring_setting_initial_:		db "Setting initial state...",0ah,0
_cstring_getdevicecaps_fa:		db "GetDeviceCaps failed: %s",0
_cstring_couldnt_create_a:		db "Couldn",27h,"t create a Direct3D device: %s",0ah,0
_cstring_using_s_code_pat2:		db "Using %s code path because it is the best available path on this hardware.",0ah,0
_cstring_no_valid_renderi:		db "No valid rendering code path detected.",0ah,0
_cstring_getting_direct3d:		db "Getting Direct3D 9 interface...",0ah,0
_cstring_direct3d_9_faile:		db "Direct3D 9 failed to initialize",0ah,0



;All constant floats and doubles:
SECTION .rdata
_float_1_00000000:		dd 0x3f800000	; 1
_float_255_00000000:		dd 0x437f0000	; 255
_float_65535_00000000:		dd 0x477fff00	; 65535
_float_0_50000000:		dd 0x3f000000	; 0.5
_float_1_33333337:		dd 0x3faaaaab	; 1.33333
_float_16_00000000:		dd 0x41800000	; 16

