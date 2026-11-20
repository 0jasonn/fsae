#include "engine/functions.h"
#include "actor/object/coin.h"

void kirakira(Entity *e) {
    if (e->action == 0) {
        e->action++;
        e->unk_1b = 0x2a;
        e->unk_5e.b0 = 3;
        e->direction = 0x10;
        e->speed = 0x20;
        e->unk_20 = 0x3c;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b6 = 3;
        e->spriteSettings.b16 = 1;
        InitAnimationForceUpdate(e, 7);
    }
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if ((e->frame & 0x80) != 0) {
        PutObjWork(e);
    }
}
