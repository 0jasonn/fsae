#include "enemy/em2c.h"
#include "global.h"

ARM void em2c_type1(Entity *e) {
    if (e->action != 0 && V(e)->unk_7c->health == 0) {
        PutObjWork(e);
        return;
    }
    data_020d101c[e->action](e);
}
