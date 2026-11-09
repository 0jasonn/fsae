#include "engine/functions.h"
#include "actor/object/objutil_5.h"

// 0x02050280 (original name ObjCdirSet, plain symbol). Maps the low bits of e->direction to the animation state,
// moving the b2 sprite bit with it. Returns the new animation state.
u32 ObjCdirSet(Entity *e) {
    u8 dir = e->direction;
    u32 cur = e->animationState;
    u32 word;
    u32 type;

    if (!(dir & 0x80)) {
        type = (dir & 0x1c) >> 2;
        if (type & 1) {
            if (((type - cur + 1) & 4) == 0) {
                return cur;
            }
        }
        cur = (dir >> 2) & 0x7e;
        word = *(u32 *)&e->spriteSettings;
        e->animationState = cur;
        if (cur <= 4) {
            word &= ~4;
            *(u32 *)&e->spriteSettings = word;
        } else {
            word |= 4;
            *(u32 *)&e->spriteSettings = word;
        }
    }
    return cur;
}
