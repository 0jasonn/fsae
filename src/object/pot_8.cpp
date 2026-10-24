#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Pot actor, clash with another entity (module pot). Address -> name:
//   0x0205f224 pot_clash (original name)
//   (pot_puton at 0x0205f250 is not done yet)

ARM void pot_clash(Entity *e, Entity *other) {
    Entity *effect = EffectSet(e, 5, 0x80);

    if (effect != NULL) {
        effect->parent = other;
    }
    PutObjWork(e);
}
