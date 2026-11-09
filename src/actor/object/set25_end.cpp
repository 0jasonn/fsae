#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// 0x0206672c set25_end (original name): smoke on odd frames until the countdown in subtimer ends, then the
// cell is redrawn, the screen shakes and the entity is removed.

void set25_end(Entity *e) {
    u8 timer = ++e->timer;
    if (timer < e->subtimer) {
        if (timer & 1) {
            breakSmokeSet(e);
        }
    } else {
        recell1(e);
        YureSet(8, 0);
        PutObjWork(e);
    }
}
