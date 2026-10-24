#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_ReleaseWrapper (Menu_ReleaseWrapper)

// Menu_ReleaseWrapper (0x020bf06c): releases the menu held by the wrapper (func_020bc6c4), notifies func_020c2c48 and
// clears the wrapper pointer. Called by Knife_ForwardMenuWrapper.
extern "C" void Menu_ReleaseWrapper(MenuWrapper *wrapper, void *arg);
ARM void Menu_ReleaseWrapper(MenuWrapper *wrapper, void *arg) {
    MenuWork *menu;

    menu = wrapper->ptr;
    func_020bc6c4(menu);
    func_020c2c48(arg, menu);
    wrapper->ptr = 0;
}
