#include "engine/functions.h"
#include "knife/comm/multisio.h"
#include "global.h"

// MultiSioInit() (0x0204ed00): sets up the timer 3 control shadow, clears the link work and points its five buffer
// pointers at the buffers inside it, then resets the wireless manager if it is in state 14 or 15.
// The read-modify-writes go through a volatile view of multiSioRegs.timerCtrl (the ROM's separate multiSioCtrl word).
void MultiSioInit(void) {
    void *manager = func_020909c8();
    multiSioRegs.unk_1e = 0;
    multiSioRegs.timerCtrl = 0x2000;
    *(vu16 *)&multiSioRegs.timerCtrl |= 3 | 0x4000;
    *(vu16 *)&multiSioRegs.timerCtrl |= 8;
    OSi_CpuClear32(0, &multiSioWork, 0x1b8);
    multiSioWork.unk_14 = 0xd;
    multiSioWork.unk_18 = 0xd;
    multiSioWork.bufA = multiSioWork.subA;
    multiSioWork.bufB = multiSioWork.subB;
    multiSioWork.bufC = multiSioWork.subC;
    multiSioWork.bufD = multiSioWork.subD;
    multiSioWork.bufE = multiSioWork.subE;
    if ((u32)(Knife_Comm_WirelessManager_getState(manager) - 0xe) <= 1) {
        Knife_Comm_WirelessManager_reset(manager);
    }
}
