#include "engine/functions.h"
#include "global.h"
#include "enemy/em23.h"
#include "enemy/em23_4.h"

// Functions in this file: em23_damage (0x0203fadc).

ARM void em23_damage(Entity *e) {
    if (e->type != 0) {
        e->action = 1;
    } else {
        e->action = 3;
        e->timer = 0x1e;
        e->statusFlags &= 0x7f;
    }
    if ((*(u16 *)&data_0212cee6[e->contactedEntity->type * 0x94] & 0x4000) == 0) {
        Entity *child = GetEnemyWork(0x23);
        if (child != NULL) {
            Entity *contacted;
            child->type = e->type;
            child->type2 = 1;
            contacted = e->contactedEntity;
            child->child = contacted;
            *(u16 *)&data_0212cee6[contacted->type * 0x94] |= 0x4000;
        }
    }
    GenericKnockback(e, em23_stateTable);
}
