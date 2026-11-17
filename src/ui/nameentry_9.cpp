#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build, or provisional names for func_ addresses):
//   nameEntryUIView::entryCheck (0x020af424), nameEntryUIView::entry_regist (0x020af4a0)

extern "C" {
void nameEntryUIView_moveOut(void *self);
void fsCreateFile(s32 a);
extern "C" void func_020ac038(s32 a, s32 b, s32 c, s32 d);
void subtask_dialogDelete(void);
extern "C" void clearSaveData(s32 a);
}

extern u8 data_021806f0[];
extern u8 data_021350b0[];
extern u8 data_021350f7[];

// Copies the entered name to the selected save slot and starts the registration delay.
void nameEntryUIView_entryCheck(void *self) {
    u32 i;
    u8 *obj;
    u8 *slot;
    u8 selectedSlot;

    obj = (u8 *)self;
    i = 0;
    selectedSlot = data_021806f0[0x53d];
    if ((u32)(s8)obj[0x42] <= i) {
        goto copyDone;
    }
    {
        slot = data_021350b0 + selectedSlot * 0x50;
        do {
            *(u16 *)(slot + 8 + i * 2) = *(u16 *)(obj + 0x34 + i * 2);
            i++;
        } while (i < (u32)*(volatile s8 *)(obj + 0x42));
    }
copyDone:
    func_020ac038(8, 0, 0, 0);
    obj[0x49] = 5;
    obj[0x43] = 0x1e;
}

// nameEntryUIView::entry_regist (0x020af4a0): counts down the registration timer at 0x43; at zero it clears the
// selected slot when it holds a name (state 6) or leaves the screen (state 7)
void nameEntryUIView_entry_regist(void *self) {
    u8 *obj;
    u8 sel;
    u8 timer;

    obj = (u8 *)self;
    sel = data_021806f0[0x53d];
    if (obj[0x43] == 0xf) {
        fsCreateFile(sel);
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
