#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Pot actor, throw end (module pot). Address -> name:
//   0x0205f084 pot_throw_end (original name throw_end): clashes with the player that threw the pot

void pot_throw_end(Entity *e) {
    pot_clash(e, data_0212ceb0[e->type2].entity);
}

// Pot actor, delete (module pot). Address -> name:
//   0x0205f0a8 throw_delete (removes the entity)
//   (throw_hold at 0x0205f0b4 is in the next unit)

void throw_delete(Entity *e) {
    PutObjWork(e);
}

// Pot actor, hold check (module pot). Address -> name:
//   0x0205f0b4 throw_hold (original name)
//   (throw_holdoff at 0x0205f0e0 is in pot_4.cpp; pot_push at 0x0205f0f4 is parked)

void throw_hold(Entity *e) {
    // PlayerData byte at 0x05 (unk_03[2]) of the player that holds the pot: nonzero means it is still held
    if (data_0212ceb0[e->type2].specialState != 0) {
        return;
    }
    throw_holdoff(e);
}

// Pot actor, state reset (module pot). Address -> name:
//   0x0205f0e0 throw_holdoff (original name): sets the state to 1 and clears the sub action
//   (throw_hold at 0x0205f0b4 is in the previous unit; pot_clash at 0x0205f224 is in the next unit)

void throw_holdoff(Entity *e) {
    e->action = 1;
    e->subAction = 0;
}
