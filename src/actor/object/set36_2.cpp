#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdecls_a.h"
#include "actor/object/set36.h"

extern EntityFunc set36Table[];        // set36Table, indexed by action
extern void setrupee(Entity *e);       // setrupee, 0x0206b4dc (setrupee.cpp)

extern ScrollOrigin mapState;

// set36_move, 0x0206b404
void set36_move(Entity *e) {
    Vars_Set36 *v = VARS(Vars_Set36, e);
    if (GetCellKind(v->mapPos, e->layer) != 0x4008) {
        return;
    }
    func_0208366c(0x4000, v->mapPos, e->layer);
    e->action = 2;
    v->unk_78 = 0;
    v->unk_7a = 0;
    v->timer = 0x3c;
    EnqueueSFX(0x98);
}
