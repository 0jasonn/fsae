#include "engine/functions.h"
#include "global.h"
#include "object/effectdecls.h"

// Set49 family (module set49), 0x0206f680 .. 0x0206f69c (dispatcher).
// Address -> name: 0x0206f680 Set49

// Action table of Set49, set49Table
extern const EntityFunc set49Table[];

ARM void Set49(Entity *e) {
    set49Table[e->action](e);
}
