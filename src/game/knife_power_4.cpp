#include "engine/functions.h"
#include "global.h"
#include "game/knife_power.h"
#include "game/decls_g.h"

// Functions in this file (original names from the debug build):
//   Knife::PowerManager::update (0x020c81a0)

namespace Knife {

// File-local view of the bytes of PowerManager from 0x0c on (the class names only the first ones)
typedef struct PowerManagerView {
    /* 00 */ u8 unk_00[0x0c];
    /* 0c */ u8 lcdOnRequested; // set by finalize; selects the LCD-on branch at the end of update
    /* 0d */ u8 lcdWasOn; // whether the LCD was on when the lid was closed
    /* 0e */ u8 lidClosed; // lid state read from bit 15 of the register at 0x02ffffa8 on the last update
    /* 0f */ u8 lidJustClosed; // the lid closed in this update
    /* 10 */ u8 lidJustOpened; // the lid opened in this update
} PowerManagerView;

// Knife::PowerManager::update() (0x020c81a0): follows the lid state and switches the LCD power and the
// wireless state when it changes
ARM void PowerManager::update(void) {
    PowerManagerView *view;
    u8 lidClosed;
    s32 ret;

    if (!isActive()) {
        return;
    }
    view = (PowerManagerView *)this;
    lidClosed = (((s32)(*(volatile u16 *)0x02ffffa8 & 0x8000)) >> 15) != 0;
    view->lidJustClosed = view->lidClosed == 0 && lidClosed;
    view->lidJustOpened = view->lidClosed != 0 && lidClosed == 0;
    view->lidClosed = lidClosed;
    if (view->lidJustClosed != 0) {
        m4aSoundResume();
        if (PM_GetLCDPower() == 1) {
            view->lcdWasOn = func_02012e58() != 0;
            PM_SetLCDPower(0);
        }
    }
    if (view->lidClosed != 0) {
        ret = Knife_Comm_WirelessManager_getState(func_020909c8());
        if (sleepLockCount == 0 && ret == 0) {
            func_0201d038(0xc, 0x8000, 0);
        }
    }
    if (view->lidJustOpened != 0) {
        m4aSoundResume();
    }
    if (view->lidClosed != 0) {
        return;
    }
    if (view->lcdOnRequested != 0) {
        if (PM_GetLCDPower() != 0) {
            return;
        }
        ret = PM_SetLCDPower(1);
        if (ret != 0 && view->lcdWasOn != 0) {
            GX_DispOn();
            *(u32 *)0x04001000 |= 0x10000;
        }
    } else {
        if (PM_GetLCDPower() != 1) {
            return;
        }
        view->lcdWasOn = func_02012e58() != 0;
        PM_SetLCDPower(0);
    }
}

}
