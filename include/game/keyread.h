#ifndef GAME_KEYREAD_H
#define GAME_KEYREAD_H

#include "engine/functions.h"

extern u16 data_0212c510;      // keys pressed this frame (including auto-repeat)
extern u16 data_0212c514;      // keys held
extern u8 data_0212c548[4];    // frames each direction key has been held (up, left, down, right order of the key bits 0x40, 0x10, 0x80, 0x20)

extern u16 data_0212c518;      // keys reported as repeating this frame
extern u16 data_0212c51c;      // frames until the next repeat

// State cleared whenever the key state changes (it looks like the touch state of the frame; layout unknown).
typedef struct KeyAuxState {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ u16 unk_04;
    /* 06 */ u8 unk_06[10];
    /* 10 */ u32 unk_10;
} KeyAuxState;
extern KeyAuxState data_0212c5d4;

extern "C" {
void KeyRead(void);
void KeyRepeat(void);
}

#endif
