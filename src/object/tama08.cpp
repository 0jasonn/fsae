#include "engine/functions.h"
#include "object/tama08.h"

// Tama08 family, address -> name (original names from symbols.txt):
//   0x0207f84c Tama08, 0x0207f874 tama08_normal, 0x0207f890 tama08_damage

// Tama08, 0x0207f84c. Runs the state table entry that func_02085294 picks.
ARM void Tama08(Entity *e) {
    data_020dcf74[func_02085294()](e);
}

// tama08_normal, 0x0207f874. Runs the action of the current state.
ARM void tama08_normal(Entity *e) {
    data_020dcf60[e->action](e);
}

// tama08_damage, 0x0207f890. A contact with exactly 0x80 removes the actor; otherwise it is bounced: action 4, the
// direction flipped by 0x10 and the speed and the z velocity set.
ARM void tama08_damage(Entity *e) {
    if (e->contactFlags == 0x80) {
        PutObjWork(e);
        return;
    }
    e->action = 4;
    e->direction = e->direction ^ 0x10;
    e->speed = 0x80;
    e->zVelocity = 0x12000;
    e->statusFlags = 0;
    InitAnimationForceUpdate(e, 8);
}
