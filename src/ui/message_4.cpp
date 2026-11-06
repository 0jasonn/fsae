#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/message.h"

// Functions in this file (original names from the debug build):
//   Message, State_ClearFlagE3

// Per-frame message update: starts a new box, runs the state tables and draws the windows
void Message(void) {
    u8 mode;
    u32 i;

    if (telopRequest.active == 1) {
        telopRequest.active = 0;
        telopBox.state = 1;
    }

    mode = messageRequest[0];
    switch (mode) {
    case 1:
        messageBox.lineChangeReq = 0;
        messageBox.state = 1;
        data_0216efbc[0] = (data_0216efbc[0] + 1) | 0x80;
        break;
    case 0x87:
        if (messageBox.windowPhase <= 1) {
            messageBox.state = 5;
        } else if (messageBox.windowPhase <= 6) {
            messageBox.state = 4;
        }
        break;
    }

    do {
        i = telopBox.state;
    } while (telopStates[i]() != 0);

    if (messageBox.waitTimer != 0) {
        messageBox.waitTimer--;
    } else if (messageBox.lineChangeReq != 0) {
        messageBox.lineChangeReq = 0;
        knife_msgLineChange(&messageBox, 2);
    } else {
        do {
            i = messageBox.state;
        } while (messageStates[i]() != 0);
    }

    deleteWindow();
    telopWindow();
    createWindow();
}

// Last state of the message box loop: clears its state flag and finishes
int State_ClearFlagE3(void) {
    messageBox.windowMode = 0;
    return 0;
}
