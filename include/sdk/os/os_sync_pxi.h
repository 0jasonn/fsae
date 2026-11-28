#ifndef SDK_OS_OS_SYNC_PXI_H
#define SDK_OS_OS_SYNC_PXI_H

// TwlSDK OS start-up handshake with the other processor.
#include "types.h"

// Handshake bytes polled by OSi_SyncWithOtherProc (in the shared area at 0x02fffff0 + ...).
typedef struct OsSyncWork {
    /* 00 */ volatile u8 request;
    /* 01 */ volatile u8 reply;
    /* 02 */ volatile u8 done;
    /* 03 */ volatile u8 ready;
} OsSyncWork;

extern "C" {
void OSi_SendToPxi(u32 command);
void OSi_SyncWithOtherProc(u32 role, OsSyncWork *work);
}

#endif
