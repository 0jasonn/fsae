#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set66.h"

// Set66 type1 (module set66, second unit). Address -> name:
//   0x02075240 set66_type1 (original name; dispatches on e->action)
//   0x0207525c rr_type1_init_07525c (dsd name, original type1_init)
//   0x0207528c type1_charload (original name)
//   0x020752f8 rr_type1_move (dsd name, original type1_move)
//   0x0207543c rr_type1_wait_07543c (dsd name, original type1_wait)
//   0x020754ac rr_type1_vanish (dsd name, original type1_vanish)
//   0x02075528 rr_poscopy (original name)
//   0x0207553c plStCheck (original name)

ARM void set66_type1(Entity *e) {
    set66_type1Actions[e->action](e);
}

ARM void rr_type1_init_07525c(Entity *e) {
    e->action = 1;
    e->timer = 0x1e;
    e->spriteSettings.b14 = 3;
    InitAnimationForceUpdate(e, 0);
}

ARM void type1_charload(Entity *e) {
    Vars_Set66 *v;

    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (VGroupLoadWait(e)) {
        return;
    }
    v = VARS(Vars_Set66, e);
    func_020845b0((u32)(0x6400000 + ((v->vramSlot + 1) << 9)),
                  KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x9a) + 0x200, 0x100);
    e->action = 2;
    e->spriteSettings.b0 = 1;
}
