#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names; the bitmasks are the sound channel book-keeping at data_02183d60):
//   SndChannel_TryLock (SndChannel_TryLock), SndChannel_Unlock (SndChannel_Unlock), SndChannel_ClearWord0 (SndChannel_ClearWord0),
//   SndChannel_ClearWord4 (SndChannel_ClearWord4), SndChannel_Reset (SndChannel_Reset), SndChannel_Reserve (SndChannel_Reserve),
//   SndChannel_UnlockIndex (SndChannel_UnlockIndex)

extern "C" {
void SND_LockChannel(u32 mask, u32 flag);
void SND_UnlockChannel(u32 mask, u32 flag);
}

// Book-keeping words of the sound channels: +0 and +4 are masks, +8 the locked channels. The reservation table at
// data_02183d6c has 0x14 bytes per entry (index at +0, a value at +8).
typedef struct SndChannelBits {
    u32 word0;
    u32 word4;
    u32 locked;
} SndChannelBits;
extern SndChannelBits data_02183d60;

typedef struct SndChannelEntry {
    u32 index;
    u8 unk_04[4];
    u32 unk_08;
    u8 unk_0c[8];
} SndChannelEntry;
extern SndChannelEntry data_02183d6c[];

// SndChannel_TryLock (0x020bf418): locks the channels of the mask unless one of them is already locked. Zero is
// accepted without locking.
extern "C" s32 SndChannel_TryLock(u32 mask);
ARM s32 SndChannel_TryLock(u32 mask) {
    if (mask == 0) {
        return 1;
    }
    if (mask & data_02183d60.locked) {
        return 0;
    }
    SND_LockChannel(mask, 0);
    data_02183d60.locked |= mask;
    return 1;
}

// SndChannel_Unlock (0x020bf45c): unlocks the channels of the mask.
extern "C" void SndChannel_Unlock(u32 mask);
ARM void SndChannel_Unlock(u32 mask) {
    if (mask == 0) {
        return;
    }
    SND_UnlockChannel(mask, 0);
    data_02183d60.locked &= ~mask;
}

// SndChannel_ClearWord0 (0x020bf48c): clears the bits of the mask in word 0.
extern "C" void SndChannel_ClearWord0(u32 mask);
ARM void SndChannel_ClearWord0(u32 mask) {
    data_02183d60.word0 &= ~mask;
}

// SndChannel_ClearWord4 (0x020bf4a8): clears the bit of the channel index in word 4.
extern "C" void SndChannel_ClearWord4(u32 index);
ARM void SndChannel_ClearWord4(u32 index) {
    data_02183d60.word4 &= ~(1 << index);
}

// SndChannel_Reset (0x020bf4c8): clears the three book-keeping words.
extern "C" void SndChannel_Reset(void);
ARM void SndChannel_Reset(void) {
    data_02183d60.locked = 0;
    data_02183d60.word0 = 0;
    data_02183d60.word4 = 0;
}

// SndChannel_Reserve (0x020bf4e4): locks the channel of the index and returns its reservation entry (0 when the
// channel is busy).
extern "C" SndChannelEntry *SndChannel_Reserve(u32 index);
ARM SndChannelEntry *SndChannel_Reserve(u32 index) {
    SndChannelEntry *entry;

    if (SndChannel_TryLock(1 << index) == 0) {
        return 0;
    }
    entry = &data_02183d6c[index];
    entry->index = index;
    entry->unk_08 = 0;
    return entry;
}

// SndChannel_UnlockIndex (0x020bf528): unlocks the channel whose index is the first word of the argument.
extern "C" void SndChannel_UnlockIndex(u32 *ref);
ARM void SndChannel_UnlockIndex(u32 *ref) {
    SndChannel_Unlock(1 << *ref);
}
