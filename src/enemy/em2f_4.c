#include "enemy/em2f.h"
#include "global.h"

ARM void getStormMoveInfo(Entity *e) {
    V(e)->unk_74 = data_020d1448[Random() & 1];
    V(e)->unk_78 = *V(e)->unk_74++;
    V(e)->unk_7a = *V(e)->unk_74++;
    e->direction = *V(e)->unk_74++;
    V(e)->unk_7e = 0x80;
}

