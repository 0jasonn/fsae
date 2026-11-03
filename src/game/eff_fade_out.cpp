#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// Screen effect work entries (module eff): 0x0209b8c0 eff_fade_out

// Advances the fade out; removes the entry once the level reaches -1.0.
int eff_fade_out(void *work, s32 index) {
    EffWork *w = (EffWork *)work;
    s32 *brightness = &data_0217d334; // local pointer: keeps the global's address in its own register
    s32 ret = 0;
    s32 level = w->level;

    *brightness = level >> 12;
    level += w->speed;
    w->level = level;
    if (level <= -0x10000) {
        *brightness = -16;
        effwk_del(work, index);
        ret = 1;
    }
    return ret;
}
