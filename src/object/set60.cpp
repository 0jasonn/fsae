#include "engine/functions.h"
#include "global.h"
#include "object/set58.h"

// Set60 actor (module set60). Address -> name:
//   0x02074418 Set60 (provisional name; dispatches on e->action)
//   0x02074434 set60_init (original name)
//   0x02074460 set60_move (original name)

extern const EntityFunc set60_actions[]; // set60_actions, indexed by e->action

ARM void Set60(Entity *e) {
    set60_actions[e->action](e);
}

ARM void set60_init(Entity *e) {
    e->action++;
    e->spriteSettings.b0 = 1;
    InitAnimationForceUpdate(e, e->unk_23);
}

ARM void set60_move(Entity *e) {
    Entity *child;

    if (e->type == 0) {
        UpdateAnimationSingleFrame(e);
    }
    if (e->type2 != 0) {
        e->spriteSettings.b0 = e->spriteSettings.b0 ^ 1;
    }
    if (!(e->timer & 0x80)) {
        if (e->timer != 0) {
            e->timer--;
            if (e->timer == 0) {
                PutObjWork(e);
            }
        } else if (e->frame & 0x80) {
            PutObjWork(e);
        }
    }
    child = e->child;
    if (child == NULL) {
        return;
    }
    e->x.WORD = child->x.WORD;
    e->y.WORD = child->y.WORD;
    e->z.WORD = child->z.WORD;
}
