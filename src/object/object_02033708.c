#include "object/object_02033708.h"
#include "global.h"

ARM void func_02033708(Entity *e) {
    if (e->action != 0 && V(e)->unk_7c->health == 0) {
        DeleteEntity(e);
        return;
    }
    data_020d101c[e->action](e);
}
