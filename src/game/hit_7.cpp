#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit_6.h"

// Wisp hit (module hit, seventh unit). Original name: hit_wisp (hit_wisp(OBJ_WORK_*, OBJ_WORK_*, unsigned char)).
// Vars overlay of the wisp's own field, placed after the shared Entity block.
typedef struct WispVars {
    u8 unk_00[0x72];
    u16 wispTimer; // set to 0x258 when a wisp hits
} WispVars;

ARM BOOL hit_wisp(Entity *e, Entity *t, u8 unused) {
    u16 timer;
    u8 knockback;

    timer = 0x258;
    data_0212ceca[e->type * 0x94] = 1;
    VARS(WispVars, e)->wispTimer = timer;
    e->unk_42 = *(u8 *)&t->attackKnockback;
    knockback = *(u8 *)&t->attackKnockback;
    if (knockback & 0x80) {
        e->iframes = timer - 0x268 - (s8)knockback;
    } else {
        e->iframes = (s8)knockback + 0x10;
    }
    if (t->iframes == 0) {
        t->iframes = 0xff;
    }
    return 1;
}
