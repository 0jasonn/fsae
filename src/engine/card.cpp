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

void *CARDi_GetWorkPtr(void) {
    return *(void **)data_0217da64;
}

// Asserts that the CARD work pointer has been installed.
void CARDi_GetWork(void) {
    if (CARDi_GetWorkPtr() == NULL) {
        OS_Terminate();
    }
}

void CARDi_SetWorkPtr(void *work) {
    *(void **)data_0217da64 = work;
}

void *CARD_GetRomHeader(void) {
    return (void *)0x02fffa80;
}

void *CARD_GetOwnRomHeader(void) {
    return (void *)0x02fffe00;
}

void *CARD_GetOwnRomHeaderTWL(void) {
    return (void *)0x02ffe000;
}

// Locks the card bus: takes the resource lock, then waits for the bus condition.
void CARD_LockRom(u16 value) {
    CardLockEvent ev;

    CARDi_AcquireLock(value, 1);
    OS_InitEvent(&ev);
    OS_CreateVAlarm(ev.alarm);
    ev.fn = (void *)CARDi_LockBusCondition;
    ev.arg = &value;
    CARDi_PeekEventListener(&ev);
    OS_WaitEventEx(&ev, 1, 0, 1);
}

void G3C_Direct1(u16 value) {
    CardBus_Release(value);
    CARDi_ReleaseLock(value, 1);
}

