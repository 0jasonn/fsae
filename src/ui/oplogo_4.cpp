#include "engine/functions.h"
#include "global.h"
#include "engine/display_state.h"


void oplogo_fadeOff(Entity *e) {
    e->spriteSettings.b0 = 0;
}

void oplogo_info(Entity *e) {
    s16 offset = displayState.bg[0].scrollY;
    e->action = 1;
    if (data_0212c4dc == 4) {
        if (offset < -0x90) {
            offset = offset + 8;
        }
    } else {
        if (offset > -0xc0) {
            offset = offset - 8;
        }
    }
    displayState.bg[0].scrollY = offset;
}
