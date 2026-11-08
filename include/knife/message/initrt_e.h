#ifndef WIP_E_INITRT_E_H
#define WIP_E_INITRT_E_H

#include "knife/message/rtinfo_e.h"

namespace Knife {
namespace Message {

class TextRenderer {
public:
    s32 renderText(const RenderTarget *target, u32 textId, Language language);
    s32 renderText(const RenderTarget *target, const Text *text);
};

s32 i_InitRenderTarget(int index, RenderTarget *target, const TextRenderSceneInfo *info, Language language);

}
}

extern "C" {
void Knife_Message_TextRenderer_setField50_54(Knife::Message::RenderTarget *self, s32 a, s32 b);
void Knife_Message_TextRenderer_setField58(Knife::Message::RenderTarget *self, s32 value);
s32 Knife_Message_i_IsExText(u32 textId);
}

extern ExTextState data_0217d56c;
extern Knife::Message::TextRenderer data_0217d594;

#endif
