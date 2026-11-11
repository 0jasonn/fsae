#include "actor/object/em2a_core.h"

// Core part of the boss: reacts to hits and follows the parent (em2a_core, 0x02031cb0).
void em2a_core(Entity *e) {
    Entity *spawn;
    Entity *parent;
    s32 health;
    s32 amount;
    u8 owner;

    if (e->action == 2) {
        if (e->contactFlags & 0x80) {
            e->iframes = 0xf0;
            if (e->contactedEntity->type == (e->type2 & 0xf)) {
                switch (e->contactFlags & 0x7f) {
                case 0:
                    break;
                case 0x10:
                    data_0212cebc[e->contactedEntity->type * 0x94] = 6;
                    data_0212cee8[e->contactedEntity->type * 0x94] = 1;
                case 4:
                case 8:
                case 0xc:
                case 0x18:
                    e->parent->iframes = 0x18;
                    e->iframes = 0x18;
                    health = e->parent->health - e->contactedEntity->attackDamage;
                    if (health <= 0) {
                        health = 0;
                    }
                    e->parent->health = health;
                    e->spriteSettings.b16 = (e->type2 & 0xf) + 7;
                    e->spriteSettings.b20 = e->spriteSettings.b16;
                    SoundReq(0x2d);
                    break;
                }
            } else {
                switch (e->contactFlags & 0x7f) {
                case 4:
                case 8:
                case 0xc:
                case 0x10:
                    if (e->parent->action == 0x10) {
                        break;
                    }
                    if (TEMPLATE_ENTITY(e->contactedEntity->type)->iframes == 0) {
                        amount = 4 - ((PalBits *)&playerWork[e->contactedEntity->type].unk_3e)->b;
                        if (amount <= 1) {
                            amount = 1;
                        }
                        AddHeart(TEMPLATE_ENTITY(e->contactedEntity->type), (s16)-amount);
                    }
                    e->contactedEntity->iframes = 0x18;
                    if (e->parent->action != 0xe) {
                        spawn = GetSetWork(0x60, 0, 0);
                        if (spawn != NULL) {
                            spawn->unk_1b = 0x81;
                            spawn->unk_23 = 0x21;
                            spawn->x.HALF.HI = e->parent->x.HALF.HI;
                            spawn->y.HALF.HI = e->parent->y.HALF.HI + 1;
                            spawn->spriteSettings.b16 = e->parent->spriteSettings.b20 + 1;
                            spawn->spriteSettings.b20 = spawn->spriteSettings.b16;
                            spawn->spriteSettings.b14 = e->parent->spriteSettings.b14;
                            spawn->spriteSettings.b30 = e->parent->spriteSettings.b30;
                            spawn->spriteSettings.b6 = e->parent->spriteSettings.b6;
                            spawn->unk_20 = e->parent->unk_20;
                            spawn->timer = 0x78;
                        }
                    }
                case 0:
                    parent = e->parent;
                    if (parent->action != 0xe) {
                        if (parent->action == 0x10) {
                            break;
                        }
                        parent->timer = 0x78;
                        e->parent->action = 0xe;
                    }
                    if (TEMPLATE_ENTITY(e->contactedEntity->type)->iframes == 0) {
                        TEMPLATE_ENTITY(e->contactedEntity->type)->iframes = 0x18;
                        func_0208ab50(e->contactedEntity);
                    }
                    break;
                }
            }
        }
        if (e->iframes == 0) {
            owner = localPlayerIndex;
            if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                owner = *Knife_Single_SinglePlay_GetInstance();
            }
            if (owner == VCP(e)->ownerIndex) {
                e->spriteSettings.b16 = (e->type2 & 0xf) + 7;
                e->spriteSettings.b20 = e->spriteSettings.b16;
            } else {
                e->spriteSettings.b16 = e->parent->spriteSettings.b16 + 1;
                e->spriteSettings.b20 = e->spriteSettings.b16;
            }
        }
        if (e->parent->health == 0) {
            EmDie(e);
        }
    } else {
        if (e->parent->action == 9) {
            e->action = 1;
            e->statusFlags &= 0x7f;
            e->spriteSettings.b0 = 1;
            e->layer = e->parent->layer;
            e->spriteSettings.b16 = (e->timer & 0xf) + 7 + e->type;
            if (e->spriteSettings.b16 > 10) {
                e->spriteSettings.b16 -= 4;
            }
            if (e->subtimer-- == 0) {
                if (VCP(e)->subtimerStart != 0) {
                    e->subtimer = VCP(e)->subtimerStart = VCP(e)->subtimerStart - 1;
                } else {
                    e->subtimer = 1;
                }
                e->type = (e->type + 1) & 3;
            }
        } else {
            e->action = 2;
            e->statusFlags |= 0x80;
            owner = localPlayerIndex;
            if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                owner = *Knife_Single_SinglePlay_GetInstance();
            }
            if (owner == VCP(e)->ownerIndex) {
                e->spriteSettings.b16 = (e->type2 & 0xf) + 7;
                e->spriteSettings.b20 = e->spriteSettings.b16;
            } else {
                e->spriteSettings.b16 = e->parent->spriteSettings.b16 + 1;
                e->spriteSettings.b20 = e->spriteSettings.b16;
            }
            e->hitbox = em2a_corePartHitboxes[e->timer];
        }
    }
    e->x.WORD = e->parent->x.WORD;
    e->y.WORD = e->parent->y.WORD;
    if (e->parent->frame & (1 << (e->timer & 0xf))) {
        e->y.WORD++;
    } else {
        e->unk_5e.b0 = 1;
    }
}
