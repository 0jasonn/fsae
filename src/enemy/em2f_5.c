#include "enemy/em2f.h"
#include "global.h"

ARM void getFiveMoveInfo(Entity *e) {
    V(e)->unk_74 = data_020d1474[Random() & 3];
    V(e)->unk_78 = *V(e)->unk_74++;
    V(e)->unk_7a = *V(e)->unk_74++;
    e->direction = *V(e)->unk_74++;
    V(e)->unk_7e = 0x80;
}

ARM int gufuVitalCheck(Entity *e) {
    u8 hp = e->health;
    u8 difficulty = data_0212c7c8.unk_3;
    int result = 0;
    if (((const u8 *)data_020d1432)[difficulty * 2] > hp) {
        result = 1;
        if (((const u8 *)data_020d1432)[difficulty * 2 + 1] > hp) {
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
