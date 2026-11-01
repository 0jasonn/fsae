#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "enemy/em1b.h"

// Actor em1b (original names from the debug build): Em1b, em1b_type0, type0_normal, type0_damage.
// Later units: em1b_type0_init, type0_move, em1b_type1, type1_init, type1_move (in this same address range).

extern EntityFunc em1b_typeActions[];        // em1b_typeActions, indexed by e->type
extern EntityFunc em1b_type0Actions[];       // em1b_type0Actions, EnemyFunctionHandler table
extern EntityFunc em1b_type0NormalActions[]; // em1b_type0NormalActions, indexed by e->action

void ofsset(Entity *e);

void Em1b(Entity *e) {
    em1b_typeActions[e->type](e);
}

void em1b_type0(Entity *e) {
    Vars_Em1b *vars = VARS(Vars_Em1b, e);

    vars->savedX = e->x.HALF.HI;
    vars->savedY = e->y.HALF.HI;
    EnemyFunctionHandler(e, em1b_type0Actions);
    ofsset(e);
}

void type0_normal(Entity *e) {
    em1b_type0NormalActions[e->action](e);
}

void type0_damage(Entity *e) {
    Vars_Em1b *vars = VARS(Vars_Em1b, e);

    e->child->iframes = e->iframes;
    vars->child1->iframes = e->iframes;
    vars->child2->iframes = e->iframes;
    GenericKnockback(e, em1b_type0Actions);
}
