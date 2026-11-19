#include "engine/functions.h"
#include "actor/enemy/em13.h"
#include "global.h"

// em13_init (0x0203c27c): sets up a wizzrobe. An actor placed at the map origin asks for type 2; otherwise its position
// is converted into the cell base (cellX/cellY) plus the offset inside the cell (subX/subY) and the actor is put back in
// the middle of that cell. Then the wait time follows from the type and the first move is chosen.
void em13_init(Entity *e) {
    if (e->x.HALF.HI == 0 && e->y.HALF.HI == 0) {
        e->type2 = 2;
    } else {
        V(e)->cellX = ((e->x.HALF.HI & 0xfc0) >> 2) + mapState.originX + data_0213492c[e->areaIndex * 2];
        V(e)->subX = ((((u32)e->x.HALF.HI) << 26) >> 22) + 0x10;
        V(e)->cellY = ((e->y.HALF.HI & 0xfc0) >> 2) + mapState.originY + em12_spawnOffsetY[e->areaIndex * 2];
        V(e)->subY = ((((u32)e->y.HALF.HI) << 26) >> 22) + 0x10;
        e->x.HALF.HI = V(e)->cellX + (V(e)->subX >> 1);
        e->y.HALF.HI = V(e)->cellY + (V(e)->subY >> 1);
    }
    e->z.HALF.HI = -2;
    V(e)->waitFrames = (e->type2 + 1) * 0x1e;
    e->unk_2e = 5;
    e->hitbox = em13_hitbox;
    nextMove(e);
}
