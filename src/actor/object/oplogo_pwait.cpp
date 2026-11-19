#include "engine/functions.h"
#include "global.h"
#include "engine/irq.h"

extern u8 data_0212c4dc;  // opening/title scene step
extern u8 localPlayerIndex;
#include "engine/effect_state.h"

// oplogo_pwait (0x02068714): "press button" prompt of the opening logo. The first call places the sprite; afterwards it
// shows the prompt (b0 = 2) while the button blink bit is set.
void oplogo_pwait(Entity *e) {
    if (0 == e->action) {
        e->action = 1;
        e->x.HALF.HI = 0x100;
        e->y.HALF.HI = 0xc0;
        e->unk_1b = 0x4e;
        e->unk_20 = 0xa0;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b6 = 2;
        e->spriteSettings.b16 = 7;
    } else {
        e->spriteSettings.b0 = 0;
        if (data_0212c4dc != 4) {
            return;
        }
        if (localPlayerIndex == 0 && (effectState.progress & 0x80)) {
            return;
        }
        if (frameState.frameCount & 0x10) {
            e->spriteSettings.b0 = 2;
        }
    }
}
