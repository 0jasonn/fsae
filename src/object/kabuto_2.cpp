#include "engine/functions.h"
#include "global.h"
#include "object/c_decls_2.h"
#include "engine/player.h"

extern "C" void kabutowari(Entity *e);
void kabutowari(Entity *e) {
    Entity *other;

    other = data_0212ceb0[e->type].entity;
    if (data_0212ceb0[e->type].weapon != e) {
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
    }
    if (data_0212ceb0[e->type].inUse == 0) {
        goto clear_c3;
    }
    if (data_0212ceb0[e->type].unk_02 != 0) {
        goto normal_n1;
    }
    data_0212ceb0[e->type].weapon = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
    return;
normal_n1:
    if ((other->frame & 0x80) == 0) {
        goto normal_n2;
    }
    data_0212ceb0[e->type].weapon = 0;
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
    data_0212ceb0[e->type].weapon = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
}
