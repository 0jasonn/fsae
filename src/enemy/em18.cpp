#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name, original function is em18_knockback):
//   em18_knockback -> em18_knockback

extern const u8 data_020d2968[]; // knockback function table of em18

// Knockback: passes the entity to the generic knockback with the em18 table.
ARM void em18_knockback(Entity *e) {
    GenericKnockback(e, data_020d2968);
}
