// Implementer B, round 4: nopos (0x02043da8).

#include "enemy/encnt.h"
#include "global.h"

ARM void nopos(EncntEntry *e, u16 index) {
    e->x = 0;
    e->y = 0;
    data_02134b48.timer = 1;
}
