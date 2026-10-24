#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// eff_white_out_init, 0x0209b9cc (eff_white_out parked).

// eff_white_out_init(long) (0x0209b9cc): adds a white out entry from 0 upwards.
ARM void eff_white_out_init(s32 speed) {
    EffWork *work;

    *(s32 *)(data_0217c23c + 0xf50) = 0;
    work = effwk_add();
    work->kind = 6;
    work->level = 0;
    work->speed = speed;
    *(s32 *)(data_0217d23c + 0xf8) = work->level >> 12;
}
