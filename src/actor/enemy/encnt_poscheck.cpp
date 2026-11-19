#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/encnt.h"

// encnt_poscheck (0x0204406c): marks the spawn slots that are blocked by the map grid or too close to the player.
void encnt_poscheck(void) {
    EncntEntry *entry;
    u16 playerX;
    u16 playerY;
    u16 i;
    u16 cell;
    s16 diff;

    playerX = encntState.entity->x.HALF.HI;
    playerY = encntState.entity->y.HALF.HI;
    for (i = 0; i < encntState.limit; i++) {
        entry = &encntState.entries[i];
        entry->taken = 0;
        switch (encntState.kind) {
            case 0:
            case 1:
            case 2:
            case 5:
            case 6:
            case 7:
            default:
                entry->x = (entry->x & 0x3f0) + 8;
                entry->y = (entry->y & 0x3f0) + 8;
                cell = ((entry->x - mapState.originX) >> 4) | (((entry->y - mapState.originY) >> 4) << 6);
                if (data_02158fa0[cell + 0x2004] != 0 || data_02163fa4[cell + 0x2004] != 0) {
                    entry->taken = 1;
                }
            case 3:
                diff = entry->x - playerX;
                if (diff > -0x20 && diff < 0x20) {
                    diff = entry->y - playerY;
                    if (diff > -0x20 && diff < 0x20) {
                        entry->taken = 1;
                    }
                }
            case 4:
                break;
        }
    }
    encntState.count++;
}

// encnt_setem (0x020441cc): spawns the enemy of every free slot (a set object for kinds other than 4, an enemy for kind 4).
void encnt_setem(void) {
    EncntEntry *entry;
    u16 i;
    Entity *spawned;

    if (encntSharedState[0] == 0) {
        nextset();
        return;
    }
    if (encntState.kind != 4) {
        for (i = 0; i < encntState.limit; i++) {
            entry = &encntState.entries[i];
            if (entry->taken == 0) {
                spawned = GetSetWork(10, 0, 0);
                if (spawned != NULL) {
                    SPAWNV(spawned)->posA = encntState.posA;
                    SPAWNV(spawned)->posB = encntState.posB;
                    spawned->x.HALF.HI = entry->x;
                    spawned->y.HALF.HI = entry->y;
                    SPAWNV(spawned)->lifeTime = 0x4b0;
                    func_0208ae30(spawned);
                }
            }
        }
        nextset();
        return;
    }
    encntState.timer--;
    if (encntState.timer != 0) {
        return;
    }
    for (i = 0; i < encntState.limit; i++) {
        entry = &encntState.entries[i];
        if (entry->taken == 0) {
            spawned = GetEnemyWork(encntState.posA);
            if (spawned != NULL) {
                spawned->type = encntState.posB;
                spawned->x.HALF.HI = entry->x;
                spawned->y.HALF.HI = entry->y;
                SPAWNV(spawned)->lifeTime = 0x4b0;
                func_0208ae30(spawned);
            }
        }
    }
    nextset();
}
