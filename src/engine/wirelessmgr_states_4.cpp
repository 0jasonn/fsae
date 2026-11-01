#include "engine/wm_d.h"
#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_callbacks_api.h"
#include "engine/wm_connect_b_api.h"

// Knife::Comm::WirelessManager state update functions (plain names, self is the manager). The state machine is kept in
// WmDWork: state (0x1cc4), timer (0x1cd8, the step inside a state) and the controller flag (0x1cdc).

extern char data_0211b1a8[];
extern char data_0211b1b4[];
extern char data_0211b1c0[];

extern "C" u16 WM_GetAllowedChannel(void);
extern "C" u32 WM_PowerOff(void *callback);
extern "C" void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
extern "C" BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
extern "C" void Knife_Comm_ChildInfo_cleanup(void *child);

// update_child2idle: step 1 disconnects the child (WM_Disconnect) and step 3 returns to the off state.
extern char data_0211b274[];
extern "C" void Knife_Comm_WirelessManager_update_child2idle(void *self);
void Knife_Comm_WirelessManager_update_child2idle(void *self) {
    WmDWork *w = (WmDWork *)self;
    u32 code;

    switch (w->timer) {
    case 0:
    case 2:
        break;
    case 1:
        Knife_Comm_WirelessManager_deleteMPBuffer(self);
        code = WM_Disconnect((void *)Knife_Comm_WirelessManager_callback_WM_StepTimer4, 0);
        if (Knife_Comm_WirelessManager_handleResult(self, code, 0, data_0211b274) != 0) {
            w->timer = 2;
        } else {
            Knife_Comm_WirelessManager_internalReset(self);
        }
        break;
    case 3:
        w->state = 2;
        w->timer = 0;
        w->unk_1cdc = 0;
        break;
    }
}

// update_reset: once the timer reaches 9999, clears the 15 child entries (stride 0x28 from +0x1a04) and returns to the
// off state (state 2, timer 0, flag 0).
extern "C" void Knife_Comm_WirelessManager_update_reset(void *self);
void Knife_Comm_WirelessManager_update_reset(void *self) {
    WmDWork *w = (WmDWork *)self;
    s32 i;
    u8 *child;

    if (w->timer != 9999) {
        return;
    }
    child = (u8 *)self + 0x204;
    child = child + 0x1800;
    for (i = 0; i < 15; i++) {
        Knife_Comm_ChildInfo_cleanup(child + i * 0x28);
    }
    w->state = 2;
    w->timer = 0;
    w->unk_1cdc = 0;
}
