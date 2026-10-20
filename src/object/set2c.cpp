#include "engine/functions.h"
#include "global.h"

// Set2c actor (module set2c). Address -> name:
//   0x0205a73c Set2c (dispatcher, named here after the other set actors; dsd name Set2c)
//   set2c_init at 0x0205a758 is in scratch/agentF/nonmatching/set2c_init.c
//   0x0205a798 set2c_wait (original name)

typedef struct Vars_Set2c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // ParseTypeBits(e->type2), tested against em12_typeMasks[e->areaIndex]
    /* 64 */ u32 flagMask; // flagBits[e->type], set or cleared in em12_typeMasks
} Vars_Set2c;

extern const EntityFunc set2c_actions[]; // set2c_actions, indexed by e->action
extern u32 em12_typeMasks[];
extern const u32 flagBits[]; // flagBits, indexed by e->type

ARM void Set2c(Entity *e) {
    set2c_actions[e->action](e);
}
