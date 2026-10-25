#include "engine/functions.h"
#include "global.h"
#include "enemy/delprt.h"

// Functions in this file: delprtInfo (0x0203dfa8). Toggles this entity's flag bits in its parent.

ARM void delprtInfo(Entity *e) {
    e->parent->type2 ^= (u8)flagBits[e->type2];
}
