#ifndef SDK_WM_WM_STANDARD_H
#define SDK_WM_WM_STANDARD_H

// TwlSDK WM library commands (wm_standard.c): each checks the WM state, installs the callback and sends one command to
// the ARM7. They return 2 (operating) when the command was sent.
#include "types.h"

// Parent parameters handed to WM_SetParentParameter (0x40 bytes; TwlSDK WMParentParam).
typedef struct WmParentParam {
    u8 *userGameInfo;       // 0x00
    u16 userGameInfoLength; // 0x04
    u16 padding;            // 0x06
    u32 ggid;               // 0x08
    u16 tgid;               // 0x0c
    u16 entryFlag;          // 0x0e
    u16 maxEntry;           // 0x10
    u16 multiBootFlag;      // 0x12
    u16 ksFlag;             // 0x14: key sharing
    u16 csFlag;             // 0x16
    u16 beaconPeriod;       // 0x18
    u16 rsv1[4];            // 0x1a
    u16 rsv2[8];            // 0x22
    u16 channel;            // 0x32
    u16 parentMaxSize;      // 0x34
    u16 childMaxSize;       // 0x36
    u16 rsv3[4];            // 0x38
} WmParentParam;

// Request block sent to the ARM7 for the StartConnectEx command (0x28 bytes).
typedef struct WmStartConnectExReq {
    u16 apiId;     // 0x00
    u16 pad_02;    // 0x02
    void *bssDesc; // 0x04
    u8 ssid[24];   // 0x08
    u32 powerSave; // 0x20
    u16 pad_24;    // 0x24
    u16 authMode;  // 0x26
} WmStartConnectExReq;

extern "C" {
s32 WMi_EnableEx(void *callback, u32 flag);
u32 WM_Disable(void *callback);
u32 WM_PowerOn(void *callback);
s32 WM_PowerOff(void *callback);
s32 WM_Reset(void *callback);
s32 WM_SetParentParameter(void *callback, void *parentParam);
s32 WMi_StartParentEx(void *callback, u32 flag);
u32 WM_EndParent(void *callback);
s32 WM_EndScan(void *callback);
s32 WM_StartConnectEx(void *callback, u16 *bssDesc, const u8 *ssid, u32 powerSave, u16 authMode);
u32 WM_Disconnect(void *callback, u16 aid);
}

#endif
