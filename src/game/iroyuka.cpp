#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"

// Functions in this file (original names from the debug build):
//   ChangeIroyuka

// Game state byte 1 (data_0212c7c8) and the counter block at data_0216f820
extern u32 data_0216f820[];

// Sets the new value of the counter block when the game state is not 1 and the block is active
void ChangeIroyuka(u8 value) {
    if (data_0212c7c8.unk_01 != 1 && data_0216f820[2] != 0) {
        data_0216f820[1] = value + 1;
    }
}
