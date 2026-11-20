#include "engine/functions.h"
#include "game/zmem.h"
#include "engine/player.h"
#include "actor/object/boots_init.h"

// boots_init (0x020244d4): takes the weapon slot of its owner, copies the start-up state from the owner's entity and
// allocates the hitbox buffer. Removed at once when the owner's boots flags are clear.
void boots_init(Entity *e) {
    Entity *owner;

    owner = playerWork[e->type].entity;
    if (playerWork[e->type].hitFlags != 0) {
        playerWork[e->type].weapon = e;
        e->action++;
        e->unk_1b = 0x60;
        e->spriteSettings.b16 = 3;
        e->unk_20 = owner->unk_20;
        e->spriteSettings.b6 = owner->spriteSettings.b6;
        e->attackDamage = (playerWork[e->type].nutBits.b0 << 1) + 3;
        e->attackKnockback = 6;
        e->unk_5c = 0x600;
        e->unk_40 = 0x10;
        e->poseId = 3;
        e->hitbox = zMalloc(8);
        func_0208ab14(e, owner);
        func_02084180(e);
        boots_move(e);
        return;
    }
    PutObjWork(e);
}
