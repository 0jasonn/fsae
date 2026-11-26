#include "engine/functions.h"
#include "engine/player.h"
#include "game/cockpitdata.h"
#include "game/mathutil.h"

// Module item: AddRupee (between add_sub and AddKey).

// Adds delta rupees (negative to pay, never below 0): updates the cockpit gain/loss counters and sound, then takes
// the amount from the entity owner's counter or, past its end, one rupee at a time round-robin from the players.

void AddRupee(Entity *e, s32 delta) {
    s32 amount;
    u8 i;
    u32 idx;
    u8 tries;
    u16 remaining;
    amount = (delta < 0 && (s32)gameState.score + delta < 0) ? -gameState.score : delta;
    if (gameState.unk_24 != 0 && (gameState.unk_24 & 0x80) == 0 && delta > 0) {
        delta = (s16)(delta << 1);
        amount = delta;
        SoundReq(0x8f);
    } else {
        SoundReq(8);
    }
    cockpitState.redraw = 1;
    if (amount >= 0) {
        cockpitState.rupeeGain += amount;
        cockpitState.rupeeGainTimer = 0x78;
        if (cockpitState.rupeeGain > 9999) {
            cockpitState.rupeeGain = 9999;
        }
        if (cockpitState.rupeeLossTimer == 0) {
            cockpitState.rupeeShown = cockpitState.rupeeGain;
        }
    } else {
        cockpitState.rupeeGainTimer = 0;
        cockpitState.rupeeGain = 0;
        cockpitState.rupeeLoss += amount;
        cockpitState.rupeeLossTimer = 0x3c;
        if (cockpitState.rupeeLoss < -9999) {
            cockpitState.rupeeLoss = -9999;
        }
        cockpitState.rupeeShown = cockpitState.rupeeLoss;
    }
    if (delta < 0 && gameState.score == 0) {
        return;
    }
    if (delta + data_0212c7d4[e->type] < 0) {
        remaining = abs_s32(delta) - data_0212c7d4[e->type];
        data_0212c7d4[e->type] = 0;
        do {
            tries = 4;
            do {
                gameState.unk_25 = (gameState.unk_25 + 1) & 3;
                idx = gameState.unk_25;
                if (gameState.playerCounters[idx] != 0) {
                    gameState.playerCounters[idx]--;
                    break;
                }
                tries--;
            } while (tries != 0);
            remaining--;
        } while (remaining != 0);
    } else {
        data_0212c7d4[e->type] = add_sub(data_0212c7d4[e->type], delta, 99999);
    }
    gameState.score = 0;
    for (i = 0; i < gameState.playerCount; i++) {
        gameState.score += gameState.playerCounters[i];
    }
    pinch_bgm_check();
}
