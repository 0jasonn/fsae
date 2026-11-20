#include "engine/functions.h"
#include "global.h"
#include "actor/object/zeldafade.h"

#include "engine/effect_state.h"

// door_silver_fade, 0x020693fc: when the door-silver flag reaches 5, start the fade and count it up.
void door_silver_fade(Entity *e) {
    if (effectState.progress != 5) {
        return;
    }
    ZeldaFadeSet(e, 0);
    effectState.progress++;
}
