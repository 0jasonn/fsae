#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_AcquirePoolEntry (Menu_AcquirePoolEntry)

s32 Menu_InRange(void *self, s32 value, s32 low, s32 high);
s32 Menu_ClampValue(void *self, s32 value, s32 low, s32 high);
extern "C" MenuPoolEntry *Menu_FindPoolEntry(MenuPool *pool, s32 id);

// Menu_AcquirePoolEntry (0x020beda0): claims the entry for the id (the existing one, or a new one from Menu_AllocPoolEntry)
// when the pool is ready and the id is in range. The entry is cleared, and when value is not 0x80 its level is set
// from the clamped value. Returns the entry, or 0.
ARM void *Menu_AcquirePoolEntry(void *poolObj, s32 id, s32 value) {
    MenuPool *pool = (MenuPool *)poolObj;
    MenuPoolEntry *entry;
    s32 level;

    if (pool->ready == 0) {
        return 0;
    }
    if (Menu_InRange(pool, id, 0, pool->count) == 0) {
        return 0;
    }
    entry = Menu_FindPoolEntry(pool, id);
    if (entry == 0) {
        entry = Menu_AllocPoolEntry(pool, 1);
    }
    if (entry == 0) {
        return 0;
    }
    SndSlot_ReleaseFirst(entry, 0);
    SndState_StartEntryList(entry, 0, id);
    if (value != 0x80) {
        level = Menu_ClampValue(pool, value, 0, 0xff);
        func_020bf9dc(entry, 0xffff, level - 0x80);
    }
    entry->id = id;
    entry->unk_08 = 0;
    return entry;
}
