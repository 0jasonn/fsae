#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (provisional name):
//   lobby_copyBounds (0x020b52f8)

// lobby_copyBounds(dst, src) (0x020b52f8, provisional name): sets dst to (0, 0, src->x, src->y) for the two halfword
// fields of src at +8 and +0xa
extern "C" void lobby_copyBounds(s16 *dst, const s16 *src);
ARM void lobby_copyBounds(s16 *dst, const s16 *src) {
    s16 w;
    s16 h;

    h = src[5];
    w = src[4];
    dst[0] = 0;
    dst[1] = 0;
    dst[2] = w;
    dst[3] = h;
}
