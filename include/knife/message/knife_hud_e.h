#ifndef WIP_E_KNIFE_HUD_E_H
#define WIP_E_KNIFE_HUD_E_H

#include "engine/functions.h"
#include "knife/app/knife_hud.h"
#include "knife/app/knife_hud_layout.h"

// Tables of the game-over banner (rodata). Per language: the characters of the banner as halfwords (0 terminated).
typedef struct KnifeHudBannerChars {
    u16 ch[16];
} KnifeHudBannerChars;

// One entry of a glyph lookup table: the character code (0 ends the table) and two words
typedef struct KnifeHudGlyphEntry {
    u32 code;
    s32 unk_04;
    s32 unk_08;
} KnifeHudGlyphEntry;

// Glyph table per char data type (16 entries of 12 bytes)
typedef struct KnifeHudGlyphTable {
    KnifeHudGlyphEntry entry[16];
} KnifeHudGlyphTable;

// Horizontal position of each banner character, per language
typedef struct KnifeHudBannerX {
    s32 x[16];
} KnifeHudBannerX;

// OAM parts of the call arrow of one direction (0x64 bytes): the first entry and then two pairs, one pair is shown at a
// time (blinking). Each part: offset from the arrow position, attr2 without the palette bits, bits of attr1 and attr0.
typedef struct KnifeHudCallPart {
    s32 dx;        // 0x00
    s32 dy;        // 0x04
    s32 attr2;     // 0x08
    s32 attr1Bits; // 0x0c
    s32 attr0Bits; // 0x10
} KnifeHudCallPart;

typedef struct KnifeHudCallArrow {
    KnifeHudCallPart part[5];
} KnifeHudCallArrow;

// Offset of the arrow tip from the clamped player position, per direction
typedef struct KnifeHudArrowOffset {
    s32 x;
    s32 y;
} KnifeHudArrowOffset;

extern const KnifeHudCallArrow data_020de04c[4];
extern const KnifeHudArrowOffset data_020ddcb8[4];

extern const KnifeHudBannerChars data_020ddd8c[];
extern const KnifeHudGlyphTable data_020ddecc[];
extern const KnifeHudBannerX data_020de1dc[];

extern "C" {
void Knife_Hud_HudManager_startGameOverAnim(Knife::Hud::HudManager *self);
void Knife_Hud_HudManager_getPlayerPos(const Knife::Hud::HudManager *self, int player, VecFx32 *pos);
}

#endif
