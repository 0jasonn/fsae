#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/pane.h"
#include "engine/level_table_api.h"

// level_table: functions Level_getEntry (0x020b70c0) and Level_noop (0x020b70e4), both matching.

// Level_getEntry(self, level) (0x020b70c0, provisional name): returns entry 2 of the table at +0x18 when level is below
// 0x10, entry 1 when it is exactly 0x10 and entry 0 above it
void *Level_getEntry(void *self, u32 level) {
    u32 index;
    void **table;

    index = 1;
    if (level < 0x10) {
        index = 2;
    } else {
        if (level > 0x10) {
            index = 0;
        }
    }
    table = *(void ***)((u8 *)self + 0x18);
    return table[index];
}

// Level_noop(self) (0x020b70e4, provisional name): does nothing
void Level_noop(void *self) {
}

// level_table_2: function Level_deletingDtor (0x020b70e8), matching. It follows Level_noop, the empty destructor of the
// Level class, and frees the block through operator delete.

// Level_deletingDtor(self) (0x020b70e8, provisional name): deleting destructor of the Level class, returns self
void *Level_deletingDtor(void *self) {
    operator delete(self);
    return self;
}
