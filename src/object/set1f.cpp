#include "engine/functions.h"
#include "object/set1f.h"
#include "global.h"

// Set1f actor (module set1f). Address -> name:
//   0x02059fbc Set1f (original name)

ARM void Set1f(Entity *e) {
    set1f_actions[e->action](e);
}
