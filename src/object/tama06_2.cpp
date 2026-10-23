#include "engine/functions.h"
#include "object/tama06.h"

// tama06 family (type1 and type2 pieces), address -> name (original names from symbols.txt):
//   0x0207f120 tama06_type1, 0x0207f13c tama06_type1_init, 0x0207f180 tama06_type1_move,
//   0x0207f230 tama06_type2, 0x0207f24c tama06_type2_init
//   (tama06_type2_move 0x0207f290 is parked in scratch/agentC/nonmatching)

// tama06_type1, 0x0207f120. Runs the action of the current state.
ARM void tama06_type1(Entity *e) {
    data_020dce04[e->action](e);
}

// tama06_type1_init, 0x0207f13c. Starts action 1 with z -4 and the sprite priority 3, then moves the piece.
ARM void tama06_type1_init(Entity *e) {
    e->action = 1;
    e->z.HALF.HI = 1 - 5;
    e->unk_5e.b0 = 3;
    func_0208ae78(e);
    InitAnimationForceUpdate(e, 1);
    tama06_type1_move(e);
}

// tama06_type1_move, 0x0207f180. Places the piece relative to the parent: by the offset table of the parent's frame
// and animation, or by the 6-entry table while the parent is in action 4.
ARM void tama06_type1_move(Entity *e) {
    Entity *parent;
    parent = e->parent;
    if (parent->action != 4) {
        e->x.HALF.HI = parent->x.HALF.HI + data_020dce74[parent->frame + parent->animationState * 8];
        e->y.HALF.HI = parent->y.HALF.HI + data_020dce74[parent->frame + parent->animationState * 8 + 1];
    } else {
        e->x.HALF.HI = parent->x.HALF.HI + data_020dce3c[parent->animationState * 6 + (parent->frame & 0xf)];
        e->y.HALF.HI = parent->y.HALF.HI + data_020dce3c[parent->animationState * 6 + (parent->frame & 0xf) + 1];
    }
}

// tama06_type2, 0x0207f230. Runs the action of the current state.
ARM void tama06_type2(Entity *e) {
    data_020dce14[e->action](e);
}

// tama06_type2_init, 0x0207f24c. Same start as tama06_type1_init, then moves the piece as a type 2.
ARM void tama06_type2_init(Entity *e) {
    e->action = 1;
    e->z.HALF.HI = 1 - 5;
    e->unk_5e.b0 = 3;
    func_0208ae78(e);
    InitAnimationForceUpdate(e, 1);
    tama06_type2_move(e);
}
