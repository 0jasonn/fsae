#include "engine/functions.h"
// Functions in this file:
//   isBossFloor -> isBossFloor
//   shuffleStage -> shuffleStage
#include "game/player_flags.h"
#include "global.h"

BOOL isBossFloor(void) {
    gameState.periodicFlag = (gameState.phaseTimer % 3 == 2) ? 0x81 : 0;
    return gameState.periodicFlag != 0;
}

void shuffleStage(void) {
    u8 oldIndex = gameState.unk_01;
    u8 newIndex;
    do {
        newIndex = Random() & 3;
        gameState.unk_01 = newIndex;
    } while (newIndex == oldIndex);
}
