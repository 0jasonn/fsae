#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// eff_white_in_init, 0x0209ba50 (eff_white_in parked).

// eff_white_in_init(long) (0x0209ba50): adds a white in entry from 0x10000 downwards.
ARM void eff_white_in_init(s32 speed) {
    EffWork *work;

    *(s32 *)(data_0217c23c + 0xf50) = 0;
    work = effwk_add();
    work->kind = 7;
    work->level = 0x10000;
    work->speed = -speed;
    *(s32 *)(data_0217d23c + 0xf8) = work->level >> 12;
}
