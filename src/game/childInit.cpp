#include "engine/functions.h"
#include "actor/enemy/em26.h"

// childInit (0x02040d60): sets up the second bubble part and registers it.
void childInit(Entity *parent, Entity *child) {
    child->objKind = 3;
    child->objId = 0x27;
    child->iframes = 0xf8;
    V(child)->unk_64 = V(parent)->unk_64;
    V(child)->homeX = V(parent)->homeX;
    V(child)->homeY = V(parent)->homeY;
    V(child)->resetVal0 = V(parent)->resetVal0;
    V(child)->resetVal1 = V(parent)->resetVal1;
    V(child)->resetVal2 = V(parent)->resetVal2;
    V(child)->resetVal3 = V(parent)->resetVal3;
    EmPalamCopy(parent, child);
    RegistObjWork(4, child);
}
