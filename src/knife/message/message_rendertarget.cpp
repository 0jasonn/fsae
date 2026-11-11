#include "engine/functions.h"
#include "knife/message/initrt.h"

namespace Knife {
namespace Message {

// i_InitRenderTarget(int, RenderTarget*, TextRenderSceneInfo const*, Language) (0x020a2f1c): sets up render target
// number index of the scene (BG or OBJ variant by its kind, main or sub screen by kind < 10), then renders its text, a
// text from the extended text getter when the id is an extended one, otherwise by id. Returns 0 on failure.
s32 i_InitRenderTarget(int index, RenderTarget *target, const TextRenderSceneInfo *info, Language language) {
    RenderTargetDesc *desc = &info->targets[index];
    bool isMain = desc->kind < 10;
    const PaletteSetting *palette;
    Text text;

    if (desc->kind == 4 || desc->kind == 0xe) {
        GXOamAttr *oam = info->oamMain;
        palette = (const PaletteSetting *)info->objPaletteMain;
        if (!isMain) {
            oam = info->oamSub;
            palette = (const PaletteSetting *)info->objPaletteSub;
        }
        if (!target->initialize_forOBJ(desc->area, oam, isMain, desc->v0c, desc->v10, desc->v14, desc->v18, desc->v1c, desc->v28, desc->v2c, desc->v30 != 0, desc->v20, palette)) {
            return 0;
        }
        s16 posY = desc->posY;
        s16 posX = desc->posX;
        target->unk_5c = posX;
        target->unk_5e = posY;
    } else {
        palette = (const PaletteSetting *)info->bgPaletteMain;
        if (!isMain) {
            palette = (const PaletteSetting *)info->bgPaletteSub;
        }
        if (!target->initialize_forBG(desc->area, isMain, desc->kind % 10, desc->v0c, desc->v10, desc->v14, desc->v18, desc->v1c, desc->v20, palette)) {
            return 0;
        }
        s16 posY = desc->posY;
        s16 posX = desc->posX;
        target->unk_5c = posX;
        target->unk_5e = posY;
        Knife_Message_TextRenderer_setField50_54(target, desc->v28, desc->v2c);
        Knife_Message_TextRenderer_setField58(target, desc->v30);
    }
    if (Knife_Message_i_IsExText(desc->textId) && data_0217d56c.getter != NULL) {
        text.clear();
        if (!data_0217d56c.getter->getText(&text, desc->textId, language)) {
            return 0;
        }
        return data_0217d594.renderText(target, &text);
    }
    return data_0217d594.renderText(target, desc->textId, language);
}

}
}
