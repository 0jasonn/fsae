#include "engine/functions.h"
#include "game/knife_message.h"
#include "game/message.h"
#include "global.h"
#include "types.h"
#include "enemy/knife_msgsys.h"

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispInit (0x0204b2f0)

extern u8 pauseDialogBuffer[]; // pause dialog buffer
extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" s32 KnifeApp_getCurrentLanguage(void *app);
extern "C" void Knife_Message_MessageTextRender_initWithCanvas(void *self, void *a, void *b, u16 c, u32 d, u32 e, u32 f, u32 g);


// messageRequest byte 5: the width of the message in cells (5 bits)
typedef struct MsgRequestWidth {
    u8 unk_00[5];
    u8 width : 5;
} MsgRequestWidth;

// Initialises the message box: clears the pause dialog buffer, sets up the text renderer canvas (the normal box or the
// closing box, openMode 2), tokenizes the message and starts it at subState 1.
void knife_commDispInit(KNIFE_MSGSYS *msg) {
    WindowSlot *slot;
    u16 frameSize;
    u16 msgId;
    void *app;

    MI_CpuFill8(pauseDialogBuffer, 0, 0x800);
    slot = &data_0216efe0[data_0212c618[3]];
    if (msg->openMode != 2) {
        frameSize = (u16)(((MsgRequestWidth *)messageRequest)->width << 3);
        Knife_Message_MessageTextRender_initWithCanvas(msg->renderer, (void *)data_021371a0,
                                                       (void *)(pauseDialogBuffer + ((slot->tileY * 0x20 + 0x22) * 2)), 0x3090,
                                                       0, 0, frameSize, 0x20);
        ((Knife::Message::MessageTextRender *)msg->renderer)->setSceneInfo(msg);
        ((Knife::Message::MessageTextRender *)msg->renderer)->setField35(2);
        ((Knife::Message::MessageTextRender *)msg->renderer)->setField34(0x10);
        msg->renderer->canvasOps->clear(&msg->renderer->canvas, 0xf);
        knife_msgLineChange((MsgWork *)msg, 0);
        msgId = *(u16 *)(messageRequest + 6);
    } else {
        Knife_Message_MessageTextRender_initWithCanvas(msg->renderer, (void *)0x6014bc0, (void *)((u8 *)pauseDialogBuffer + 0x5c0), 0x305e,
                                                       0, 0, 0xa8, 0x10);
        ((Knife::Message::MessageTextRender *)msg->renderer)->setSceneInfo(msg);
        ((Knife::Message::MessageTextRender *)msg->renderer)->setField35(2);
        msg->renderer->canvasOps->clear(&msg->renderer->canvas, 0xf);
        Knife_palletChange((MsgWork *)msg, 0x71);
        msgId = msg->msgId;
    }
    app = KnifeApp_getInstance();
    msg->tokenizer->tokenize(msgId, (Knife::Message::Language)KnifeApp_getCurrentLanguage(app), (const Knife::Message::IAppInfoGetter *)msg->appInfo);
    msg->tokenIndex = 0;
    msg->tokenSub = 0;
    msg->subState = 1;
}
