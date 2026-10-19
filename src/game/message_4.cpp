#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/message.h"

// Functions in this file (original names from the debug build):
//   Message, State_ClearFlagE3

// Per-frame message update: starts a new box, runs the state tables and draws the windows
ARM void Message(void) {
    u8 mode;
    u32 i;

    if (telopRequest.active == 1) {
        telopRequest.active = 0;
        telopBox.state = 1;
    }

    mode = messageRequest[0];
    switch (mode) {
    case 1:
        data_0217d39c.lineChangeReq = 0;
        data_0217d39c.state = 1;
        data_0216efbc[0] = (data_0216efbc[0] + 1) | 0x80;
        break;
    case 0x87:
        if (data_0217d39c.windowPhase <= 1) {
            data_0217d39c.state = 5;
        } else if (data_0217d39c.windowPhase <= 6) {
            data_0217d39c.state = 4;
        }
        break;
    }

    do {
        i = telopBox.state;
    } while (telopStates[i]() != 0);

    if (data_0217d39c.waitTimer != 0) {
        data_0217d39c.waitTimer--;
    } else if (data_0217d39c.lineChangeReq != 0) {
        data_0217d39c.lineChangeReq = 0;
        knife_msgLineChange(&data_0217d39c, 2);
    } else {
        do {
            i = data_0217d39c.state;
        } while (messageStates[i]() != 0);
    }

    deleteWindow();
    telopWindow();
    createWindow();
}

// Last state of the message box loop: clears its state flag and finishes
ARM int State_ClearFlagE3(void) {
    data_0217d39c.windowMode = 0;
    return 0;
}
