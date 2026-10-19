#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   LoadJyouchuu

// Game state byte 1, the row table of bgmIndexTable (row byte 1 indexes data_020d7da8) and the per-state table data_020d7d84
extern u8 data_0212c7c8[];
extern u32 bgmIndexTable[];
extern const u16 data_020d7da8[];
extern const u16 data_020d7d84[];

// Loads the data of the current stage (state 5 and up use the row of the current stage)
ARM void LoadJyouchuu(void) {
    u8 state;
    u8 *row;

    state = data_0212c7c8[1];
    if (state >= 5) {
        row = *(u8 **)((u8 *)bgmIndexTable[state] + data_0212c7c8[0x48] * 8);
        DataLoad(data_020d7da8[row[1]]);
    } else {
        DataLoad(data_020d7d84[state]);
    }
}
