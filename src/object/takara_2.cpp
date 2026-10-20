#include "engine/functions.h"
#include "game/stageseldecls.h"

// Treasure chest module, second unit. Address -> name (dsd names without an original name):
//   0x0207bff8 takara_setFromWork, 0x0207c014 takara_spawnRandom

// takara_setFromWork, 0x0207bff8. Calls set_takara2 with the kind stored in the first work's byte 3.
ARM void takara_setFromWork(Entity *work, Entity *target, u16 value) {
    set_takara2(((u8 *)work)[3], value, target);
}

// takara_spawnRandom, 0x0207c014. Picks a random chest kind for the type of e and sets it up.
ARM void takara_spawnRandom(int unused, Entity *e, u16 value) {
    u8 kind = GetRandomTakara(data_02117a68, e->type);
    set_takara2(kind, value, e);
}
