#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"

// effect_kazan (module effect_kazan), 0x0206df1c .. 0x0206dfe4.
// Address -> name: 0x0206df1c effect_kazan

// Offsets of the palette block inside the resource, indexed by subtimer, kazanPalOffsetTable
extern const u16 kazanPalOffsetTable[];

ARM void effect_kazan(Entity *e) {
    u8 timer;

    if (e->action == 0) {
        e->action = e->action + 1;
        e->timer = 0xc;
        e->subtimer = 0;
    }
    timer = e->timer;
    e->timer = timer - 1;
    if (timer == 0) {
        u8 *resource = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x34);
        CgPalletSet((u16 *)(resource + kazanPalOffsetTable[e->subtimer]), 0xf, 1);
        e->timer = 0xc;
        e->subtimer = (e->subtimer == 5) ? 0 : e->subtimer + 1;
    }
    if (e->type2 == KNIFE_CURSOR_INDEX()) {
        return;
    }
    CgPalletSet((u16 *)(KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0x33) + 0x1e0), 0xf, 1);
    PutObjWork(e);
}
