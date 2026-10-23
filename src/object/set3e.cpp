#include "engine/functions.h"
#include "global.h"
#include "object/cellcalls.h"

// Set3e actor (module set3e). Address -> name:
//   0x0205d9d4 Set3e (original name), 0x0205d9f0 set3e_init
//   (set3e_init at 0x0205d9f0 is in scratch/agentF/nonmatching)

typedef struct Vars_Set3e {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 unk_64;
} Vars_Set3e;

extern const EntityFunc data_020d8c50[]; // state table indexed by e->action
extern const u8 data_020d8c48[];         // hitbox of the set3e actor

ARM void Set3e(Entity *e) {
    data_020d8c50[e->action](e);
}
