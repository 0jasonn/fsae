#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// Screen effect work entries (module eff): 0x0209ba94 eff_white_in

// Advances the white in; removes the entry once the level reaches 0.
int eff_white_in(void *work, s32 index) {
    EffWork *w = (EffWork *)work;
    s32 *brightness = &data_0217d334; // local pointer: keeps the global's address in its own register
    s32 ret = 0;
    s32 level = w->level;

    *brightness = level >> 12;
    w->level = level + w->speed;
    if (w->level <= 0) {
        *brightness = 0;
        effwk_del(work, index);
        ret = 1;
    }
    return ret;
}
