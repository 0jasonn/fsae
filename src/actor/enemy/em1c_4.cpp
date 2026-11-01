#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "actor/enemy/em1c.h"

// Actor em1c, wait state setter (unit 4).
void em1c_waitSet(Entity *e) {
    e->action = 1;
    e->timer = 0x3c;
    e->subtimer = 0;
}
