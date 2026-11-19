#include "engine/functions.h"
#include "global.h"
#include "knife/comm/change_buffer.h"

// Wireless player number, 0x02082f3c: GetMyPlayerNo returns this machine's player number in a wireless session, or 0xff.

#include "engine/com_work.h"

// GetMyPlayerNo (0x02082f3c)
s32 GetMyPlayerNo(void) {
    void *manager;
    s32 state;
    ComPacket *group;

    manager = func_020909c8();
    state = Knife_Comm_WirelessManager_getState(manager);
    group = &comWork.recv[0];
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        if (state == 8 || state == 0xb) {
            return Knife_Comm_GetPlayerNoByAID(Knife_Comm_WirelessManager_getAID(manager), &group->groupWord);
        }
    }
    return 0xff;
}
