#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_thunder family (module effect_thunder), 0x0206e4d8 .. 0x0206e598 (dispatcher and init).
// Address -> name: 0x0206e4d8 effect_thunder, 0x0206e4f4 effect_thunder_init

// Action table of effect_thunder, effectThunderTable
extern const EntityFunc effectThunderTable[];

// Five entries indexed by type2, one table per coordinate
typedef struct ThunderOffsetList {
    s32 v[5];
} ThunderOffsetList;
extern const ThunderOffsetList thunderOffsetX; // thunderOffsetX
extern const ThunderOffsetList thunderOffsetY; // thunderOffsetY

ARM void effect_thunder(Entity *e) {
    effectThunderTable[e->action](e);
}

ARM void effect_thunder_init(Entity *e) {
    u8 action = e->action;
    ThunderOffsetList xs;
    ThunderOffsetList ys;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    xs = thunderOffsetX;
    ys = thunderOffsetY;
    e->x.HALF.HI = xs.v[e->type2];
    e->y.HALF.HI = ys.v[e->type2];
    InitAnimationForceUpdate(e, e->type);
}

ARM void effect_thunder_move(Entity *e) {
    e->unk_1b = 0xb1;
    e->spriteSettings.b20 = 7;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    e->spriteSettings.b0 = 1;
    UpdateAnimationSingleFrame(e);
    e->timer = e->timer + 1;
    if (e->timer == 0x1d) {
        PutObjWork(e);
    }
}
