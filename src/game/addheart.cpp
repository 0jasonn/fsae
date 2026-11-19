#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/cockpitdata.h"

// AddHeart (0x02025d9c): adds amount (in eighths of a heart) to the health of the player entity e, clamped to the
// number of heart containers, mirrors it into the other player in single play and returns the new health. A heal
// plays the heart sound and, in wireless play, announces the full-health bonus once all players are full.
s32 AddHeart(Entity *e, s32 amount) {
    s16 newHealth;
    u8 i;
    u8 count;
    s32 allOk;
    void *app;
    u8 *singlePlay;

    newHealth = (s16)(e->health + amount);
    app = KnifeApp_getInstance();
    singlePlay = Knife_Single_SinglePlay_GetInstance();
    if (amount < 0) {
        if (playerWork[e->type].unk_07 & 0x80) {
            return e->health;
        }
        if (playerKeysPrev[e->type] & 0x1000) {
            return e->health;
        }
        if (KnifeApp_isWirelessMode(app) == 0) {
            if (singlePlay[1] != 0) {
                if (e->type != singlePlay[0]) {
                    return e->health;
                }
            } else if (e->type != singlePlay[0]) {
                return e->health;
            }
            if (playerWork[0].callState == 0 && playerWork[1].callState == 0 && playerWork[0].entity->health != 0 &&
                playerWork[1].entity->health != 0) {
            } else {
                return e->health;
            }
        }
    } else {
        if (KnifeApp_isWirelessMode(app) == 0) {
            if (playerWork[e->type].callState == 0 && playerWork[e->type ^ 1].callState != 0) {
                return e->health;
            }
        }
    }

    if (newHealth >= gameState.unk_64[e->type] * 8) {
        newHealth = (s16)(gameState.unk_64[e->type] * 8);
    } else if (newHealth < 0) {
        newHealth = 0;
    }
    e->health = (u8)newHealth;
    gameState.playerTimer60[e->type] = (u8)newHealth;

    if (KnifeApp_isWirelessMode(app) == 0) {
        if (newHealth <= 0 && singlePlay[1] == 0) {
            playerWork[e->type ^ 1].entity->health = 0x28;
            gameState.playerTimer60[e->type ^ 1] = 0x28;
        } else {
            playerWork[e->type ^ 1].entity->health = (u8)newHealth;
            gameState.playerTimer60[e->type ^ 1] = (u8)newHealth;
        }
    }

    if (amount < 0) {
        gameState.unk_24 = 0;
    } else {
        allOk = 1;
        func_02085f98(e, 7);
        if (gameState.unk_24 == 0) {
            count = gameState.playerCount;
            for (i = 0; i < count; i++) {
                if (gameState.playerTimer60[i] != gameState.unk_64[i] * 8) {
                    allOk = 0;
                    break;
                }
            }
            if (allOk != 0 && KnifeApp_isWirelessMode(app) != 0) {
                gameState.unk_24 = 1;
                SoundReq(0x3e);
                TelopRequest(0x3e9);
            }
        }
    }
    pinch_bgm_check();
    return e->health;
}
