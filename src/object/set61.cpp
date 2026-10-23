#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Set61 actor (module set61). Address -> name:
//   0x02074508 Set61 (original name)

// Spawner for the Tama object of each connected player. Puts a fresh object work on
// the player's position and jitters it twice along x every 30 frames.
ARM void Set61(Entity *e) {
    u8 action;
    u8 i;
    Entity *tama;

    action = e->action;
    if (action != 0) {
        if (e->subtimer-- != 0) {
            return;
        }
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            tama = GetTamaWork(0xc);
            if (tama != NULL) {
                tama->x.HALF.HI = data_0212ceb0[i].entity->x.HALF.HI;
                tama->y.HALF.HI = data_0212ceb0[i].entity->y.HALF.HI;
                if (Random() & 1) {
                    tama->x.HALF.HI = tama->x.HALF.HI + (s16)(Random() & 0x1f);
                } else {
                    tama->x.HALF.HI = tama->x.HALF.HI - (s16)(Random() & 0x1f);
                }
                if (Random() & 1) {
                    tama->x.HALF.HI = tama->x.HALF.HI + (s16)(Random() & 0x1f);
                } else {
                    tama->x.HALF.HI = tama->x.HALF.HI - (s16)(Random() & 0x1f);
                }
            }
        }
        e->subtimer = 30;
        e->timer--;
        if (e->timer == 0) {
            PutObjWork(e);
        }
        return;
    }

    e->action = action + 1;
    e->timer = 1;
    e->subtimer = 30;
    if (e->type == 0) {
        e->timer = e->timer + 1;
        if (Random() & 1) {
            e->timer++;
        }
    }
}
