#ifndef ACTOR_ENEMY_KNIFE_MSGSYS_H
#define ACTOR_ENEMY_KNIFE_MSGSYS_H

#include "types.h"
#include "knife/message/knife_canvas.h"
#include "knife/message/knife_message.h"
#include "ui/message.h"

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

typedef NNSG2dCharCanvasOps MsgCanvasOps;

// Text renderer as the message box reads it (Knife::Message::MessageTextRender, see game/knife_message.h)
typedef struct MsgRendererView {
    u8 unk_00[0x0c];
    union {
        NNSG2dCharCanvas canvas; // 0x0c
        // Same canvas fields in declaration order for direct access to canvasOps.
        struct {
            void *canvasBits;
            u32 canvasWidth;
            u32 canvasHeight;
            u8 canvasColorDepth;
            s32 canvasRowStride;
            const MsgCanvasOps *canvasOps; // 0x20
        };
    };
} MsgRendererView;

// KNIFE_MSGSYS itself is defined in game/message.h.

#endif
