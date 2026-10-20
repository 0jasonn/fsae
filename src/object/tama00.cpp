#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama00 actor family, first unit. Address -> name (original names from symbols.txt):
//   0x0207c7c8 Tama00, 0x0207c7f0 tama00_normal, 0x0207c80c tama00_damage

extern const EntityFunc data_020dc9c4[]; // Tama00 action table (indexed by the value of func_02085294)
extern const EntityFunc data_020dc970[]; // tama00_normal action table, indexed by e->action

// Tama00, 0x0207c7c8. Runs the state of the kind returned by func_02085294.
ARM void Tama00(Entity *e) {
    data_020dc9c4[func_02085294()](e);
}

// tama00_normal, 0x0207c7f0. Runs the current action.
ARM void tama00_normal(Entity *e) {
    data_020dc970[e->action](e);
}

// tama00_damage, 0x0207c80c. Removes the object when it is marked as dead (contact flag 0x80), otherwise starts the
// hajiki (flick) motion with the saved base direction.
ARM void tama00_damage(Entity *e) {
    if (e->contactFlags == 0x80) {
        PutObjWork(e);
        return;
    }
    e->direction = e->baseDirection;
    tama00_hajikiInit(e);
}

extern const u8 data_020dc968[]; // hitbox of the tama00 actor
