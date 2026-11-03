#include "engine/functions.h"
#include "global.h"

// Set2c actor (module set2c). Address -> name:
//   0x0205a758 set2c_init (original name)

typedef struct Vars_Set2c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;  // ParseTypeBits(e->type2)
    /* 64 */ u32 flagMask;  // flagBits[e->type]
} Vars_Set2c;
extern const u32 flagBits[]; // flagBits

void set2c_init(Entity *e) {
    e->action++;
    VARS(Vars_Set2c, e)->typeBits = ParseTypeBits(e->type2);
    VARS(Vars_Set2c, e)->flagMask = flagBits[e->type];
    e->subtimer = 0x1e;
}
