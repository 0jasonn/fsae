#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name for a func_ address):
//   nameEntryUIView_clearWork nameEntryUIView_clearWork (0x020afc70)

// nameEntryUIView_clearWork (0x020afc70): sets the state word to 4, clears the 0x80 bytes of the buffer at 0x34 and the
// flags at 0x100 to 0x107, and sets the two words at 0xc8 and 0xcc to 0 and -1
ARM void nameEntryUIView_clearWork(void *self) {
    u8 *obj;

    obj = (u8 *)self;
    *(s32 *)(obj + 4) = 4;
    *(u16 *)(obj + 0x100) = 0;
    obj[0x104] = 0;
    obj[0x106] = 0;
    obj[0x107] = 0;
    MI_CpuFill(obj + 0x34, 0, 0x80);
    *(s32 *)(obj + 0xc8) = 0;
    *(s32 *)(obj + 0xcc) = -1;
}
