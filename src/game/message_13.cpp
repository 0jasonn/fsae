#include "engine/functions.h"
#include "global.h"
#include "ui/message.h"

// Sets the message status: window phase of the message box and the status byte of the message request block
void statusUpdate(MSG_STATUS mode) {
    messageBox.windowPhase = mode;
    messageRequest[0] = messageBox.windowPhase;
}
