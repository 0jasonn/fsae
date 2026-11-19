#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "ui/message.h"
#include "types.h"
#include "engine/message_request.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   MessageInitialize -> MessageInitialize
//   TelopInitialize -> TelopInitialize

extern u8 data_0217d350[];

void MessageInitialize(void) {
    MemClearFast(&messageRequest, 0x18);
    MemClearFast(&messageBox, 0xe8);
    MemClearFast(data_0216efe0, 0x10);
    MemClearFast(data_0216eff0, 0x10);
    MemClearFast(data_0217d350, 4);
    data_0216efbc[0] = 0;
}

void TelopInitialize(void) {
    MemClearFast(&telopRequest, 0x18);
    MemClearFast(&telopBox, 0xe8);
    MemClearFast(telopWindowSlots, 0x10);
    MemClearFast(data_0216f010, 0x10);
    data_0216efbc[1] = 0;
}

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

    mode = messageRequest.phase;
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

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   Stub_ReturnZero -> Stub_ReturnZero

int Stub_ReturnZero(void) {
    return 0;
}
