#include "engine/functions.h"
#include "global.h"
#include "knife/comm/comerror_work.h"

// CommErrorCheck (0x02029968): returns 0 and ends the communication when the players keep reporting different states
// (more than 0x3c frames in a row) or a connection bit is lost; 1 while everything is fine.
int CommErrorCheck(u32 expectedStatus) {
    void *manager = func_020909c8();
    void *app = KnifeApp_getInstance();
    s32 state;
    u32 timer;

    if (COM_WORK->holdFlag != 0) {
        return 1;
    }
    if (data_0212c4d4 != 0) {
        return 1;
    }
    if (KnifeApp_isWirelessMode(app) == 0) {
        return 1;
    }
    state = Knife_Comm_WirelessManager_getState(manager);
    if (state != 8 && state != 0xb) {
        func_0202809c();
        Task_Chain(8);
        return 0;
    }
    if (comerror_error_check(expectedStatus) != 0) {
        timer = 0;
    } else {
        timer = COM_WORK->errorTimer + 1;
    }
    COM_WORK->errorTimer = timer;
    if ((opTitleState & 0x3000) != 0 || COM_WORK->errorTimer > 0x3c) {
        func_0202809c();
        Task_Chain(8);
        return 0;
    }
    return 1;
}
