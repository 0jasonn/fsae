#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set37Table[];        // set37Table, indexed by action
extern const u8 set37Hitbox[];         // set37Hitbox
extern const s8 set37BobTable[];       // set37BobTable, indexed by timer & 7
extern u16 data_0212c5bc;              // frame counter

void adjust(Entity *e);

// set37_demo, 0x0206b730
ARM void set37_demo(Entity *e) {
    adjust(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    AddHeart(e->contactedEntity, 0xa0);
    PutObjWork(e);
}

// adjust, 0x0206b768: follows the contacted entity's position and bits.
ARM void adjust(Entity *e) {
    ObjPosCopy(e->contactedEntity, e);
    e->spriteSettings.b30 = e->contactedEntity->spriteSettings.b30;
    e->spriteSettings.b14 = e->contactedEntity->spriteSettings.b14;
    e->unk_5e.b0 = 3;
    e->z.HALF.HI -= 0x10;
}
