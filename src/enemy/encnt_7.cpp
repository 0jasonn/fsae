#include "engine/functions.h"
// Implementer B, round 4: plbackatt (0x02043f00) and plfrontatt (0x02043f38).
// Both run the init function when initialised is clear, then housha0att when taken is clear.

#include "enemy/encnt.h"
#include "global.h"

ARM void plbackatt(EncntEntry *e, u16 index) {
    if (e->initialised == 0) {
        plbackinit(e, index);
    }
    if (e->taken == 0) {
        housha0att(e, index);
    }
}

ARM void plfrontatt(EncntEntry *e, u16 index) {
    if (e->initialised == 0) {
        plfrontinit(e, index);
    }
    if (e->taken == 0) {
        housha0att(e, index);
    }
}
