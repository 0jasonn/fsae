#include "engine/functions.h"
#include "engine/card.h"

// NitroSDK CARD unit (plain names from the ROM). Functions in this file:
//   CARDi_GetWorkPtr (0x020a3900), CARDi_GetWork (0x020a3910), CARDi_SetWorkPtr (0x020a3928),
//   CARD_GetRomHeader (0x020a3938), CARD_GetOwnRomHeader (0x020a3944), CARD_GetOwnRomHeaderTWL (0x020a3950),
//   CARD_LockRom (0x020a395c), G3C_Direct1 (0x020a39cc), CARDi_ReleaseLock (0x020a3a60),
//   CARDi_GetAccessLevel (0x020a3ae0).
// CARDi_AcquireLock (0x020a39e8) is parked in scratch/agentC/nonmatching.

void CARDi_ReleaseLock(u32 owner, u32 level) {
    CardLock *lock = (&data_0217dae0);
    u32 state = OS_DisableInterrupts();

    if (lock->owner != (s32)owner || lock->count == 0) {
        OS_Terminate();
    } else {
        if (lock->level != (s32)level) {
            OS_Terminate();
        }
        if (--lock->count == 0) {
            lock->owner = -3;
            lock->level = 0;
            OS_WakeupThread(lock->queue);
        }
    }
    OS_RestoreInterrupts(state);
}

// Access level from the boot type and the TWL card header flags: 7 on a DSi boot, otherwise bits for
// the media type (4), the game card (1) and the NAND (2).
s32 CARDi_GetAccessLevel(void) {
    CardRomHeader *header;
    s32 level = 0;
    s32 useFlags;

    if (OS_GetBootType() == 1) {
        level = 7;
    } else {
        header = (CardRomHeader *)CARD_GetOwnRomHeaderTWL();
        useFlags = 0;
        if (header->f8) {
            level |= 4;
            useFlags = 1;
        } else if (header->f5) {
            useFlags = 1;
        }
        if (useFlags != 0) {
            if (header->f15) {
                level |= 1;
            }
            if (header->f16) {
                level |= 2;
            }
        }
    }
    return level;
}
