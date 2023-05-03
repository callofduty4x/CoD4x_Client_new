#include "bg_shared.h"
#include "bg_local.h"
#include "bg_weapon.h"
#include <game/game_shared.h>
#include <algorithm>

dvar_s* bg_viewBobMax;
dvar_s* bg_weaponBobMax;
dvar_s* bg_weaponBobLag;
dvar_s* bg_weaponBobAmplitudeBase;
dvar_s* bg_weaponBobAmplitudeRoll;


double BG_GetBobCycle(playerState_s *ps)
{
    double v = (ps->bobCycle & 0xFF) / 255.0 * M_PI;
    return 2 * v + 2 * M_PI;
}


double BG_CalculateWeaponMovement_HorizontalBobFactor(playerState_s *ps, float cycle, float speed)
{
    float amplitude;
    /*WeaponDef *weapDef;

    //weapDef = BG_GetWeaponDef(ps->weapon);
    //if ( ps->waterlevel < 3 )
    {
        if ( ps->pm_flags & 0x400000 )
        {
            amplitude = (float)(speed * bg_weaponBobAmplitudeDtp->current.value) * weapDef->vDtpBob[0];
        }
        else */
        if ( ps->viewHeightTarget == 11 )
        {
            amplitude = speed * bg_bobAmplitudeProne->current.vector[0];
        }
        else if ( ps->viewHeightTarget == 40 )
        {
            amplitude = speed * bg_bobAmplitudeDucked->current.vector[0];
//            amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeDucked->current.vector[0];

        }
        else if ( ps->pm_flags & 0x8000 )
        {
//            amplitude = (float)(speed * bg_weaponBobAmplitudeSprinting->current.vector[0]) * weapDef->vSprintBob[0];
            amplitude = speed * bg_bobAmplitudeSprinting->current.vector[0];

        }
        else
        {
            amplitude = speed * bg_bobAmplitudeStanding->current.vector[0];
            //amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeStanding->current.vector[0];
        }
/*
    }
    
    else
    {
        amplitude = bg_weaponBobAmplitudeSwimming->current.value;
    }
    */
    if ( amplitude > bg_weaponBobMax->current.value )
    {
        amplitude = bg_weaponBobMax->current.value;
    }
    return sin(cycle) * amplitude;
}



double BG_CalculateWeaponMovement_VerticalBobFactor(playerState_s *ps, float cycle, float speed)
{
    float amplitude; // [esp+8h] [ebp-8h]
    /*
    WeaponDef *weapDef; // [esp+Ch] [ebp-4h]

    weapDef = BG_GetWeaponDef(ps->weapon);
    if ( ps->waterlevel < 3 )
    {
        if ( ps->pm_flags & 0x400000 )
        {
            amplitude = (float)(speed * bg_weaponBobAmplitudeDtp->current.vector[1]) * weapDef->vDtpBob[1];
        }
        else
        */
        if ( ps->viewHeightTarget == 11 )
        {
            amplitude = speed * bg_bobAmplitudeProne->current.vector[1];
        }
        else if ( ps->viewHeightTarget == 40 )
        {
        //    amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeDucked->current.vector[1];
            amplitude = speed * bg_bobAmplitudeDucked->current.vector[1];
        }
        else if ( ps->pm_flags & 0x8000 )
        {
            //amplitude = (float)(speed * bg_weaponBobAmplitudeSprinting->current.vector[1]) * weapDef->vSprintBob[1];
            amplitude = speed * bg_bobAmplitudeSprinting->current.vector[1];
        }
        else
        {
            amplitude = speed * bg_bobAmplitudeStanding->current.vector[1];
//            amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeStanding->current.vector[1];
        }
/*        
    }
    else
    {
        amplitude = bg_weaponBobAmplitudeSwimming->current.vector[1];
    }
*/
    if ( amplitude > bg_weaponBobMax->current.value )
    {
        amplitude = bg_weaponBobMax->current.value;
    }

    return (sin(cycle * 4.0 + M_PI / 2) * 0.2 + sin(cycle * 2.0)) * 0.75 * amplitude;
}



void BG_CalculateViewMovement_BobAngles(viewState_t *vs, float *angles)
{
    int weapIndex;
    float fBobCycle;
    float cycle;
    float speed;
    float horBob;
    vec3_t vAngOfs;
    float fPositionLerp;
    playerState_s *ps;
    WeaponDef *weapDef;

    ps = vs->ps;
    weapIndex = BG_GetViewmodelWeaponIndex(vs->ps);
    weapDef = BG_GetWeaponDef(weapIndex);
    if ( weapDef->overlayReticle )
    {
        fBobCycle = BG_GetBobCycle(ps);
        
        //cycle = (float)((float)(3.1415927 * bg_weaponBobLag->current.value) + fBobCycle) + 6.2831855;
        cycle = ((M_PI * bg_weaponBobLag->current.value) + fBobCycle) + 2 * M_PI;
        speed = vs->xyspeed * bg_weaponBobAmplitudeBase->current.value;
        //speed = vs->xyspeed * 0.16;
        
        vAngOfs[0] = BG_CalculateWeaponMovement_VerticalBobFactor(ps, cycle, speed) * -1.0;
        vAngOfs[1] = BG_CalculateWeaponMovement_HorizontalBobFactor(ps, cycle, speed) * -1.0;
        
        //dbgCon->Print("vAngOfs: {:.8f} {:.8f}\n", vAngOfs[0], vAngOfs[1]);
        
        horBob = BG_CalculateWeaponMovement_HorizontalBobFactor(ps, cycle - 0.47123894, speed * bg_weaponBobAmplitudeRoll->current.value);
        //horBob = BG_CalculateWeaponMovement_HorizontalBobFactor(ps, cycle - 0.47123894, speed * 1.5);

        vAngOfs[2] = std::min(0.0, (double)horBob);

        fPositionLerp = ps->fWeaponPosFrac;
        if ( fPositionLerp != 0.0 )
        {
            VectorScale(vAngOfs, 1.0 - ((1.0 - weapDef->fAdsBobFactor) * fPositionLerp), vAngOfs);
        }
        VectorMA(angles, fPositionLerp, vAngOfs, angles);
    }
}



double BG_CalculateViewMovement_HorizontalBobFactor(playerState_s *ps, float cycle, float speed)
{
    float amplitude;
    /*WeaponDef *weapDef;

    //weapDef = BG_GetWeaponDef(ps->weapon);
    //if ( ps->waterlevel < 3 )
    {
        if ( ps->pm_flags & 0x400000 )
        {
            amplitude = (float)(speed * bg_weaponBobAmplitudeDtp->current.value) * weapDef->vDtpBob[0];
        }
        else */
        if ( ps->viewHeightTarget == 11 )
        {
            amplitude = speed * bg_bobAmplitudeProne->current.vector[0];
        }
        else if ( ps->viewHeightTarget == 40 )
        {
            amplitude = speed * bg_bobAmplitudeDucked->current.vector[0];
//            amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeDucked->current.vector[0];

        }
        else if ( ps->pm_flags & 0x8000 )
        {
//            amplitude = (float)(speed * bg_weaponBobAmplitudeSprinting->current.vector[0]) * weapDef->vSprintBob[0];
            amplitude = speed * bg_bobAmplitudeSprinting->current.vector[0];

        }
        else
        {
            amplitude = speed * bg_bobAmplitudeStanding->current.vector[0];
//            amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeStanding->current.vector[0];
        }
/*
    }
    
    else
    {
        amplitude = bg_weaponBobAmplitudeSwimming->current.value;
    }
    */
    if ( amplitude > bg_viewBobMax->current.value )
    {
        amplitude = bg_viewBobMax->current.value;
    }
    return sin(cycle) * amplitude;
}



double BG_CalculateViewMovement_VerticalBobFactor(playerState_s *ps, float cycle, float speed)
{
    float amplitude; // [esp+8h] [ebp-8h]
    /*
    WeaponDef *weapDef; // [esp+Ch] [ebp-4h]

    weapDef = BG_GetWeaponDef(ps->weapon);
    if ( ps->waterlevel < 3 )
    {
        if ( ps->pm_flags & 0x400000 )
        {
            amplitude = (float)(speed * bg_weaponBobAmplitudeDtp->current.vector[1]) * weapDef->vDtpBob[1];
        }
        else
        */
        if ( ps->viewHeightTarget == 11 )
        {
            amplitude = speed * bg_bobAmplitudeProne->current.vector[1];
        }
        else if ( ps->viewHeightTarget == 40 )
        {
            amplitude = speed * bg_bobAmplitudeDucked->current.vector[1];
  //          amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeDucked->current.vector[1];

        }
        else if ( ps->pm_flags & 0x8000 )
        {
            //amplitude = (float)(speed * bg_weaponBobAmplitudeSprinting->current.vector[1]) * weapDef->vSprintBob[1];
            amplitude = speed * bg_bobAmplitudeSprinting->current.vector[1];
        }
        else
        {
            amplitude = speed * bg_bobAmplitudeStanding->current.vector[1];
//            amplitude = (1.0 - ps->fWeaponPosFrac) * speed * bg_bobAmplitudeStanding->current.vector[1];
        }
/*        
    }
    else
    {
        amplitude = bg_weaponBobAmplitudeSwimming->current.vector[1];
    }
*/
    if ( amplitude > bg_viewBobMax->current.value )
    {
        amplitude = bg_viewBobMax->current.value;
    }
    return (sin(cycle * 4.0 + 1.5707964) * 0.2 + sin(cycle * 2.0)) * 0.75 * amplitude;
}


void BG_CalculateViewMovement_AdsBob(viewState_t *vs, float *angles)
{
    int weapIndex;
    float adsBobFactor;
    float bobCycle;
    playerState_s *ps;
    WeaponDef *weapDef;

    ps = vs->ps;
    if ( vs->ps->fWeaponPosFrac > 0.0 && !(ps->eFlags & 0x300) )
    {
        weapIndex = BG_GetViewmodelWeaponIndex(ps);
        weapDef = BG_GetWeaponDef(weapIndex);
        if ( weapDef->fAdsViewBobMult > 0.0 )
        {
            adsBobFactor = ps->fWeaponPosFrac * weapDef->fAdsViewBobMult;
            bobCycle = BG_GetBobCycle(ps);
            angles[0] = angles[0] - BG_CalculateViewMovement_VerticalBobFactor(ps, bobCycle, vs->xyspeed) * adsBobFactor;
            angles[1] = angles[1] - BG_CalculateViewMovement_HorizontalBobFactor(ps, bobCycle, vs->xyspeed) * adsBobFactor;
        }
    }
}

void BG_CalculateViewMovement_IdleAngles(viewState_t *vs, float *angles)
{
    float v;
    float s;
    float fTargScale;
    float fTargFactor;
    float idleSpeed;
    int weapIndex;
    WeaponDef *weapDef;
    playerState_s *ps;

    ps = vs->ps;
    weapIndex = BG_GetViewmodelWeaponIndex(vs->ps);
    weapDef = BG_GetWeaponDef(weapIndex);
    if ( weapDef->overlayReticle )
    {
        if ( ps->fWeaponPosFrac != 0.0 )
        {
            if ( BG_IsAimDownSightWeapon(weapIndex) )
            {
                fTargScale = (float)((float)(weapDef->fAdsIdleAmount - weapDef->fHipIdleAmount) * ps->fWeaponPosFrac) + weapDef->fHipIdleAmount;
                idleSpeed = (float)((float)(weapDef->adsIdleSpeed - weapDef->hipIdleSpeed) * ps->fWeaponPosFrac) + weapDef->hipIdleSpeed;
                if ( zero_idle_movement->current.enabled )
                {
                    fTargScale = 0.0;
                    idleSpeed = 0.0;
                }
            }
            else if ( weapDef->fHipIdleAmount == 0.0 )
            {
                //fTargScale = 0.0;
                fTargScale = 80.0;
                //idleSpeed = 0.0;
                idleSpeed = 1.0;
            }
            else
            {
                fTargScale = weapDef->fHipIdleAmount;
                idleSpeed = weapDef->hipIdleSpeed;
            }
            /*
            if ( !(ps->eFlags & 8) || ps->pm_flags & 0x400000 )
            {
                if ( ps->eFlags & 4 )
                {
                    fTargFactor = weapDef->fIdleCrouchFactor;
                }
                else
                {
                    fTargFactor = 1.0;
                }
            }
            else
            {
                fTargFactor = weapDef->fIdleProneFactor;
            }*/
            if ( ps->eFlags & 8 )
            {
                fTargFactor = weapDef->fIdleProneFactor;

            }else if ( ps->eFlags & 4 ){
                
                fTargFactor = weapDef->fIdleCrouchFactor;
            }
            else
            {
                fTargFactor = 1.0;
            }
/*            
            if ( weapDef->overlayReticle )
            {
*/
            if ( ps->fWeaponPosFrac != 0.0 && fTargFactor != vs->fLastIdleFactor )
            {
                if ( fTargFactor <= vs->fLastIdleFactor )
                {
                    vs->fLastIdleFactor = vs->fLastIdleFactor - vs->frametime * 0.5;
                    if ( fTargFactor > vs->fLastIdleFactor )
                    {
                        vs->fLastIdleFactor = fTargFactor;
                    }
                }
                else
                {
                    vs->fLastIdleFactor = vs->frametime * 0.5 + vs->fLastIdleFactor;
                    if ( vs->fLastIdleFactor > fTargFactor )
                    {
                        vs->fLastIdleFactor = fTargFactor;
                    }
                }
            }
//            }
            s = fTargScale * vs->fLastIdleFactor * ps->fWeaponPosFrac * ps->holdBreathScale;
            *vs->weapIdleTime += (signed int)(ps->holdBreathScale * vs->frametime * 1000.0 * idleSpeed);
            
            v = sin((float)*vs->weapIdleTime * 0.0007);
            angles[1] += s * v * 0.01;

            v = sin((float)*vs->weapIdleTime * 0.001);
            angles[0] += s * v * 0.01;
        }
    }
}

void BG_CalculateViewMovement_DamageKick(viewState_t *vs, float *angles)
{
    int weapIndex;
    float v;
    float fRatio;
    float fFactor;
    playerState_s *ps;
    WeaponDef *weapDef;

    if ( vs->damageTime )
    {
        ps = vs->ps;
        weapIndex = BG_GetViewmodelWeaponIndex(vs->ps);
        weapDef = BG_GetWeaponDef(weapIndex);
        fFactor = 1.0 - (ps->fWeaponPosFrac * 0.5);
        if ( ps->fWeaponPosFrac != 0.0 )
        {
            if ( weapDef->overlayReticle )
            {
                fFactor = (ps->fWeaponPosFrac * 0.5 + 1.0) * fFactor;
            }
        }
        fRatio = (float)(vs->time - vs->damageTime);
        if ( fRatio >= 100.0 )
        {
            fRatio = 1.0 - ((fRatio - 100.0) / 400.0);
            if ( fRatio > 0.0 )
            {
                v = 1.0 - GetLeanFraction(1.0 - fRatio);
                v = v * fFactor;
                angles[0] += (v * vs->v_dmg_pitch);
                angles[2] += (v * vs->v_dmg_roll);
            }
        }
        else
        {
            v = GetLeanFraction(fRatio / 100.0);
            v = v * fFactor;
            angles[0] += (v * vs->v_dmg_pitch);
            angles[2] += (v * vs->v_dmg_roll);
        }
    }
}


void BG_CalculateViewAngles(viewState_t *vs, float *angles)
{
    VectorClear(angles);
    BG_CalculateViewMovement_DamageKick(vs, angles);
    BG_CalculateViewMovement_IdleAngles(vs, angles);
    BG_CalculateViewMovement_BobAngles(vs, angles);
    BG_CalculateViewMovement_AdsBob(vs, angles);
}
