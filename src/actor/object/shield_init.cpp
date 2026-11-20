#include "engine/functions.h"
#include "engine/local_player_index.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/shield.h"

// shieldInit (0x02076bf0): ties the shield to the player of its type: registers itself as the player's weapon, takes
// the player's sprite layer bits and animation, sets its hit values and runs the first move.
void shieldInit(Entity *e) {
    Entity *owner = playerWork[e->type].entity;
    playerWork[e->type].weapon = e;
    e->action++;
    e->spriteSettings.b0 = 1;
    if (localPlayerIndex == e->type) {
        *(u32 *)&e->spriteSettings |= 0x1000000; // bit 24 of the sprite word, a 1-bit flag inside the b24 field (proposal in the report)
    }
    e->spriteSettings.b16 = 3;
    e->unk_1b = 0x10;
    e->unk_40 = 1;
    e->attackDamage = 0;
    e->attackKnockback = 0xc;
    e->poseId = 0x12;
    func_0208ab14(e, owner);
    e->unk_20 = owner->unk_20;
    e->spriteSettings.b6 = owner->spriteSettings.b6;
    e->animationState = owner->animationState & 0xe;
    shieldMove(e);
}
