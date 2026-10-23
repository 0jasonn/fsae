#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Actor em1b (original names from the debug build): Em1b, em1b_type0, type0_normal, type0_damage.
// Later units: em1b_type0_init, type0_move, em1b_type1, type1_init, type1_move (in this same address range).

typedef struct Vars_Em1b {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 savedX;   // copied from x in em1b_type0, one per frame
    /* 72 */ u16 savedY;   // copied from y in em1b_type0
    /* 74 */ Entity *child1; // second part, set by em1b_type0_init
    /* 78 */ Entity *child2; // third part
} Vars_Em1b;

extern EntityFunc em1b_typeActions[];        // em1b_typeActions, indexed by e->type
extern EntityFunc em1b_type0Actions[];       // em1b_type0Actions, EnemyFunctionHandler table
extern EntityFunc em1b_type0NormalActions[]; // em1b_type0NormalActions, indexed by e->action

void ofsset(Entity *e);

ARM void Em1b(Entity *e) {
    em1b_typeActions[e->type](e);
}

ARM void em1b_type0(Entity *e) {
    Vars_Em1b *vars = VARS(Vars_Em1b, e);

    vars->savedX = e->x.HALF.HI;
    vars->savedY = e->y.HALF.HI;
    EnemyFunctionHandler(e, em1b_type0Actions);
    ofsset(e);
}

ARM void type0_normal(Entity *e) {
    em1b_type0NormalActions[e->action](e);
}

ARM void type0_damage(Entity *e) {
    Vars_Em1b *vars = VARS(Vars_Em1b, e);

    e->child->iframes = e->iframes;
    vars->child1->iframes = e->iframes;
    vars->child2->iframes = e->iframes;
    GenericKnockback(e, em1b_type0Actions);
}
