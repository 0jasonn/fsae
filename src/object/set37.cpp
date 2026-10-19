#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set37Table[];        // set37Table, indexed by action
extern const u8 set37Hitbox[];         // set37Hitbox
extern const s8 set37BobTable[];       // set37BobTable, indexed by timer & 7
extern u16 data_0212c5bc;              // frame counter

// Set37, 0x0206b5b8: runs the state function for the current action.
ARM void set37(Entity *e) {
    set37Table[e->action](e);
}
