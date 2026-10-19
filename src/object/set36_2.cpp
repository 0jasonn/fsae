#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set36Table[];        // set36Table, indexed by action
extern void setrupee(Entity *e);       // setrupee, 0x0206b4dc (setrupee.cpp)

// Scroll origin used to turn screen position into a map position (data_0212c648, shared).
typedef struct ScrollOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 baseX;
    /* 1a */ u16 baseY;
} ScrollOrigin;
extern ScrollOrigin data_0212c648;

// Actor fields of the Set36 family, file-local.
typedef struct Vars_Set36 {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 unk_78;     // count of blinks left
    /* 79 */ u8 unk_79;
    /* 7a */ u8 unk_7a;
    /* 7b */ u8 unk_7b;
    /* 7c */ u16 mapPos;    // position on the map, from set36_init
    /* 7e */ u16 timer;
} Vars_Set36;

// set36_move, 0x0206b404
ARM void set36_move(Entity *e) {
    Vars_Set36 *v = VARS(Vars_Set36, e);
    if (func_02083ca8(v->mapPos, e->layer) != 0x4008) {
        return;
    }
    func_0208366c(0x4000, v->mapPos, e->layer);
    e->action = 2;
    v->unk_78 = 0;
    v->unk_7a = 0;
    v->timer = 0x3c;
    EnqueueSFX(0x98);
}
