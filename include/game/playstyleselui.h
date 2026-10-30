#ifndef WIP_E_PLAYSTYLESELUI_H
#define WIP_E_PLAYSTYLESELUI_H

// playStyleSelUIView: the play style select screen (derives from basedUIView, 0x00..0x30). rootView and secondView are
// the two static view objects set up by initialize; entries[] (0x3c..0x5c) holds the saved values popped by
// viewWillApper into unk_5d.

#include "types.h"
#include "game/baseduiview.h"

typedef struct PlayStyleSelUIView {
    /* 00 */ basedUIView base;
    /* 30 */ basedUIView *rootView; // data_0217e354 object, the root view
    /* 34 */ basedUIView *secondView; // data_0217e498 object
    /* 38 */ s32 entryCount;
    /* 3c */ u32 entries[8];
    /* 5c */ u8 unk_5c;
    /* 5d */ u8 unk_5d;
    /* 5e */ u8 unk_5e;
} PlayStyleSelUIView;

extern "C" {
void playStyleSelUIView_initialize(PlayStyleSelUIView *self);
void playStyleSelUIView_viewWillApper(PlayStyleSelUIView *self);
s32 func_02019968(void);
}

#endif
