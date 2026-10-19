#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/stopblock.h"

// Functions in this file (original names from the debug build):
//   sbKemuriSet

// Places the smoke (kemuri) object at the stop block's cell, in the layer bits of the key
ARM void sbKemuriSet(STOPBLOCK_WORK_ *block) {
    Entity *e;

    e = GetSetWork(0xf, 2, 0);
    if (e == 0) {
        return;
    }
    e->x.HALF.HI = ((((u32)block->key << 26) >> 22)) | 8;
    e->y.HALF.HI = ((block->key & 0xfc0) >> 2) | 8;
    e->layer = block->key & 0xc000;
    func_0208ae78(e);
}
