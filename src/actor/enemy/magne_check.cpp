#include "engine/functions.h"
#include "engine/player.h"
#include "actor/enemy/em20.h"
#include "actor/enemy/em20_magne.h"
#include "global.h"

// magneCheck (0x0203ef24): the magnet pull on a masked enemy. Starting at a random player, collects the direction of every
// player who stands in line with the enemy (within 12 pixels on x or y), shares its layer and faces it; opposite pulls cancel
// out. While the same direction keeps pulling, pullTimer counts up and shakes the enemy sideways; after 30 frames the enemy
// is knocked over (action 7, dust effect). Returns 1 while pulled in the stored direction, otherwise the number of pulls.
int magneCheck(Entity *e) {
    PlayerData *pw;      // playerWork[slot]
    u8 count;
    u8 slot;
    u8 dir;
    u8 j;
    Entity *player;
    u8 k;
    u8 pullDir[4];
    Entity *dust;
    u8 i;

    if (e->action == 0 || e->poseId == 6) {
        return 0;
    }
    slot = Random() % gameState.playerCount;
    pullDir[0] = pullDir[1] = pullDir[2] = pullDir[3] = 0xff;
    i = 0;
    count = 0;
    do {
        pw = &playerWork[slot];
        if ((pw->unk_0f & ~0xd2) != 0) {
            player = pw->entity;
            if ((u16)(player->x.HALF.HI - e->x.HALF.HI + 0xc) <= 0x18 || (u16)(player->y.HALF.HI - e->y.HALF.HI + 0xc) <= 0x18) {
                if (((e->layer & player->layer) >> 14) != 0) {
                    dir = GetFacingDirection(e, player);
                    if ((pw->entity->animationState ^ 4) == ((dir + 4) & 0x18) >> 2) {
                        pullDir[count] = (dir + 4) & 0x18;
                        count++;
                    }
                }
            }
        }
        slot++;
        i++;
        if (slot >= gameState.playerCount) {
            slot = 0;
        }
    } while (i < gameState.playerCount);
    if (count != 0) {
        for (j = 0; j < count - 1; j++) {
            for (i = j + 1; i < count; i++) {
                if ((pullDir[j] ^ 0x10) == pullDir[i]) {
                    pullDir[j] = 0xff;
                    pullDir[i] = 0xff;
                    count -= 2;
                }
            }
        }
        if (count != 0) {
            if (VMAGNE(e)->pullDir != 0xff) {
                for (k = 0; k < 4; k++) {
                    if (VMAGNE(e)->pullDir == pullDir[k]) {
                        VMAGNE(e)->pullTimer++;
                        if (VMAGNE(e)->pullTimer > 0x1e) {
                            e->action = 7;
                            e->timer = 0x5a;
                            e->zVelocity = 0x18000;
                            e->poseId = 6;
                            InitAnimationForceUpdate(e, e->animationState + 4);
                            dust = GetEnemyWork(0x20);
                            if (dust != NULL) {
                                dust->type = 1;
                                dust->direction = pullDir[k];
                                ObjPosCopy(e, dust);
                            }
                        } else if (VMAGNE(e)->pullTimer & 1) {
                            e->x.HALF.HI += magneShakeOffsets[(VMAGNE(e)->pullTimer & 6) >> 1];
                        }
                        return 1;
                    }
                }
            }
            VMAGNE(e)->pullTimer = 0;
            i = 0;
            if (pullDir[0] == 0xff) {
                do {
                    i++;
                } while (pullDir[i] == 0xff);
            }
            VMAGNE(e)->pullDir = pullDir[i];
        }
    } else {
        VMAGNE(e)->pullDir = 0xff;
    }
    return count;
}
