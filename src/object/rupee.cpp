#include "engine/functions.h"
#include "object/plate.h"
#include "global.h"

// Rupee actor (module rupee). Address -> name:
//   0x020586e8 rupee_init (original name)
//   0x02058708 rupee_move (original name)
//   0x020587b0 rupee1 (original name)
//   0x020587dc rupee10 (original name)
//   0x02058808 rupee100 (original name)
//   0x02058834 rupee1000 (original name)
//   0x02058860 rupee10000 (original name)

ARM void rupee_init(Entity *e) {
    e->action++;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 0;
}

ARM void rupee_move(Entity *e, s8 dx, u32 divisor) {
    e->spriteSettings.b0 = 2;
    e->x.HALF.HI = e->parent->x.HALF.HI + dx - 1;
    e->y.HALF.HI = e->parent->y.HALF.HI + 4;
    if (e->parent->unk_23 >= 7) {
        e->y.HALF.HI += 5;
    }
    InitAnimationForceUpdate(e, (VPLATE(e->parent)->count / divisor) % 10 + 0xc);
    if (data_021349c0[0x27] != 0) {
        PutObjWork(e);
    }
}

ARM void rupee1(Entity *e) {
    if (e->action == 0) {
        rupee_init(e);
    }
    rupee_move(e, 0xc, 1);
}

ARM void rupee10(Entity *e) {
    if (e->action == 0) {
        rupee_init(e);
    }
    rupee_move(e, 0x6, 10);
}

ARM void rupee100(Entity *e) {
    if (e->action == 0) {
        rupee_init(e);
    }
    rupee_move(e, 0, 100);
}

ARM void rupee1000(Entity *e) {
    if (e->action == 0) {
        rupee_init(e);
    }
    rupee_move(e, -6, 1000);
}

ARM void rupee10000(Entity *e) {
    if (e->action == 0) {
        rupee_init(e);
    }
    rupee_move(e, -12, 10000);
}
