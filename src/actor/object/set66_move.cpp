#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set66.h"

// Set66 type1 move (module set66). Address -> name:
//   0x020752f8 rr_type1_move (dsd name, original type1_move)

// rr_type1_move (0x020752f8): the rupee rush slot marker. Once all 16 slot bits of the parent are set it moves on
// (action 3). Otherwise it follows the player standing on it (func_02084110 returns one bit per player), sets or clears
// its own slot bit in the parent mask and its highlight, and tells the single player instance which players stand on it.
void rr_type1_move(Entity *e) {
    u8 touching;
    UpdateAnimationSingleFrame(e);
    if (VARS(Vars_Set66, e->parent)->typeBits == 0xffff) {
        e->action = 3;
        e->timer = 0x3c;
        rr_poscopy(e, e->child);
        return;
    }
    touching = func_02084110(e);
    if (touching != 0) {
        if (touching & 1) {
            e->child = playerWork[0].entity;
        }
        if (touching & 2) {
            e->child = playerWork[1].entity;
        }
        if (touching & 4) {
            e->child = playerWork[2].entity;
        }
        if (touching & 8) {
            e->child = playerWork[3].entity;
        }
        if (!(VARS(Vars_Set66, e->parent)->typeBits & flagBits[e->type2])) {
            VARS(Vars_Set66, e->parent)->typeBits |= flagBits[e->type2];
            e->spriteSettings.b16 = 1;
            EnqueueSFX(0x18);
        }
    } else {
        VARS(Vars_Set66, e->parent)->typeBits &= ~flagBits[e->type2];
        e->spriteSettings.b16 = 0;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        u8 *instance;
        if (CountBits(touching) >= 2) {
            touching = 1;
        }
        instance = Knife_Single_SinglePlay_GetInstance();
        instance[8] |= touching;
        instance[9] = 0xff;
    }
}
