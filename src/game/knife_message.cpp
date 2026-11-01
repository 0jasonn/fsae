#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"
#include "game/knife_message_api.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::MessageTextRender::clearCanvasLine (0x0209fcdc + 0x020a0508 range; this is 0x020a0508)

namespace Knife {
namespace Message {

// MessageTextRender::clearCanvasLine(long, long, long) (0x020a0508): fills cells of the canvas with a colour
void MessageTextRender::clearCanvasLine(s32 line, s32 lines, s32 color) {
    u32 spread = SpreadColor32(&canvas, color);
    u8 *dst = (u8 *)canvas.pBits + line * canvas.width * Knife_CharBytes(&canvas);
    s32 size = canvas.width * lines * Knife_CharBytes(&canvas);

    MIi_CpuClearFast(spread, dst, size);
}

}
}

// Functions in this file (original names from the debug build, or guessed where the debug build has none):
//   MessageTextRender::setField34 (0x020a056c), setField35 (0x020a0564) (names guessed from the stored byte)
// Fields 0x34..0x38 of MessageTextRender are not known yet, so the setters only name the slot.

namespace Knife {
namespace Message {

// MessageTextRender::setField35 (0x020a0564): stores the byte at +0x35
void MessageTextRender::setField35(u8 value) {
    field35 = value;
}

// MessageTextRender::setField34 (0x020a056c): stores the byte at +0x34
void MessageTextRender::setField34(u8 value) {
    field34 = value;
}

}
}

// Functions in this file (plain names from the debug build, C linkage):
//   Knife::Message::MessageTextRender::initWithCanvas (0x020a0574, Knife_Message_MessageTextRender_initWithCanvas)

extern "C" void Record_InitTable(void *canvas, void *bits, s32 cellWidth, s32 cellHeight, s32 depth);
extern "C" void func_020c6008(void *buffer, s32 cellWidth, s32 cellHeight, s32 cellX, s32 cellY, s32 a, s32 b, s32 c);
extern "C" void *KnifeApp_getInstance(void);
extern "C" void *KnifeApp_getField20Address(void *app);

// MessageTextRender fields this function sets (the class in game/knife_message.h keeps these as bytes)
typedef struct MessageTextRenderFields {
    u8 unk_00[0x04];
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    void *buffer;      // 0x08: the buffer the text is drawn into
    u8 canvas[0x10];   // 0x0c: the text canvas
    u8 unk_1c[0x24 - 0x1c];
    void *canvasRef;   // 0x24: points at the canvas
    void *field20;     // 0x28: field 20 of the application
    s32 unk_2c;        // 0x2c: set to 1 here
    s32 unk_30;        // 0x30: set to 1 here
} MessageTextRenderFields;

// MessageTextRender::initWithCanvas(void*, void*, unsigned short, unsigned long, unsigned long, unsigned long, unsigned long)
// (0x020a0574): sets up the canvas from the pixel size (cells are 8 pixels), links the application field and clears the offset
void Knife_Message_MessageTextRender_initWithCanvas(void *a, void *bits, void *buffer, u16 palette, u32 x, u32 y, u32 width, u32 height) {
    MessageTextRenderFields *self = (MessageTextRenderFields *)a;

    Record_InitTable(self->canvas, bits, width >> 3, height >> 3, 4);
    self->field20 = KnifeApp_getField20Address(KnifeApp_getInstance());
    self->canvasRef = self->canvas;
    self->unk_2c = 1;
    self->unk_30 = 1;
    func_020c6008(buffer, width >> 3, height >> 3, x >> 3, y >> 3, 0x20, palette & 0x3ff, 0);
    self->buffer = buffer;
    self->offsetX = 0;
    self->offsetY = 0;
}

// Functions in this file (names guessed from the stored field, the debug build has none):
//   MessageTextRender::clearField36 (0x020a0624), getField36 (0x020a0630), setSceneInfo (0x020a0638)

namespace Knife {
namespace Message {

// MessageTextRender::clearField36 (0x020a0624): clears the byte at +0x36
void MessageTextRender::clearField36(void) {
    field36 = 0;
}

// MessageTextRender::getField36 (0x020a0630): reads the byte at +0x36
u8 MessageTextRender::getField36(void) const {
    return field36;
}

// MessageTextRender::setSceneInfo (0x020a0638): stores the scene block pointer at +0x38
void MessageTextRender::setSceneInfo(void *info) {
    sceneInfo = (MessageSceneInfo *)info;
}

}
}
