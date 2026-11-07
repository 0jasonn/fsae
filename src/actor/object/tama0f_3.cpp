#include "actor/object/tama0f_a.h"

// Storm shot (tama0f_storm, 0x0207d794): hops between the players when hit, then hovers and drops sparks.
void tama0f_storm(Entity *e) {
    int index;
    Entity *spawn;

    UpdateAnimationSingleFrame(e);
    if (e->contactFlags & 0x80) {
        switch (e->contactFlags & 0x7f) {
        case 1:
            e->iframes = 0xf0;
            if (VS(e)->stormTimer != 0) {
                if (e->timer == e->contactedEntity->type) {
                    index = func_02085608();
                    if (index == e->timer) {
                        index = (u8)(index + 1);
                        if (index == gameState.playerCount) {
                            index = 0;
                        }
                    }
                    e->direction = func_02086078(e, PLAYER_ENTITY(index));
                } else {
                    e->direction = func_02086078(e, PLAYER_ENTITY(e->timer));
                }
            } else {
                index = func_02085608();
                if (index == e->timer) {
                    index = (u8)(index + 1);
                    if (index == gameState.playerCount) {
                        index = 0;
                    }
                }
                e->direction = func_02086078(e, PLAYER_ENTITY(index));
            }
            EnqueueSFX(0xb4);
            break;
        case 4:
        case 8:
        case 0xc:
            e->iframes = 0xf0;
            if (VS(e)->stormTimer != 0) {
                if (e->timer == e->contactedEntity->type) {
                    VS(e)->stormTimer--;
                    index = func_02085608();
                    if (index == e->timer) {
                        index = (u8)(index + 1);
                        if (index == gameState.playerCount) {
                            index = 0;
                        }
                    }
                    e->timer = index;
                    e->spriteSettings.b16 = (index & 0xff) + 7;
                    e->spriteSettings.b20 = e->spriteSettings.b16;
                    if (VS(e)->stormTimer != 0) {
                        e->direction = func_02086078(e, PLAYER_ENTITY(index));
                    } else {
                        e->direction = func_02086078(e, e->parent);
                    }
                }
            } else {
                e->direction = func_02086078(e, e->parent);
            }
            EnqueueSFX(0xb4);
            break;
        }
    }
    if (VS(e)->stormTimer == 0) {
        e->spriteSettings.b16++;
        if (e->spriteSettings.b16 > 10) {
            e->spriteSettings.b16 = 7;
        }
        e->spriteSettings.b20 = e->spriteSettings.b16;
        if (e->parent->z.HALF.HI > -16) {
            if (func_02085a88(e, e->parent, 16, 16)) {
                e->parent->action = 4;
                e->parent->timer = 8;
                e->parent->subtimer = 0;
                VARS(Vars_Tama0fParent, e->parent)->stormActive = 0;
                PutObjWork(e);
                return;
            }
        }
    }
    func_020852ec(e);
    if (e->wallFlags != 0) {
        VARS(Vars_Tama0fParent, e->parent)->stormActive = 0;
        PutObjWork(e);
    }
    e->subtimer--;
    if (e->subtimer == 0) {
        e->subtimer = 3;
        spawn = GetSetWork(0x60, 0, 1);
        if (spawn != NULL) {
            spawn->unk_1b = 0xa0;
            spawn->unk_23 = 9;
            spawn->x.HALF.HI = e->x.HALF.HI;
            spawn->y.HALF.HI = e->y.HALF.HI;
            spawn->spriteSettings.b16 = e->spriteSettings.b16;
            spawn->spriteSettings.b14 = e->spriteSettings.b14;
            spawn->spriteSettings.b30 = e->spriteSettings.b30;
            spawn->spriteSettings.b6 = e->spriteSettings.b6;
            spawn->unk_20 = e->unk_20;
            spawn->unk_5e.b0 = 0;
        }
    }
    VS(e)->lifeCounter++;
    if (VS(e)->lifeCounter > 0x21c) {
        VS(e)->lifeCounter = 0;
    }
}
