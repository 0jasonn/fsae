#include "engine/functions.h"
#include "global.h"
#include "actor/object/set36.h"
#include "actor/object/objdecls.h"
#include "actor/object/set36_actions.h"


// set36_init (0x0206b368): snaps the actor to the middle of its map cell, remembers the cell index and starts the
// animation of its type.
void set36_init(Entity *e) {
    Vars_Set36 *v = VARS(Vars_Set36, e);
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 0;
    e->x.HALF.HI = (e->x.HALF.HI & 0x3f0) + 8;
    e->y.HALF.HI = (e->y.HALF.HI & 0x3f0) + 8;
    v->mapPos = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
    func_0208366c(0x4000, v->mapPos, e->layer);
    InitAnimationForceUpdate(e, e->type);
}
