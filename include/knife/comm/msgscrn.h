#ifndef WIP_A_MSGSCRN_A_H
#define WIP_A_MSGSCRN_A_H

#include "engine/functions.h"
#include "ui/msgwin.h"
#include "knife/message/textrender.h"
#include "knife/message/textrender_setup.h"
#include "knife/message/knife_font.h"
#include "knife/message/knife_message_api.h"

// Message screen description (Knife::Message::KNIFE_MSGSCRN, 0x38 bytes) as knife_MakeMsgScreen reads and rewrites it.
typedef struct KnifeMsgScrn {
    u16 *screenBuffer;   // 0x00: tile map position (u16 cells)
    u8 *charBase;        // 0x04: character data position
    u8 unk_08[8];
    u16 charInfo;        // 0x10: bits 0..9 first character, bits 12..15 palette
    u8 styleFlags;       // 0x12: bit 0 framed, bits 1..3 frame style, bits 4..7 frame palette
    u8 layoutFlags;      // 0x13: bit 0 centered text, bit 3 no alignment, bit 4 centered on x, bit 5 bottom aligned
    u8 textCols;         // 0x14: fixed text width in characters (0: measured)
    u8 unk_15;
    u8 lineHeight;       // 0x16
    u8 paletteSel;       // 0x17: index into the palette table
    u8 unk_18[3];
    u8 widthPx;          // 0x1b: maximum text width
    u8 heightCells;      // 0x1c
    u8 unk_1d[7];
    u32 requestFlags;    // 0x24: last argument of KnifeApp_MessageRequest
    u8 unk_28[0x34 - 0x28];
    void *appWork;       // 0x34: tokenizer / app work of the message
} KnifeMsgScrn;

extern const u32 msgFramePalette[];   // per palette selection: low nibble is the palette, low byte the fill byte of the frame
extern const char *dialogText;   // text of the current dialog

extern "C" {
void Knife_Message_TextRender_drawText(KnifeTextRender *self, const char *text, u32 flag);
}

#endif
