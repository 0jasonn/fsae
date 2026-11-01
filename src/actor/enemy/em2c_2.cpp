#include "engine/functions.h"
#include "actor/enemy/em2c.h"
#include "global.h"

void em2c_type1(Entity *e) {
    if (e->action != 0 && V(e)->lockEntity->health == 0) {
        PutObjWork(e);
        return;
    }
    em2c_type1Actions[e->action](e);
}
