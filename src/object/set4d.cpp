#include "engine/functions.h"
#include "global.h"

// Set4d actor (module set4d). Address -> name:
//   0x0205e558 set4d_init
//   (set4d_move at 0x0205e580 is in the next unit)

typedef struct Vars_Set4d {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ const u8 *info; // GetInfoAdrs(areaIndex, type)
} Vars_Set4d;

ARM void set4d_init(Entity *e) {
    VARS(Vars_Set4d, e)->info = GetInfoAdrs(e->areaIndex, e->type);
    e->action = e->action + 1;
}
