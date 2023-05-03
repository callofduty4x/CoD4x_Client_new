#include "../q_shared.h"
#include "bg_weapon.h"

dvar_s* zero_idle_movement;


void BG_RegisterDvarsEx()
{
    bg_weaponBobAmplitudeBase = Dvar_RegisterFloat("bg_weaponBobAmplitudeBase", 0.16, 0.0, 1.0, 0, "The base speed-based weapon bob amplitude");
    //bg_weaponBobAmplitudeSprinting = Dvar_RegisterVec2("bg_weaponBobAmplitudeSprinting", 0.02, 0.014, 0.0, 1.0, 0x180u, "The multiplier to apply to the player's speed to get the weapon bob amplitude while sprinting");
    //bg_weaponBobAmplitudeStanding = Dvar_RegisterVec2("bg_weaponBobAmplitudeStanding", 0.055, 0.025, 0.0, 1.0, 0x4080u, "The multiplier to apply to the player's speed to get the weapon bob amplitude while standing");
    //bg_weaponBobAmplitudeDucked = Dvar_RegisterVec2("bg_weaponBobAmplitudeDucked", 0.045000002, 0.025, 0.0, 1.0, 0x180u, "The multiplier to apply to the player's speed to get the weapon bob amplitude while ducking");
    //bg_weaponBobAmplitudeProne = Dvar_RegisterVec2("bg_weaponBobAmplitudeProne", 0.02, 0.0049999999, 0.0, 1.0, 0x180u, "The multiplier to apply to the player's speed to get the weapon bob amplitude while prone");
    bg_weaponBobAmplitudeRoll = Dvar_RegisterFloat("bg_weaponBobAmplitudeRoll", 1.5, 0.0, 90.0, 0x180u, "The amplitude applied to the roll for weapon bobbing");
    bg_weaponBobMax = Dvar_RegisterFloat("bg_weaponBobMax", 10.0, 0.0, 36.0, 0x180u, "The maximum allowed weapon/viewmodel bob amplitude");
    bg_weaponBobLag = Dvar_RegisterFloat("bg_weaponBobLag", 0.25, -1.0, 1.0, 0x180u, "The lag that will be applied the weapon bob cycle");
    //bg_viewBobMax = Dvar_RegisterFloat("bg_bobMax", 8.0, 0.0, 36.0, 0x180u, "The maximum allowed bob amplitude");
    bg_viewBobMax = Dvar_RegisterFloat("bg_bobMax", 45.0, 0.0, 50.0, 0x180u, "The maximum allowed bob amplitude");
    zero_idle_movement = Dvar_RegisterBool("zero_idle_movement", 0, 0x80u, "Turn the ADS idle movement off.");
}


