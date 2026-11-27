#include "engine/functions.h"
#include "actor/enemy/em12.h"
#include "global.h"

// igoalGetDir (0x0203bca4): picks the direction the em12 actor walks in. While it has no home in the area it aims at the
// players (first the current target, then the others in rotation); once none of them is in the area it walks back to its
// home position, probing the cells ahead of the walk offsets for blocked ones.
void igoalGetDir(Entity *e) {
    u32 cellB;
    u16 idx;
    const u16 *list;
    u32 cellA;
    u16 work;     // reused: player being tried (no home yet), tries left (home path), blocked flag (probe)
    u16 listLeft;
    int player;   // start player (no home yet), then the player being tried (home path)

    if (V(e)->w70.b.inArea == 0) {
        if (tgtareacheck(e, V(e)->target)) {
            e->direction = GetFacingDirection(e, V(e)->target);
            return;
        }
        player = frameCounter.frame & 3;
        work = player;
        do {
            if (gameState.playerCount > work) {
                if (tgtareacheck(e, playerWork[work].entity)) {
                    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
                        V(e)->target = playerWork[work].entity;
                    } else {
                        V(e)->target = playerWork[*Knife_Single_SinglePlay_GetInstance()].entity;
                    }
                    e->direction = GetFacingDirection(e, V(e)->target);
                    return;
                }
            }
            work = (work + 1) & 3;
        } while (player != work);
        V(e)->w70.b.inArea = 1;
        V(e)->w70.b.walkState = 0;
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->homeX, V(e)->homeY);
        return;
    }

    work = 4;
    player = frameCounter.frame & 3;
    do {
        if (tgtareacheck(e, playerWork[player].entity)) {
            V(e)->w70.b.inArea = 0;
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
                V(e)->target = playerWork[player].entity;
            } else {
                V(e)->target = playerWork[*Knife_Single_SinglePlay_GetInstance()].entity;
            }
            e->direction = GetFacingDirection(e, V(e)->target);
            break;
        }
        player = (player + 1) & 3;
        work--;
    } while (work != 0);
    if (work != 0) {
        return;
    }

    if (V(e)->w70.b.walkState != 0) {
    if (V(e)->w70.b.walkState == 1) {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->homeX, V(e)->homeY);
        V(e)->w70.b.unk_73 = (e->direction + 4) & 0x18;
        if (V(e)->w70.b.unk_73 < e->direction) {
            e->direction = (V(e)->w70.b.unk_73 + 8) & 0x18;
        } else {
            e->direction = (V(e)->w70.b.unk_73 - 8) & 0x18;
        }
        V(e)->w70.b.walkState |= 0x80;
    } else {
        if ((V(e)->w70.b.walkState & 2) != 0) {
            e->direction ^= 0x10;
        }
    }

    {
        int flags = V(e)->w70.b.walkState;
        int bits = flags & 0x70;
        if (bits != 0) {
            V(e)->w70.b.walkState = (flags & 0x87) | (bits >> 1);
            if (V(e)->w70.b.walkState & 0x10) {
                e->direction = V(e)->w70.b.unk_73;
                return;
            }
            if (V(e)->w70.b.walkState & 8) {
                V(e)->w70.b.walkState = 0;
            }
            return;
        }
    }

    {
        idx = V(e)->w70.b.unk_73 >> 1;
        work = 1;
        list = data_020d2144;
        cellA = func_02083c8c((s16)(e->x.HALF.HI + em12_walkOffsets[idx]), (s16)(e->y.HALF.HI + em12_walkOffsets[idx + 1]), e->layer);
        cellB = func_02083c8c((s16)(e->x.HALF.HI + em12_walkOffsets[idx + 2]), (s16)(e->y.HALF.HI + em12_walkOffsets[idx + 3]), e->layer);
    }
    if (data_02171e0c[cellA] == 0 && data_02171e0c[cellB] == 0) {
        work = 0;
    }
    listLeft = 11;
    {
        do {
            if (*list == cellA || *list == cellB) {
                work = 1;
                break;
            }
            listLeft--;
            list++;
        } while (listLeft != 0);
    }
    if (work != 0) {
        if ((e->direction >> 3) == e->animationState) {
            V(e)->w70.b.walkState |= 0x20;
            return;
        }
        V(e)->w70.b.walkState |= 0x40;
        return;
    }
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->homeX, V(e)->homeY);
    } else {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, V(e)->homeX, V(e)->homeY);
    }
}
