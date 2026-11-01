#ifndef WIP_B_KNIFE_MSGSYS_H
#define WIP_B_KNIFE_MSGSYS_H

#include "types.h"
#include "game/knife_canvas.h"
#include "game/knife_message.h"

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

// Knife::Message::KNIFE_MSGSYS: the message box state used by the knife_commDisp* group (implementer B).
// Only the fields these functions touch are named; the offsets are the matched code's.

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

typedef struct KNIFE_MSGSYS {
    /* 00 */ MsgRendererView *renderer;
    /* 04 */ Knife::Message::TextTokenizer *tokenizer;
    /* 08 */ const void *appInfo;   // IAppInfoGetter passed to the tokenizer
    /* 0c */ u8 unk_0c[0x12 - 0x0c];
    /* 12 */ u16 msgId;             // text id of the message
    /* 14 */ u8 unk_14[0x25 - 0x14];
    /* 25 */ u8 openMode;           // 2 while the message box is closing
    /* 26 */ u8 unk_26[0x30 - 0x26];
    /* 30 */ s16 tokenIndex;
    /* 32 */ s16 tokenSub;
    /* 34 */ u8 cellRows[4][0x1e];  // attribute cells of four text rows, 30 bytes each; shifted up by the roll
    /* ac */ u8 lineQueue[4];       // line changes waiting to run (shifted by the roll)
    /* b0 */ u8 unk_b0[0xd1 - 0xb0];
    /* d1 */ u8 subState;           // index into the move table of the message box
    /* d2 */ u8 unk_d2[0xd6 - 0xd2];
    /* d6 */ u8 unk_d6;             // nonzero makes the wait state return early
    /* d7 */ u8 palletBits;         // palette bits passed to Knife_palletChange with 0x40
    /* d8 */ u8 unk_d8[0xdc - 0xd8];
    /* dc */ u8 stepTimer;          // frames left in the wait state
    /* dd */ u8 unk_dd;
    /* de */ s8 unk_de;
    /* df */ u8 unk_df;
    /* e0 */ u8 lineChangeReq;      // set when the line change has to run
    /* e1 */ u8 unk_e1[0xe7 - 0xe1];
    /* e7 */ u8 noTelopWait;        // nonzero: the wait does not depend on the telop request
} KNIFE_MSGSYS;

#endif
