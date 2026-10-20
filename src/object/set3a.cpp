#include "engine/functions.h"
#include "global.h"

// Set3a actor (module set3a). Address -> name:
//   0x0205b730 Set3a (original name), dispatches on e->action through set3a_actions, PutObjWork while the fade is flagged

extern const EntityFunc set3a_actions[]; // set3a_actions, indexed by e->action
extern u8 data_02171d1c;                 // 1 while no fade partner is active (see ZeldaFadeFlagGet)

ARM void Set3a(Entity *e) {
    if (data_02171d1c == 1) {
        PutObjWork(e);
        return;
    }
    set3a_actions[e->action](e);
}
