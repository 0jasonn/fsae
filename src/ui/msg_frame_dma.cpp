#include "engine/functions.h"
#include "global.h"
#include "ui/message.h"

// Knife_msgFrameDma (0x0204b1b4): uploads the message window frame graphics for the given bank to VRAM. While the
// window is closing (openMode 2) it uploads the narrow frame (0x1ba, 0x1bb) instead of the full one (0x1b6). The
// request byte (bank | 0x80) is remembered in unk_e6 so that an unchanged bank is not uploaded again.
void Knife_msgFrameDma(KNIFE_MSGSYS *msg, u32 bank) {
    u32 request = bank | 0x80;
    if (msg->unk_e6 == request) {
        return;
    }
    msg->unk_e6 = request;
    if (msg->openMode != 2) {
        u8 *frame = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1b6) + bank * 0x100;
        func_020845b0(0x06015100, frame, 0x100);
    } else {
        u8 *frame = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1ba);
        func_020845b0(0x06014b60, frame, 0x60);
        func_020845b0(0x06014b60 - 0x80, KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1bb) + bank * 0x80, 0x80);
    }
}
