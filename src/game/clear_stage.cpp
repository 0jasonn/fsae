#include "engine/functions.h"
#include "engine/player.h"

// stageProgress (gameState + 0x90): bits 0-1 hold the highest floor reached in mode 5, bits 4-7 one bit per floor
// in mode 6.

// ClearNewStageUpdate (0x02048cb8): records the stage just cleared. In mode 5 the progress counter (1..3) is raised
// to this stage and, when the last stage of the third floor is done, every player's slot gets flag 1; in mode 6
// the floor bit is set and, with all three floors cleared, every slot gets flag 2.
void ClearNewStageUpdate(void) {
    int i;
    if (gameState.unk_01 == 5) {
        u8 stage = gameState.unk_48 % 3 + 1;
        u8 progress = gameState.slotWords[0].stageProgress;
        if ((u8)(progress & 3) < stage) {
            progress = progress & 0xfc;
            gameState.slotWords[0].stageProgress = progress | stage;
        }
        if ((gameState.slotWords[0].stageProgress & 3) != 3 || stage != 3) {
            return;
        }
        for (i = 0; i < gameState.playerCount; i++) {
            gameState.slots[i].flags |= 1;
        }
    } else if (gameState.unk_01 == 6) {
        int floor = gameState.unk_48 % 3;
        u8 bits = gameState.slotWords[0].stageProgress | (u8)(1 << (floor + 4));
        gameState.slotWords[0].stageProgress = bits;
        if ((bits & 0xf0) != 0x70 || floor + 1 != 3) {
            return;
        }
        for (i = 0; i < gameState.playerCount; i++) {
            gameState.slots[i].flags |= 2;
        }
    }
}
