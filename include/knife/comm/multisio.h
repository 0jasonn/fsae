#ifndef KNIFE_COMM_MULTISIO_H
#define KNIFE_COMM_MULTISIO_H

#include "engine/functions.h"
#include "engine/player.h"
#include "engine/string16_copy.h"

// Wireless link work used by the MultiSio* functions (0x0216fb38, cleared as 0x1b8 bytes by MultiSioInit).
// The pointers at 0x1c..0x2c point into the work itself. Field names are provisional.
typedef struct MultiSioWork {
    /* 00 */ u8 started;
    /* 01 */ u8 phase;
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03;
    /* 04 */ u8 sendFlag;
    /* 05 */ u8 unk_05;
    /* 06 */ u8 linkFlag;
    /* 07 */ u8 unk_07;
    /* 08 */ u8 unk_08;
    /* 09 */ u8 unk_09;
    /* 0a */ u8 unk_0a;
    /* 0b */ u8 unk_0b;
    /* 0c */ u8 unk_0c[8];
    /* 14 */ u32 unk_14;
    /* 18 */ u32 unk_18;
    /* 1c */ void *bufA;      // points to 0x30
    /* 20 */ void *bufB;      // points to 0x4c
    /* 24 */ void *bufC;      // points to 0x68
    /* 28 */ void *bufD;      // points to 0xd8
    /* 2c */ void *bufE;      // points to 0x148
    /* 30 */ u8 subA[0x1c];
    /* 4c */ u8 subB[0x1c];
    /* 68 */ u8 subC[0x70];
    /* d8 */ u8 subD[0x70];
    /* 148 */ u8 subE[0x70];
} MultiSioWork;

// Multi-play SIO control (GBA REG_SIOCNT layout) and data word
typedef struct SioMultiCnt {
    u16 baudRate : 2;
    u16 si : 1;       // 0 = parent
    u16 sd : 1;       // 1 = all linked
    u16 id : 2;
    u16 error : 1;
    u16 enable : 1;   // transfer busy
    u16 unk_8 : 4;
    u16 mode : 2;
    u16 irqEnable : 1;
    u16 unk_15 : 1;
    u16 data;
} SioMultiCnt;

typedef union MultiSioFlags {
    struct {
        u32 players : 4;
        u32 unk_4 : 3;
        u32 parent : 1;
        u32 unk_8 : 24;
    };
    u32 word; // the whole flag word (copied into the packet's group word)
} MultiSioFlags;

// Timer / SIO register shadow words (0x02171e3c): +0x08 control, +0x0a count, +0x1e
typedef struct MultiSioRegs {
    /* 00 */ u8 unk_00[8];
    union {
        struct {
    /* 08 */ u16 timerCtrl;
    /* 0a */ u16 timerCount;
        };
    /* 08 */ SioMultiCnt sioCnt;
    };
    /* 0c */ u8 unk_0c[0x1e - 0x0c];
    /* 1e */ u16 unk_1e;
} MultiSioRegs;

typedef volatile u16 vu16;

extern MultiSioWork multiSioWork;   // multiSioWork
extern MultiSioRegs multiSioRegs;   // multiSioRegs
extern vu16 multiSioCtrl;           // multiSioCtrl, the same address as multiSioRegs.timerCtrl

extern "C" void MultiSioStart(void);
extern "C" void MultiSioStop(void);

#define REG_TM3CNT (*(volatile u32 *)0x0400010c)
#define REG_IME (*(vu16 *)0x04000208)

// Not in functions.h yet (plain symbol names in the original)
extern "C" int Knife_Comm_WirelessManager_getParentFlag(void *manager);
extern "C" int Knife_Comm_WirelessManager_getConnectedAIDs(void *manager, int a);
extern "C" void Knife_Comm_setPlayerBit(int index, void *flags);
extern "C" void Knife_Comm_removePlayerFromGroup(int index, void *flags);
u32 MultiSioRecvDataCheck(void *recvData);
u32 MultiSioMain(void *recvData, bool keepLink);
extern "C" void MultiSioSendDataSet(void *a);
extern "C" int Knife_Comm_WirelessManager_getFrameFlag(void *manager);
extern "C" u32 Knife_Comm_GetPlayerNoByAID(int index, const void *info);
int set5c_returnZero(void); // C++ symbol, always returns 0
s8 subtask_getFlag(u32 index); // C++ symbol _Z15subtask_getFlagm, src/game/subtask_draw_2.cpp

// Timer control value snapshot taken by MultiSioMain
typedef struct MultiSioRegSnapshot {
    /* 00 */ u16 ctrl;
    /* 02 */ u16 count;
} MultiSioRegSnapshot;

extern MultiSioFlags multiSioFlags; // multiSioFlags
extern u8 data_0212c4d4;


#include "engine/multisio_save.h"   // multiSioSelect

// The packet passed to MultiSioSendDataSet is a ComPacket (engine/com_work.h).
#include "engine/com_work.h"
#include "knife/comm/wirelessmanager.h"

extern u8 data_02fe0000[];

#endif
