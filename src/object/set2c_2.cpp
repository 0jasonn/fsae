#include "engine/functions.h"
#include "global.h"

// Set2c actor, second unit (module set2c). Address -> name:
//   0x0205a798 set2c_wait (original name)

typedef struct Vars_Set2c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // ParseTypeBits(e->type2), tested against em12_typeMasks[e->areaIndex]
    /* 64 */ u32 flagMask; // flagBits[e->type], set or cleared in em12_typeMasks
} Vars_Set2c;

extern u32 em12_typeMasks[];

ARM void set2c_wait(Entity *e) {
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
