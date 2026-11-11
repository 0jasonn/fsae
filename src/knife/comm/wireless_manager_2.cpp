#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/wireless_manager.h"
#include "knife/comm/wireless_manager_methods.h"

// Knife::Comm::WirelessManager, 0x02090ecc. func_02090ecc (C++ linkage as declared in functions.h): the flag at 0x1cdc.
// The unit starts here because getState (0x02090ea4) is parked in scratch/agentD/nonmatching.

s32 func_02090ecc(void *manager) {
    WirelessManagerWork *wm;

    wm = (WirelessManagerWork *)manager;
    return wm->unk_1cdc;
}

// Knife::Comm::WirelessManager::turnOn / turnOff / reset (0x02090ed8..0x020912a4). Each runs with
// interrupts disabled (WmInterruptSection), rejects an unexpected state, performs the SDK call through
// handleResult, and moves to the next state.

// Knife::Comm::WirelessManager::turnOn(bool) (0x02090ed8)
BOOL Knife_Comm_WirelessManager_turnOn(void *self, BOOL on) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;

    if (wm->state != 0) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    if (func_02019968() == 0) {
        return FALSE;
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, func_0201f838(Knife_Comm_WirelessManager_callback_WM_EnableStep), 0, data_0211b0dc)) {
        return FALSE;
    }
    wm->state = 1;
    wm->timer = 0;
    wm->unk_1cdc = 1;
    wm->connectPhase = 0;
    return TRUE;
}

// Knife::Comm::WirelessManager::turnOff() (0x02090ff4)
BOOL Knife_Comm_WirelessManager_turnOff(void *self) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;

    if (wm->state < 2) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    if (wm->state == 2) {
        if (!Knife_Comm_WirelessManager_handleResult(self, WM_PowerOff(Knife_Comm_WirelessManager_callback_WM_PowerOffStep), 0, data_0211b0e8)) {
            return FALSE;
        }
        wm->timer = 2;
    } else {
        if (wm->state == 8 || wm->state == 0xb) {
            WM_EndDataSharing((u8 *)self + 0x1e0);
        }
        if (!Knife_Comm_WirelessManager_handleResult(self, WM_Reset(Knife_Comm_WirelessManager_callback_WM_Reset), 0, data_0211b0f4)) {
            return FALSE;
        }
        wm->timer = 0;
    }
    wm->unk_1cdc = 1;
    wm->state = 3;
    wm->connectPhase = 0;
    return TRUE;
}

// Knife::Comm::WirelessManager::reset() (0x02091184)
BOOL Knife_Comm_WirelessManager_reset(void *self) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;

    if (wm->state < 2) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    if (wm->state == 8 || wm->state == 0xb) {
        WM_EndDataSharing((u8 *)self + 0x1e0);
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_Reset(Knife_Comm_WirelessManager_callback_WM_Reset), 0, data_0211b100)) {
        return FALSE;
    }
    wm->state = 0xd;
    wm->timer = 0;
    wm->unk_1cdc = 1;
    return TRUE;
}
