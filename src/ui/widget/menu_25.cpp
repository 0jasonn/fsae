#include "engine/functions.h"
#include "global.h"
#include "ui/widget/menu.h"
#include "engine/work21_clear.h"

// TODO(headers): this declaration of lobby_callWithZeroPos differs from the shared one;
// see the header restructure report.
extern "C" void lobby_callWithZeroPos(s32 active, void *buf);

// State copied from a list by Menu_CopyViewState: a rectangle (filled by Menu_GetRect), then fields at +0x10..+0x1c.
typedef struct MenuViewState {
    /* 00 */ s16 rect[4];
    /* 08 */ u8 unk_08[0x10 - 0x08];
    /* 10 */ u32 unk_10;
    /* 14 */ s16 unk_14;
    /* 16 */ s16 unk_16;
    /* 18 */ u32 unk_18;
    /* 1c */ u32 unk_1c;
    /* 20 */ u32 unk_20;
} MenuViewState;

// Functions in this file (provisional names, role not confirmed):
//   Menu_CopyViewState (Menu_CopyViewState), Menu_SyncListRect (Menu_SyncListRect)

// Menu_CopyViewState (0x020be70c): fills the view state of dst from the list (the rectangle through Menu_GetRect).
extern "C" void Menu_CopyViewState(MenuList *list, MenuViewState *dst);
void Menu_CopyViewState(MenuList *list, MenuViewState *dst) {
    Menu_GetRect((s16 *)dst, list->active);
    dst->unk_10 = list->unk_10;
    dst->unk_14 = list->unk_14;
    dst->unk_16 = list->unk_16;
    dst->unk_18 = list->unk_08;
    dst->unk_1c = list->active;
}

// Menu_SyncListRect (0x020be750): when the list is active, reads its rectangle (Work21_clear), copies the view state
// and passes both to lobby_callWithZeroPos.
void Menu_SyncListRect(MenuList *list) {
    MenuViewState state;

    if (list->active == 0) {
        return;
    }
    Work21_clear(&state);
    Menu_CopyViewState(list, &state);
    lobby_callWithZeroPos(list->active, &state);
}
