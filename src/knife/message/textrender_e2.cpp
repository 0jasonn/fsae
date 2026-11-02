#include "engine/functions.h"
#include "knife/message/textrender_e2.h"
#include "knife/comm/multisio.h"
#include "game/decls_e.h"

extern u8 data_0212ca20[]; // group info block, the member names are 0x34 bytes apart from +0x14
extern const u16 data_020de6f8[]; // empty string

#define BG_CNT(addr) (*(volatile u16 *)(addr))

// Width of a rotation / scaling BG screen in cells, by the screen size bits of its control register
#define SCREEN_WIDTH_AFFINE(addr)              switch (BG_CNT(addr) & 0xc000) {           case 0:                                        return 0x80;                           case 0x4000:                                   return 0x100;                          case 0x8000:                                   return 0x200;                          case 0xc000:                                   return 0x400;                          }                                          break

// Knife::Message::TextRenderer::getScreenWidth(bool, int) (0x020a5a58), plain name: width in cells of the screen of a BG
// layer (main for isBg, sub otherwise) read from its control register; the rotation / scaling BGs 2 and 3 depend on the
// BG mode. Unknown layers terminate.
s32 Knife_Message_TextRenderer_getScreenWidth(s32 isBg, s32 index) {
    s32 bgMode = Knife_Message_TextRenderer_getBgMode(isBg);
    s32 layer = 0;

    if (isBg == 0) {
        layer = 10;
    }
    switch (index + layer) {
    case 0:
        return (BG_CNT(0x4000008) & 0x4000) ? 0x200 : 0x100;
    case 1:
        return (BG_CNT(0x400000a) & 0x4000) ? 0x200 : 0x100;
    case 2:
        if (bgMode == 0) {
            return (BG_CNT(0x400000c) & 0x4000) ? 0x200 : 0x100;
        }
        SCREEN_WIDTH_AFFINE(0x400000c);
    case 3:
        if (bgMode == 0) {
            return (BG_CNT(0x400000e) & 0x4000) ? 0x200 : 0x100;
        }
        SCREEN_WIDTH_AFFINE(0x400000e);
    case 10:
        return (BG_CNT(0x4001008) & 0x4000) ? 0x200 : 0x100;
    case 11:
        return (BG_CNT(0x400100a) & 0x4000) ? 0x200 : 0x100;
    case 12:
        if (bgMode == 0) {
            return (BG_CNT(0x400100c) & 0x4000) ? 0x200 : 0x100;
        }
        SCREEN_WIDTH_AFFINE(0x400100c);
    case 13:
        if (bgMode == 0) {
            return (BG_CNT(0x400100e) & 0x4000) ? 0x200 : 0x100;
        }
        SCREEN_WIDTH_AFFINE(0x400100e);
    }
    OS_Terminate();
    return 0;
}

