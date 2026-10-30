#ifndef WIP_E_GROUPCREATEUI_H
#define WIP_E_GROUPCREATEUI_H

// groupCreateUIView: the group create screen. Derives from basedUIView (0x00..0x30). Slot 0 of its vtable is
// initialize's first object, slot 3 enter and slot 4 leave are set by initialize through the static block at
// data_0217e4fc. entryCount is the number of pushed entries, entries[] holds the views (0x3c..0x5c).

#include "types.h"
#include "game/baseduiview.h"

typedef struct GroupCreateUIView {
    /* 00 */ basedUIView base;
    /* 30 */ basedUIView *rootView; // data_0217e2f4 object, set as the root view by initialize
    /* 34 */ basedUIView *secondView; // data_0217e4fc object
    /* 38 */ s32 entryCount;
    /* 3c */ basedUIView *entries[8];
    /* 5c */ u16 unk_5c;
    /* 5e */ u8 unk_5e;
    /* 5f */ u8 unk_5f;
    /* 60 */ u8 unk_60;
} GroupCreateUIView;

extern "C" {
void groupCreateUIView_initialize(GroupCreateUIView *self);
void groupCreateUIView_viewWillApper(GroupCreateUIView *self);
}

#endif
