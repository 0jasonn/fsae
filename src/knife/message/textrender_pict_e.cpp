#include "knife/message/textrender_pict_e.h"

// Knife::Message::TextRender::onReadPictTag(Pictogram) (0x020a1394), plain name: draws the icon of the pictogram into the
// canvas at the current position (the icon sheet depends on the game state byte) and moves the position on by 16
void Knife_Message_TextRender_onReadPictTag(KnifeTextRender *self, s32 pictogram) {
    PictogramTable table = data_020de5f4;
    u16 packed = table.entry[pictogram];
    u16 cell = ((packed & 0xc0) << 6) | 0x400 | (packed & 0x3f);
    BOOL alt = (gameState.unk_8e == 1 || gameState.unk_8e == 4);
    u8 *sheet;

    if (alt) {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x286);
    } else {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1be);
    }
    IconToCanvas(sheet + (((u32)cell << 24) >> 17), (u8 *)self + 4, self->startX, self->unk_32 + self->unk_77);
    self->startX = self->startX + 0x10;
}

// Knife::Message::TextRender::onReadButtonTag(Button) (0x020a1470), plain name: like the pictogram tag, with the button
// table; buttons 3 and 4 use fixed cells. After the icon the position is rounded to the cell grid and the palette of the
// two cell rows of the icon is set
void Knife_Message_TextRender_onReadButtonTag(KnifeTextRender *self, s32 button) {
    ButtonTable table = data_020de5d8;
    u16 packed = table.entry[button];
    u16 cell = ((packed & 0xc0) << 6) | 0x400 | (packed & 0x3f);
    BOOL alt = (gameState.unk_8e == 1 || gameState.unk_8e == 4);
    u8 *sheet;
    u16 *map;
    s32 row;

    if (alt) {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x286);
    } else {
        sheet = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1be);
    }
    if (button == 3) {
        cell = 0x21;
    }
    if (button == 4) {
        cell = 0x22;
    }
    IconToCanvas(sheet + (((u32)cell << 24) >> 17), (u8 *)self + 4, self->startX, self->unk_32 + self->unk_77);
    if (self->startX > 0) {
        self->startX = (self->startX + 7) & 0xf8;
    }
    map = (u16 *)(*(u8 **)((u8 *)self + 0x2c) + (((self->unk_32 / 8) * 0x20 + self->startX / 8) << 1));
    for (row = 0; row < 2; row++) {
        map[row * 0x20] = (map[row * 0x20] & 0xfff) | (self->unk_82 << 12);
        map[row * 0x20 + 1] = (map[row * 0x20 + 1] & 0xfff) | (self->unk_82 << 12);
    }
    self->startX = self->startX + 0x10;
}
