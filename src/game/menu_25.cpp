#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_CopyViewState (Menu_CopyViewState), Menu_SyncListRect (Menu_SyncListRect)

// Menu_CopyViewState (0x020be70c): fills the view state of dst from the list (the rectangle through Menu_GetRect).
extern "C" void Menu_CopyViewState(MenuList *list, MenuViewState *dst);
ARM void Menu_CopyViewState(MenuList *list, MenuViewState *dst) {
    Menu_GetRect((s16 *)dst, list->active);
    dst->unk_10 = list->unk_10;
    dst->unk_14 = list->unk_14;
    dst->unk_16 = list->unk_16;
    dst->unk_18 = list->unk_08;
    dst->unk_1c = list->active;
}

// Menu_SyncListRect (0x020be750): when the list is active, reads its rectangle (func_020b7080), copies the view state
// and passes both to lobby_callWithZeroPos.
extern "C" void Menu_SyncListRect(MenuList *list);
ARM void Menu_SyncListRect(MenuList *list) {
    MenuViewState state;

    if (list->active == 0) {
        return;
    }
    func_020b7080(&state);
    Menu_CopyViewState(list, &state);
    lobby_callWithZeroPos(list->active, &state);
}
