#include "engine/functions.h"
#include "game/message.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   knife_commDispDie, knife_commDispLF

// Advances the message to its next state and clears the sub state; a finished message box (openMode 2) also clears unk_e7
ARM void knife_commDispDie(MsgWork *msg) {
    msg->state++;
    msg->subState = 0;
    if (msg->openMode == 2) {
        msg->unk_e7 = 0;
    }
}

// Fields of the message box that game/message.h does not name yet
typedef struct MsgLfFields {
    /* 00 */ u8 unk_00[0xdc];
    /* dc */ u8 timer; // frames until the line feed is finished
    /* dd */ u8 unk_dd[0xe4 - 0xdd];
    /* e4 */ u8 counter; // frames the arrow has been shown
} MsgLfFields;

#define MSG_LF(msg) ((MsgLfFields *)(msg))

extern u8 localPlayerIndex[];
extern u8 data_0212c5bc[];
extern u16 data_0212c58c[];

// Line feed of the message: waits for the timer and the key flags, then starts the next line
ARM void knife_commDispLF(MsgWork *msg) {
    u8 index;
    u8 state;
    void *instance;

    if (msg->openMode == 2) {
        state = data_0212c5bc[0x11];
        if ((state & 0x80) != 0 && (state & 3) == localPlayerIndex[0]) {
            return;
        }
    }
    if (MSG_LF(msg)->timer != 0) {
        MSG_LF(msg)->timer--;
        if (MSG_LF(msg)->timer != 0) {
            return;
        }
        msg->subState = 5;
        msg->unk_ac[2] = 0;
        msg->unk_ac[3] = 0;
        knife_msgLineChange(msg, 0);
        msg->subState = 1;
        return;
    }
    instance = KnifeApp_getInstance();
    index = localPlayerIndex[0];
    if (KnifeApp_isWirelessMode(instance) == 0) {
        index = Knife_Single_SinglePlay_GetInstance()[0];
    }
    if ((data_0212c58c[index] & 1) == 0) {
        MSG_LF(msg)->counter++;
        return;
    }
    SoundReq(0x42);
    MSG_LF(msg)->counter = 0;
    msg->subState = 5;
    msg->unk_ac[2] = 0;
    msg->unk_ac[3] = 0;
    knife_msgLineChange(msg, 0);
    msg->subState = 1;
    msg->unk_e7 = 0;
}
