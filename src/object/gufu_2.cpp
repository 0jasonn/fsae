#include "engine/functions.h"
#include "engine/misc_d.h"
#include "global.h"
#include "object/d_decls.h"

// Gufu hand and body actors (module gufu, second unit). Address -> name:
//   0x02074680 gufu_typeDispatch (provisional name; dispatches on e->type)
//   0x0207469c gufu_hand (original name; dispatches on e->action)
//   0x020746b8 gufu_hand_init (original name)
//   0x02074704 gufu_hand_move (original name)
//   0x0207478c gufu_body (original name; dispatches on e->action)
//   0x020747a8 gufu_body_init (original name)

extern const EntityFunc gufu_typeActions[]; // gufu_typeActions, indexed by e->type
extern const EntityFunc gufu_handActions[]; // gufu_handActions, indexed by e->action
extern const EntityFunc gufu_bodyActions[]; // gufu_bodyActions, indexed by e->action

ARM void gufu_typeDispatch(Entity *e) {
    gufu_typeActions[e->type](e);
}

ARM void gufu_hand(Entity *e) {
    gufu_handActions[e->action](e);
}

ARM void gufu_hand_init(Entity *e) {
    e->action++;
    e->unk_20 = 0x60;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b6 = 1;
    e->unk_1b = 0x9a;
    InitAnimationForceUpdate(e, 0);
}

ARM void gufu_hand_move(Entity *e) {
    Entity *child;

    UpdateAnimationSingleFrame(e);
    if (e->frame == 2) {
        e->frame = 0;
        data_021349c0[0x0d] = 1;
        SoundReq(0x204);
        SoundReq(0x202);
        return;
    }
    if (e->frame & 0x80) {
        data_021349c0[0x0d] = 2;
        child = GetSetWork(0x62, 1, 0);
        child->x.HALF.HI = 0x80;
        child->y.HALF.HI = 0x38;
        PutObjWork(e);
    }
}

ARM void gufu_body(Entity *e) {
    gufu_bodyActions[e->action](e);
}

ARM void gufu_body_init(Entity *e) {
    e->action++;
    e->unk_20 = 0x60;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b6 = 1;
    e->unk_1b = 0x9b;
    CallbackForJpeg((void *)0x6402c00, KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x1e6));
    InitAnimationForceUpdate(e, 1);
}
