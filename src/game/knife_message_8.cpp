#include "engine/functions.h"
#include "global.h"

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
extern "C" void Knife_Message_MessageTextRender_initWithCanvas(void *a, void *bits, void *buffer, u16 palette, u32 x, u32 y, u32 width, u32 height);
ARM void Knife_Message_MessageTextRender_initWithCanvas(void *a, void *bits, void *buffer, u16 palette, u32 x, u32 y, u32 width, u32 height) {
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
