#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpitdata.h"

// Module item (original names from the debug build): AddRupeeKakera

// Counts one kakera for the entity's type and gives the telop for the collected count.
void AddRupeeKakera(Entity *e) {
    data_0212c830[e->type] += 1;
    SoundReq(0x8f);
    switch (data_0212c830[e->type]) {
    case 1:
        TelopRequest(0x515);
        telopRequest.params[0] = (u16)(e->type + 1);
        telopRequest.params[2] = 500;
        break;
    case 2:
    case 3:
        TelopRequest(0x516);
        telopRequest.params[0] = (u16)(e->type + 1);
        telopRequest.params[1] = (u16)(4 - data_0212c830[e->type]);
        break;
    case 4:
        cockpitState.kakeraTimer[e->type] = 0xf;
        break;
    }
}
