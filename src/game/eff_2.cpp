#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// eff_fade_in_init, 0x0209b90c (eff_fade_in and eff_fade_in2 parked).

// eff_fade_in_init(long) (0x0209b90c): adds a fade in entry starting at -0x10000.
ARM void eff_fade_in_init(s32 speed) {
    EffWork *work;

    *(s32 *)(data_0217c23c + 0xf50) = 0;
    work = effwk_add();
    work->kind = 4;
    work->level = -0x10000;
    work->speed = speed;
    *(s32 *)(data_0217d23c + 0xf8) = work->level >> 12;
}
