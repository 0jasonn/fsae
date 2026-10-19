#include "engine/functions.h"
#include "global.h"
#include "object/setmisc.h"

// Set6b actor, second unit (module set6b). Address -> name:
//   0x020613b4 set6b_move, 0x0206140c set6b_tidimu (original names)

extern s16 scrollArgs[3];
void func_02085934(Entity *e, u8 mode);
void func_020859a0(Entity *e, u8 a, u8 b);

ARM void set6b_move(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
    } else {
        e->action++;
        CockpitOff();
        SoundReq(0xad);
    }
    if (e->type == 0) {
        func_02085934(e, 3);
    } else {
        UpdateAnimationSingleFrame(e);
    }
}


ARM void set6b_tidimu(Entity *e) {
    int next;

    if (e->type == 0) {
        func_02085934(e, 3);
    } else {
        UpdateAnimationSingleFrame(e);
    }
    if (e->timer < 0xfc) {
        next = e->timer + 4;
        e->timer = (u8)next;
        scrollArgs[1] = (next & 0xff) + 0x100;
        scrollArgs[0] = scrollArgs[1];
        scrollArgs[2] = 0;
        ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
        e->z.HALF.HI = e->timer >> 4;
    } else {
        func_02085d34(e);
        PutObjWork(e);
    }
}
