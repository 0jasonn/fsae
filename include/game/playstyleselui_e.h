#ifndef WIP_E_PLAYSTYLESELUI_E_H
#define WIP_E_PLAYSTYLESELUI_E_H

// playStyleSelUIView: the play style select screen. Derives from basedUIView; slot 0 of its vtable (data_02124af8) is
// initialize, slot 1 update, slot 2 an empty function, slot 3 viewWillApper and slot 4 leave. Only the fields the
// matched functions use are named.

#include "types.h"
#include "game/baseduiview.h"

typedef struct PlayStyleSelUIView {
    /* 00 */ basedUIView base;
    /* 30 */ basedUIView *rootView; // first child, set as the root view by initialize
    /* 34 */ basedUIView *secondView;
    /* 38 */ s32 unk_38;
    /* 3c */ u8 unk_3c[0x5d - 0x3c];
    /* 5d */ u8 unk_5d;
} PlayStyleSelUIView;

void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);

extern "C" {
void playStyleSelUIView_leave(void *self);
void playStyleSelUIView_vfunc2(void *self);
void DC_FlushRange(void *base, u32 size);
extern void *data_02180d9c;
}

#endif
