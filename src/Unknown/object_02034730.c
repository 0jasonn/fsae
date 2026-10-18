#include "Unknown/Object_02033708.h"
#include "global.h"

ARM void func_02034730(Entity *e, Entity *first) {
    func_0203464c(first, e, VL(first->parent)->unk_7c);
    Entity *second = first->child;
    func_0203464c(second, first, VL(second->parent)->unk_7c);
    Entity *third = second->child;
    func_0203464c(third, second, VL(third->parent)->unk_7c);
    Entity *last = third->child;
    func_0203464c(last, third, VL(last)->unk_7c);
    PositionRelative(last, VC(last)->unk_70, 0, 1);
}

ARM void func_020347a8(Entity *e) {
    Entity *obj = CreateEnemy(0x2c);
    if (obj == NULL) {
        return;
    }
    obj->type = 4;
    obj->timer = e->timer;
    CopyPosition(e, obj);
}
