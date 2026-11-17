#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "types.h"
#include "engine/a_decls.h"
#include "engine/decls_a.h"

// Per-frame update of the boots object: while its owner is the object itself and the flags say worn it takes the owner's
// state (plsync), otherwise the object frees its hitbox and is put away.
void boots_move(Entity *e) {
    Entity *tmpl;
    Entity *owner;
    u8 flags;

    tmpl = playerWork[e->type].entity;
    e->iframes = 0;
    owner = playerWork[e->type].weapon;
    if (owner != e) {
        zFree((void *)e->hitbox);
        func_020841b0(e);
        PutObjWork(e);
        return;
    }
    flags = playerWork[e->type].hitFlags;
    if (flags == 0) {
        zFree((void *)e->hitbox);
        func_020841b0(e);
        playerWork[e->type].weapon = NULL;
        PutObjWork(e);
        return;
    }
    if ((flags & 0x40) != 0 && (flags & 0x80) == 0) {
        e->spriteSettings.b0 = 1;
        e->statusFlags = 0xad;
        boots_plsync(e, tmpl);
        return;
    }
    e->spriteSettings.b0 = e->statusFlags = 0;
}

