#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Work block: a top pointer at +0x14, a base at +0x18, sixteen slots from +0x1c, an offset at +0x60, a mask halfword at
// +0x68 and a flag byte at +0x6a.
typedef struct SlotWork {
    u8 unk_00[0x14];
    u32 top;
    u32 base;
    u32 slots[16];
    u8 unk_5c[4];
    u32 offset;
    u8 unk_64[4];
    u16 mask;
    u8 flag;
} SlotWork;

extern "C" u32 Slot_RestoreFromStack(SlotWork *self);

// Slot_RestoreFromStack(self) (0x0200c93c): with the stack words that end at base + offset (16 bytes less when flag is
// set), walks down from the top and stores each word into the slot selected by its bit in mask, from slot 15 down. Then
// top becomes base + offset. Returns the word at +0x54.
ARM u32 Slot_RestoreFromStack(SlotWork *self) {
    u32 offset;
    u32 *stackWord;
    s32 i;

    offset = self->offset;
    stackWord = (u32 *)(self->base + offset - (self->flag != 0 ? 0x10 : 0));
    for (i = 15; i >= 0; i--) {
        if (self->mask & (1 << i)) {
            stackWord--;
            self->slots[i] = *stackWord;
        }
    }
    self->top = self->base + offset;
    return self->slots[14];
}
