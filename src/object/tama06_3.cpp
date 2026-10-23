#include "engine/functions.h"
#include "object/tama06.h"

// tama06 family, type0 position helpers, address -> name (original names from symbols.txt):
//   0x0207f31c type0PosSet, 0x0207f3f0 type0WaitPosSet, 0x0207f434 type0AttackPosSet

// type0PosSet, 0x0207f31c. Places the piece at the parent's position moved by the direction's scale and sine/cosine.
ARM void type0PosSet(Entity *e) {
    s32 scale;
    scale = data_020dce54[e->direction];
    e->x.HALF.HI = e->parent->x.HALF.HI + ((scale * trigTable[e->direction * 8]) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - 8 - ((scale * trigTable[e->direction * 8 + 0x40]) >> 8);
}
