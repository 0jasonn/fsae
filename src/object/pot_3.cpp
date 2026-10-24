#include "engine/functions.h"
#include "global.h"

// Pot actor, delete (module pot). Address -> name:
//   0x0205f0a8 throw_delete (removes the entity)
//   (throw_hold at 0x0205f0b4 is in the next unit)

ARM void throw_delete(Entity *e) {
    PutObjWork(e);
}
