#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpitdata.h"

// Module item (original names from the debug build): AddKey

// Adds one key of the entity's type and links the entity to the key work. Plays the key sound.
ARM void AddKey(Entity *e) {
    Entity *keyWork;

    keyWork = GetSetWork(0x4b, 0, 0);
    if (keyWork != 0) {
        keyWork->contactedEntity = e;
    }
    data_0212c824[e->type] += 1;
    data_0212c618[2] = 1;
    SoundReq(9);
}
