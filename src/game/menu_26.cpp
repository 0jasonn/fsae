#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_FindPoolEntry (Menu_FindPoolEntry)

// Menu_FindPoolEntry (0x020bee6c): finds the entry in use with the id (the id must be in range 0..count, see
// Menu_InRange). Returns 0 when there is none.
s32 Menu_InRange(void *self, s32 value, s32 low, s32 high);
extern "C" MenuPoolEntry *Menu_FindPoolEntry(MenuPool *pool, s32 id);
ARM MenuPoolEntry *Menu_FindPoolEntry(MenuPool *pool, s32 id) {
    u32 i;
    s32 offset;
    u8 *entry;

    if (Menu_InRange(pool, id, 0, pool->count) == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        offset = i * 0x18;
        entry = (u8 *)pool + offset;
        if (id == *(s32 *)(entry + 0xb8)) {
            if (*(s32 *)(entry + 0xb4) != 0) {
                return (MenuPoolEntry *)((u8 *)pool + 0xb4 + offset);
            }
        }
    }
    return 0;
}
