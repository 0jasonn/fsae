#ifndef WIP_E_KNIFE_MESSAGE_H
#define WIP_E_KNIFE_MESSAGE_H

#include "engine/functions.h"
#include "game/knife_canvas.h"

namespace Knife {
namespace Message {

// Voice of a speech tag (values not known yet)
typedef enum Voice { VOICE_0, VOICE_1, VOICE_2, VOICE_3 } Voice;

// Language of the message text (values not known yet; the game-over character table is indexed by 5 to 7)
typedef enum Language { LANGUAGE_0, LANGUAGE_1, LANGUAGE_2, LANGUAGE_3, LANGUAGE_4, LANGUAGE_5, LANGUAGE_6, LANGUAGE_7 } Language;

// Scene block pointed to by MessageTextRender::sceneInfo (+0x38). Only the bytes the tag handlers use are named.
typedef struct MessageSceneInfo {
    u8 unk_00[0x0d];
    u8 voice;      // 0x0d: voice set by the speech tag
    u8 unk_0e[0xd6 - 0x0e];
    u8 waitFlag;   // 0xd6: set by the wait tag when the value is 0xff
    u8 unk_d7;
    u8 colorReset; // 0xd8: cleared by the colour tag
    u8 unk_d9[3];
    u8 field_dc;   // 0xdc
    u8 waitCount;  // 0xdd: value of the wait tag
} MessageSceneInfo;

// Text renderer of the message window (Knife::Message::MessageTextRender). Only the fields the
// functions matched so far use are named; the rest is kept as bytes.
class MessageTextRender {
public:
    void clearCanvasLine(s32 line, s32 lines, s32 color);
    void setField34(u8 value);
    void setField35(u8 value);
    void clearField36(void);
    u8 getField36(void) const;
    void setSceneInfo(void *info);
    void setOffset(s16 x, s16 y);
    void setSceneField_dc(u8 value);
    void onReadWaitTag(int value);
    void onReadBlankTag(int value);
    void onReadSelectTag(void);
    void onReadTextSETag(Voice voice);

    u8 unk_00[0x04];
    s16 offsetX;   // 0x04
    s16 offsetY;   // 0x06
    u8 unk_08[0x04];
    NNSG2dCharCanvas canvas; // 0x0c: the text canvas (pBits, width and height in cells, colour depth)
    u8 unk_1c[0x34 - 0x1c];
    u8 field34;
    u8 field35;
    u8 field36;
    u8 unk_37;
    MessageSceneInfo *sceneInfo; // 0x38
};

}
}

#endif
