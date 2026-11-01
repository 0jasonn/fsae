#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "actor/object/set0a.h"

// Set actor unit 5 (module set). Address -> name (original names):
//   0x02057c64 Set0a

extern const EntityFunc data_020d8794[];
extern u8 encntSharedState;

void Set0a(Entity *e) {
    if (VARS(SetVars, e)->retainFlag != 0 && encntSharedState == 0) {
        PutObjWork(e);
        return;
    }
    data_020d8794[e->action](e);
}
