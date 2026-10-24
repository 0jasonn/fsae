#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   set6c_init (0x0209de18); set6c_move (0x0209dec0) is parked in scratch/agentE/nonmatching/set6c_move.cpp

extern PlayerData *data_0212c53c;     // current player slot pointer
void set6c_move(Entity *e);

// set6c_init(OBJ_WORK_*) (0x0209de18): attaches the object to the current player's entity
ARM void set6c_init(Entity *e) {
    if (e->type == 0) {
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b16 = data_0212c53c->entity->type + 7;
        e->contactedEntity = data_0212c53c->entity;
    } else {
        e->spriteSettings.b0 = 2;
    }
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 1;
    e->timer = e->type2;
    e->action++;
    InitAnimationForceUpdate(e, 0);
    set6c_move(e);
}
