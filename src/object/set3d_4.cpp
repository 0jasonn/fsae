#include "engine/functions.h"
#include "global.h"
#include "object/set3d.h"

// Set3d actor, fourth unit (module set3d). Address -> name:
//   0x0205d9c8 set3d_setWaitOne (renamed from set3d_setWaitOne)

typedef struct Vars_Set3d {
    /* 00 */ u8 unk_00[0x68];
    /* 68 */ u32 waitCount;
} Vars_Set3d;

ARM void set3d_setWaitOne(Entity *e) {
    VARS(Vars_Set3d, e)->waitCount = 1;
}
