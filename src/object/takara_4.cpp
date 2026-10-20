#include "engine/functions.h"
#include "game/stageseldecls.h"

// Treasure chest module, fourth unit. Address -> name (dsd names without an original name):
//   0x0207c180 takara_spawnChance, 0x0207c1e0 takara_setKind15

// takara_spawnChance, 0x0207c180. Opens the kind 0x0f chest with a random chance while data_0212c54c is zero;
// otherwise picks a random kind.
ARM void takara_spawnChance(int unused, Entity *e, u16 value) {
    if (data_0212c54c == 0 && (Random() & 1) != 0) {
        set_takara2(0xf, value, e);
        return;
    }
    {
        u8 kind = GetRandomTakara(data_02117a68, e->type);
        set_takara2(kind, value, e);
    }
}

// takara_setKind15, 0x0207c1e0. Sets the chest of kind 0x0f.
ARM void takara_setKind15(int unused, Entity *e, u16 value) {
    set_takara2(0xf, value, e);
}

// GetRandomTakara, 0x0207c1fc. Random entry of the table list[data_0212c81c[type]].
ARM u8 GetRandomTakara(u8 **list, u8 type) {
    return list[data_0212c81c[type]][Random() & 0x1f];
}
