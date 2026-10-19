#include "engine/functions.h"
#include "global.h"

// Shared sound helper (original name GufuFuyusnd). Address -> name:
//   0x02060a70 GufuFuyusnd (original name)

typedef struct Vars_Gufu {
    /* 00 */ u8 unk_00[0x7f];
    /* 7f */ u8 sfxTimer; // counts down; when it is 0 the sound is played and the timer is reset to 0x3c
} Vars_Gufu;

ARM void GufuFuyusnd(Entity *e) {
    if (VARS(Vars_Gufu, e)->sfxTimer != 0) {
        VARS(Vars_Gufu, e)->sfxTimer--;
        return;
    }
    VARS(Vars_Gufu, e)->sfxTimer = 0x3c;
    EnqueueSFX(0xaf);
}
