#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_a.h"

// heart_areaCheck, 0x0206b000 (original areaCheck(OBJ_WORK_*)): 1 if the entity is in the area of any connected player.
ARM int heart_areaCheck(Entity *e) {
    u16 i;
    i = 0;
    if ((s32)data_0212c7c8.unk_0 > 0) {
        do {
            if (func_02083ed8(e, data_0212ceb0[i].entity)) {
                return 1;
            }
            i++;
        } while ((s32)data_0212c7c8.unk_0 > (s32)i);
    }
    return 0;
}
