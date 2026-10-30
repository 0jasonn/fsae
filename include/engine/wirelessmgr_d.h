#ifndef WIP_D_WIRELESSMGR_D_H
#define WIP_D_WIRELESSMGR_D_H

#include "types.h"
#include "engine/wireless_manager_d.h"
#include "engine/comm_parentinfo.h"

// REG_IME, the interrupt master enable.
#define WM_REG_IME (*(volatile u16 *)0x04000208)

// Field of the WirelessManager at a byte offset from its start (for the fields the D units do not name yet).
#define WM_FIELD(self, off, type) (*(type *)((u8 *)(self) + (off)))

// Knife::Comm::InterruptDisabledSection as a stack instance: the vtable at 0 (data_0211b0d4), the REG_IME value saved
// at 4. The constructor saves REG_IME and clears it; the destructor restores it.
extern char data_0211b0d4[];
extern char data_0211b0dc[];
extern char data_0211b19c[];
extern char data_0211b0e8[];
extern char data_0211b0f4[];
extern char data_0211b100[];
extern char data_0211b10c[];

class WmInterruptSection {
public:
    WmInterruptSection(void) {
        u16 saved;

        vtbl = data_0211b0d4;
        saved = WM_REG_IME;
        WM_REG_IME = 0;
        savedIme = saved;
    }
    ~WmInterruptSection(void) {
        vtbl = data_0211b0d4;
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
    }

    void *vtbl;
    u32 savedIme;
};

// Functions of the WirelessManager that are not declared in functions.h (plain names, extern "C").
extern "C" void Knife_Comm_WirelessManager_internalReset(void *self);
extern "C" void Knife_Comm_WirelessManager_update_off2idle(void *self);
extern "C" void Knife_Comm_WirelessManager_update_idle(void *self);
extern "C" void Knife_Comm_WirelessManager_update_idle2off(void *self);
extern "C" void Knife_Comm_WirelessManager_update_scan(void *self);
extern "C" void Knife_Comm_WirelessManager_update_scan2idle(void *self);
extern "C" void Knife_Comm_WirelessManager_update_idle2parent(void *self);
extern "C" void Knife_Comm_WirelessManager_update_parent(void *self);
extern "C" void Knife_Comm_WirelessManager_update_parent2idle(void *self);
extern "C" void Knife_Comm_WirelessManager_update_idle2child(void *self);
extern "C" void Knife_Comm_WirelessManager_update_child(void *self);
extern "C" void Knife_Comm_WirelessManager_update_child2idle(void *self);
extern "C" void Knife_Comm_WirelessManager_update_reset(void *self);
extern "C" void Knife_Comm_WirelessManager_update_empty0(void *self);
extern "C" void Knife_Comm_WirelessManager_update_empty14(void *self);
extern "C" void Knife_Comm_WirelessManager_update_empty15(void *self);
extern "C" void Knife_Comm_WirelessManager_update_waitScan(void *self);

// SDK and dsd-named functions called by the WirelessManager code (the names are the ROM symbols).
extern "C" s32 func_02019968(void);                    // thunk to a function outside the ARM9 image (a check)
extern "C" s32 func_0201f838(void *callback);          // WM_Enable(callback)
extern "C" s32 Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);  // WM result handler
extern "C" void Knife_Comm_WirelessManager_callback_WM_EnableStep(void *result);  // WM_Enable callback
extern "C" void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);  // WM_PowerOff callback
extern "C" s32 WM_Reset(void *callback);
extern "C" s32 WM_PowerOff(void *callback);
extern "C" s32 WM_GetAID(void);
extern "C" s32 WM_GetConnectedAIDs(void);
extern "C" s32 WM_GetLinkLevel(void);
extern "C" void MI_CpuFill8(void *dst, u32 value, u32 size);
extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern "C" s32 WM_GetDispersionScanPeriod(void);
extern "C" s32 WM_StartScanEx(void *callback, void *param);
extern "C" void Knife_Comm_WirelessManager_callback_WM_StartScanEx(void *result);
extern "C" void WM_EndDataSharing(void *buf);
extern "C" void OS_Terminate(void);
extern "C" void Knife_Comm_WirelessManager_callback_WM_Reset(void *arg);

#endif
