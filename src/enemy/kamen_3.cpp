#include "engine/functions.h"
#include "global.h"
#include "enemy/kamen.h"

// Functions in this file: kamen_kemuriSet (0x0203eed4).

ARM void kamen_kemuriSet(Entity *e) {
    V_KAMEN(e)->kemuriTimer--;
    if ((V_KAMEN(e)->kemuriTimer & 0x7) != 0) {
        return;
    }
    Entity *puff = GetSetWork(0xf, 0x11, 0);
    if (puff != 0) {
        ObjPosCopyOfs32(e, puff, 0, 0x10000);
    }
}
