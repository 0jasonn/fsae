#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/message.h"

// Functions in this file (original names from the debug build):
//   msgDie, tlpDie

// Message box shutdown: starts the close animation and resets the state
int msgDie(void) {
    statusUpdate((MSG_STATUS)0);
    messageBox.windowMode = 4;
    messageBox.state = 0;
    return 0;
}

// Telop box shutdown: stops the telop window and releases the request
int tlpDie(void) {
    telopUpdate(0);
    telopBox.state = 0;
    telopRequest.active = 0;
    telopBox.windowPhase = 0;
    return 0;
}
