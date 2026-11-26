#include "engine/functions.h"
#include "ui/message.h"
#include "ui/message.h"

// msgInit() (0x0204a258): message box initialization: clears the work blocks, copies the request into the box, sets up
// the window and returns 1 (the message states run next).
int msgInit(void) {
    KNIFE_MSGSYS *msg = &messageBox;
    u32 guardFlags;
    s32 one;

    MemClearFast(data_0216efe0, 0x10);
    MemClearFast(data_0217d358, 0x14);
    MemClearFast(msg, 0xe8);
    MIi_CpuCopy32(&messageRequest, &msg->windowPhase, 0x18);
    msg->layoutFlags = (msg->layoutFlags & ~0xf) | 1;
    Knife_MsgReadPtrFromID(&msg->datRead, msg->msgId);
    one = 1;
    data_0216efbc[0x24] = data_0216efbc[0x2c] = data_0216efbc[0];
    msg->openMode = one;
    msg->state = 2;
    Knife_msgFrameDma(msg, msg->frameBank);
    statusUpdate((MSG_STATUS)one);
    msg->renderer = (struct MsgRendererView *)((u8 *)KnifeApp_getInstance() + 0x108);
    msg->tokenizer = (Knife::Message::TextTokenizer *)((u8 *)KnifeApp_getInstance() + 0x44);
    Knife_palletChange(msg, 0x71);
    guardFlags = *(u32 *)(data_0216efbc + 4);
    if ((guardFlags & 1) == 0) {
        *(u8 **)(data_0216efbc + 0xc) = data_0211ed80;
        *(u32 *)(data_0216efbc + 0x10) = 0;
        *(u32 *)(data_0216efbc + 0x14) = 0;
        *(u32 *)(data_0216efbc + 4) = guardFlags | 1;
    }
    msg->appInfo = data_0216efc8;
    *(KNIFE_MSGSYS **)(data_0216efc8 + 4) = msg;
    return one;
}
