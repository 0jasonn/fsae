#include "knife/comm/singleplay_a.h"

// Knife::Single::SinglePlay::UpdateEnemyCheck(SinglePlayWork&, SpWorkPair&) (0x02095878): looks for something near the
// first player that starts a special partner action: the held object (kind 3 id 0xe: pulled together with the second
// player or aimed at), the carried object (kind 3 id 0x17), or, with no special state, an Em30 that can be attacked (rupee
// rush floors) or a bomb-like object (kind 8 action 3) within range. Returns FALSE on every path.
BOOL Knife_Single_SinglePlay_UpdateEnemyCheck(void *self, SpWorkPair *pair) {
    SinglePlayWork *work = (SinglePlayWork *)self;
    u8 special = pair->player0->specialState;
    u8 found;
    Entity *held;
    Entity *other;
    Entity *node;
    u8 facing;
    u32 keyBits;
    s32 dir;
    u8 color;
    SpKeyMasks masks;

    if (special >= 2 && work->unk_0a != 3) {
        if (special == 2) {
            held = *(Entity **)((u8 *)pair->data0 + 0x18);
            if (held != NULL && held->objKind == 3 && held->objId == 0xe) {
                pair->unk_38 = 1;
                if ((pair->player1->specialState & 2) && (other = *(Entity **)((u8 *)pair->data1 + 0x18)) != NULL &&
                    held->parent == other->parent) {
                    masks = data_020ddb38;
                    dir = pair->entity0->animationState >> 1;
                    if (!(pair->unk_18 & masks.v[(u8)(dir ^ 2)])) {
                        keyBits = *(u16 *)((u8 *)work + 0x14) | 1;
                    } else {
                        keyBits = *(u16 *)((u8 *)work + 0x14) | (u16)(masks.v[(u8)dir] | 1);
                    }
                    *(u16 *)((u8 *)work + 0x14) = keyBits;
                    work->unk_0c = 0;
                    return TRUE;
                }
                if (pair->distX <= 0x30 && pair->distY <= 0x30) {
                    facing = pair->entity0->animationState >> 1;
                    if (facing & 1) {
                        node = held->parent;
                        if (node != NULL) {
                            pair->unk_20 = pair->entity0->x.HALF.HI + ((node->x.HALF.HI - pair->entity0->x.HALF.HI) << 1);
                        } else {
                            pair->unk_20 = pair->entity0->x.HALF.HI + data_0211b2dc[facing];
                        }
                        pair->unk_22 = pair->entity0->y.HALF.HI;
                        pair->unk_34 = 6;
                    } else {
                        pair->unk_38 = 0;
                    }
                }
            }
        } else {
            other = *(Entity **)pair->entity0->unk_6c;
            if (other != NULL && (node = other->child) != NULL && node->objKind == 3 && node->objId == 0x17) {
                if (pair->distX <= 0x50 && pair->distY <= 0x50) {
                    facing = pair->entity0->animationState >> 1;
                    pair->unk_20 = pair->entity0->x.HALF.HI + data_0211b2f4[facing * 2];
                    pair->unk_22 = pair->entity0->y.HALF.HI + data_0211b2f4[facing * 2 + 1];
                    pair->unk_38 = 2;
                    *(u16 *)((u8 *)work + 0x2a) = 0;
                    work->unk_0a = 0;
                    work->unk_24 = work->unk_26 = work->unk_28 = *(u16 *)((u8 *)work + 0x2a);
                }
            }
        }
    } else {
        if (work->unk_0a <= 2 || (work->unk_0a > 0xc && work->unk_0a <= 0xf && pair->nearFlag != 0)) {
            found = 0;
            if (gameState.unk_01 == 2 && gameState.periodicFlag != 0) {
                node = (Entity *)data_0212c6b0[4].next;
                while (node != (Entity *)&data_0212c6d0) {
                    if (node->objId == 0x30 && node->type == 0 && Em30CheckAttack(node)) {
                        if (abs_s32(node->x.HALF.HI - pair->entity0->x.HALF.HI) <= *(s16 *)(data_0211b298 + 0x26) &&
                            abs_s32(node->y.HALF.HI - pair->entity0->y.HALF.HI) <= *(s16 *)(data_0211b298 + 0x24)) {
                            color = Em30GetRightColor(node);
                            found = 1;
                            work->unk_0a = (work->contNo == color) ? 0xe : 0xd;
                            break;
                        }
                    }
                    node = (Entity *)((EntityNode *)node)->next;
                }
            } else {
                node = (Entity *)data_0212c6b0[4].next;
                while (node != (Entity *)&data_0212c6d0) {
                    if (node->objId == 8 && node->action == 3) {
                        VecFx32 posA = {0, 0, 0};
                        posA.x = pair->entity0->x.HALF.HI << 12;
                        posA.y = pair->entity0->y.HALF.HI << 12;
                        VecFx32 posB = {0, 0, 0};
                        posB.x = node->x.HALF.HI << 12;
                        posB.y = node->y.HALF.HI << 12;
                        if (VEC_Distance(&posA, &posB) <= 0x20000) {
                            work->unk_0a = 0xf;
                            *(u16 *)((u8 *)work + 0x24) = 0;
                            found = 1;
                            break;
                        }
                    }
                    node = (Entity *)((EntityNode *)node)->next;
                }
            }
            if (!found && work->unk_0a > 2) {
                work->unk_0a = 1;
                Knife_Single_SinglePlay_SinglePlayLogList_UpdateCurrentLogDistance((u8 *)work + 0x34, 0x12);
            }
        }
    }
    return FALSE;
}
