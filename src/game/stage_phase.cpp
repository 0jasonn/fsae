

#include "engine/functions.h"
#include "engine/player.h"
#include "game/stage.h"

// GameState_UpdatePhase (0x02049454): advances the stage phase at the end of a floor. While the phase machine runs
// (active) it follows phaseFlags (0xf0 and up: done, 0x10: restart the timer, 0x20: reset the per-player items and the
// score, 0x40: next phase); in the modes from 5 it counts to 3 and refills the held items; otherwise the difficulty
// decides whether a boss floor comes next and which stage index (unk_01) is drawn. Returns TRUE when the phase is over.
BOOL GameState_UpdatePhase(void) {
    BOOL one = TRUE;
    u32 zero = 0;
    u8 i;
    int slot;

    if (gameState.active != 0) {
        gameState.periodicFlag = zero;
        if (gameState.phaseFlags >= 0xf0) {
            return one;
        }
        if (gameState.phaseFlags & 0x10) {
            gameState.phaseTimer = one;
        }
        if (gameState.phaseFlags & 0x20) {
            for (i = 0; i < 4; i++) {
                gameState.playerCounters[i] = zero;
                gameState.kakeraCount[i] = zero;
                gameState.heldItems[i] = 9;
                gameState.health[i] = 0x28;
            }
            gameState.score = gameState.phaseTimer = gameState.unk_24 = zero;
            PlWorkClear();
        }
        if (gameState.phaseFlags & 0x40) {
            gameState.phaseTimer++;
        }
    } else if (gameState.unk_01 >= 5) {
        if (++gameState.phaseTimer == 3) {
            return one;
        }
        for (slot = zero; slot < gameState.playerCount; slot++) {
            gameState.heldItems[slot] = 9;
        }
    } else {
        gameState.phaseTimer++;
        switch (gameState.difficulty) {
        case 0:
            if (gameState.periodicFlag != 0) {
                return one;
            }
            isBossFloor();
            return FALSE;
        case 1:
            if (gameState.periodicFlag != 0) {
                return one;
            }
            isBossFloor();
            if (gameState.periodicFlag != 0) {
                gameState.unk_01 = 2;
            } else {
                shuffleStage();
            }
            return FALSE;
        case 2:
            if (gameState.periodicFlag != 0 && gameState.unk_01 == 2) {
                return one;
            }
            shuffleStage();
            if (isBossFloor()) {
                gameState.unk_01 = 0xff;
                if (gameState.phaseTimer == 0xb) {
                    gameState.unk_01 = 2;
                }
                if (gameState.unk_01 == 2) {
                    return FALSE;
                }
                shuffleStage();
                while (gameState.unk_01 == 2 || (gameState.usedPickMask & (one << gameState.unk_01))) {
                    shuffleStage();
                }
                gameState.usedPickMask |= (u8)(one << gameState.unk_01);
            }
            break;
        }
    }
    return FALSE;
}
