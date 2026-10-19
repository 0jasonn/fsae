#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/message.h"

// Functions in this file (original names from the debug build):
//   msgDie, tlpDie

// Message box shutdown: starts the close animation and resets the state
ARM int msgDie(void) {
    statusUpdate((MSG_STATUS)0);
    data_0217d39c.windowMode = 4;
    data_0217d39c.state = 0;
    return 0;
}

// Telop box shutdown: stops the telop window and releases the request
ARM int tlpDie(void) {
    telopUpdate(0);
    data_0217d484.state = 0;
    data_0217d36c.active = 0;
    data_0217d484.windowPhase = 0;
    return 0;
}
