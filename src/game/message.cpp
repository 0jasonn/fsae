#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   Callback_Empty0 -> Callback_Empty0
//   Callback_Empty1 -> Callback_Empty1
//   Callback_Empty2 -> Callback_Empty2
//   Callback_Empty3 -> Callback_Empty3
//   Status_ArmIfEnabled -> Status_ArmIfEnabled
//   TelopClose -> TelopClose
//   MessageRequest -> MessageRequest

// Work blocks in the bss, accessed by byte offset
extern u8 telopRequest[];
extern u8 messageRequest[];
extern u8 telopBox[];
extern const u8 messageInitData[];


ARM void Callback_Empty0(void) {
}

ARM void Callback_Empty1(void) {
}

ARM void Callback_Empty2(void) {
}

ARM void Callback_Empty3(void) {
}

ARM void Status_ArmIfEnabled(void) {
    u8 value = messageRequest[0] & 0x7f;
    if (value != 0) {
        messageRequest[0] = 0x87;
    }
}

ARM void TelopClose(void) {
    u16 flags = *(u16 *)(telopRequest + 6);
    if (flags & 0x8000) {
        *(u16 *)(telopRequest + 6) = flags & 0x7fff;
    }
    telopBox[0xe7] = 1;
}

ARM void MessageRequest(u16 value) {
    MIi_CpuCopy32(messageInitData, messageRequest, 0x18);
    *(u16 *)(messageRequest + 6) = value;
}
