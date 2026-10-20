#include "engine/functions.h"
#include "game/stageseldecls.h"

// Tama0c actor family, fourth unit. Address -> name (original names from symbols.txt; dsd name without one):
//   0x0207ce40 tama0c_fall, 0x0207ce9c tama0c_remove

// tama0c_fall, 0x0207ce40. Counts the timer down, then falls until the gravity update reports the ground; a type 0
// actor plays its effect before it is removed, others just advance their type.
ARM void tama0c_fall(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    if (e->type != 0) {
        e->type++;
    } else {
        EffectSet(e, 0xd, 0);
    }
    PutObjWork(e);
}

// tama0c_remove, 0x0207ce9c. Removes the actor.
ARM void tama0c_remove(Entity *e) {
    PutObjWork(e);
}
