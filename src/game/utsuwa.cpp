#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Adds amount to the heart container count of a player (GameState::unk_64, clamped to at most 0x14 and at least 3) and copies
// the result to the other player outside wireless mode.
void AddHeartUtsuwa(u8 type, s8 amount) {
    gameState.maxHearts[type] += (u8)amount;
    if (gameState.maxHearts[type] > 0x14) {
        gameState.maxHearts[type] = 0x14;
    }
    if (gameState.maxHearts[type] < 6) {
        gameState.maxHearts[type] = 3;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        gameState.maxHearts[type ^ 1] = gameState.maxHearts[type];
    }
}
