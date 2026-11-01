#include "engine/functions.h"
#include "game/subtask_dialog.h"

extern u8 data_021806f0[]; // the game state block of the subtask
extern u8 data_021350b0[]; // table of 0x50-byte entries, selected by the byte at data_021806f0 + 0x53d

// subtask_dialogWaitSend (0x020abf5c): status 0 starts the request and waits until the status reaches 2; status 2
// sends the entry (0x34 bytes at +8); anything else returns 0
BOOL subtask_dialogWaitSend(void) {
    void *obj;
    s32 status;
    u8 index;
    u8 *entry;

    obj = func_020909c8();
    KnifeApp_getInstance();
    status = Knife_Comm_WirelessManager_getState(obj);
    if (status == 0) {
        Knife_Comm_WirelessManager_turnOn(obj, 0);
        while (status != 2) {
            OS_WaitVBlankIntr();
            Knife_Comm_WirelessManager_update(obj);
            status = Knife_Comm_WirelessManager_getState(obj);
        }
    }
    if (status == 2) {
        index = data_021806f0[0x53d];
        entry = data_021350b0 + index * 0x50;
        if (Knife_Comm_WirelessManager_startParent(obj, 4, 0x34, entry + 8, 0xe) != 0) {
            return 1;
        }
        SoundReq(0x40);
        return 0;
    }
    return 0;
}
