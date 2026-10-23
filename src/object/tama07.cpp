#include "engine/functions.h"
#include "object/tama07.h"

// Tama07 family, address -> name (original names from symbols.txt; the names of tama07_remove is a guess):
//   0x0207f488 Tama07, 0x0207f4b0 tama07_normal, 0x0207f4e8 tama07_damage
//   (tama07_init 0x0207f550 is parked in scratch/agentC/nonmatching; tama07_remove is in tama07_2.cpp)

// Tama07, 0x0207f488. Runs the state table entry that func_02085294 picks.
ARM void Tama07(Entity *e) {
    data_020dcf28[func_02085294()](e);
}

// tama07_normal, 0x0207f4b0. Drops the link to the parent once the parent is dead, then runs the action.
ARM void tama07_normal(Entity *e) {
    if (e->parent != 0) {
        if (e->parent->health == 0) {
            e->parent = 0;
        }
    }
    data_020dced4[e->action](e);
}

// tama07_damage, 0x0207f4e8. While the contact flags are 0x83 or less the actor is caught by the contacted actor (it
// becomes its child); otherwise it is removed through tama07_remove.
ARM void tama07_damage(Entity *e) {
    if (e->contactFlags <= 0x83) {
        e->action = 2;
        e->subtimer = 0;
        e->spriteSettings.b0 = 1;
        e->statusFlags = 0;
        e->z.HALF.HI = 0;
        e->child = e->contactedEntity;
        e->child->z.HALF.HI = 0;
        if (e->parent != 0) {
            VARS(Vars_Tama07Parent, e->parent)->carried = e->contactedEntity;
        }
        InitAnimationForceUpdate(e, 4);
        return;
    }
    tama07_remove(e);
}
