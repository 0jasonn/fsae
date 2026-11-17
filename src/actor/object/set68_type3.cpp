#include "engine/functions.h"
#include "global.h"
#include "actor/object/set66.h"

// set68_type3 (0x02075984): starts hidden state (palette depends on type2) and plays the animation; whenever the
// animation reports frame 1 on a type2 0 actor it advances a 4 step timer and plays a sound at the start of each
// cycle. It is removed when bit 3 of the type masks is set.
void set68_type3(Entity *e) {
    if (e->action == 0) {
        e->spriteSettings.b0 = 1;
        e->timer = 0;
        e->spriteSettings.b14 = 3;
        u8 palette = e->type2 == 0 ? 3 : 2;
        e->action = 1;
        e->unk_5e.b0 = palette;
        InitAnimationForceUpdate(e, e->type2);
    }
    UpdateAnimationSingleFrame(e);
    if (e->type2 == 0 && e->frame == 1) {
        e->frame = 0;
        if (e->timer == 0) {
            SoundReq(0x21d);
        }
        e->timer = (e->timer + 1) & 3;
    }
    if (em12_typeMasks[0] & 8) {
        PutObjWork(e);
    }
}
