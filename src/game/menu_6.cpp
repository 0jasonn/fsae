#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Ends the pending reset: when sub+0x39c is set, the object at 0x370 is reset and the flag is cleared.
ARM void Menu_Reset(MenuWork *menu) {
    void *self;
    s32 pending;

    pending = menu->sub.unk_39c;
    if (pending == 0) {
        return;
    }
    self = menu;
    func_020bc7b8(&self, pending);
    menu->sub.unk_39c = 0;
    Menu_SetActive((MenuList *)menu->sub.unk_370, 0);
}
