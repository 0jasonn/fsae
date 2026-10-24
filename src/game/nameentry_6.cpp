#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/subtask.h"

// Functions in this file (original names from the debug build, or provisional names for func_ addresses):
//   nameEntryUIView::backspace() (0x020af104), nameEntryUIView_changeCharSet nameEntryUIView_changeCharSet (0x020af17c)

extern "C" {
void nameEntryUIView_loadScreen(void *self);
void nameEntryUIView_keybord_disp(void *self);
}

// nameEntryUIView::backspace (0x020af104): removes the last character of the name and redraws the entries
ARM void nameEntryUIView_backspace(void *self) {
    u8 *obj;
    u32 i;

    obj = (u8 *)self;
    if ((s8)obj[0x42] == 0) {
        return;
    }
    obj[0x42] = (u8)((s8)obj[0x42] - 1);
    if ((s8)obj[0x42] < 0) {
        obj[0x42] = 0;
    }
    *(u16 *)(obj + 0x34 + (s8)obj[0x42] * 2) = 0;
    i = 0;
    while (i < (u32)((s8)obj[0x42] + 1)) {
        Knife_Message_RedrawText(i, 0);
        i++;
    }
    SoundReq(0x94);
}

// nameEntryUIView_changeCharSet (0x020af17c): switches the character table of the keyboard (mode 1 or 2) and reloads it
ARM void nameEntryUIView_changeCharSet(void *self) {
    u8 *obj;
    s32 mode;

    obj = (u8 *)self;
    mode = (s8)obj[0x46];
    switch (mode) {
    case 1:
        if ((s8)obj[0x47] != 0) {
            obj[0x47] = 0;
            nameEntryUIView_loadScreen(self);
            nameEntryUIView_keybord_disp(self);
            SoundReq(0x3e);
        }
        break;
    case 2:
        if ((s8)obj[0x47] != 1) {
            obj[0x47] = 1;
            nameEntryUIView_loadScreen(self);
            nameEntryUIView_keybord_disp(self);
            SoundReq(0x3e);
        }
        break;
    }
}
