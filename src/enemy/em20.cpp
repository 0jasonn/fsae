#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name, original function is em20_knockback):
//   em20_knockback -> em20_knockback

extern const u8 em20_stateTable[]; // knockback function table of em20

// Knockback: passes the entity to the generic knockback with the em20 table.
ARM void em20_knockback(Entity *e) {
    GenericKnockback(e, em20_stateTable);
}
