#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 body actions, second unit (module set58). Address -> name:
//   0x02073588 body_hikari (original name)
//   0x020735c8 body_wait (original name)
//   0x02073640 body_appearwait (original name)
//   0x020736cc body_move (original name)

ARM void body_hikari(Entity *e) {
    Entity *child;

    child = GetSetWork(0x58, 7, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, child, 0, 0x80000);
    e->action = 3;
}

ARM void body_wait(Entity *e) {
    Entity *child;

    if ((em12_typeMasks & 1) == 0) {
        return;
    }
    child = GetSetWork(0x58, 2, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopy(e, child);
    FadeSet(2, 4);
    SoundReq(0x218);
    e->action = 4;
    e->timer = 0x3c;
    e->spriteSettings.b0 = 1;
}

ARM void body_appearwait(Entity *e) {
    Entity *child;

    UpdateAnimationSingleFrame(e);
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    if (func_02081b64() != 0) {
        e->action = 5;
        e->timer = 0x78;
        e->subtimer = 0;
        return;
    }
    child = GetSetWork(0x58, 1, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, child, 0, -0x140000);
    e->action = 5;
    e->timer = 0x78;
    e->subtimer = 0;
}

ARM void body_move(Entity *e) {
    Entity *child;

    if (e->timer != 0) {
        e->timer--;
    } else {
        if (e->subtimer == 0 && (em12_typeMasks & 0x40)) {
            child = GetSetWork(0x58, 9, 0);
            if (child != NULL) {
                ObjPosCopyOfs32(e, child, 0, -0x4c0000);
                child->parent = e;
                e->subtimer = 1;
            }
        }
        if (V58(e)->unk_7c == 0) {
            if (func_02081b64() != 0) {
                em12_typeMasks |= 0x20;
                V58(e)->unk_7c = 1;
            }
        }
    }
    UpdateAnimationSingleFrame(e);
}
