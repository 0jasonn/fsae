#include "engine/wm_d.h"
#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Knife::Comm::WirelessManager state update functions (plain names, self is the manager). The state machine is kept in
// WmDWork: state (0x1cc4), timer (0x1cd8, the step inside a state) and the controller flag (0x1cdc).

extern char data_0211b1a8[];
extern char data_0211b1b4[];
extern char data_0211b1c0[];

extern "C" u16 WM_GetAllowedChannel(void);
extern "C" u32 WM_PowerOn(void *callback);
extern "C" u32 WM_PowerOff(void *callback);
extern "C" u32 WM_Disable(void *callback);
extern "C" void Knife_Comm_WirelessManager_callback_WM_Enable(void *result);
extern "C" void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
extern "C" void Knife_Comm_WirelessManager_callback_WM_ResetStep(void *result);
extern "C" BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
extern "C" void Knife_Comm_ChildInfo_cleanup(void *child);

// update_off2idle: powers the wireless hardware on, step by step (timer 1 starts WM_PowerOn).
extern "C" void Knife_Comm_WirelessManager_update_off2idle(void *self);
ARM void Knife_Comm_WirelessManager_update_off2idle(void *self) {
    WmDWork *w = (WmDWork *)self;
    u32 code;

    switch (w->timer) {
    case 0:
    case 2:
    case 4:
        break;
    case 1:
        code = WM_PowerOn((void *)Knife_Comm_WirelessManager_callback_WM_Enable);
        if (Knife_Comm_WirelessManager_handleResult(self, code, 0, data_0211b1a8) != 0) {
            w->timer = 2;
        }
        break;
    case 3:
        w->state = 2;
        w->timer = 0;
        w->unk_1cdc = 0;
        break;
    case 5:
        w->state = 0;
        w->timer = 0;
        w->unk_1cdc = 0;
        break;
    }
}

// update_idle: refreshes the allowed channel mask.
extern "C" void Knife_Comm_WirelessManager_update_idle(void *self);
ARM void Knife_Comm_WirelessManager_update_idle(void *self) {
    ((WmDWork *)self)->channelMask = WM_GetAllowedChannel();
}

// update_idle2off: powers the wireless hardware off, step by step (timer 1 starts WM_PowerOff, timer 3 WM_Disable).
extern "C" void Knife_Comm_WirelessManager_update_idle2off(void *self);
ARM void Knife_Comm_WirelessManager_update_idle2off(void *self) {
    WmDWork *w = (WmDWork *)self;
    u32 code;

    switch (w->timer) {
    case 0:
    case 2:
    case 4:
        break;
    case 1:
        code = WM_PowerOff((void *)Knife_Comm_WirelessManager_callback_WM_PowerOffStep);
        if (Knife_Comm_WirelessManager_handleResult(self, code, 0, data_0211b1b4) != 0) {
            w->timer = 2;
        }
        break;
    case 3:
        code = WM_Disable((void *)Knife_Comm_WirelessManager_callback_WM_ResetStep);
        if (Knife_Comm_WirelessManager_handleResult(self, code, 0, data_0211b1c0) != 0) {
            w->timer = 4;
        }
        break;
    case 5:
        w->state = 0;
        w->timer = 0;
        w->unk_1cdc = 0;
        break;
    }
}
