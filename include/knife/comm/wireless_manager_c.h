#ifndef WIP_C_WIRELESS_MANAGER_H
#define WIP_C_WIRELESS_MANAGER_H

// Self-contained declarations for the Knife::Comm::WirelessManager methods implemented by agent C
// (turnOn, turnOff, reset, endParent, disconnect, updateUserGameInfo, internalReset).
//
// These are kept here instead of reusing include/knife/comm/wirelessmgr_d.h / wm_work.h because those
// headers declare internalReset (and functions.h declares turnOn/turnOff) with a `void` return type,
// while the original functions all return BOOL (the disassembly sets r0 to 0 or 1 before returning).
// The reviewer should fix those shared declarations to BOOL and then this file can be folded back into
// them.

#include "types.h"

// REG_IME, the interrupt master enable.
#define WM_REG_IME (*(volatile u16 *)0x04000208)

// The vtable of the InterruptDisabledSection and the handleResult name strings (rodata).
extern char data_0211b0d4[];
extern char data_0211b0dc[];  // name for handleResult after WM_Enable (turnOn)
extern char data_0211b0e8[];  // name for handleResult after WM_PowerOff (turnOff)
extern char data_0211b0f4[];  // name for handleResult after WM_Reset (turnOff)
extern char data_0211b100[];  // name for handleResult after WM_Reset (reset)
extern char data_0211b130[];  // name for handleResult after WM_EndDataSharing (endParent)
extern char data_0211b144[];  // name for handleResult after WM_EndMP (endParent)
extern char data_0211b160[];  // name for handleResult after WM_EndDataSharing (disconnect)
extern char data_0211b174[];  // name for handleResult after WM_EndMP (disconnect)
extern char data_0211b18c[];  // name for handleResult after WM_SetGameInfo (updateUserGameInfo)
extern char data_0211b19c[];  // name for handleResult after WM_Reset (internalReset)

// Knife::Comm::InterruptDisabledSection as a stack instance (same layout as include/knife/comm/wirelessmgr_d.h):
// the vtable at +0 and the saved REG_IME value at +4. The constructor saves REG_IME and clears it; the
// destructor restores it.
class WmInterruptSection {
public:
    inline WmInterruptSection(void) {
        u16 saved;

        vtbl = data_0211b0d4;
        saved = WM_REG_IME;
        WM_REG_IME = 0;
        savedIme = saved;
    }
    inline ~WmInterruptSection(void) {
        vtbl = data_0211b0d4;
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
    }

    void *vtbl;
    u32 savedIme;
};

// The game-info block the manager fills and hands to WM_SetGameInfo (magic 0x464e4b = "KNF").
typedef struct KnifeGameInfo {
    u32 magic;    // 0x00: 0x464e4b ("KNF")
    u16 value;    // 0x04
    u16 linkLevel; // 0x06
} KnifeGameInfo;

// WirelessManager fields used by the C units, at their offsets from the start of the manager.
typedef struct WmCWork {
    u8 unk_0000[0x20];
    KnifeGameInfo gameInfo;   // 0x20: the game info handed to WM_SetGameInfo
    u8 unk_0028[0x1a4 - 0x28];
    u16 paramA;               // 0x1a4: WM_SetGameInfo argument (unk2)
    u8 unk_1a6[0x1ae - 0x1a6];
    u16 isFlag;               // 0x1ae: flag passed to WM_SetGameInfo (unk5)
    u16 userValue;            // 0x1b0: copied into gameInfo.value
    u8 unk_1b2[0x1cc4 - 0x1b2];
    s32 state;                // 0x1cc4
    u8 unk_1cc8[0x1cd0 - 0x1cc8];
    u16 paramD;               // 0x1cd0: WM_SetGameInfo argument (unk4)
    u8 unk_1cd2[0x1cd8 - 0x1cd2];
    s32 timer;                // 0x1cd8
    u8 unk_1cdc;              // 0x1cdc: controller flag
    u8 unk_1cdd;              // 0x1cdd: frame flag
    u8 unk_1cde[0x1ce4 - 0x1cde];
    s32 connectPhase;         // 0x1ce4
} WmCWork;

// SDK and ROM functions the WirelessManager methods call.
extern "C" {
s32 func_02019968(void);                                          // thunk to a check outside the ARM9 image
s32 func_0201f838(void *callback);                                // WM_Enable(callback)
s32 WM_Reset(void *callback);
s32 WM_PowerOff(void *callback);
s32 WM_EndDataSharing(void *buf);
s32 WM_EndMP(void *callback);
s32 WM_SetGameInfo(void *callback, void *gameInfo, u16 unk2, u32 unk3, u16 unk4, u8 unk5);
s32 Knife_Comm_WirelessManager_getLinkLevel(void *self);
void OS_Terminate(void);
BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
void Knife_Comm_WirelessManager_callback_WM_EnableStep(void *result);
void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
void Knife_Comm_WirelessManager_callback_WM_Reset(void *result);
void Knife_Comm_WirelessManager_callback_WM_StepTimer5(void *result);
void Knife_Comm_WirelessManager_callback_WM_ClearFlag(void *result);
}

// C++-linkage ROM function (mangled symbol _Z13func_02090eccPv).
s32 func_02090ecc(void *self);

// The functions implemented by agent C (all return BOOL, as the original does).
extern "C" {
BOOL Knife_Comm_WirelessManager_turnOn(void *self, BOOL on);
BOOL Knife_Comm_WirelessManager_turnOff(void *self);
BOOL Knife_Comm_WirelessManager_reset(void *self);
BOOL Knife_Comm_WirelessManager_endParent(void *self);
BOOL Knife_Comm_WirelessManager_disconnect(void *self);
BOOL Knife_Comm_WirelessManager_updateUserGameInfo(void *self);
BOOL Knife_Comm_WirelessManager_internalReset(void *self);
}

#endif
