#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// 0x18-byte entry of the cursor table pointed to by the word at menu+0x348 (provisional layout).
typedef struct MenuCursorEntry {
    /* 00 */ u32 value;
    /* 04 */ u8 unk_04[4];
    /* 08 */ u32 value8;
    /* 0c */ u32 *table;
    /* 10 */ u8 unk_10[8];
} MenuCursorEntry;

// Looks up the cell at (row, column) of the cursor table, packs the cell as (row + 1) << 16 | (column + 1), and
// updates the cursor state of the menu sub-object. The data passed to func_020bdd60 is the table value for the
// column, or the entry's own value when the column is -1.
ARM void Menu_SetCursorPos(MenuWork *menu) {
    s32 row;
    s32 column;
    u32 packed;
    MenuCursorEntry *entry;
    u32 *table;
    const void *data;
    s32 moved;

    row = Ctrl_getSliderIndexA(menu->unk_358);
    column = Ctrl_getSliderIndexB(menu->unk_358);
    entry = (MenuCursorEntry *)((u8 *)*(void **)*(void **)((u8 *)menu + 0x348) + (s16)row * 0x18);
    if (column == -1) {
        data = (const void *)entry->value;
    } else {
        table = entry->table;
        data = (const void *)table[Ctrl_getSliderIndexB(menu->unk_358)];
    }
    packed = (u32)(row + 1) << 16 | (u32)(column + 1);
    moved = (s32)menu->sub.unk_608 > (s32)packed;
    func_020bdd60(menu, data, menu->sub.unk_3f8 + (0x500 - 0x3f8), moved);
    func_020bbbfc(menu->unk_354, entry->value8, (u16)row);
    menu->sub.unk_608 = packed;
}
