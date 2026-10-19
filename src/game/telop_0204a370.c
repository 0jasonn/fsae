#include "global.h"
#include "types.h"
#include "game/message.h"

// Functions in this file (original names from the debug build):
//   tlpInit

// Telop box initialization: clears the work blocks and sets up the telop window; returns 0 (the telop states run next)
ARM int tlpInit(void) {
    MsgWork *telop = &data_0217d484;
    u32 idMask = 0x7fff;
    u8 initMode = 2;
    u32 flags;

    func_02029a50(data_0216f000, 0x10);
    func_02029a50(telop, 0xe8);
    MIi_CpuCopy32(&data_0217d36c, data_0217d490, 0x18);
    telop->layoutFlags = (telop->layoutFlags & ~0xf) | 1;
    telop->msgId &= idMask;
    Knife_MsgReadPtrFromID(data_0217d4a8, telop->msgId);
    MIi_CpuClearFast(idMask - 0x8000, (u8 *)&data_021371a0 + 0x1080, 0x500);
    Stub_IgnoreArg(initMode);
    SoundReq(0x79);
    telop->drawFlags = (telop->drawFlags & ~0x1f) | 0x18;
    telop->unk_2a = 0xa0;
    telop->unk_25 = initMode;
    telop->state = initMode;
    Knife_msgFrameDma(telop, ((u32)telop->layoutFlags << 26) >> 30);
    telop->uiPtrA = (u8 *)KnifeApp_getInstance() + 0x144;
    telop->uiPtrB = (u8 *)KnifeApp_getInstance() + 0x180;
    Knife_palletChange(telop, 0x71);
    flags = *(u32 *)(data_0216efbc + 8);
    if ((flags & 1) == 0) {
        *(u8 **)(data_0216efbc + 0x18) = data_0211ed80;
        *(u32 *)(data_0216efbc + 0x1c) = 0;
        *(u32 *)(data_0216efbc + 0x20) = 0;
        *(u32 *)(data_0216efbc + 8) = flags | 1;
    }
    telop->unk_08 = data_0216efd4;
    *(MsgWork **)(data_0216efd4 + 4) = telop;
    return 0;
}
