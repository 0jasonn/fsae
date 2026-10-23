#include "engine/functions.h"
#include "object/tama0f.h"
#include "object/tama_decls.h"

// tama0f family, address -> name (original names from symbols.txt):
//   0x0207de68 tama0f_demo, 0x0207df44 tama0f_ruppyset

// tama0f_demo, 0x0207de68. While subAction is set it falls and removes the actor on landing. Otherwise it counts the
// subtimer down, follows the parent's height and, when it is directly above the parent, faces it.
ARM void tama0f_demo(Entity *e) {
    u8 subAction;
    u8 subtimer;
    UpdateAnimationSingleFrame(e);
    subAction = e->subAction;
    if (subAction != 0) {
        if (UpdateGravity(e, 0x2000) != 0) {
            return;
        }
        PutObjWork(e);
        return;
    }
    subtimer = e->subtimer;
    e->subtimer = subtimer - 1;
    if (subtimer != 0) {
        if (e->z.HALF.HI > e->parent->z.HALF.HI) {
            e->z.HALF.HI = e->z.HALF.HI - 1;
        } else if (VARS(Vars_TamaParent, e->parent)->parentState == 4) {
            if (em2e_type4Hidden != 0) {
                e->subAction = subAction + 1;
            }
        }
        if (e->x.HALF.HI == e->parent->x.HALF.HI && e->y.HALF.HI == e->parent->y.HALF.HI + 8) {
            e->direction = ObjGetDir2(e, e->parent, 0, 8);
            MoveDir(e);
        }
    } else {
        PutObjWork(e);
    }
}

// tama0f_ruppyset, 0x0207df44. Spawns an item of the given kind and marks it with type2 1.
// The original debug name is ruppyset(OBJ_WORK_*, unsigned char); the symbols.txt name is kept.
ARM void tama0f_ruppyset(Entity *e, u8 kind) {
    Entity *item = ItemSet(e, kind);
    if (item != 0) {
        item->type2 = 1;
    }
}
