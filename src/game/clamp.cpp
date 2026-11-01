#include "engine/functions.h"
#include "global.h"
#include "game/clamp_api.h"

// Functions in this file (original name from the debug build, plain in the ROM):
//   clamp_s8 (0x020ac898)

// clamp_s8(signed char&, signed char, signed char) (0x020ac898): limits the byte to [low, high]
void clamp_s8(signed char &value, signed char low, signed char high) {
    if (value < low) {
        value = low;
        return;
    }
    if (value > high) {
        value = high;
    }
}
