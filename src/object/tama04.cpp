#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama03 and Tama04 actor families. Address -> name (original names from symbols.txt; dsd names without one):
//   0x0207e5c0 Tama03, 0x0207e5dc tama03_nop, 0x0207e5e0 tama03_nop2, 0x0207e5e4 Tama04,
//   0x0207e60c tama04_normal, 0x0207e628 tama04_damage

extern const EntityFunc data_020dcc1c[]; // Tama03 action table, indexed by e->action
extern const EntityFunc data_020dcc88[]; // tama04_normal action table, indexed by e->action
extern const EntityFunc data_020dcca4[]; // Tama04 action table, indexed by func_02085294

// Tama03, 0x0207e5c0. Runs the action of the current state.
ARM void Tama03(Entity *e) {
    data_020dcc1c[e->action](e);
}

// tama03_nop, 0x0207e5dc. Does nothing.
ARM void tama03_nop(void) {
}

// tama03_nop2, 0x0207e5e0. Does nothing.
ARM void tama03_nop2(void) {
}

// Tama04, 0x0207e5e4. Runs the state of the kind returned by func_02085294.
ARM void Tama04(Entity *e) {
    data_020dcca4[func_02085294()](e);
}

// tama04_normal, 0x0207e60c. Runs the current action.
ARM void tama04_normal(Entity *e) {
    data_020dcc88[e->action](e);
}

// tama04_damage, 0x0207e628. Removes the object when it is marked as dead (contact flag 0x80), otherwise starts the
// hajiki (flick) motion with the saved base direction.
ARM void tama04_damage(Entity *e) {
    if (e->contactFlags == 0x80) {
        PutObjWork(e);
        return;
    }
    e->direction = e->baseDirection;
    tama04_hajikiInit(e);
}
