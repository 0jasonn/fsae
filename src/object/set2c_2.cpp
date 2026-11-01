#include "engine/functions.h"
#include "global.h"
#include "object/set2c.h"

// Set2c actor, second unit (module set2c). Address -> name:
//   0x0205a798 set2c_wait (original name)

extern u32 em12_typeMasks[];

void set2c_wait(Entity *e) {
    u8 areaIndex;
    if (e->subtimer != 0) {
        e->subtimer--;
        return;
    }
    areaIndex = e->areaIndex;
    if (VARS(Vars_Set2c, e)->typeBits == (VARS(Vars_Set2c, e)->typeBits & em12_typeMasks[areaIndex])) {
        em12_typeMasks[areaIndex] &= ~VARS(Vars_Set2c, e)->flagMask;
        return;
    }
    em12_typeMasks[areaIndex] |= VARS(Vars_Set2c, e)->flagMask;
    if (e->timer != 0) {
        return;
    }
    PutObjWork(e);
}
