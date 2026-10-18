#include "Unknown/Object_02033708.h"
#include "global.h"

ARM void func_02034730(Entity *e, Entity *first) {
    func_0203464c(first, e, VL(first->unk_54)->unk_7c);
    Entity *second = first->unk_58;
    func_0203464c(second, first, VL(second->unk_54)->unk_7c);
    Entity *third = second->unk_58;
    func_0203464c(third, second, VL(third->unk_54)->unk_7c);
    Entity *last = third->unk_58;
    func_0203464c(last, third, VL(last)->unk_7c);
    func_02050390(last, VC(last)->unk_70, 0, 1);
}

ARM void func_020347a8(Entity *e) {
    Entity *obj = func_0204bd80(0x2c);
    if (obj == NULL) {
        return;
    }
    obj->unk_0a = 4;
    obj->unk_17 = e->unk_17;
    func_0205031c(e, obj);
}
