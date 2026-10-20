#include "engine/functions.h"
#include "game/stageseldecls.h"

// Treasure chest module, third unit. Address -> name (dsd names without an original name):
//   0x0207c0c8 takara_nop, 0x0207c0cc takara_spawnRandom2

// takara_nop, 0x0207c0c8. Does nothing (placeholder action).
ARM void takara_nop(void) {
}

// takara_spawnRandom2, 0x0207c0cc. Like takara_spawnRandom, with the second random table.
ARM void takara_spawnRandom2(int unused, Entity *e, u16 value) {
    u8 kind = GetRandomTakara(data_02117a28, e->type);
    set_takara2(kind, value, e);
}
