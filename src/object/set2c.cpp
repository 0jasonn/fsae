#include "engine/functions.h"
#include "global.h"
#include "object/set2c.h"

// Set2c actor (module set2c). Address -> name:
//   0x0205a73c Set2c (dispatcher, named here after the other set actors; dsd name Set2c)
//   set2c_init at 0x0205a758 is in scratch/agentF/nonmatching/set2c_init.c
//   0x0205a798 set2c_wait (original name)

extern const EntityFunc set2c_actions[]; // set2c_actions, indexed by e->action
extern u32 em12_typeMasks[];
extern const u32 flagBits[]; // flagBits, indexed by e->type

void Set2c(Entity *e) {
    set2c_actions[e->action](e);
}
