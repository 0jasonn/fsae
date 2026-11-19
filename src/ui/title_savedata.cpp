#include "engine/functions.h"
#include "engine/misc.h"
#include "global.h"

extern u8 comWork[];

// title_savedata (0x02053114): title screen step for the save data / player check. When the blend request is idle and
// the effect state is 2 it resets the display, finalizes the opening task and, if the players' key group nibbles
// (high nibble of each game slot's byte 4; 0xf0 = none) disagree, chains task 8.
void title_savedata(void) {
    u8 mode;
    u8 firstKey;
    u8 i;
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    *(u16 *)(comWork + 0x12) = 8;
    mode = effectState.phase;
    switch (mode) {
        case 0:
        case 1:
            return;
        case 2:
            break;
        default:
            return;
    }
    DispReset();
    OpeningTaskFinalzie();
    firstKey = gameState.slots[0].unk_04 & 0xf0;
    if (firstKey == 0xf0) {
        return;
    }
    for (i = 1; i < gameState.playerCount; i++) {
        int key = gameState.slots[i].unk_04 & 0xf0;
        if (key != 0xf0 && firstKey != key) {
            Task_Chain(8);
            return;
        }
    }
}
