#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"

// Bomb wall check (module bomb, third unit). Original name: BombWallCk(OBJ_WORK_*).

// Checks the 3x3 cells around the bomb (offsets of 0x10 in both directions) and, where a cell has kind 0x3c, spawns
// an object of type 0x49 at that cell.
ARM void BombWallCk(Entity *e) {
    s16 y;
    s32 offX;
    s32 offY;
    u8 row;
    u8 col;
    s16 x;
    Entity *child;

    offY = 0x10;
    for (row = 3; row != 0; row--) {
        y = offY;
        offX = 0x10;
        for (col = 3; col != 0; col--) {
            x = offX;
            if (func_02083ccc(e, x, y) == 0x3c) {
                child = GetSetWork(0x49, 0, 0);
                if (child != NULL) {
                    child->x.HALF.HI = e->x.HALF.HI + offX;
                    child->y.HALF.HI = e->y.HALF.HI + offY;
                }
            }
            offX -= 0x10;
        }
        offY -= 0x10;
    }
}
