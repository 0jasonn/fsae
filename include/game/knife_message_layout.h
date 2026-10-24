#ifndef WIP_E_KNIFE_MESSAGE_LAYOUT_H
#define WIP_E_KNIFE_MESSAGE_LAYOUT_H

#include "types.h"
#include "game/knife_message.h"

// Message scene block (pointed to by MessageTextRender::sceneInfo) with the fields the colour and palette code uses.
// Bytes the other tag handlers name differently are kept in the same place (see game/knife_message.h).
typedef struct KnifeMsgSceneLayout {
    u8 unk_00[0x25];
    u8 mode25;        // 0x25: 2 selects the first palette table, otherwise the second
    u8 unk_26[0x2b - 0x26];
    u8 palette2b;     // 0x2b: palette bits of the current colour (low nibble)
    u8 unk_2c[0x34 - 0x2c];
    u8 cellTable[0xd7 - 0x34]; // 0x34: attribute cells, 30 per row
    u8 paletteFlags;  // 0xd7: palette bits (0x30) of the current colour
    u8 colorReset;    // 0xd8: cleared by the colour tag
    u8 indent;        // 0xd9: indent of the text, compared with the x offset
    u8 unk_da[0xe1 - 0xda];
    u8 rowStep;       // 0xe1: row step of the second table, doubled
} KnifeMsgSceneLayout;

extern const u8 data_020de45c[]; // colour tag table 1 (index: colour type)
extern const u8 data_020de470[]; // colour tag table 2 (index: table 1 value)

#endif
