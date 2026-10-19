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

// Set36, 0x0206b34c: runs the state function for the current action.
ARM void Set36(Entity *e) {
    set36Table[e->action](e);
}
