#include "engine/functions.h"
#include "object/set0c.h"
#include "global.h"

// Set0c actor, type dispatch. Address -> name:
//   0x0205819c set0c_typeDispatch (provisional, set0c_typeActions[e->type](e))

ARM void set0c_typeDispatch(Entity *e) {
    set0c_typeActions[e->type](e);
}
