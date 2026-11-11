#ifndef WIP_E_SETUPRT_E_H
#define WIP_E_SETUPRT_E_H

#include "knife/message/rtinfo.h"

namespace Knife {
namespace Message {

// Text renderer (see knife/message/textrender.h for the full layout): the fields set by SetupTextRenderer
class TextRenderer {
public:
    BOOL initialize(u32 poolSize);
    void setScreenBuffer(void *buffer, bool isObj, s32 index);

    u8 unk_00[0x50];
    s32 sceneArgs[4];  // 0x50
    u8 unk_60[0x98 - 0x60];
    s32 unk_98;
    s32 unk_9c;
};

s32 i_InitRenderTarget(int index, RenderTarget *target, const TextRenderSceneInfo *info, Language language);
s32 SetupTextRenderer(const TextRenderSceneInfo *info, Language language, IExTextGetter *getter);

}
}

// The two OAM buffers of the pictogram renderers (main and sub), rodata pointers
typedef struct PictOamPair {
    GXOamAttr *main;
    GXOamAttr *sub;
} PictOamPair;
extern const PictOamPair data_02124974;
extern const Knife::Message::TextRenderSceneInfo *data_02124970;

extern Knife::Message::TextRenderer data_0217d594;
extern Knife::Message::PictogramRenderer data_0217d650;
extern Knife::Message::PictogramRenderer data_0217d858;
extern ExTextState data_0217d56c;

void Knife_Message_CleanupTextRenderer(void); // C++ linkage

extern "C" {
void Knife_Message_TextRenderer_setField64(Knife::Message::TextRenderer *self, Knife::Message::PictogramRenderer *renderer);
void Knife_Message_TextRenderer_setField68(Knife::Message::TextRenderer *self, Knife::Message::PictogramRenderer *renderer);
void *Knife_Message_PictogramRenderer_PictogramRenderer(void *self);
void *func_0208e148(u32 size);
void OS_Terminate(void);
}

#endif
