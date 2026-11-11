#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit.h"

// Rupee-like hit (hit handler table entry): when the rupee can be taken (the slot is neither busy nor flagged), the slot's
// flags are set, e is placed at t and takes over its sprite bits.
BOOL hit_rupeelike(Entity *e, Entity *t, u8 unused) {
    u16 bits;

    if (func_020860dc(e) != 0) {
        if ((playerWork[e->type].statusFlags & 0x81) == 0 && playerWork[e->type].unk_26 == 0) {
            playerWork[e->type].unk_1a |= 0x80;
            playerWork[e->type].unk_0a |= 0x80;
            bits = playerWork[e->type].statusFlags;
            bits |= 0x10;
            playerWork[e->type].statusFlags = bits;
            playerWork[e->type].unk_02 = 0;
            ObjPosCopyOfs32(t, e, 0, 1);
            e->spriteSettings.b14 = t->spriteSettings.b14;
            e->spriteSettings.b30 = t->spriteSettings.b30;
            e->iframes = 0xff;
            t->iframes = 0xf8;
            return 1;
        }
    }
    return 0;
}
