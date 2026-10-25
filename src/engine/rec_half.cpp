#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// rec_half: function Rec_setHalf102 (0x020b72e0), matching.

// Rec_setHalf102(self, value) (0x020b72e0, provisional name): stores the halfword value at +0x102 of the record
extern "C" void Rec_setHalf102(void *self, u32 value);
ARM void Rec_setHalf102(void *self, u32 value) {
    *(u16 *)((u8 *)self + 0x102) = value;
}
