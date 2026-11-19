#include "engine/functions.h"
#include "global.h"
#include "actor/object/stick_actions.h"

// Stick actor of the rotating bar (module stick). Address -> name:
//   0x0206c0b0 stick_move (original name)

typedef struct Vars_StickParent {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 phase; // rotation counter of the bar (hidden below 8)
} Vars_StickParent;

// Follows the bar (its parent): hidden until the bar has started, then placed along the arm by the low bits of the
// phase and animated with the facing given by its high bits.
void stick_move(Entity *e) {
    u32 facing;
    u16 offset;
    Entity *parent = e->parent;

    if (VARS(Vars_StickParent, parent)->phase < 8) {
        e->spriteSettings.b0 = 0;
        return;
    }
    e->spriteSettings.b0 = 1;
    offset = (VARS(Vars_StickParent, parent)->phase - 8) & 7;
    switch (e->type) {
    case 0:
        e->y.HALF.HI = parent->y.HALF.HI - offset - 0x10;
        break;
    case 1:
        e->x.HALF.HI = parent->x.HALF.HI + offset + 0x11;
        break;
    case 2:
        e->y.HALF.HI = parent->y.HALF.HI + offset + 0x10;
        break;
    case 3:
        e->x.HALF.HI = parent->x.HALF.HI - offset - 0x11;
        break;
    }
    facing = (u16)((VARS(Vars_StickParent, e->parent)->phase - 8) >> 4);
    if (facing != e->animationState) {
        e->animationState = facing;
        InitAnimationForceUpdate(e, e->type + facing * 4 + 8);
    }
}
