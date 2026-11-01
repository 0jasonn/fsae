#include "engine/functions.h"
#include "actor/object/set02.h"
#include "global.h"

// Set02 actor (module set02). Address -> name:
//   0x0205a090 Set02 (original name)

void Set02(Entity *e) {
    if (e->type >= 0x17) {
        set02_typeActions[e->type - 0x17](e);
    } else {
        set02_actions[e->action](e);
    }
}
