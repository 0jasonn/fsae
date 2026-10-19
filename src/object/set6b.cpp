#include "engine/functions.h"
#include "global.h"
#include "object/setmisc.h"

// Set6b actor (module set6b). Address -> name:
//   0x0206127c Set6b (provisional: dispatches e->action through data_02115a4c)
//   0x02061298 set6b_init, 0x02061330 set6b_wait, 0x020613b4 set6b_move, 0x0206140c set6b_tidimu (original names)

extern const EntityFunc data_02115a4c[]; // indexed by e->action
extern s16 scrollArgs[3];
void func_02085934(Entity *e, u8 mode);
void func_020859a0(Entity *e, u8 a, u8 b);

ARM void Set6b(Entity *e) {
    data_02115a4c[e->action](e);
}


ARM void set6b_init(Entity *e) {
    u8 action;

    action = e->action;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b14 = 0;
    e->action = action + 1;
    e->spriteSettings.b30 = 0;
    e->timer = 0xfc;
    func_02085cf8(e);
    scrollArgs[1] = 0x200;
    scrollArgs[0] = scrollArgs[1];
    scrollArgs[2] = 0;
    ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
    e->z.HALF.HI = 0x10;
    if (e->type == 0) {
        func_020859a0(e, 0, 3);
        SoundReq(0x19);
    } else {
        InitAnimationForceUpdate(e, 0);
    }
}

