#include "engine/functions.h"
#include "engine/blend_request.h"
#include "engine/player.h"
#include "game/pause_req.h"
#include "knife/comm/comerror_work.h"
#include "game/pause_req.h"

// pause_return_to_title() (0x020543ac): runs once the fade is over. In wireless play it first closes the session
// (turnOff, or waits while the manager is busy or in states 3, 0xd and 0xf) and marks the pause as closing the link;
// otherwise, or when the manager is idle (state 0), it clears the objects, messages and communication state and chains
// to the title (task 0xc) or, when the link was not being closed, reloads the game start (task 7).
void pause_return_to_title(void) {
    void *manager;
    s32 state;
    u8 one;

    if (blendRequest.blendEnabled != 0) {
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        manager = func_020909c8();
        state = Knife_Comm_WirelessManager_getState(manager);
        if (func_02090ecc(manager)) {
            return;
        }
        one = 1;
        pauseState.unk_0f = one;
        switch (state) {
        case 0:
            break;
        case 3:
        case 0xd:
        case 0xf:
            return;
        case 8:
            Knife_Comm_WirelessManager_turnOff(manager);
            data_0212c4d4 = one;
            return;
        case 0xb:
            data_0212c4d4 = one;
            return;
        default:
            Knife_Comm_WirelessManager_turnOff(manager);
            data_0212c4d4 = 1;
            return;
        }
    }
    if (gameState.unk_01 == 5) {
        UnlockTokiWave();
    }
    ObjWorkPoolClear();
    ObjMoveInit();
    MessageInitialize();
    TelopInitialize();
    ComInitState();
    data_0212c4d4 = 0;
    if (pauseState.unk_0f == 0) {
        Task_Chain(7);
        subTask_game_start_reload();
        func_020827a8(3);
        data_0212c4dc = 1;
    } else {
        Task_Chain(0xc);
    }
}
