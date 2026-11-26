#ifndef SDK_WM_WM_SYSTEM_H
#define SDK_WM_WM_SYSTEM_H

// TwlSDK WM library system part (wm_system.c): the library state, the per-command callback table and the state checks.
#include "types.h"

typedef void (*WmCallback)(void *result);

// Status block shared with the ARM7 (read after DC_InvalidateRange).
typedef struct WmStatusBlock {
    u16 state; // 0x00: current WM state (0 = ready, 1 = stop, 2 = idle, ...)
    u8 unk_02[0x7c - 0x02];
    void *mpSendBuf;     // 0x07c: data being sent (WM_SetMPDataToPortEx refuses it again)
    u8 unk_80[0x86 - 0x80];
    u16 unk_86;          // 0x086: invalidated before sending (child)
    u8 unk_88[0x182 - 0x88];
    u16 mpReadyBitmap;   // 0x182: child: nonzero once the parent's MP is ready (name is a guess)
    u8 unk_184[0x188 - 0x184];
    u16 aid;             // 0x188: own AID, 0 = parent (name is a guess)
} WmStatusBlock;

// Work area owned by the WM library (handed to WM_Init by the caller).
typedef struct WmWork {
    u8 unk_00[4];
    WmStatusBlock *status;          // 0x004
    u8 unk_08[0x10];
    WmCallback callbackTable[0x4d]; // 0x018: per-command callbacks
    u32 connectedAids;              // 0x14c
    u16 aid;                        // 0x150
} WmWork;

// WM library state at data_0212b960 (0x18 bytes).
typedef struct WmState {
    u16 initialized;             // 0x00
    u16 pad_02;                  // 0x02
    WmWork *work;                // 0x04
    void (*sleepCallback)(void); // 0x08: 0x10-byte callback record handed to the PM list (dsd: data_0212b968)
    u32 sleepCallbackArg;        // 0x0c
    u8 unk_10[8];                // 0x10
} WmState;

extern WmState data_0212b960;

extern "C" {
void WMi_SetCallbackTable(u32 id, WmCallback callback);
void *WMi_GetWorkPointer(void);
s32 WMi_CheckInitialized(void);
s32 WMi_CheckIdle(void);
s32 WMi_CheckStateEx(s32 count, ...);

// Not decompiled yet.
u16 WM_GetAID(void);
u16 WM_GetConnectedAIDs(void);
}

#endif
