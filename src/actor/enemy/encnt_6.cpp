#include "engine/functions.h"
// Implementer B, round 4: nopos (0x02043da8).

#include "actor/enemy/encnt.h"
#include "global.h"

void nopos(EncntEntry *e, u16 index) {
    e->x = 0;
    e->y = 0;
    encntState.timer = 1;
}
