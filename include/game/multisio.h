#ifndef WIP_C_MULTISIO_H
#define WIP_C_MULTISIO_H

#include "engine/functions.h"
#include "engine/player.h"

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

// Timer / SIO register shadow words (0x02171e3c): +0x08 control, +0x0a count, +0x1e
typedef struct MultiSioRegs {
    /* 00 */ u8 unk_00[8];
    /* 08 */ u16 timerCtrl;
    /* 0a */ u16 timerCount;
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
extern "C" void Knife_Comm_WirelessManager_reset(void *manager);
extern "C" int Knife_Comm_WirelessManager_getLinkLevel(void *manager);
extern "C" int func_02091e7c(void *manager);
extern "C" int func_02092234(void *manager, int a);
extern "C" void Knife_Comm_setPlayerBit(int index, void *flags);
extern "C" void func_020ae3b0(int index, void *flags);
extern "C" u16 MultiSioRecvDataCheck(void *a);
extern "C" u32 MultiSioMain(void *a, s32 b);
extern "C" void MultiSioSendDataSet(void *a);
extern "C" u32 func_0209200c(void *manager);
extern "C" u32 func_02092168(void *manager);
extern "C" int func_020921b0(void *manager);
extern "C" const void *func_02092100(void *manager, int index);
extern "C" u32 Knife_Comm_GetPlayerNoByAID(int index, const void *info);
extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);
int set5c_returnZero(void); // C++ symbol, always returns 0
extern "C" void func_0200a3c8(u16 *dst, const u16 *src);
extern "C" void func_0209205c(void *manager, void *packet);
s8 subtask_getFlag(u32 index); // C++ symbol _Z15subtask_getFlagm, src/game/subtask_draw_2.cpp

// Timer control value snapshot taken by MultiSioMain
typedef struct MultiSioRegSnapshot {
    /* 00 */ u16 ctrl;
    /* 02 */ u16 count;
} MultiSioRegSnapshot;

extern u32 multiSioFlags; // multiSioFlags
extern u8 data_0212c4d4;

// Entry of the send table data_021350b0, 0x50 bytes each, selected by multiSioSelect.index
typedef struct MultiSioEntry {
    /* 00 */ u32 word00;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 b05;
    /* 06 */ u16 h06;
    /* 08 */ u16 str08[8];   // zero-terminated, copied into the packet
    /* 18 */ u32 w18;
    /* 1c */ u8 unk_1c[0x48 - 0x1c];
    /* 48 */ u8 b48;
    /* 49 */ u8 unk_49[0x50 - 0x49];
} MultiSioEntry;

typedef struct MultiSioSelect {
    /* 00 */ u8 unk_00[4];
    /* 04 */ u8 index;
} MultiSioSelect;

// Bitfield word at packet+0x24 built by MultiSioSendDataSet
typedef struct MultiSioPacketBits {
    u32 b0 : 2;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 2;
    u32 b9 : 2;
    u32 b11 : 2;
    u32 b13 : 10;
    u32 b23 : 7;
    u32 b30 : 2;
} MultiSioPacketBits;

// Packet passed to MultiSioSendDataSet (the same struct is copied into the send buffer)
typedef struct MultiSioPacket {
    /* 00 */ u8 unk_00[0x14];
    /* 14 */ u16 unk_14[8];
    /* 24 */ MultiSioPacketBits bits;
    /* 28 */ u32 unk_28;
    /* 2c */ u8 unk_2c[4];
    /* 30 */ u32 unk_30;
} MultiSioPacket;

extern MultiSioEntry data_021350b0[];
extern MultiSioSelect multiSioSelect; // multiSioSelect
extern u8 localPlayerIndex;
extern u8 data_02fe0000[];

#endif
