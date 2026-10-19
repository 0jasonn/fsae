#include "engine/functions.h"
#include "enemy/em2f.h"
#include "global.h"

ARM void getFiveMoveInfo(Entity *e) {
    V(e)->pathCursor = em2f_fivePaths[Random() & 3];
    V(e)->targetX = *V(e)->pathCursor++;
    V(e)->targetY = *V(e)->pathCursor++;
    e->direction = *V(e)->pathCursor++;
    V(e)->pathWait = 0x80;
}

ARM int gufuVitalCheck(Entity *e) {
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

ARM void gufuBindPls(void) {
    for (u8 i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].unk_14 = 1;
    }
    BindPlayers();
}
