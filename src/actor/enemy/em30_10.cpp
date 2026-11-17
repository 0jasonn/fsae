#include "engine/functions.h"
#include "actor/enemy/delprt.h"
#include "global.h"

// Overlay of the fields type0_kamae uses.
typedef struct VarsKamae {
    /* 00 */ u8 unk_00[0x71];
    /* 71 */ s8 turnStep; // signed change of direction per frame
} VarsKamae;

#define KAMAE(e) VARS(VarsKamae, e)

// type0_kamae (0x020426e0): turns the entity's direction by turnStep each frame until it reaches the end angle (0x60 or
// 0xa0), then switches to action 9, marks its flag bit in the parent and plays a sound.
void type0_kamae(Entity *e) {
    Entity *parent = e->parent;

    if (parent->unk_6c[4] & 4) {
        return;
    }
    e->direction += KAMAE(e)->turnStep;
    if (KAMAE(e)->turnStep > 0) {
        if (e->direction == 0x58) {
            e->direction = 0x60;
            e->action = 9;
            parent->unk_6c[4] |= (u8)flagBits[e->type2];
            EnqueueSFX(0x9e);
        }
    } else if (e->direction == 0xa8) {
        e->direction = 0xa0;
        e->action = 9;
        parent->unk_6c[4] |= (u8)flagBits[e->type2];
        EnqueueSFX(0x9e);
    }
}
