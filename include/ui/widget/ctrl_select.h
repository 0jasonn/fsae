#ifndef WIP_F_CTRL_SELECT_H
#define WIP_F_CTRL_SELECT_H

// Declarations for the Ctrl list-cursor code of implementer F (round 16). Callees that are not in engine/functions.h
// are declared here; the reviewer moves the shared ones.

#include "engine/functions.h"
#include "types.h"
#include "ui/widget/ctrl_items.h"

// Slider at +0x5c (and +0x60) of the Ctrl object: its position, the window of visible rows and the current index.
typedef struct CtrlSliderWin {
    /* 00 */ u8 unk_00[0xc];
    /* 0c */ s16 posX;
    /* 0e */ s16 posY;
    /* 10 */ u8 unk_10[0x22 - 0x10];
    /* 22 */ s16 windowFirst;   // index of the first visible row
    /* 24 */ u16 windowCount;   // number of visible rows
    /* 26 */ u8 unk_26[0x2a - 0x26];
    /* 2a */ s16 index;         // current index in the list
} CtrlSliderWin;

// Flags byte at +0x10 of the Ctrl object
typedef struct CtrlFlags10 {
    u8 disabled : 1; // set: the position update does nothing
    u8 unk_bits : 7;
} CtrlFlags10;

// Ctrl object: a base position at +4/+6, the position at +0xc/+0xe, the item list at +0x14, the pool object at +0x1c,
// two embedded objects with a vtable at +0x20 and +0x3c, the list slider at +0x5c, a second slider at +0x60, the cursor
// view at +0x88 and its two sub-objects at +0x8c and +0x90, the mode at +0x9c, the selected flag at +0xae.
typedef struct CtrlSelectObj {
    /* 00 */ u8 unk_00[4];
    /* 04 */ s16 baseX;
    /* 06 */ s16 baseY;
    /* 08 */ u8 unk_08[0xc - 0x08];
    /* 0c */ s16 posX;
    /* 0e */ s16 posY;
    /* 10 */ CtrlFlags10 flags10;
    /* 11 */ u8 unk_11[0x14 - 0x11];
    /* 14 */ CtrlRingItemList *itemList;
    /* 18 */ void *unk_18;
    /* 1c */ void *pool;
    /* 20 */ u8 subA[0x2e - 0x20]; // embedded object, its first word is the vtable
    /* 2e */ s16 unk_2e;
    /* 30 */ u8 subA2[0x3c - 0x30];
    /* 3c */ u8 subB[0x5c - 0x3c]; // embedded object, its first word is the vtable
    /* 5c */ CtrlSliderWin *sliderA;
    /* 60 */ CtrlSliderWin *sliderB;
    /* 64 */ u8 unk_64[0x70 - 0x64];
    /* 70 */ u8 *unk_70;
    /* 74 */ u8 *unk_74;
    /* 78 */ u8 unk_78[0x88 - 0x78];
    /* 88 */ void *cursor;
    /* 8c */ void *unk_8c;
    /* 90 */ void *unk_90;
    /* 94 */ u8 unk_94[0x9c - 0x94];
    /* 9c */ u16 mode;
    /* 9e */ u8 unk_9e[0xa2 - 0x9e];
    /* a2 */ s16 unkA2;
    /* a4 */ s16 unkA4;
    /* a6 */ s16 unkA6;
    /* a8 */ u8 unk_a8[0xaa - 0xa8];
    /* aa */ s16 unkAA;
    /* ac */ u8 unk_ac;
    /* ad */ u8 flagAd;
    /* ae */ u8 selected;
} CtrlSelectObj;

extern "C" {
void func_020b7fec(void *obj, void *arg, s32 value);
void func_020bb788(void *self, u16 mode);
void Ctrl_selectCurrentItem(void *self, s32 flag);
void Ctrl_setSliderIndexA(void *self, s32 value);
void Ctrl_setSliderIndexB(void *self, s32 value);
void RectFlagPair_setFlag(void *self, s32 flag);
void *Menu_AcquirePoolEntry(void *pool, s32 id, s32 value);
s32 Ctrl_advanceSelection(void *self);
void Ctrl_updatePosition(void *self, const s16 *delta);
s32 Ctrl_retreatSelection(void *self);
s32 RectSlot_status(void *self);
}

#endif
