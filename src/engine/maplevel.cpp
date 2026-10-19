#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   get_maplevel

extern const u8 data_02103dc4[];

// Map level byte of the current stage: picks a row of data_02103dc4 by the stage counter and indexes it by a
// value computed from the game state
ARM u8 get_maplevel(void) {
    u32 value;
    const u8 *row;

    if (data_0212c7c8.unk_1[0] == 2) {
        value = data_0212c7c8.difficulty + 3;
        row = data_02103dc4 + value * 8;
    } else {
        value = data_0212c7c8.stage - 1;
        row = data_02103dc4 + value * 8;
    }
    return row[Random() & 7];
}
