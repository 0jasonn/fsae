#include "engine/functions.h"
#include "global.h"
#include "engine/k_decls.h"

// nameEntryUIView::checkSpace() const (0x020af344): returns 1 when any of the entered characters (u16 list at +0x34, count
// in the signed byte at +0x42) is not a space (0x20). The count is read again every pass (volatile access).
s32 nameEntryUIView_checkSpace(void *self) {
    u8 *obj = (u8 *)self;
    u32 i;

    for (i = 0; i < (u32) * (volatile s8 *)(obj + 0x42); i++) {
        if (*(u16 *)(obj + 0x34 + i * 2) != 0x20) {
            return 1;
        }
    }
    return 0;
}
