#include "engine/functions.h"
#include "global.h"

// Connect screen actors (module connect). Address -> name:
//   0x0205a42c connect_agb (original name)
//   connect_btn at 0x0205a480 is in scratch/agentF/nonmatching/connect_btn.c

ARM void connect_agb(Entity *e) {
    if (e->action != 0) {
        return;
    }
    e->action = 1;
    e->unk_1b = 0x9f;
    e->unk_20 = 0;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b6 = 3;
    e->x.HALF.HI = 0x78;
    e->y.HALF.HI = 0x48;
}
