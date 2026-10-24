#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names; the sound slots are 0x44-byte records at data_02183ec4, the lists are
// 0x24-byte heads at data_02184304):
//   SndSlot_ReleaseFirst (SndSlot_ReleaseFirst), SndSlot_ReleaseAll (SndSlot_ReleaseAll), SndSlot_ResetFirst (SndSlot_ResetFirst)

extern u8 data_02183ec4[];
extern u8 data_02184304[];

extern "C" {
void func_020bfd78(void *obj, s32 arg);
void func_020bfdc8(void *obj, s32 arg);
void *func_020c2064(void *head, void *node);
}

// SndSlot_ReleaseFirst (0x020bf89c): releases the object held in the first word of the slot.
extern "C" void SndSlot_ReleaseFirst(void *slot, s32 arg);
ARM void SndSlot_ReleaseFirst(void *slot, s32 arg) {
    func_020bfd78(*(void **)slot, arg);
}

// SndSlot_ReleaseAll (0x020bf8ac): releases every slot whose flag at +0x2c is set.
extern "C" void SndSlot_ReleaseAll(s32 arg);
ARM void SndSlot_ReleaseAll(s32 arg) {
    s32 i;
    u8 *slot;

    for (i = 0; i < 16; i++) {
        slot = data_02183ec4 + i * 0x44;
        if (slot[0x2c] != 0) {
            func_020bfd78(slot, arg);
        }
    }
}

// SndSlot_ResetFirst (0x020bf8ec): resets the object held in the first word of the slot.
extern "C" void SndSlot_ResetFirst(void **slot, s32 arg);
ARM void SndSlot_ResetFirst(void **slot, s32 arg) {
    func_020bfdc8(*slot, arg);
}
