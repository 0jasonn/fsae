#include "engine/functions.h"
#include "global.h"

// Set50 actor, second unit (module set50). Address -> name:
//   0x02070194 moji_fall (original name; moji_init at 0x02070140 is in scratch/agentD/nonmatching)
//   0x020701b4 set50_nop (no-op action, provisional name)
// moji_init (0x02070140) is in scratch/agentD/nonmatching (not matched yet).

ARM void moji_fall(Entity *e) {
    if (func_02086044(e, 0x1600) == 0) {
        e->action = 2;
    }
}

ARM void set50_nop(Entity *e) {
}
