#include "engine/functions.h"
#include "actor/enemy/em29.h"
#include "global.h"

// damageCheck (0x02042dc8): checks both parts of the boss (the entities at 0x78 and 0x7c) for a hit of the matching
// kind. Only when both parts were hit by the same attack does the boss take damage: the parent gets its invulnerability
// frames from the knockback of the attack (copied to the child), loses the damage (halved outside wireless mode),
// resets its direction and drops rupees.
void damageCheck(Entity *e) {
    int hitFlags = 0;
    {
        Entity *partA = VPARTS(e)->partA;
        u8 contactA = partA->contactFlags;
        if ((contactA & 0x80) && (u16)(contactA - 0x84) <= 0x9f) {
            hitFlags |= 0x10;
            if (partA->spriteSettings.b20 - 7 == partA->contactedEntity->type) {
                hitFlags |= 1;
            }
        }
    }
    {
        Entity *partB = VPARTS(e)->partB;
        u8 contactB = partB->contactFlags;
        if ((contactB & 0x80) && (u16)(contactB - 0x84) <= 0x9f) {
            hitFlags |= 0x20;
            if (partB->spriteSettings.b20 - 7 == partB->contactedEntity->type) {
                hitFlags |= 2;
            }
        }
    }
    if (hitFlags == 0) {
        return;
    }
    if ((hitFlags & 3) != 3) {
        return;
    }
    u8 allFlags = 0xff;
    e->parent->contactFlags = allFlags;
    s32 invulnerableFrames = VPARTS(e)->partA->contactedEntity->attackKnockback;
    if (invulnerableFrames < 0) {
        invulnerableFrames = 0xef - allFlags - invulnerableFrames;
    } else {
        invulnerableFrames = invulnerableFrames + 16;
    }
    e->parent->iframes = invulnerableFrames;
    e->child->iframes = e->parent->iframes;
    u8 damageB = VPARTS(e)->partB->contactedEntity->attackDamage;
    u8 damage = VPARTS(e)->partA->contactedEntity->attackDamage;
    if (damage <= damageB) {
        damage = damageB;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        damage = damage >> 1;
    }
    if (e->parent->health > damage) {
        e->parent->health -= damage;
    } else {
        e->parent->health = 0;
    }
    e->baseDirection = 0;
    EmBossDropRupee(e, W(e)->unk_74[0]++, 0, 8);
    EnqueueSFX(0x2d);
}
