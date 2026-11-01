#include "engine/wm_d.h"
#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_callbacks_api.h"

// Knife::Comm::WirelessManager state update functions (plain names, self is the manager). The state machine is kept in
// WmDWork: state (0x1cc4), timer (0x1cd8, the step inside a state) and the controller flag (0x1cdc).

extern char data_0211b1a8[];
extern char data_0211b1b4[];
extern char data_0211b1c0[];

extern "C" u32 WM_PowerOff(void *callback);
extern "C" void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
extern "C" BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
extern "C" void Knife_Comm_ChildInfo_cleanup(void *child);

// update_scan2idle: the scan step (timer 1) returns to idle with state 2 and clears the flag.
extern "C" void Knife_Comm_WirelessManager_update_scan2idle(void *self);
void Knife_Comm_WirelessManager_update_scan2idle(void *self) {
    WmDWork *w = (WmDWork *)self;

    if (w->timer != 0) {
        if (w->timer == 1) {
            w->state = 2;
            w->timer = 0;
            w->unk_1cdc = 0;
        }
    }
}
