#include "engine/functions.h"
#include "actor/enemy/em2f.h"
#include "global.h"

void getFiveMoveInfo(Entity *e) {
    V(e)->pathCursor = em2f_fivePaths[Random() & 3];
    V(e)->targetX = *V(e)->pathCursor++;
    V(e)->targetY = *V(e)->pathCursor++;
    e->direction = *V(e)->pathCursor++;
    V(e)->pathWait = 0x80;
}

int gufuVitalCheck(Entity *e) {
    u8 hp = e->health;
    u8 difficulty = data_0212c7c8.difficulty;
    int result = 0;
    if (((const u8 *)em2f_vitalThresholds)[difficulty * 2] > hp) {
        result = 1;
        if (((const u8 *)em2f_vitalThresholds)[difficulty * 2 + 1] > hp) {
            result = 2;
        }
    }
    return result;
}

void gufuBindPls(void) {
    for (u8 i = 0; i < data_0212c7c8.playerCount; i++) {
        data_0212ceb0[i].unk_14 = 1;
    }
    BindPlayers();
}
