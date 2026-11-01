#ifndef WIP_B_KNIFE_MSGSYS_H
#define WIP_B_KNIFE_MSGSYS_H

#include "types.h"
#include "game/knife_canvas.h"
#include "game/knife_message.h"
#include "game/message.h"

// Only the member the message box calls (tokenize, original Knife::Message::TextTokenizer::tokenize). The class is
// declared here, not with engine/text_tokenizer.h, which defines its own copies of Language and Voice.
namespace Knife {
namespace Message {
class IAppInfoGetter;
class TextTokenizer {
public:
    BOOL tokenize(u32 textId, Language language, const IAppInfoGetter *appInfo);
};
}
}

// Types the knife_commDisp* group reaches through the message box (Knife::Message::KNIFE_MSGSYS).

// Canvas callbacks reached through the text renderer at +0x20 (the callee gets the canvas and a value; name guessed)
typedef struct MsgCanvasOps {
    u8 unk_00[4];
    void (*clear)(NNSG2dCharCanvas *canvas, u32 value); // 0x04
} MsgCanvasOps;

// Text renderer as the message box reads it (Knife::Message::MessageTextRender, see game/knife_message.h)
typedef struct MsgRendererView {
    u8 unk_00[0x0c];
    NNSG2dCharCanvas canvas; // 0x0c
    u8 unk_1c[0x20 - 0x1c];
    MsgCanvasOps *canvasOps; // 0x20
} MsgRendererView;

// KNIFE_MSGSYS itself is defined in game/message.h.

#endif
