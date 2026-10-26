#ifndef WIP_E_MODESELUI_E_H
#define WIP_E_MODESELUI_E_H

// modeSelUIView: the mode select screen (new / copy / remove). Only the fields the matched functions use are named.
// The view derives from basedUIView (vtable at data_02124af8 is the playStyleSelUIView one; the modeSel vtable is at
// data_02124b64). Slot 0 of the vtable is initialize, slot 1 update, slot 2 an empty function, slot 3 viewWillApper,
// slot 4 leave.

#include "types.h"
#include "game/baseduiview.h"

typedef struct ModeSelUIView {
    /* 00 */ basedUIView base;
    /* 30 */ s32 unk_30; // cleared at the end of initialize
    /* 34 */ u8 unk_34[0x54 - 0x34];
    /* 54 */ basedUIView *child; // the playStyleSelUIView object (data_0217e3d4)
    /* 58 */ u8 unk_58[0x5b - 0x58];
    /* 5b */ u8 unk_5b;
    /* 5c */ u8 unk_5c;
    /* 5d */ u8 unk_5d;
    /* 5e */ u8 unk_5e;
    /* 5f */ u8 unk_5f;
    /* 60 */ u16 unk_60;
} ModeSelUIView;

extern "C" {
void modeSelUIView_initialize(ModeSelUIView *self);
void modeSelUIView_viewWillApper(ModeSelUIView *self);
void modeSelUIView_leave(ModeSelUIView *self);
void modeSelUIView_update(ModeSelUIView *self);
void modeSelUIView_move(ModeSelUIView *self, s32 step);
void modeSelUIView_vfunc2(void *self);
s32 modeSelUIView_updateApper(void *self);
s32 modeSelUIView_updateMain(void *self);
s32 modeSelUIView_updateDisapper(void *self);
s32 modeSelUIView_updateCopy(void *self);
s32 modeSelUIView_updateRemove(void *self);
void func_020a9494(void *self);
void func_020a94a4(void *self);
extern u8 data_0217d23c[];
extern u8 data_0217e2d4[];
extern u8 data_0217e3d4[];
extern u8 data_0217e6f0[];
extern u8 data_02124af8[];
}

#endif
