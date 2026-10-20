#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 aura actions (module set58). Address -> name:
//   0x02073a4c set58_aura (original name; dispatches on e->action)
//   0x02073a68 aura_init (original name)
//   0x02073ac0 aura_up (original name)
//   0x02073b48 aura_move (original name)

extern const EntityFunc set58_auraActions[]; // set58_auraActions, indexed by e->action

ARM void set58_aura(Entity *e) {
    set58_auraActions[e->action](e);
}

ARM void aura_init(Entity *e) {
    set58_actionInit(e);
    e->unk_5e.b0 = 0;
    e->spriteSettings.b0 = 1;
    if (func_02081b64() == 0) {
        return;
    }
    e->spriteSettings.b16 = e->spriteSettings.b16 + 1;
}

ARM void aura_up(Entity *e) {
    ObjPosCopy(e->parent, e);
    if (e->z.HALF.HI != -20) {
        return;
    }
    e->action = 2;
    e->timer = 0x5a;
    func_02085cf8(e);
    {
        u32 word = *(u32 *)&e->spriteSettings;
        u32 field = (word << 22) >> 30;
        field |= 2;
        word &= ~0x300;
        word |= (field << 30) >> 22;
        *(u32 *)&e->spriteSettings = word;
    }
    e->speed = 0x1000000;
    scrollArgs.data[0] = 0x100;
    scrollArgs.data[1] = 0x100;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}

ARM void aura_move(Entity *e) {
    s32 speed;

    e->timer--;
    if (e->timer == 0) {
        em12_typeMasks |= 1;
        e->action = 3;
        func_02085d34(e);
        return;
    }
    speed = e->speed - 0x18000;
    e->speed = speed;
    scrollArgs.data[0] = 0x100;
    scrollArgs.data[1] = speed >> 16;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}
