#include "engine/functions.h"
#include "global.h"
#include "ui/widget/menu.h"

// Sound object referenced by a menu sound handle (fields by the offsets used in the sound helpers).
typedef struct MenuSoundObj {
    /* 00 */ u8 unk_00[0x34];
    /* 34 */ u16 state;
    /* 36 */ u16 unk_36;
    /* 38 */ u16 value38;
    /* 3a */ u16 value3a;
    /* 3c */ u8 player;
} MenuSoundObj;

// Functions in this file (provisional names, role not confirmed):
//   MenuSound_SetFade (MenuSound_SetFade), MenuSound_SetFadeTimes (MenuSound_SetFadeTimes)

// MenuSound_SetFade (0x020bfa1c): marks the object in the reference as fading (+0x34 = 1) with the value at +0x38.
void MenuSound_SetFade(void * volatile *ref, u16 value) {
    if (*ref != 0) {
        ((MenuSoundObj *)*ref)->state = 1;
        ((MenuSoundObj *)*ref)->value38 = value;
    }
}

// MenuSound_SetFadeTimes (0x020bfa3c): sets the state (+0x34 = 2), the value at +0x38 and the value at +0x3a.
void MenuSound_SetFadeTimes(void * volatile *ref, u16 value, u16 value2) {
    if (*ref != 0) {
        ((MenuSoundObj *)*ref)->state = 2;
        ((MenuSoundObj *)*ref)->value38 = value;
        ((MenuSoundObj *)*ref)->value3a = value2;
    }
}
