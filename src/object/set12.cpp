#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"
#include "object/set12.h"

// Set12 actor (module set12). Address -> name:
//   0x020637f4 Set12 (original name)

ARM void Set12(Entity *e) {
    if (VARS(Vars_Set12, e)->isPresent != 0) {
        if (!(flagBits[e->type & 0x1f] & em12_typeMasks[e->areaIndex])) {
            VARS(Vars_Set12, e)->isPresent = 0;
        }
    }
    if (e->action != 4) {
        yukaCheck(e);
    }
    set12_stateTable[e->action](e);
    VARS(Vars_Set12, e)->requestBits = 0;
}
