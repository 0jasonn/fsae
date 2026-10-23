#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set26.h"

// Set26 actor and its item units (module set26). Address -> name:
//   0x02067890 Set26 (dispatcher by type2)
//   0x020678ac set26_type0, 0x020678c8 set26_type1 (dispatchers by action)
//   0x020678e4 itemget_type0_init

// Dispatcher: runs the handler for the current type2.
ARM void Set26(Entity *e) {
    set26_typeTable[e->type2](e);
}

// Dispatcher: runs the handler for the current action (type 0 items).
ARM void set26_type0(Entity *e) {
    set26_type0Table[e->action](e);
}

// Dispatcher: runs the handler for the current action (type 1 items).
ARM void set26_type1(Entity *e) {
    set26_type1Table[e->action](e);
}

// Init of a type 0 item: advances the action and sets the status, the pose and the hitbox.
ARM void itemget_type0_init(Entity *e) {
    u8 action;

    action = e->action;
    e->action = action + 1;
    e->statusFlags = 0x89;
    e->unk_40 = 0x38;
    e->poseId = 0x45;
    e->hitbox = itemget_type0_hitbox;
    e->unk_5c = 0xaa;
}
