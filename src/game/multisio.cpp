#include "engine/functions.h"
#include "global.h"
#include "game/multisio.h"

// Wireless link (MultiSio) functions: MultiSioStart and MultiSioStop. MultiSioInit and MultiSioMain are parked in scratch/agentC/nonmatching.

// MultiSioStart (0x0204edc4)
ARM void MultiSioStart(void) {
    void *manager;

    manager = func_020909c8();
    if (multiSioWork.started != 0) {
        multiSioWork.linkFlag = 1;
    }
    if ((u32)(Knife_Comm_WirelessManager_getState(manager) - 14) <= 1) {
        Knife_Comm_WirelessManager_reset(manager);
    }
}

// MultiSioStop (0x0204ee08)
ARM void MultiSioStop(void) {
    void *manager;

    manager = func_020909c8();
    multiSioRegs.timerCtrl = 0x2003;
    REG_TM3CNT = 0x6e8b;
    multiSioWork.linkFlag = 0;
    if (Knife_Comm_WirelessManager_getState(manager) >= 2) {
        Knife_Comm_WirelessManager_reset(manager);
    }
}
