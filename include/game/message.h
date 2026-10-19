#ifndef WIP_C_MESSAGE_H
#define WIP_C_MESSAGE_H

#include "types.h"

// Per-state function of the message box (data_02103c00) and the telop box (data_02103c18).
// A state returns 0 when it is finished for this frame.
typedef int (*MsgStateFunc)(void);
typedef void (*MsgVoidFunc)(void);

// Telop request block (data_0217d36c, 0x18 bytes)
typedef struct TelopWork {
    /* 00 */ u8 active;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 flags; // low nibble = 3 while a request is active, bits 4-5 = bank of (id - 1000) / 100
    /* 03 */ u8 unk_03[3];
    /* 06 */ u16 requestId; // bit 15 is set while the telop is busy
} TelopWork;

// One window slot (8 bytes): the telop and message boxes each have a primary and a secondary array of two
typedef struct WindowSlot {
    /* 00 */ u8 unk_00;
    /* 01 */ u8 active;
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03;
    /* 04 */ u8 tileX;
    /* 05 */ u8 tileY;
    /* 06 */ u8 width;
    /* 07 */ u8 height;
} WindowSlot;

// Message box (data_0217d39c) and telop box (data_0217d484), both 0xe8 bytes with the same layout
typedef struct MsgWork {
    /* 00 */ u8 *uiPtrA; // KnifeApp + 0x108 (msg) or + 0x144 (telop) (guess)
    /* 04 */ u8 *uiPtrB; // KnifeApp + 0x44 (msg) or + 0x180 (telop) (guess)
    /* 08 */ u8 *unk_08; // data_0216efc8 (msg) or data_0216efd4 (telop) (guess)
    /* 0c */ u8 windowPhase; // window opening progress, compared with 1 and 6 in Message (guess)
    /* 0d */ u8 unk_0d;
    /* 0e */ u8 layoutFlags; // low nibble = 1 after msgInit/tlpInit, bits 4-5 = bank passed to Knife_msgFrameDma
    /* 0f */ u8 unk_0f;
    /* 10 */ u8 drawFlags; // low 5 bits set to 0x18 by tlpInit (guess)
    /* 11 */ u8 unk_11;
    /* 12 */ u16 msgId;
    /* 14 */ u8 unk_14[0x25 - 0x14];
    /* 25 */ u8 unk_25;
    /* 26 */ u8 unk_26[0x2a - 0x26];
    /* 2a */ u8 unk_2a; // set to 0xa0 by tlpInit (guess)
    /* 2b */ u8 unk_2b[0xac - 0x2b];
    /* ac */ u8 unk_ac[4]; // cleared when the window starts closing
    /* b0 */ u8 unk_b0[0xd0 - 0xb0];
    /* d0 */ u8 state; // index into the state table
    /* d1 */ u8 subState; // index into the move table data_02103c34
    /* d2 */ u8 waitTimer; // frames to wait before the state table runs again
    /* d3 */ u8 unk_d3[0xe0 - 0xd3];
    /* e0 */ u8 lineChangeReq; // set when the line change has to run (knife_msgLineChange)
    /* e1 */ u8 unk_e1[2];
    /* e3 */ u8 windowMode; // 1 while the window opens, 3 while it closes
    /* e4 */ u8 unk_e4[0xe7 - 0xe4];
    /* e7 */ u8 unk_e7;
} MsgWork;

extern TelopWork data_0217d36c;
extern MsgWork data_0217d39c;
extern MsgWork data_0217d484;
extern u8 data_0216efbc[];
extern u8 data_0217d384[];
extern u8 data_0217d3c0[];
extern u8 data_0217d4a8[];
extern u8 data_0217d358[];
extern u8 data_0217d3a8[];
extern u8 data_0217d490[];
extern u8 data_0216efc8[];
extern u8 data_0216efd4[];
extern u8 data_0211ed80[];
extern u8 data_021371a0[];
extern u8 data_021361a0[];
extern void func_02026774(void);
extern void telopFrame(s8 height, u16 *tiles);
extern void telopString(u16 *tiles, u8 flag);
extern MsgStateFunc data_02103c00[];
extern MsgStateFunc data_02103c18[];
extern MsgVoidFunc data_02103c34[];
extern WindowSlot data_0216f000[];
extern WindowSlot data_0216f010[];
extern WindowSlot data_0216efe0[];
extern WindowSlot data_0216eff0[];
extern u8 data_0212c618[];

extern void *KnifeApp_getInstance(void);
extern void func_02029a50(void *dst, u32 size);
extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void statusUpdate(int mode);
extern int telopUpdate(int mode);
extern int msgWinSizeChange(int mode);
extern void SoundReq(int sfx);
extern void Stub_IgnoreArg(int arg);
extern void knife_msgLineChange(MsgWork *msg, s32 lines);
extern void Knife_msgFrameDma(MsgWork *msg, u32 bank);
extern void Knife_palletChange(MsgWork *msg, u8 pallet);
extern void *Knife_MsgReadPtrFromID(void *dat, u16 id);
extern void deleteWindow(void);
extern void telopWindow(void);
extern void createWindow(void);

#endif
