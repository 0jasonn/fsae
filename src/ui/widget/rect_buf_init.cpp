#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/rect_links.h"

// rect_buf_init: function RectBufSet_init (0x020bc84c), provisional name.

// Two buffers at +0x10 and +0x14 (both made by func_020b7b1c, the second aligned to 0x20 when used)
typedef struct RectBufSet {
    u8 unk_00[0x10];   // 0x00
    void *bufA;        // 0x10
    void *bufB;        // 0x14
} RectBufSet;

// RectBufSet_init(self, arg1, sourceA, sourceB, arg5, arg6) (0x020bc84c, provisional name): initialises the set with
// Menu_setupHardware, makes bufA from sourceA (size 4) and bufB from sourceB (size 0x20), then calls func_020bc99c with
// bufA, bufB rounded up to 0x20 and the two other arguments
extern "C" void RectBufSet_init(RectBufSet *self, s32 arg1, void *sourceA, void *sourceB, s32 arg5, u16 arg6);
void RectBufSet_init(RectBufSet *self, s32 arg1, void *sourceA, void *sourceB, s32 arg5, u16 arg6) {
    Menu_setupHardware(self, arg1);
    self->bufA = func_020b7b1c(sourceA, self, 4, 0);
    self->bufB = func_020b7b1c(sourceB, self, 0x20, 0);
    func_020bc99c(self, self->bufA, ((s32)self->bufB + 0x1f) & ~0x1f, arg5, arg6);
}
