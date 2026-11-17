#ifndef KNIFE_COMM_WIRELESS_MANAGER_H
#define KNIFE_COMM_WIRELESS_MANAGER_H

#include "types.h"
#include "knife/comm/comm_parentinfo.h"

// Parameter block of WM_StartScanEx (0x44 bytes, SDK WMScanExParam)
typedef struct WmScanExParam {
    void *scanBuf;        // 0x00
    u16 scanBufSize;      // 0x04
    u16 channelList;      // 0x06
    u16 maxChannelTime;   // 0x08
    u8 bssid[6];          // 0x0a
    u16 scanType;         // 0x10
    u16 ssidLength;       // 0x12
    u8 ssid[0x30];        // 0x14
} WmScanExParam;

// Knife::Comm::WirelessManager fields used by the D units. Offsets from the start of the manager. Only the fields
// the functions so far read or write are named; the rest is kept as bytes.
typedef struct WirelessManagerWork {
    u8 unk_0000[0xcc0];
    WmScanExParam scanParam;               // 0xcc0: parameter block of WM_StartScanEx
    Knife::Comm::ParentInfo parents[16];   // 0xd04: the 16 parent entries found by scanning (0xd0 bytes each)
    u8 unk_1a04[0x1c9c - 0x1a04];
    void *allocator;         // 0x1c9c: the allocator given to init (non-NULL once initialized)
    void *buf1;              // 0x1ca0: 0xf00-byte buffer
    void *buf2;              // 0x1ca4: 0x400-byte buffer
    u8 unk_1ca8[0x1cb8 - 0x1ca8];
    u8 scanMode;             // 0x1cb8
    u8 endScanRequest;       // 0x1cb9: set by requestEndScan while scanning
    u8 unk_1cba[0x1cc4 - 0x1cba];
    s32 state;               // 0x1cc4: the state machine index (0 to 15)
    s32 maxLevel;            // 0x1cc8: the largest field_c8 of the parent entries
    u8 entryFlag;            // 0x1ccc: the flag given to setEntry
    u8 unk_1ccd;
    u16 channelMask;         // 0x1cce: allowed channels
    u8 unk_1cd0[0x1cd8 - 0x1cd0];
    s32 timer;               // 0x1cd8
    u8 callPending;          // 0x1cdc: an SDK call is pending (set after a started call, cleared by its callback; func_02090ecc returns it)
    u8 unk_1cdd;             // 0x1cdd
} WirelessManagerWork;

#endif
