#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name for a func_ address):
//   nameEntryUIView_getCursorGroup nameEntryUIView_getCursorGroup (0x020af050)
//   nameEntryUIView_setRowCursor (0x020af0b0)

// nameEntryUIView_getCursorGroup (0x020af050): maps the index r2 of the entry to a group 1 to 4 when the mode is 5,
// otherwise returns the value of the mode field at offset 0x46
s32 nameEntryUIView_getCursorGroup(void *self, s32 mode, s32 index) {
    if (mode == 5) {
        if (index >= 0 && index <= 2) {
            return 1;
        }
        if (index >= 3 && index <= 6) {
            return 2;
        }
        if (index >= 7 && index <= 9) {
            return 3;
        }
        if (index >= 10 && index <= 12) {
            return 4;
        }
    }
    return (s8)((u8 *)self)[0x46];
}

// Moves the cursor to the final column of the current row.
void nameEntryUIView_setRowCursor(void *self) {
    u8 *obj;
    s32 position;
    s32 row;

    obj = (u8 *)self;
    if ((s8)obj[0x46] == 4) {
        return;
    }
    position = *(s16 *)(obj + 0x4a);
    row = position / 5;
    obj[0x4d] = (u8)row;
    *(volatile u8 *)(obj + 0x4c) = 4;
    *(s16 *)(obj + 0x4a) = (s16)((s8)obj[0x4d] * 5 + 4);
    obj[0x44] = 1;
    *(volatile u8 *)(obj + 0x46) = 4;
}
