#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set26.h"

// Item units of the set26 module (module itemget). Address -> name:
//   0x02067a3c itemget_type1_init

// Init of a type 1 item: advances the action and stores the type bits of the entity.
ARM void itemget_type1_init(Entity *e) {
    u8 action;

    action = e->action;
    e->action = action + 1;
    VARS(Vars_Set26, e)->typeBits = ParseTypeBits(e->type);
}
