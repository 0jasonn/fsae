#ifndef WIP_E_RTINFO_E_H
#define WIP_E_RTINFO_E_H

#include "engine/functions.h"
#include "knife/message/text_tokenizer.h"
#include "knife/subtask/subtask.h"
#include "knife/message/pictogram.h"

namespace Knife {
namespace Message {

struct PaletteSetting;

// Descriptor of one render target of a scene (0x34 bytes, rodata of the scene): text id, kind, the VRAM/area pointer
// and the sizes handed to RenderTarget::initialize_forBG / initialize_forOBJ
typedef struct RenderTargetDesc {
    u32 textId;       // 0x00
    s32 kind;         // 0x04: 4 and 0x0e draw OBJ text, below 10 the main screen
    void *area;       // 0x08
    s32 v0c;
    s32 v10;
    s32 v14;
    s32 v18;
    s32 v1c;
    s32 v20;
    s16 posX;         // 0x24
    s16 posY;         // 0x26
    s32 v28;
    s32 v2c;
    s32 v30;          // 0x30: flag of the OBJ variant
} RenderTargetDesc;

// Knife::Message::TextRenderSceneInfo: the text pool size, palette settings (main and sub, BG and OBJ), screen buffers,
// the OAM buffers, the pictogram settings of both screens and the table of render target descriptors
typedef struct TextRenderSceneInfo {
    u32 poolSize;                 // 0x00
    u8 bgPaletteMain[8];          // 0x04
    u8 objPaletteMain[8];         // 0x0c
    u8 bgPaletteSub[8];           // 0x14
    u8 objPaletteSub[8];          // 0x1c
    void *bgBuffers[4];           // 0x24
    void *objBuffers[4];          // 0x34
    GXOamAttr *oamMain;           // 0x44
    GXOamAttr *oamSub;            // 0x48
    PictCharInfo pictMain;        // 0x4c
    s32 pictMainFirst;            // 0x238: first OAM entry of the main pictograms
    s32 pictMainCount;            // 0x23c
    PictCharInfo pictSub;         // 0x240
    s32 pictSubFirst;             // 0x42c
    s32 pictSubCount;             // 0x430
    s32 rendererArgs[4];          // 0x434: stored in the text renderer at +0x50
    s32 renderer98;               // 0x444
    s32 renderer9c;               // 0x448
    s32 targetCount;              // 0x44c
    RenderTargetDesc *targets;    // 0x450
} TextRenderSceneInfo;

class RenderTarget {
public:
    s32 initialize_forBG(void *area, bool main, int a, int b, int c, int d, int e, int f, int g, const PaletteSetting *palette);
    s32 initialize_forOBJ(void *area, GXOamAttr *oam, bool main, int a, int b, int c, int d, int e, int f, int g, bool flag, int h, const PaletteSetting *palette);

    u8 unk_00[0x5c];
    s16 unk_5c;
    s16 unk_5e;
};

class IExTextGetter {
public:
    virtual bool getText(Text *text, u32 textId, Language language);
};

}
}

typedef struct ExTextState {
    s32 count;                             // 0x00: number of render targets
    Knife::Message::IExTextGetter *getter; // 0x04
    Knife::Message::Language language;     // 0x08
    u8 *targets;                           // 0x0c: the render targets, 0x68 bytes each
} ExTextState;

#endif
