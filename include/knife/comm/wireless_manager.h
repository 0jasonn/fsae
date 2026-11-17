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

// The game-info block the manager fills and hands to WM_SetGameInfo (magic 0x464e4b = "KNF").
typedef struct KnifeGameInfo {
    u32 magic;     // 0x00: 0x464e4b ("KNF")
    u16 value;     // 0x04
    u16 linkLevel; // 0x06
} KnifeGameInfo;

// Knife::Comm::WirelessManager (the singleton returned by func_020909c8), the one layout every unit uses. Offsets from
// the start of the manager. Only the fields the functions so far read or write are named; the rest is kept as bytes.
typedef struct WirelessManagerWork {
    u8 unk_0000[0x20];
    KnifeGameInfo gameInfo;                // 0x20: the game info handed to WM_SetGameInfo
    u8 unk_0028[0x1a4 - 0x28];
    u16 paramA;                            // 0x1a4: WM_SetGameInfo argument (unk2)
    u8 unk_1a6[0x1ae - 0x1a6];
    u16 isFlag;                            // 0x1ae: flag passed to WM_SetGameInfo (unk5)
    u16 userValue;                         // 0x1b0: copied into gameInfo.value
    u8 unk_1b2[0x1d2 - 0x1b2];
    u16 bestChannel;                       // 0x1d2: channel of the best measured level (MeasureChannel callback)
    u8 unk_1d4[0xcc0 - 0x1d4];
    WmScanExParam scanParam;               // 0xcc0: parameter block of WM_StartScanEx
    Knife::Comm::ParentInfo parents[16];   // 0xd04: the 16 parent entries found by scanning (0xd0 bytes each)
    u8 unk_1a04[0x1c5c - 0x1a04];
    u32 slots[16];                         // 0x1c5c: 16 words
    void *allocator;                       // 0x1c9c: the allocator given to init (WmAllocatorIface, non-NULL once initialized)
    void *buf1;                            // 0x1ca0: 0xf00-byte buffer
    void *buf2;                            // 0x1ca4: 0x400-byte buffer (scan results)
    void *recvBuf;                         // 0x1ca8
    void *sendBuf;                         // 0x1cac
    u32 recvSize;                          // 0x1cb0
    s32 sendSize;                          // 0x1cb4
    u8 scanMode;                           // 0x1cb8
    u8 endScanRequest;                     // 0x1cb9: set by requestEndScan while scanning
    u8 unk_1cba[0x1cbc - 0x1cba];
    s32 channel;                           // 0x1cbc: channel index used by stepNextChannel
    s32 bestLevel;                         // 0x1cc0: best measured level (MeasureChannel callback)
    s32 state;                             // 0x1cc4: the state machine index (0 to 15)
    s32 maxLevel;                          // 0x1cc8: the largest field_c8 of the parent entries
    u8 entryFlag;                          // 0x1ccc: the flag given to setEntry (also set from isFlag when connecting)
    u8 unk_1ccd;
    u16 channelMask;                       // 0x1cce: allowed channels (set by the enable callback)
    u16 paramD;                            // 0x1cd0: WM_SetGameInfo argument (unk4)
    u8 unk_1cd2[0x1cd4 - 0x1cd2];
    s32 timer2;                            // 0x1cd4
    s32 timer;                             // 0x1cd8: the step inside a state
    u8 callPending;                        // 0x1cdc: an SDK call is pending (set after a started call, cleared by its callback; func_02090ecc returns it)
    u8 unk_1cdd;                           // 0x1cdd: frame flag
    u8 unk_1cde[0x1ce0 - 0x1cde];
    u16 linkValue;                         // 0x1ce0
    u8 unk_1ce2[2];
    s32 connectPhase;                      // 0x1ce4: connect phase (StartConnect and StartMP callbacks)
} WirelessManagerWork;

#endif
