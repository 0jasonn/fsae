#include "engine/functions.h"
#include "ui/message.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   knife_commDispDie, knife_commDispLF

// Advances the message to its next state and clears the sub state; a finished message box (openMode 2) also clears unk_e7
void knife_commDispDie(KNIFE_MSGSYS *msg) {
    msg->state++;
    msg->subState = 0;
    if (msg->openMode == 2) {
        msg->noTelopWait = 0;
    }
}

extern u8 localPlayerIndex[];
extern u8 frameCounter[];
extern u16 playerKeys[];

// Line feed of the message: waits for the timer and the key flags, then starts the next line
void knife_commDispLF(KNIFE_MSGSYS *msg) {
    u8 index;
    u8 state;
    void *instance;

    if (msg->openMode == 2) {
        state = frameCounter[0x11];
        if ((state & 0x80) != 0 && (state & 3) == localPlayerIndex[0]) {
            return;
        }
    }
    if (msg->stepTimer != 0) {
        msg->stepTimer--;
        if (msg->stepTimer != 0) {
            return;
        }
        msg->subState = 5;
        msg->lineQueue[2] = 0;
        msg->lineQueue[3] = 0;
        knife_msgLineChange(msg, 0);
        msg->subState = 1;
        return;
    }
    instance = KnifeApp_getInstance();
    index = localPlayerIndex[0];
    if (KnifeApp_isWirelessMode(instance) == 0) {
        index = Knife_Single_SinglePlay_GetInstance()[0];
    }
    if ((playerKeys[index] & 1) == 0) {
        msg->cursorState++;
        return;
    }
    SoundReq(0x42);
    msg->cursorState = 0;
    msg->subState = 5;
    msg->lineQueue[2] = 0;
    msg->lineQueue[3] = 0;
    knife_msgLineChange(msg, 0);
    msg->subState = 1;
    msg->noTelopWait = 0;
}
