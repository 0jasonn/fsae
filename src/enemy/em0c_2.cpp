#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0c, provisional names from their behaviour):
//   em0c_stop -> em0c_stop, em0c_wait -> em0c_wait

// Stop: when the flags at 0x74 are all inside the mask of the area, the action becomes 2.
ARM void em0c_stop(Entity *e) {
    u32 flags;
    u32 masked;

    flags = *(u32 *)((u8 *)e + 0x74);
    masked = flags & em12_typeMasks[e->areaIndex];
    if (flags == masked) {
        e->action = 2;
    }
}

// Wait: counts the subtimer down (action 3 at zero). Then the type decides: with bit 1 the object is put away when the
// mask of the area is inside the flags at 0x78; with type 1 the action returns to 1 when the flags at 0x74 leave the mask.
ARM void em0c_wait(Entity *e) {
    u32 flags;
    u32 masked;

    e->subtimer -= 1;
    if (e->subtimer == 0) {
        e->action = 3;
    }
    if ((e->type & 2) != 0) {
        flags = *(u32 *)((u8 *)e + 0x78);
        masked = flags & em12_typeMasks[e->areaIndex];
        if (flags != masked) {
            return;
        }
        PutObjWork(e);
        return;
    }
    if (e->type != 1) {
        return;
    }
    flags = *(u32 *)((u8 *)e + 0x74);
    masked = flags & em12_typeMasks[e->areaIndex];
    if (flags != masked) {
        e->action = 1;
    }
}
