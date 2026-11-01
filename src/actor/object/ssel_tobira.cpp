#include "engine/functions.h"
#include "global.h"
#include "actor/object/ss.h"
#include "actor/object/effectdecls.h"

// ssel_tobira family (module ssel_tobira), 0x0206f174 .. 0x0206f190 (dispatcher).
// Address -> name: 0x0206f174 ssel_tobira

// Action table of ssel_tobira, sselTobiraTable
extern const EntityFunc sselTobiraTable[];

void ssel_tobira(Entity *e) {
    sselTobiraTable[e->action](e);
}
