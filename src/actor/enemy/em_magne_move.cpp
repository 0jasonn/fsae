#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// EmMagneMove (0x02045cb0): pulls the enemy towards every player standing close enough on the same layer. A player counts
// when he faces the enemy; two players pulling in opposite directions cancel each other out, and each remaining pull is
// applied with the given speed (a pull that is not on one of the four directions also adds a sideways pull of 0x80).
// Returns the number of players that are still pulling.
u8 EmMagneMove(Entity *e, u16 speed) {
    u8 dir;
    PlayerData *pw;      // playerWork[i], the player being tested
    u8 j;
    u8 k;
    u8 base;
    u8 count;
    Entity *playerEntity;
    u8 i;
    u8 pullDir[4];

    pullDir[0] = pullDir[1] = pullDir[2] = pullDir[3] = 0xff;
    i = 0;
    count = 0;
    do {
        pw = &playerWork[i];
        if ((pw->unk_0f & ~0xd2) == 0) {
            continue;
        }
        playerEntity = pw->entity;
        if (((e->layer & playerEntity->layer) >> 14) == 0) {
            continue;
        }
        if ((u16)(playerEntity->x.HALF.HI - e->x.HALF.HI + 0xc) > 0x18) {
            if ((u16)(playerEntity->y.HALF.HI - e->y.HALF.HI + 0xc) > 0x18) {
                continue;
            }
        }
        dir = GetFacingDirection(e, pw->entity);
        if (((dir + 0x14) & 0x18) >> 2 == pw->entity->animationState) {
            pullDir[count] = dir;
            count++;
        }
    } while (++i < gameState.playerCount);
    if (count != 0) {
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (((pullDir[i] + 0x14) & 0x18) == ((pullDir[j] + 4) & 0x18)) {
                    pullDir[i] = 0xff;
                    pullDir[j] = 0xff;
                    count -= 2;
                }
            }
        }
        for (k = 0; k < gameState.playerCount; k++) {
            if (pullDir[k] == 0xff) {
                continue;
            }
            base = (pullDir[k] + 4) & 0x18;
            func_020852f8(e, speed, base);
            if ((pullDir[k] & 7) == 0) {
                continue;
            }
            if (((pullDir[k] - base) & 0x1f) < 0x10) {
                func_020852f8(e, 0x80, (base + 8) & 0x18);
            } else {
                func_020852f8(e, 0x80, (base - 8) & 0x18);
            }
        }
    }
    return count;
}
