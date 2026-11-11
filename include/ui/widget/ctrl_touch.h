#ifndef WIP_E_CTRL_TOUCH_E_H
#define WIP_E_CTRL_TOUCH_E_H

#include "engine/functions.h"
#include "ui/widget/rect_obj_view.h"

// Touch state handed to the Ctrl input handler
typedef struct CtrlTouchState {
    s16 x;         // 0x00
    s16 y;         // 0x02
    u8 touching;   // 0x04: the stylus is down
    u8 pressed;    // 0x05: the stylus went down this frame
    u8 released;   // 0x06: the stylus went up this frame
} CtrlTouchState;

// Result of the input handler: which button fired and its value
typedef struct CtrlTouchResult {
    s16 action;    // 0x00
    s16 value;     // 0x02
} CtrlTouchResult;

// Button object of the Ctrl (a rect object): only the flag bits are read
typedef struct CtrlButtonObj {
    u8 unk_00[0x10];
    RectFlagBits flags;   // 0x10
} CtrlButtonObj;

// Ctrl object, only the fields of the input handler
typedef struct CtrlTouchObj {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ void *pool;
    /* 20 */ u8 unk_20[0x64 - 0x20];
    /* 64 */ CtrlButtonObj *buttons[9];
    /* 88 */ u8 unk_88[0x98 - 0x88];
    /* 98 */ s16 pressedButton;   // button under the stylus, -1 for none
} CtrlTouchObj;

extern "C" {
s32 Ctrl_handleTouch(CtrlTouchObj *self, CtrlTouchResult *result, const CtrlTouchState *touch);
s32 RectObjList_findHit2(void **items, s32 count, s16 *pos);
void RectObj_updateHitFlag(void *self, s16 *pos);
void *Menu_AcquirePoolEntry(void *pool, s32 id, s32 value);
u8 Ctrl_updateAc(void *self);
void Ctrl_setCounterA(void *self);
u8 Ctrl_updateAd(void *self);
s32 func_020bb450(void *self);
s32 Ctrl_advanceSelection(void *self);
void func_020bb788(void *self, u16 mode);
}

#endif
