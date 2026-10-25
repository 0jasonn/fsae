#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj.h"

// Functions in this file: bgobj_lift (0x0203e63c).

ARM void bgobj_lift(Entity *e) {
    bgobj_liftTable[e->subAction](e);
}
