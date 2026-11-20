#ifndef KNIFE_MESSAGE_TEXTRENDER_SETUP_H
#define KNIFE_MESSAGE_TEXTRENDER_SETUP_H

#include "engine/functions.h"
#include "knife/message/textrender.h"

// Message screen info (KNIFE_MSGSCRN) as the text render setup reads it
typedef struct TextRenderMsgScrn {
    u8 *screenBuffer;   // 0x00
    u8 *charBase;       // 0x04
    u8 unk_08[8];
    u16 charInfo;       // 0x10: bits 0 to 9 first character, bits 12 and up palette
    u8 unk_12[3];
    u8 unk_15;          // 0x15
    u8 unk_16[2];
    u8 unk_18;          // 0x18
    u8 palette;         // 0x19
    u8 unk_1a;
    u8 widthPx;         // 0x1b
    u8 heightCells;     // 0x1c
    u8 unk_1d[0x34 - 0x1d];
    void *appWork;      // 0x34
} TextRenderMsgScrn;

extern "C" {
void Knife_Message_TextRender_setupFromMsgScrn(KnifeTextRender *self, const TextRenderMsgScrn *info);
void Record_InitTable(void *canvas, void *bits, s32 cellWidth, s32 cellHeight, s32 depth);
void Knife_Message_TextRender_setupCanvas(KnifeTextRender *self, const TextRenderMsgScrn *info, s32 index);
}

#endif
