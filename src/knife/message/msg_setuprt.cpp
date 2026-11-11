#include "engine/functions.h"
#include "knife/message/setuprt.h"

// Knife::Message::SetupTextRenderer (0x020a2b14): resets the text renderer, sets up the pictogram OAM buffers, screen buffers and
// scene arguments from the scene info, then allocates and initialises one render target per entry. Returns 0 on failure.
namespace Knife {
namespace Message {

s32 SetupTextRenderer(const TextRenderSceneInfo *info, Language language, IExTextGetter *getter) {
    PictOamPair oam = data_02124974;
    s32 targetIndex;
    s32 bufferIndex;
    s32 argIndex;

    Knife_Message_CleanupTextRenderer();
    if (!data_0217d594.initialize(info->poolSize)) {
        return 0;
    }
    data_0217d56c.getter = getter;
    data_0217d650.assignOam(oam.main + info->pictMainFirst, info->pictMainCount);
    data_0217d650.setCharInfo(&info->pictMain);
    data_0217d650.clearAllPictogram();
    data_0217d858.assignOam(oam.sub + info->pictSubFirst, info->pictSubCount);
    data_0217d858.setCharInfo(&info->pictSub);
    data_0217d858.clearAllPictogram();
    Knife_Message_TextRenderer_setField64(&data_0217d594, &data_0217d650);
    Knife_Message_TextRenderer_setField68(&data_0217d594, &data_0217d858);
    for (bufferIndex = 0; bufferIndex < 4; bufferIndex++) {
        data_0217d594.setScreenBuffer(info->bgBuffers[bufferIndex], true, bufferIndex);
        data_0217d594.setScreenBuffer(info->objBuffers[bufferIndex], false, bufferIndex);
    }
    for (argIndex = 0; argIndex < 4; argIndex++) {
        data_0217d594.sceneArgs[argIndex] = info->rendererArgs[argIndex];
    }
    data_0217d594.unk_98 = info->renderer98;
    data_0217d594.unk_9c = info->renderer9c;
    data_0217d56c.count = info->targetCount;
    data_0217d56c.targets = (u8 *)func_0208e148(info->targetCount * 0x68);
    if (data_0217d56c.targets == NULL) {
        OS_Terminate();
        Knife_Message_CleanupTextRenderer();
        return 0;
    }
    for (targetIndex = 0; targetIndex < data_0217d56c.count; targetIndex++) {
        RenderTarget *target = (RenderTarget *)(data_0217d56c.targets + targetIndex * 0x68);
        if (target != NULL) {
            Knife_Message_PictogramRenderer_PictogramRenderer(target);
        }
        if (!i_InitRenderTarget(targetIndex, (RenderTarget *)(data_0217d56c.targets + targetIndex * 0x68), info, language)) {
            Knife_Message_CleanupTextRenderer();
            return 0;
        }
    }
    data_02124970 = info;
    data_0217d56c.language = language;
    return 1;
}

}
}
