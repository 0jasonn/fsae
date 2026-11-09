#include "engine/functions.h"
#include "global.h"
#include "ui/message.h"
#include "game/message_a.h"

// Functions in this file (original names from the debug build): tlpMove, msgMove

// Telop box move state: runs the current move on the telop box, then updates the telop window
int tlpMove(void) {
    ((MsgMoveFunc)msgMoveTable[telopBox.subState])(&telopBox);
    telopUpdate(0);
    return 0;
}

// Message box move state: opens the move window, runs the current move on the message box, then sizes the window
int msgMove(void) {
    statusUpdate((MSG_STATUS)3);
    messageBox.windowMode = 2;
    ((MsgMoveFunc)msgMoveTable[messageBox.subState])(&messageBox);
    msgWinSizeChange(0);
    return 0;
}
