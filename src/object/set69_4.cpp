#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set69_3.h"

// Set69 helper, fourth unit (module set69). Address -> name:
//   0x02076620 rr_plset (original name plset; places each player's entity for the rupee rush start)

ARM void rr_plset(Entity *e) {
    switch (data_0212c7c8.unk_0) {
    case 1:
        data_0212ceb0[0].entity->x.HALF.HI = 0x1f8;
        data_0212ceb0[0].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[0].entity->z.HALF.HI = 0;
        data_0212ceb0[0].entity->animationState = 0;
        break;
    case 2:
        data_0212ceb0[0].entity->x.HALF.HI = 0x1e6;
        data_0212ceb0[0].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[0].entity->z.HALF.HI = 0;
        data_0212ceb0[0].entity->animationState = 0;
        data_0212ceb0[1].entity->x.HALF.HI = 0x20a;
        data_0212ceb0[1].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[1].entity->z.HALF.HI = 0;
        data_0212ceb0[1].entity->animationState = 0;
        break;
    case 3:
        data_0212ceb0[0].entity->x.HALF.HI = 0x1d4;
        data_0212ceb0[0].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[0].entity->z.HALF.HI = 0;
        data_0212ceb0[0].entity->animationState = 0;
        data_0212ceb0[1].entity->x.HALF.HI = 0x1f8;
        data_0212ceb0[1].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[1].entity->z.HALF.HI = 0;
        data_0212ceb0[1].entity->animationState = 0;
        data_0212ceb0[2].entity->x.HALF.HI = 0x21c;
        data_0212ceb0[2].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[2].entity->z.HALF.HI = 0;
        data_0212ceb0[2].entity->animationState = 0;
        break;
    case 4:
        data_0212ceb0[0].entity->x.HALF.HI = 0x1c2;
        data_0212ceb0[0].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[0].entity->z.HALF.HI = 0;
        data_0212ceb0[0].entity->animationState = 0;
        data_0212ceb0[1].entity->x.HALF.HI = 0x1e6;
        data_0212ceb0[1].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[1].entity->z.HALF.HI = 0;
        data_0212ceb0[1].entity->animationState = 0;
        data_0212ceb0[2].entity->x.HALF.HI = 0x20a;
        data_0212ceb0[2].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[2].entity->z.HALF.HI = 0;
        data_0212ceb0[2].entity->animationState = 0;
        data_0212ceb0[3].entity->x.HALF.HI = 0x22e;
        data_0212ceb0[3].entity->y.HALF.HI = 0x1c8;
        data_0212ceb0[3].entity->z.HALF.HI = 0;
        data_0212ceb0[3].entity->animationState = 0;
        break;
    }
}
