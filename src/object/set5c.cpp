#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cellcommon.h"

// Functions in this file (original names from the debug build, or renames for the func_ names):
//   set5c_changeiroankyo, set5c_returnZero -> set5c_returnZero

// Four cell tables: data_020d7d7c holds the key, data_0216f82c the cell that is rewritten for that key
extern const u16 data_020d7d7c[];
extern u16 data_0216f82c[];

// Rewrites the cell of every table entry whose key matches b
ARM void set5c_changeiroankyo(u16 cell, u16 key) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (key == data_020d7d7c[i]) {
            RewCellOne(data_0216f82c[i], cell, 0x4000);
        }
    }
}

// Placeholder that always reports 0
ARM int set5c_returnZero(void) {
    return 0;
}
