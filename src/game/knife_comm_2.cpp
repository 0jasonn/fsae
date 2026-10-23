#include "engine/functions.h"
#include "global.h"
#include "game/change_buffer.h"

// Wireless player number, 0x02082f3c: GetMyPlayerNo returns this machine's player number in a wireless session, or 0xff.

extern u8 data_0212ca20[]; // group info block, the member table is at +0x30

// GetMyPlayerNo (0x02082f3c)
ARM s32 GetMyPlayerNo(void) {
    void *manager;
    s32 state;
    u8 *groupInfo;

    manager = func_020909c8();
    state = Knife_Comm_WirelessManager_getState(manager);
    groupInfo = data_0212ca20;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        if (state == 8 || state == 0xb) {
            return Knife_Comm_GetPlayerNoByAID(Knife_Comm_WirelessManager_getAID(manager), groupInfo + 0x30);
        }
    }
    return 0xff;
}
