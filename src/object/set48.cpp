#include "engine/functions.h"
#include "global.h"
#include "object/effectdecls.h"

// Set48 family (module set48), 0x0206f3e4 .. 0x0206f400 (dispatcher).
// Address -> name: 0x0206f3e4 Set48

// Action table of Set48, set48Table
extern const EntityFunc set48Table[];

ARM void Set48(Entity *e) {
    set48Table[e->action](e);
}
