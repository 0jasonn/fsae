#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build, or provisional names for func_ addresses):
//   nameEntryUIView::entry_regist (0x020af4a0)

extern "C" {
void nameEntryUIView_moveOut(void *self);
void func_020a7480(s32 a);
void func_020ac038(s32 a, s32 b, s32 c, s32 d);
void subtask_dialogDelete(void);
void clearSaveData(s32 a);
}

extern u8 data_021806f0[];
extern u8 data_021350f7[];

// nameEntryUIView::entry_regist (0x020af4a0): counts down the registration timer at 0x43; at zero it clears the
// selected slot when it holds a name (state 6) or leaves the screen (state 7)
ARM void nameEntryUIView_entry_regist(void *self) {
    u8 *obj;
    u8 sel;
    u8 timer;

    obj = (u8 *)self;
    sel = data_021806f0[0x53d];
    if (obj[0x43] == 0xf) {
        func_020a7480(sel);
    }
    timer = obj[0x43];
    obj[0x43] = timer - 1;
    if (timer != 0) {
        return;
    }
    subtask_dialogDelete();
    if ((s8)data_021350f7[sel * 0x50] != 0) {
        clearSaveData(sel);
        func_020ac038(6, 0, 0, 0);
        obj[0x49] = 6;
        obj[0x4e] = 0x78;
    } else {
        obj[0x49] = 7;
        nameEntryUIView_moveOut(self);
        SoundReq(0x44);
    }
}
