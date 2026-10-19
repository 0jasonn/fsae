#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set32Table[];        // set32Table, indexed by type
extern u8 data_0212c618[];             // game state; byte 5 is a flag

// Set32, 0x02069e0c
ARM void Set32(Entity *e) {
    if (data_0212c618[5] == 0) {
        PutObjWork(e);
        return;
    }
    set32Table[e->type](e);
}

// triangle_marker, 0x02069e44
ARM void triangle_marker(Entity *e) {
    u8 nextAction;
    if (e->action == 0) {
        nextAction = e->action + 1;
        e->action = nextAction;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b16 = 0;
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 0;
        InitAnimationForceUpdate(e, e->type);
    }
    e->x.HALF.HI = e->child->x.HALF.HI;
    e->y.HALF.HI = e->child->y.HALF.HI;
}

extern Entity *data_0212c54c;          // pointer to the marker's target entity

// ghost_marker, 0x02069ea0
ARM void ghost_marker(Entity *e) {
    u8 nextAction;
    if (e->action == 0) {
        nextAction = e->action + 1;
        e->action = nextAction;
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = e->spriteSettings.b30;
        e->spriteSettings.b16 = e->spriteSettings.b14;
        InitAnimationForceUpdate(e, e->type);
    }
    e->spriteSettings.b0 = 0;
    if (data_0212c54c == 0 || data_0212c54c->action == 3) {
        return;
    }
    e->spriteSettings.b0 = 2;
    e->x.HALF.HI = ((data_0212c54c->x.HALF.HI >> 4) & 0x3f) + 0x58;
    e->y.HALF.HI = ((data_0212c54c->y.HALF.HI >> 4) & 0x3f) + 0x30;
}
