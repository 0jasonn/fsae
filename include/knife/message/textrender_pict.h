#ifndef KNIFE_MESSAGE_TEXTRENDER_PICT_H
#define KNIFE_MESSAGE_TEXTRENDER_PICT_H

#include "engine/functions.h"
#include "engine/player.h"
#include "knife/message/textrender.h"

// Pictogram table: one entry per pictogram, the glyph cell index packed in the low and high bits (rodata, copied to the stack)
typedef struct PictogramTable {
    u16 entry[0x1f];
} PictogramTable;
extern const PictogramTable data_020de5f4;

// Button table: one entry per button (same packing as the pictogram table)
typedef struct ButtonTable {
    u16 entry[14];
} ButtonTable;
extern const ButtonTable data_020de5d8;

extern "C" {
void Knife_Message_TextRender_onReadPictTag(KnifeTextRender *self, s32 pictogram);
void Knife_Message_TextRender_onReadButtonTag(KnifeTextRender *self, s32 button);
void IconToCanvas(u8 *icon, const void *canvas, s32 x, s32 y);
}

#endif
