#ifndef ENGINE_BLEND_REQUEST_H
#define ENGINE_BLEND_REQUEST_H

#include "types.h"

// Fade/blend work (blendRequest, 0x10 bytes up to frameCounter; the original tag is FADE_WORK_). FadeInit() clears all
// 0x10 bytes, FadeSet() starts a fade, FadeMain() runs fadeModeTable[blendMode] once per frame until blendEnabled drops
// to 0. Scenes poll blendEnabled to wait for a fade to finish.
typedef struct FADE_WORK_ {
    /* 00 */ u8 blendEnabled; // nonzero while a fade/blend is running
    /* 01 */ u8 blendMode;    // index into fadeModeTable (0..5); FadeSet starts modes > 3 at 0x100 - blendWeight
    /* 02 */ u8 unk_02;       // cleared by FadeSet
    /* 03 */ u8 blendStep;    // per-frame step of blendWeight
    /* 04 */ u8 fadeRunning;  // nonzero: palette fade (MakeFadeBuff256); zero: brightness fade via displayState
    /* 05 */ u8 unk_05[2];
    /* 07 */ u8 blendColor;   // fade colour passed to MakeFadeBuff256/title_MakeFadeBuff256 (0 or 0x19, 0x16, 0x1c)
    /* 08 */ s16 blendWeight; // 0..0x100
    /* 0a */ u8 unk_0a[2];
    /* 0c */ s32 resetValue;  // bit mask of palette rows to fade (-1 all), see MakeFadeBuff256
} FADE_WORK_;
typedef FADE_WORK_ BlendRequest;

extern BlendRequest blendRequest;

#endif
