#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_a.h"

// Invincibility frames of a hit with knockback byte k: -16 - k when bit 7 is set, k + 16 otherwise.
#define HIT_KNOCKBACK_FRAMES_SHORT(k) (((k) & 0x80) ? (-16 - (s8)(k)) : ((s8)(k) + 16))

// Ice rope hit: on a fresh hit (no status bits 0x1881, state 0, action 1) spawns the ice object and damages e; while bit 0x80
// is set e only takes the damage.
BOOL hit_icerobe(Entity *e, Entity *t, u8 mode) {
    Entity *ice;
    u16 flags;

    flags = playerWork[e->type].statusFlags;
    if ((flags & 0x1881) == 0) {
        if (playerWork[e->type].state == 0 && e->action == 1) {
            ice = GetSetWork(0x55, 0, 0);
            if (ice != NULL) {
                ice->child = e;
                e->health = decVital(e, t);
                playerWork[e->type].statusFlags = 0x800;
                playerWork[e->type].state = 13;
            }
        }
    } else if (flags & 0x80) {
        e->health = decVital(e, t);
    }
    e->unk_42 = *(u8 *)&t->attackKnockback;
    e->iframes = HIT_KNOCKBACK_FRAMES_SHORT(*(u8 *)&t->attackKnockback);
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}
