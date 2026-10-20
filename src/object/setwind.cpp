#include "engine/functions.h"
#include "global.h"
#include "object/set43.h"

// setwind, 0x0206cef8 (module plmove family). Address -> name: 0x0206cef8 setwind

extern const s8 setwindOffsetTable[];  // setwindOffsetTable, dx/dy pairs by type
extern const u16 setwindSpeedTable[];  // setwindSpeedTable, indexed by subtimer

ARM void setwind(Entity *e) {
    Entity *wind;

    wind = GetSetWork(0x4a, 0, 0);
    if (wind == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, wind, setwindOffsetTable[e->type * 2] << 16, setwindOffsetTable[e->type * 2 + 1] << 16);
    wind->direction = (e->type ^ 2) << 3;
    wind->speed = setwindSpeedTable[e->subtimer];
}
