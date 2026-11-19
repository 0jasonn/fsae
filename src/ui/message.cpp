#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "ui/message.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   Callback_Empty0 -> Callback_Empty0
//   Callback_Empty1 -> Callback_Empty1
//   Callback_Empty2 -> Callback_Empty2
//   Callback_Empty3 -> Callback_Empty3
//   Status_ArmIfEnabled -> Status_ArmIfEnabled
//   TelopClose -> TelopClose
//   MessageRequest -> MessageRequest

extern const u8 messageInitData[];


void Callback_Empty0(void) {
}

void Callback_Empty1(void) {
}

void Callback_Empty2(void) {
}

void Callback_Empty3(void) {
}

void Status_ArmIfEnabled(void) {
    u8 value = messageRequest.phase & 0x7f;
    if (value != 0) {
        messageRequest.phase = 0x87;
    }
}

void TelopClose(void) {
    u16 flags = telopRequest.requestId;
    if (flags & 0x8000) {
        telopRequest.requestId = flags & 0x7fff;
    }
    telopBox.noTelopWait = 1;
}

void MessageRequest(u16 value) {
    MIi_CpuCopy32(messageInitData, &messageRequest, 0x18);
    messageRequest.msgId = value;
}
