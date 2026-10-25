#include "engine/functions.h"
#include "global.h"

// Functions in this file (plain names from the debug build, C linkage):
//   MessageSelect update (0x020a18c4)

extern u16 data_0212c510;
extern u8 localPlayerIndex;
extern u16 data_0212c58c[];
extern "C" void clamp_s8(signed char &value, signed char low, signed char high);
extern "C" void Knife_Message_MessageSelect_update(void *self);

// Selection dialog (Knife::Message::selectionDialog) as MessageSelect update sees it
typedef struct KnifeSelectMenu {
    u8 state;      // 0x00: 0 idle, 1 counting down, 2 waiting for a key, 3 choice made
    u8 unk_01;
    u8 unk_02;     // 0x02: count-down of state 1
    u8 count;      // 0x03: number of entries
    s8 selected;   // 0x04: selected entry
    u8 unk_05;
    u8 result;     // 0x06: the choice
    s8 visible;    // 0x07: 1 while the dialog is shown
} KnifeSelectMenu;

// MessageSelect update (0x020a18c4): reads the keys (the player's own in a wireless session), moves the state on and
// the selection with the up and down keys, and plays the cursor sound when the selection changes
extern "C" void Knife_Message_MessageSelect_update(void *self);
ARM void Knife_Message_MessageSelect_update(void *self) {
    KnifeSelectMenu *menu = (KnifeSelectMenu *)self;
    u16 keys;
    u8 oldSelected;
    void *app;

    app = KnifeApp_getInstance();
    keys = data_0212c510;
    if (KnifeApp_isWirelessMode(app) != 0) {
        keys = data_0212c58c[localPlayerIndex];
    } else {
        Knife_Single_SinglePlay_GetInstance();
    }
    switch (menu->state) {
    case 0:
        return;
    case 1:
        menu->unk_02--;
        if (menu->unk_02 == 0) {
            menu->state = 2;
        }
        break;
    case 2:
    case 3:
        break;
    }
    if (menu->count == 0) {
        menu->state = 3;
        return;
    }
    if (menu->state < 2) {
        return;
    }
    oldSelected = (u8)menu->selected;
    if (keys & 0x40) {
        menu->selected--;
    }
    if (keys & 0x80) {
        menu->selected++;
    } else if (keys & 1) {
        menu->state = 3;
        menu->result = 1;
        if (menu->visible != 0) {
            SoundReq(0x3e);
        }
    } else if ((keys & 8) || (keys & 2)) {
        menu->state = 3;
        menu->result = 2;
    }
    clamp_s8(menu->selected, 0, menu->count - 1);
    if (oldSelected != menu->selected && menu->visible != 0) {
        SoundReq(0x3d);
    }
}
