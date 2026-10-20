#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/cockpitdata.h"

// Module item (original names from the debug build): AddRupeeKakera

// Counts one kakera for the entity's type and gives the telop for the collected count.
ARM void AddRupeeKakera(Entity *e) {
    data_0212c830[e->type] += 1;
    SoundReq(0x8f);
    switch (data_0212c830[e->type]) {
    case 1:
        TelopRequest(0x515);
        KAKERA_U32(8) = (u16)(e->type + 1);
        KAKERA_U32(0x10) = 500;
        break;
    case 2:
    case 3:
        TelopRequest(0x516);
        KAKERA_U32(8) = (u16)(e->type + 1);
        KAKERA_U32(0xc) = (u16)(4 - data_0212c830[e->type]);
        break;
    case 4:
        data_0212c63c[e->type] = 0xf;
        break;
    }
}
