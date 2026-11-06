#include "engine/functions.h"
#include "global.h"
#include "actor/object/c_decls_2.h"
#include "engine/player.h"

extern "C" void kabutowari(Entity *e);
void kabutowari(Entity *e) {
    Entity *other;

    other = playerWork[e->type].entity;
    if (playerWork[e->type].weapon != e) {
        func_020841b0(e);
        zFree((void *)e->hitbox);
        PutObjWork(e);
    }
    if (playerWork[e->type].inUse == 0) {
        goto clear_c3;
    }
    if (playerWork[e->type].unk_02 != 0) {
        goto normal_n1;
    }
    playerWork[e->type].weapon = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
    return;
normal_n1:
    if ((other->frame & 0x80) == 0) {
        goto normal_n2;
    }
    playerWork[e->type].weapon = 0;
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
    playerWork[e->type].weapon = 0;
    func_020841b0(e);
    zFree((void *)e->hitbox);
    PutObjWork(e);
}
