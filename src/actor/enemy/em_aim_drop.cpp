#include "engine/functions.h"
#include "engine/player.h"
#include "actor/enemy/enemycommon.h"
#include "global.h"

// EmGetAimPl (0x02045eb4): picks the enemy's aim target. Starts at a random player and walks round the players (in a
// random direction) until it finds one that is not pressing the pause key, has an entity and is alive; falls back to
// player 0's entity.
Entity *EmGetAimPl(void) {
    s8 index = Random() % gameState.playerCount;
    s8 step = (Random() & 1) ? 1 : -1;
    s8 tries;
    for (tries = 0; tries < gameState.playerCount; tries++) {
        PlayerData *player = &playerWork[index];
        if (!(playerKeysPrev[index] & 0x1000) && player->entity != NULL && player->entity->health != 0) {
            return player->entity;
        }
        index += step;
        if (index == gameState.playerCount) {
            index = 0;
        }
        if (index == -1) {
            index = gameState.playerCount - 1;
        }
    }
    return playerWork[0].entity;
}

// EmBossDropRupee (0x02045f8c): a boss drops four set-work objects around e. kind (clamped to 7) selects a row of four
// object ids in the boss drop table; the objects are created starting at a random column of the row, each one aimed
// 2 direction steps further round, and are placed at e's position plus the given offsets.
void EmBossDropRupee(Entity *e, u8 kind, s16 offsetX, s16 offsetY) {
    const u8 *row;
    u8 i;
    u8 column;
    u8 dropDirection;
    if (kind > 7) {
        kind = 7;
    }
    row = &data_020d41b0[kind * 4];
    column = Random() & 3;
    dropDirection = ((e->baseDirection ^ 0x10) - 3) & 0x1f;
    for (i = 0; i < 4; i++) {
        Entity *drop = GetSetWork(0, row[column], 1);
        if (drop != NULL) {
            drop->direction = dropDirection | 0x80;
            ObjPosCopyOfs32(e, drop, offsetX << 16, offsetY << 16);
        }
        column = (column + 1) & 3;
        dropDirection = (dropDirection + 2) & 0x1f;
    }
}
