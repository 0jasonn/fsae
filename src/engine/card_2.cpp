#include "engine/functions.h"
#include "engine/card.h"

// NitroSDK CARD unit (plain names from the ROM). Functions in this file:
//   CARDi_GetWorkPtr (0x020a3900), CARDi_GetWork (0x020a3910), CARDi_SetWorkPtr (0x020a3928),
//   CARD_GetRomHeader (0x020a3938), CARD_GetOwnRomHeader (0x020a3944), CARD_GetOwnRomHeaderTWL (0x020a3950),
//   CARD_LockRom (0x020a395c), G3C_Direct1 (0x020a39cc), CARDi_ReleaseLock (0x020a3a60),
//   CARDi_GetAccessLevel (0x020a3ae0).
// CARDi_AcquireLock (0x020a39e8) is parked in scratch/agentC/nonmatching.

typedef struct CardLock {
    u8 pad_00[0x14];
    s32 owner;      // 0x14
    s32 count;      // 0x18
    u32 queue[2];   // 0x1c
    s32 level;      // 0x24
} CardLock;

// The stack block CARD_LockRom builds: an OSEvent at +0, an OSVAlarm at +0xc and the bus-lock listener at +0x34.
typedef struct CardLockEvent {
    u8 event[0x0c]; // OSEvent
    u8 alarm[0x1c]; // OSVAlarm
    u8 pad_28[0x34 - 0x28];
    void *fn;       // 0x34
    void *arg;      // 0x38
    u8 pad_3c[4];
} CardLockEvent;

// The game-card header field at 0x1b4, as bitfields.
typedef struct CardRomHeader {
    u8 pad[0x1b4];
    u32 rsv5:5;
    u32 f5:1;
    u32 rsv6:2;
    u32 f8:1;
    u32 rsv7:6;
    u32 f15:1;
    u32 f16:1;
} CardRomHeader;

#define CARD_LOCK ((CardLock *)data_0217dae0)

void CARDi_ReleaseLock(u32 owner, u32 level) {
    CardLock *lock = CARD_LOCK;
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
