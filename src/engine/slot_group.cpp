#include "engine/functions.h"
#include "global.h"
#include "types.h"

// slot_group: function Ctrl_isSlotGroup (0x020bc528), provisional name.

extern s32 data_020dfb80;

// Ctrl_isSlotGroup() (0x020bc528, provisional name): reads the word data_020dfb80. Returns 1 when it is 0..3, or 4..7
// (after subtracting 4), otherwise 0. The goto labels keep the branch shape of the original.
extern "C" s32 Ctrl_isSlotGroup(void);
ARM s32 Ctrl_isSlotGroup(void) {
    s32 v = data_020dfb80;
    s32 t = -1;

    if ((u32)v <= 3) {
        t = v;
    }
    if ((u32)t <= 3) {
        return 1;
    }
    if ((u32)v <= 3) {
        goto set_neg;
    }
    if ((u32)v <= 7) {
        v = v - 4;
        goto done;
    }
set_neg:
    v = -1;
done:
    return ((u32)v <= 3) ? 1 : 0;
}
