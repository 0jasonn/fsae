#include "engine/functions.h"
#include "global.h"
#include "actor/object/nameplate.h"

// Name plate actor (module nameplate). Address -> name:
//   0x0205b9a4 namePlate (original name), dispatches on e->action through namePlate_actions
//   namePlate_init at 0x0205b9c0 is in scratch/agentF/nonmatching/namePlate_init.c

extern const EntityFunc namePlate_actions[]; // namePlate_actions, indexed by e->action
extern u8 data_021349c0[];                   // byte 0x1b: flag that the name plate is shown

void namePlate(Entity *e) {
    namePlate_actions[e->action](e);
}
