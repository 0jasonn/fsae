#ifndef KNIFE_COMM_WIRELESS_MANAGER_METHODS_H
#define KNIFE_COMM_WIRELESS_MANAGER_METHODS_H

// Declarations for the Knife::Comm::WirelessManager methods turnOn, turnOff, reset, endParent, disconnect,
// updateUserGameInfo and internalReset (all return BOOL, as the original does), and the inline WmInterruptSection.

#include "types.h"
#include "knife/comm/wireless_manager.h"

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



// SDK and ROM functions the WirelessManager methods call.
extern "C" {
s32 func_02019968(void);                                          // thunk to a check outside the ARM9 image
s32 WM_Reset(void *callback);
s32 WM_PowerOff(void *callback);
s32 WM_EndDataSharing(void *buf);
s32 WM_EndMP(void *callback);
s32 WM_SetGameInfo(void *callback, void *gameInfo, u16 unk2, u32 unk3, u16 unk4, u8 unk5);
s32 Knife_Comm_WirelessManager_getLinkLevel(void *self);
BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
void Knife_Comm_WirelessManager_callback_WM_EnableStep(void *result);
void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
void Knife_Comm_WirelessManager_callback_WM_Reset(void *result);
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
