#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em19.h"
#include "actor/enemy/em19_4.h"
// functions.h declares func_02084ac8/func_02084ae8 as returning u32; the ROM passes the result on without an and-mask,
// so the original return type is u8 (proposed shared change). Until functions.h is changed these calls go through
// a function pointer type with the u8 return.
typedef u8 (*Em19DirQuery)(Entity *e, int a);
typedef u8 (*Em19DirQueryTarget)(Entity *e, int a, Entity *target);

void em19_kyorokyoro2(Entity *e) {
    u8 r;
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        e->action = 6;
        e->animationState = 4;
        InitAnimationForceUpdate(e, 4);
        return;
    }
    r = ((Em19DirQuery)func_02084ac8)(e, 0xe);
    if ((r & 0x80) == 0) {
        return;
    }
    bgobj_moveset(e, r);
}
