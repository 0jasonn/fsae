#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Set51 actor, second unit (module set51). Address -> name:
//   0x0205ae5c set51_move (original name)

extern const s8 data_020d8a34[]; // vertical offset table, indexed by subtimer & 7
extern u16 data_0212c594;

ARM void set51_move(Entity *e) {
    Entity *contact;

    if (e->timer == 0) {
        e->spriteSettings.b0 = 1;
        contact = e->contactedEntity;
        e->x.HALF.HI = contact->x.HALF.HI;
        e->y.HALF.HI = contact->y.HALF.HI;
        e->z.HALF.HI = contact->z.HALF.HI + data_020d8a34[e->subtimer & 7];
        if ((data_0212c594 & 1) != 0) {
            e->subtimer++;
        }
    } else {
        e->timer--;
    }
}
