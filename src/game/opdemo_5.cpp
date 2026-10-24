#include "engine/functions.h"
#include "engine/misc_d.h"
#include "game/scene_d.h"
#include "game/opdemo_c.h"
#include "global.h"

// bunshin_set (symbol bunshin_set): sets the animation bounds of the four player entities and plays sound 0x205.
extern "C" void bunshin_set(void);

ARM void bunshin_set(void) {
    u8 i;
    data_02134924 |= 8;
    i = 0;
    do {
        ObjAnimMoveSet(data_0212ceb0[i].entity, data_02104a30[i], 0x78);
        i++;
    } while (i < 4);
    SoundReq(0x205);
}
