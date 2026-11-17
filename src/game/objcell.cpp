#include "engine/functions.h"
#include "actor/object/cellcalls.h"
#include "game/objcell.h"
#include "global.h"

// CellPosGet (0x0204fd90): map cell index (6 bits per axis) of the entity position plus its hitbox offset,
// relative to the grid origin in mapState.
u16 CellPosGet(Entity *e) {
    const s8 *hitbox = (const s8 *)e->hitbox;
    u16 x = e->x.HALF.HI + hitbox[0] - mapState.originX;
    u16 y = e->y.HALF.HI + hitbox[1] - mapState.originY;
    return ((u32)x >> 4 & 0x3f) + ((u32)y << 2 & 0xfc0);
}
