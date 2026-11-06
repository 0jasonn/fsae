#include "engine/functions.h"
#include "knife/message/textrender_2.h"
#include "knife/comm/multisio.h"
#include "game/decls_e.h"

extern u8 data_0212ca20[]; // group info block, the member names are 0x34 bytes apart from +0x14
extern const u16 data_020de6f8[]; // empty string

#define BG_CNT(addr) (*(volatile u16 *)(addr))

// Width of a rotation / scaling BG screen in cells, by the screen size bits of its control register
#define SCREEN_WIDTH_AFFINE(addr)              switch (BG_CNT(addr) & 0xc000) {           case 0:                                        return 0x80;                           case 0x4000:                                   return 0x100;                          case 0x8000:                                   return 0x200;                          case 0xc000:                                   return 0x400;                          }                                          break

// Knife::Message::TextRenderer::getPlayerName(int, Knife::Message::Text *) const (0x020a5d44), plain name: sets out to the
// name of player index (the local save name outside a wireless session, the group member name inside one), or to an
// empty string
void Knife_Message_TextRenderer_getPlayerName(Knife::Message::TextRenderer *self, s32 index, Knife::Message::Text *out) {
    s32 count;
    const u16 *name;
    void *manager;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        manager = func_020909c8();
        s32 state = Knife_Comm_WirelessManager_getState(manager);
        count = 0;
        if (state == 8 || state == 0xb) {
            count = Knife_Comm_WirelessManager_getLinkLevel(manager);
        }
        if (index < count) {
            name = (const u16 *)(data_0212ca20 + index * 0x34 + 0x14);
            out->ces = (Knife::Message::ICharacterEncodingScheme *)Knife_Message_getCESObject_021770b4();
            out->data = name;
            out->size = Wstr_Length(name) << 1;
            return;
        }
    } else if (index == 0) {
        name = data_021350b0[multiSioSelect.index].str08;
        out->ces = (Knife::Message::ICharacterEncodingScheme *)Knife_Message_getCESObject_021770b4();
        out->data = name;
        out->size = Wstr_Length(name) << 1;
        return;
    }
    out->ces = (Knife::Message::ICharacterEncodingScheme *)Knife_Message_getCESObject_021770b4();
    out->data = data_020de6f8;
    out->size = 0;
}
