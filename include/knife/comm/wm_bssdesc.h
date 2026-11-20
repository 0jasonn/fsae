#ifndef KNIFE_COMM_WM_BSSDESC_H
#define KNIFE_COMM_WM_BSSDESC_H

#include "types.h"

// SDK WMBssDesc (0xc0 bytes): the description of a beacon found by a scan, followed by the game info block.
typedef struct WMBssDesc {
    u16 length;            // 0x00
    u16 rssi;              // 0x02
    u8 bssid[6];           // 0x04
    u16 ssidLength;        // 0x0a
    u8 ssid[32];           // 0x0c
    u16 capaInfo;          // 0x2c
    u16 rateSetBasic;      // 0x2e
    u16 rateSetSupport;    // 0x30
    u16 beaconPeriod;      // 0x32
    u16 dtimPeriod;        // 0x34
    u16 channel;           // 0x36
    u16 cfpPeriod;         // 0x38
    u16 cfpMaxDuration;    // 0x3a
    u16 gameInfoLength;    // 0x3c
    u16 otherElementCount; // 0x3e
    u32 gameInfo[0x20];    // 0x40 (copied in words)
} WMBssDesc;

extern "C" {
void Knife_Comm_ParentInfo_setBssDesc(void *self, const WMBssDesc *bssDesc, s32 value);
}

#endif
