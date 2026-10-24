#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   MenuSound_SetFade (MenuSound_SetFade), MenuSound_SetFadeTimes (MenuSound_SetFadeTimes)

// MenuSound_SetFade (0x020bfa1c): marks the object in the reference as fading (+0x34 = 1) with the value at +0x38.
extern "C" void MenuSound_SetFade(void * volatile *ref, u16 value);
ARM void MenuSound_SetFade(void * volatile *ref, u16 value) {
    if (*ref != 0) {
        ((MenuSoundObj *)*ref)->state = 1;
        ((MenuSoundObj *)*ref)->value38 = value;
    }
}

// MenuSound_SetFadeTimes (0x020bfa3c): sets the state (+0x34 = 2), the value at +0x38 and the value at +0x3a.
extern "C" void MenuSound_SetFadeTimes(void * volatile *ref, u16 value, u16 value2);
ARM void MenuSound_SetFadeTimes(void * volatile *ref, u16 value, u16 value2) {
    if (*ref != 0) {
        ((MenuSoundObj *)*ref)->state = 2;
        ((MenuSoundObj *)*ref)->value38 = value;
        ((MenuSoundObj *)*ref)->value3a = value2;
    }
}
