#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern u8 data_021349c0[];

// door_silver_fade, 0x020693fc: when the door-silver flag reaches 5, start the fade and count it up.
ARM void door_silver_fade(Entity *e) {
    if (data_021349c0[8] != 5) {
        return;
    }
    ZeldaFadeSet(e, 0);
    data_021349c0[8]++;
}
