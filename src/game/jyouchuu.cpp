#include "engine/functions.h"
#include "game/jyouchuu.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"
#include "game/frame_load.h"

// Functions in this file (original names from the debug build):
//   LoadJyouchuu

// Per-room table (indexed by the current frame's roomNo) and per-state table
extern const u16 data_020d7da8[];
extern const u16 data_020d7d84[];

// Loads the data of the current stage (state 5 and up use the room of the current frame)
void LoadJyouchuu(void) {
    u8 state;
    FRAME_INFO_ *frame;

    state = gameState.unk_01;
    if (state >= 5) {
        frame = bgmIndexTable[state][gameState.unk_48].frame;
        DataLoad(data_020d7da8[frame->roomNo]);
    } else {
        DataLoad(data_020d7d84[state]);
    }
}
