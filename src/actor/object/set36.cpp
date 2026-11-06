#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdecls_a.h"
#include "actor/object/set36.h"

extern EntityFunc set36Table[];        // set36Table, indexed by action
extern void setrupee(Entity *e);       // setrupee, 0x0206b4dc (setrupee.cpp)

extern ScrollOrigin mapState;

// Set36, 0x0206b34c: runs the state function for the current action.
void Set36(Entity *e) {
    set36Table[e->action](e);
}
