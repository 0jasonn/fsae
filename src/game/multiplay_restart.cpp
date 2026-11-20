#include "engine/functions.h"
#include "game/multiplay.h"
#include "engine/data_0212c500.h"
#include "engine/disp_reset.h"
#include "game/clearbuf.h"
#include "game/player.h"
#include "game/randomset.h"
#include "global.h"

// multiplay_restart (0x02047564): starts the next floor of a multiplay game. The per-player state (counters, kakera,
// held item, health, hearts and the packed power/defense/speed counters of the nut bits) is restored from the saved
// record data_0212c5ec when a game is being continued (gameState.unk_8c) and saved into it otherwise; then the display,
// work buffers and scene are reset and the multiplay state byte advances.
void multiplay_restart(void) {
    int i;

    gameState.keys[0] = gameState.keys[1] = gameState.keys[2] = gameState.keys[3] = 0;
    gameState.targetX = gameState.targetY = 0;
    gameState.unk_6e = 1;
    gameState.unk_6d &= 1;
    gameState.frameCount = 0;
    gameState.unk_50[2] = 0;
    gameState.unk_26 = 0xffff;
    if (gameState.unk_8c != 0) {
        for (i = 0; i < 4; i++) {
            gameState.playerCounters[i] = data_0212c5ec.counters[i];
            gameState.kakeraCount[i] = data_0212c5ec.flag68[i];
            gameState.heldItems[i] = data_0212c5ec.timer58[i];
            gameState.health[i] = data_0212c5ec.timer60[i];
            gameState.maxHearts[i] = data_0212c5ec.maxHearts[i];
            playerWork[i].nutBits.b0 = data_0212c5ec.nutBits[i] & 3;
            playerWork[i].nutBits.b2 = (data_0212c5ec.nutBits[i] >> 2) & 3;
            playerWork[i].nutBits.b4 = (data_0212c5ec.nutBits[i] >> 4) & 3;
        }
        gameState.score = data_0212c5ec.score;
        gameState.unk_50[0] = data_0212c5ec.unk_50;
    } else {
        for (i = 0; i < 4; i++) {
            data_0212c5ec.counters[i] = gameState.playerCounters[i];
            data_0212c5ec.flag68[i] = gameState.kakeraCount[i];
            data_0212c5ec.timer58[i] = gameState.heldItems[i];
            data_0212c5ec.timer60[i] = gameState.health[i];
            data_0212c5ec.maxHearts[i] = gameState.maxHearts[i];
            data_0212c5ec.nutBits[i] = playerWork[i].nutBits.b0 | (playerWork[i].nutBits.b2 << 2) | (playerWork[i].nutBits.b4 << 4);
        }
        data_0212c5ec.score = gameState.score;
        data_0212c5ec.unk_50 = gameState.unk_50[0];
    }
    data_0212c558 = data_0212c540.flags = 0;
    data_0212c54c = 0;
    DispReset();
    RandomSetInit();
    ClearWorkBuffer();
    Scene_ResetOverlayState();
    MessageInitialize();
    TelopInitialize();
    MIi_CpuClearFast(0, data_021361a0, 0x1000);
    CalcHeartLevel();
    StopBlockInit();
    PlWorkReset();
    data_0212c500++;
    func_020827a8(6);
}
