#ifndef WIP_B_HUD_H
#define WIP_B_HUD_H

// Knife::Hud::HudManager (the object at KnifeApp + 0x1f8) and the HUD helpers that the cockpit code calls. The original
// class methods are called through their plain dsd symbol names, with the this pointer as the first argument.
#include "engine/functions.h"

extern "C" {
void Knife_Hud_HudManager_setActivePlayer(void *hud, s32 playerNo); // original setActivePlayer(int)
s32 Knife_Hud_HudManager_startCallAnim(void *hud, s32 playerNo);    // original startCallAnim(int), nonzero when it started
void Knife_Hud_HudManager_update(void *hud, s32 mode);              // original update(int)
void func_0209e788(void *hud, s32 index, u8 value);                 // dsd name, stores value at hud + 0x70 + index * 4
}

#endif
