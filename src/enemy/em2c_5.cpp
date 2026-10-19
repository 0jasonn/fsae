#include "engine/functions.h"
#include "enemy/em2c.h"
#include "global.h"

ARM void kukiMgr(Entity *e, Entity *first) {
    kukiRangeSet(first, e, VL(first->parent)->lockValue);
    Entity *second = first->child;
    kukiRangeSet(second, first, VL(second->parent)->lockValue);
    Entity *third = second->child;
    kukiRangeSet(third, second, VL(third->parent)->lockValue);
    Entity *last = third->child;
    kukiRangeSet(last, third, VL(last)->lockValue);
    ObjPosCopyOfs32(last, VC(last)->chainA, 0, 1);
}

ARM void kukiDieDemoSet(Entity *e) {
    Entity *obj = GetEnemyWork(0x2c);
    if (obj == NULL) {
        return;
    }
    obj->type = 4;
    obj->timer = e->timer;
    ObjPosCopy(e, obj);
}
