#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Set11 actor (module set11). Address -> name:
//   0x020635bc Set11 (original name)

extern const EntityFunc data_020d9f70[]; // indexed by e->action
extern const u8 data_020d9f66[]; // hitbox
extern u16 scrollArgs[]; // affine source (scale x, scale y, rotation)
void func_02084180(Entity *e);

ARM void Set11(Entity *e) {
    data_020d9f70[e->action](e);
}
