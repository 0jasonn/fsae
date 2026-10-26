#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/decls_b2.h"

// Overlay of the em28 enemy record (the idle timer at 0x7a; the enemy's header is not included here because it
// declares the player data with other types).
typedef struct Em28Vars {
    u8 unk_00[0x7a];
    u16 idleTimer;
} Em28Vars;
#define V(e) VARS(Em28Vars, e)

typedef struct Em28Claim {
    s32 claimed;
    s32 unk_4;
} Em28Claim;
extern Em28Claim em28_claim;

// Functions in this file (module em28, fifth unit; em28.cpp to em28_4.cpp hold the others):
//   em28_normal (em28_normal(OBJ_WORK_*))

// em28_normal (0x02040f34): counts the idle timer, starts a dash when a player is ready, runs the action function,
// updates the sword and claims the shared player slot in em28_claim when the game is not in wireless mode.
ARM void em28_normal(Entity *e) {
    Entity *child;

    if (e->action != 0) {
        if (V(e)->idleTimer != 0) {
            V(e)->idleTimer = V(e)->idleTimer - 1;
        } else if (e->action < 4) {
            child = plCheck(e);
            if (child != NULL) {
                dushInit(e, child);
            }
        }
        EmMagneMove(e, 0x80);
    }

    data_020d334c[e->action](e);
    swordMgr(e);

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        if (em28_claim.unk_4 != *Knife_Single_SinglePlay_GetInstance()) {
            u8 fresh = *Knife_Single_SinglePlay_GetInstance();
            em28_claim.claimed = 0x78;
            em28_claim.unk_4 = fresh;
        }
    }

    if (em28_claim.claimed != 0) {
        em28_claim.claimed = em28_claim.claimed - 1;
    }
}
