#include "engine/functions.h"
#include "global.h"
#include "actor/object/set3d.h"

// Set3d actor, second unit (module set3d). Address -> name:
//   0x0205d0a0 set3d_initwait
//   (set3d_stalk at 0x0205d0ec is in scratch/agentF/nonmatching)

void set3d_initwait(Entity *e) {
    Vars_Set3d *vars = VARS(Vars_Set3d, e);

    if (e->z.HALF.HI == -0x20) {
        TelopRequest(0x44d);
        vars->waitCount = 0xa8c;
        e->action = 4;
    } else {
        e->z.WORD -= 0x8000;
    }
    settail(e);
}
