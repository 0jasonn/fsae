#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_AllocPoolEntry (Menu_AllocPoolEntry)

s32 Menu_WrapInto(void *self, s32 value, s32 a, s32 b);

// Menu_AllocPoolEntry (0x020beed4): moves the current index of the pool on by one (wrapped into 0..15) and looks for an
// entry that is not in use, starting there. The first free entry becomes current and is returned. When none is free and
// flag is set, the entry at the current index is returned (otherwise 0).
extern "C" MenuPoolEntry *Menu_AllocPoolEntry(MenuPool *pool, s32 flag);
ARM MenuPoolEntry *Menu_AllocPoolEntry(MenuPool *pool, s32 flag) {
    u32 i;
    s32 zero;
    s32 index;
    MenuPoolEntry *entry;

    i = 0;
    pool->current = Menu_WrapInto(pool, pool->current + 1, i, 0x10);
    zero = 0;
    for (i = 0; i < 16; i++) {
        index = Menu_WrapInto(pool, pool->current + i, zero, 0x10);
        if (pool->entries[index].unk_00 == 0) {
            pool->current = index;
            return &pool->entries[index];
        }
    }
    entry = 0;
    if (flag != 0) {
        entry = &pool->entries[pool->current];
    }
    return entry;
}
