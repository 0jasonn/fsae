#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

ARM void Menu_Begin(MenuWork *menu) {
    s32 position;

    func_020bdd60(menu, data_02127188, menu->sub.unk_3f8, 1);
    position = Menu_GetPosition(menu->sub.unk_370);
    func_020bbbfc(menu->unk_354, position, 0xffff);
    menu->sub.unk_608 = 0;
}
