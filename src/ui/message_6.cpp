#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/message.h"
#include "engine/entity.h"

// Functions in this file (original names from the debug build):
//   tlpInit

// Telop box initialization: clears the work blocks and sets up the telop window; returns 0 (the telop states run next)
int tlpInit(void) {
    KNIFE_MSGSYS *telop = &telopBox;
    u32 idMask = 0x7fff;
    u8 initMode = 2;
    u32 flags;

    MemClearFast(telopWindowSlots, 0x10);
    MemClearFast(telop, 0xe8);
    MIi_CpuCopy32(&telopRequest, &telopBox.windowPhase, sizeof(TelopWork));
    telop->layoutFlags = (telop->layoutFlags & ~0xf) | 1;
    telop->msgId &= idMask;
    Knife_MsgReadPtrFromID(&telopBox.datRead, telop->msgId);
    MIi_CpuClearFast(idMask - 0x8000, (u8 *)&data_021371a0 + 0x1080, 0x500);
    Stub_IgnoreArg(initMode);
    SoundReq(0x79);
    telop->drawFlags = (telop->drawFlags & ~0x1f) | 0x18;
    telop->unk_2a = 0xa0;
    telop->openMode = initMode;
    telop->state = initMode;
    Knife_msgFrameDma(telop, ((u32)telop->layoutFlags << 26) >> 30);
    telop->renderer = (struct MsgRendererView *)((u8 *)KnifeApp_getInstance() + 0x144);
    telop->tokenizer = (Knife::Message::TextTokenizer *)((u8 *)KnifeApp_getInstance() + 0x180);
    Knife_palletChange(telop, 0x71);
    flags = *(u32 *)(data_0216efbc + 8);
    if ((flags & 1) == 0) {
        *(u8 **)(data_0216efbc + 0x18) = data_0211ed80;
        *(u32 *)(data_0216efbc + 0x1c) = 0;
        *(u32 *)(data_0216efbc + 0x20) = 0;
        *(u32 *)(data_0216efbc + 8) = flags | 1;
    }
    telop->appInfo = data_0216efd4;
    *(KNIFE_MSGSYS **)(data_0216efd4 + 4) = telop;
    return 0;
}

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   msgOpen -> msgOpen
//   tlpOpen -> tlpOpen
//   msgClose -> msgClose
//   tlpClose -> tlpClose

// Scene state handlers: a table entry returns 0 when the state is done
int msgOpen(void) {
    if (messageBox.windowMode != 1) {
        messageBox.windowMode = 1;
        SoundReq(0x43);
    }
    statusUpdate((MSG_STATUS)2);
    if (msgWinSizeChange(1) != 0) {
        messageBox.state = 3;
    }
    return 0;
}

int tlpOpen(void) {
    if (telopUpdate(-1) != 0) {
        telopBox.state = 3;
    }
    return 0;
}

int msgClose(void) {
    if (messageBox.windowMode != 3) {
        messageBox.windowMode = 3;
        messageBox.lineQueue[3] = 0;
        messageBox.lineQueue[2] = 0;
        messageBox.lineQueue[1] = 0;
        messageBox.lineQueue[0] = 0;
        SoundReq(0x44);
    }
    statusUpdate((MSG_STATUS)7);
    if (msgWinSizeChange(-1) != 0) {
        messageBox.state = 5;
    }
    return 0;
}

int tlpClose(void) {
    if (telopUpdate(1) != 0) {
        telopBox.state = 5;
    }
    return 0;
}

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

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   Stub_ReturnZero2 -> Stub_ReturnZero2

int Stub_ReturnZero2(void) {
    return 0;
}
