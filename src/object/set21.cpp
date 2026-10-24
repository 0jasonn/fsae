#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Set21 actor, dispatcher (module set21). Address -> name:
//   0x02065a78 Set21 (state table data_02115ad0 indexed by e->action)
//   (set21_init at 0x02065a94 and set21_move at 0x02065c40 are not done yet)

extern EntityFunc data_02115ad0[]; // state table indexed by e->action

ARM void Set21(Entity *e) {
    data_02115ad0[e->action](e);
}
