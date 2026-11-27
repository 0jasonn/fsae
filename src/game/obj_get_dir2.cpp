#include "engine/functions.h"
#include "actor/enemy/em0f_2.h"

// ObjGetDir2() (0x0204fdfc): direction from e to target's position offset by (offsetX, offsetY); only the low bytes
// of the two offsets are used (signed).
// The ROM code is unoptimised: all four argument registers are spilled, the offsets are read back from their stack
// slots and every value sits in a callee-saved register with no scheduling. Only optimization level 0 reproduces it
// (scheduling off, peephole off or levels 1-3 do not); the address-taken parameters give the spill.
#pragma push
#pragma optimization_level 0
u8 ObjGetDir2(Entity *e, Entity *target, s32 offsetX, s32 offsetY) {
    s16 targetX = target->x.HALF.HI + *(s8 *)&offsetX;
    s16 targetY = target->y.HALF.HI + *(s8 *)&offsetY;
    return CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, targetX, targetY);
}
#pragma pop
