#include "engine/functions.h"
#include "global.h"
#include "object/c_decls_2.h"

extern u8 data_0212ced8[];
extern u8 data_0212cedc[];
extern u8 data_0212ceb2[];
extern u8 data_0212ceb4[];

extern "C" void kabutowari(Entity *e);
ARM void kabutowari(Entity *e) {
    Entity *other;

    other = *(Entity **)&data_0212ced8[e->type * 0x94];
    if (*(Entity **)&data_0212cedc[e->type * 0x94] != e) {
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
    }
    if (data_0212ceb4[e->type * 0x94] == 0) {
        goto clear_c3;
    }
    if (data_0212ceb2[e->type * 0x94] != 0) {
        goto normal_n1;
    }
    *(Entity **)&data_0212cedc[e->type * 0x94] = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
    return;
normal_n1:
    if ((other->frame & 0x80) == 0) {
        goto normal_n2;
    }
    *(Entity **)&data_0212cedc[e->type * 0x94] = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
    return;
normal_n2:
    sword_plsync(e, other);
    if ((other->frame & 0x20) != 0) {
        func_02085f98(other, 0xc0);
    }
    if (e->unk_21 > 0x68) {
        e->unk_21 = 0xff;
    }
    if ((other->frame & 0x8) == 0) {
        e->statusFlags = 0;
        return;
    }
    e->statusFlags |= 0x80;
    kabutoEvent(e);
    return;
clear_c3:
    *(Entity **)&data_0212cedc[e->type * 0x94] = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
}
