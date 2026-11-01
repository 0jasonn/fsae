#include "engine/functions.h"
#include "game/message.h"
#include "global.h"
#include "types.h"
#include "enemy/knife_msgsys.h"

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispWait (0x0204b6f4)

extern u8 localPlayerIndex[];
extern u8 frameCounter[];
extern u16 data_0212c58c[];

// Waits for the message box to be allowed to move on. While the box is closing (openMode 2) it waits for the frame
// counter flag and the telop request; otherwise it waits for the player's flag in data_0212c58c. Both paths end by
// setting subState to 3 (the shared block at set_sub3 keeps the code layout of the original).
void knife_commDispWait(KNIFE_MSGSYS *msg) {
    u8 playerIndex;
    u8 state;
    u8 remaining;
    void *instance;

    if (msg->openMode != 2) {
        statusUpdate((MSG_STATUS)6);
        if (msg->unk_d6 != 0) {
            return;
        }
        instance = KnifeApp_getInstance();
        playerIndex = localPlayerIndex[0];
        if (KnifeApp_isWirelessMode(instance) == 0) {
            playerIndex = Knife_Single_SinglePlay_GetInstance()[0];
        }
        if ((data_0212c58c[playerIndex] & 1) != 0) {
            goto set_sub3;
        }
        return;
    }
    state = frameCounter[0x11];
    if ((state & 0x80) != 0 && (state & 3) == localPlayerIndex[0]) {
        return;
    }
    if (msg->noTelopWait == 0) {
        if ((telopRequest.requestId & 0x8000) != 0) {
            msg->stepTimer = 1;
            return;
        }
    } else {
        msg->stepTimer = 0;
    }
    remaining = msg->stepTimer;
    msg->stepTimer = remaining - 1;
    if (remaining != 0) {
        return;
    }
set_sub3:
    msg->subState = 3;
}
