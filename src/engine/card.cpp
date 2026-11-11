#include "engine/functions.h"
#include "engine/card.h"

// NitroSDK CARD unit (plain names from the ROM). Functions in this file:
//   CARDi_GetWorkPtr (0x020a3900), CARDi_GetWork (0x020a3910), CARDi_SetWorkPtr (0x020a3928),
//   CARD_GetRomHeader (0x020a3938), CARD_GetOwnRomHeader (0x020a3944), CARD_GetOwnRomHeaderTWL (0x020a3950),
//   CARD_LockRom (0x020a395c), G3C_Direct1 (0x020a39cc), CARDi_ReleaseLock (0x020a3a60),
//   CARDi_GetAccessLevel (0x020a3ae0).
// CARDi_AcquireLock (0x020a39e8) is parked in scratch/agentC/nonmatching.

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

