#include "enemy/em2c.h"
#include "global.h"

ARM void kukiMgr(Entity *e, Entity *first) {
    kukiRangeSet(first, e, VL(first->parent)->unk_7c);
    Entity *second = first->child;
    kukiRangeSet(second, first, VL(second->parent)->unk_7c);
    Entity *third = second->child;
    kukiRangeSet(third, second, VL(third->parent)->unk_7c);
    Entity *last = third->child;
    kukiRangeSet(last, third, VL(last)->unk_7c);
    ObjPosCopyOfs32(last, VC(last)->unk_70, 0, 1);
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
