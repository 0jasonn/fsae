#include "engine/functions.h"
#include "global.h"
#include "game/shikake.h"

// Switch-block helpers (module shikake). Original names from the debug build.
//   ShikakeMove

// Runs the big-block and other-kind handlers over the 8-byte records of data_02134bb0, then clears both counts.
ARM void ShikakeMove(void) {
    u16 i;
    u8 *record;

    record = data_02134bb0;
    for (i = 0; i < (s32)data_021348e4; i++, record += 8) {
        switch (*(u32 *)record >> 24) {
        case 1:
            shikake_bigblock((u32 *)record);
            break;
        case 2:
            func_020227b4((u32 *)record);
            break;
        }
    }
    data_021348e4 = 0;
    data_021348f0 = 0;
}
