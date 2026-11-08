#include "engine/functions.h"
#include "knife/comm/singleplay_movepartner.h"

using namespace Knife::Single::SinglePlay;

// Knife::Single::SinglePlay::UpdateMovePartner(SinglePlayWork&, SpWorkPair&) (0x02094044): moves the partner (second
// player) after the controlled player. Records the controlled player's position in the log list, then picks the
// partner's target position from the follow state work->unk_0a (0 follow the log, 2 catch up, 0x10..0x12 go to the
// partner, 0x13 reset the log) and the default rules (wait, step aside, wall probe). The tail applies the formation,
// warp, truck, enemy, wall, formation-mode, stop-warp and near/far handlers in turn; the first one that returns TRUE
// ends the update. Entries of the log list hold 16.16 positions (the s32 words at +4 and +8).

#define LOG ((SinglePlayLogList *)((u8 *)work + 0x34))

void Knife_Single_SinglePlay_UpdateMovePartner(void *self, SpWorkPair *pair) {
    SinglePlayWork *work = (SinglePlayWork *)self;

    if (pair->entity0 == NULL || pair->entity1 == NULL) {
        return;
    }
    work->contChanging = ((pair->entity0->animationState >> 1) + 1) % 4 + 1;
    if (Knife_Single_SinglePlay_SinglePlayLogList_SetLog_09a2e0(LOG, pair->entity0, pair->unk_18, pair->entity0->speed, 0x12,
                                                                *(s16 *)&work->unk_2c, *(s16 *)&work->unk_2e)) {
        if (work->unk_0a == 0) {
            if (pair->nearFlag != 0) {
                if (work->contNo == 0) {
                    work->unk_0a = 1;
                }
            }
        } else {
            LOG->UpdateCurrentLogDistance(0x12);
            pair->unk_1e = LOG->GetCurrentLog()->kind;
        }
        pair->unk_3b = 1;
    }
    if (pair->entity0->speed != (pair->entity1->speed >> ((PlayerBits3e *)&pair->player1->unk_3e)->hi)) {
        pair->unk_3c = 1;
    }
    switch (work->unk_0a) {
    case 0x13:
        pair->unk_20 = pair->entity0->x.HALF.HI;
        pair->unk_22 = pair->entity0->y.HALF.HI;
        LOG->Initialize();
        break;
    case 0:
        {
            const SinglePlayLog *entry = &LOG->log[LOG->oldest];
            pair->unk_20 = entry->pos1.y;
            pair->unk_22 = entry->pos2.y;
        }
        break;
    case 0x10:
    case 0x11:
    case 0x12:
        pair->unk_20 = pair->entity1->x.HALF.HI;
        pair->unk_22 = pair->entity1->y.HALF.HI;
        break;
    case 2:
        if (pair->entity1->action == 6) {
            pair->unk_20 = pair->entity1->x.HALF.HI;
            pair->unk_22 = pair->entity1->y.HALF.HI;
            LOG->Initialize();
            pair->unk_1e = 0;
            break;
        }
        if (pair->entity1->unk_42 == 0) {
            if ((pair->distX < 4 && pair->distY < 4) ||
                !(pair->distX < 0x24 && pair->distY < 0x24 && LOG->distance < 0x12000)) {
                LOG->UpdateCurrentLogDistance(0x12);
                work->unk_0a = 1;
            } else {
                POS posA = LOG->GetCurrentLogPos();
                VecFx32 vecA = {0, 0, 0};
                s32 dx = 0;
                s32 dy;
                vecA.x = posA.x << 12;
                vecA.y = posA.y << 12;
                VecFx32 vecB = {0, 0, 0};
                vecB.x = pair->entity1->x.HALF.HI << 12;
                vecB.y = pair->entity1->y.HALF.HI << 12;
                s32 total = VEC_Distance(&vecA, &vecB);
                dy = 0;
                if (total + LOG->distance >= 0x12000) {
                    s16 limit = *(const s16 *)(data_0211b298 + 0x2e);
                    int diffX = (s16)(posA.x - pair->entity1->x.HALF.HI);
                    s16 diffY = posA.y - pair->entity1->y.HALF.HI;
                    if (limit < diffX) {
                        pair->unk_1e |= 0x10;
                    } else if (diffX < -limit) {
                        pair->unk_1e |= 0x20;
                    } else {
                        dx = diffX;
                    }
                    if (diffY > limit) {
                        pair->unk_1e |= 0x80;
                    } else if (diffY < -limit) {
                        pair->unk_1e |= 0x40;
                    } else {
                        dy = diffY;
                    }
                }
                pair->unk_20 = pair->entity1->x.HALF.HI + dx;
                pair->unk_22 = pair->entity1->y.HALF.HI + dy;
                break;
            }
        } else if (pair->entity1->unk_42 != 0) {
            pair->unk_20 = pair->entity1->x.HALF.HI;
            pair->unk_22 = pair->entity1->y.HALF.HI;
            LOG->Initialize();
            pair->unk_1e = 0;
            work->unk_0a = 2;
            if (pair->player1->unk_0b == 0) {
                pair->entity1->animationState = pair->entity0->animationState;
            }
            break;
        }
    default:
    {
        u8 mask = work->unk_0d[0];
        if (!(((mask & (1 << work->contNo)) && (pair->player1->statusFlags & 0x80)) || mask == (1 << (work->contNo ^ 1)))) {
            POS posC = LOG->GetCurrentLogPos();
            pair->unk_20 = posC.x;
            pair->unk_22 = posC.y;
            if (pair->player0->unk_24 - 0x176 == ((PalBits *)&pair->player0->paletteBits)->b &&
                (pair->nearFlag != 0 || (work->unk_12 & 2))) {
                pair->unk_20 = pair->entity1->x.HALF.HI;
                pair->unk_22 = pair->entity1->y.HALF.HI;
                pair->unk_1e = 0;
            } else if (pair->unk_3b == 0 && !(pair->unk_18 & 0xf0) &&
                       ((work->unk_12 & 3) == 2 || ((work->unk_12 & 3) == 1 && !(work->unk_0d[0] & 1)))) {
                pair->unk_20 = pair->entity0->x.HALF.HI;
                pair->unk_22 = pair->entity0->y.HALF.HI;
                LOG->Initialize();
                pair->unk_1e = 0;
            }
            if (pair->player1->unk_12 == 0x6c && pair->unk_3b != 0 && !(pair->player1->statusFlags & 0x80) &&
                (pair->entity1->layer & 0xc000) == (pair->entity0->layer & 0xc000) && work->unk_0a != 4 &&
                !(pair->player0->hitFlags & 0x40)) {
                POS posN = LOG->GetNextLogPos();
                int cellA = func_020898b4(func_02083ce4(*(s16 *)&pair->unk_20, (s16)(*(s16 *)&pair->unk_22 + 3), pair->entity1->layer));
                int cellB = func_02083d30(posN.x, (s16)(posN.y + 3), pair->entity1->layer);
                if (cellA == 0x6c && cellB != 0x21 && cellB != 0x25) {
                    POS posP = LOG->GetPrevLogPos();
                    if (abs_s32(posP.x - pair->entity1->x.HALF.HI) < 2 && abs_s32(posP.y - pair->entity1->y.HALF.HI) < 2) {
                        s16 stepX = abs_s32(posC.x - posP.x);
                        s16 stepY = abs_s32(posC.y - posP.y);
                        s32 steps = stepX + stepY;
                        if (steps < 5 && steps != 0) {
                            u16 savedFlags = pair->entity1->wallFlags;
                            s16 savedX = pair->entity1->x.HALF.HI;
                            s16 savedY = pair->entity1->y.HALF.HI;
                            pair->entity1->x.HALF.HI = *(s16 *)&pair->unk_20;
                            pair->entity1->y.HALF.HI = *(s16 *)&pair->unk_22;
                            func_0208a06c(pair->entity1);
                            if (pair->entity1->wallFlags & 0xee00) {
                                pair->entity1->x.HALF.HI = savedX;
                            }
                            if (pair->entity1->wallFlags & 0xee) {
                                pair->entity1->y.HALF.HI = savedY;
                            }
                            pair->entity1->wallFlags = savedFlags;
                            if (pair->player1->unk_0b == 0) {
                                const SinglePlayLog *cur = LOG->GetCurrentLog();
                                const SinglePlayLog *prev = &LOG->log[((u8 *)LOG)[3]];
                                s32 dx = *(const s32 *)&cur->pos1 - *(const s32 *)&prev->pos1;
                                s32 dy = *(const s32 *)&cur->pos2 - *(const s32 *)&prev->pos2;
                                u8 dirBits = 0;
                                if (abs_s32(dx) > abs_s32(dy)) {
                                    if (dx > data_02178de0) {
                                        dirBits |= 0x10;
                                    } else if (dx < -data_02178de0) {
                                        dirBits |= 0x20;
                                    }
                                } else {
                                    if (dy > data_02178de0) {
                                        dirBits |= 0x80;
                                    } else if (dy < -data_02178de0) {
                                        dirBits |= 0x40;
                                    }
                                }
                                if (dirBits & 0x10) {
                                    pair->entity1->animationState = 2;
                                } else if (dirBits & 0x20) {
                                    pair->entity1->animationState = 6;
                                } else if (dirBits & 0x40) {
                                    pair->entity1->animationState = 0;
                                } else if (dirBits & 0x80) {
                                    pair->entity1->animationState = 4;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            pair->unk_20 = pair->entity0->x.HALF.HI;
            pair->unk_22 = pair->entity0->y.HALF.HI;
            pair->unk_38 = 7;
            LOG->Initialize();
        }
    }
    }
    ((PlayerBits3e *)&pair->player1->unk_3e)->hi = 0;
    ((PlayerBits3e *)&pair->player0->unk_3e)->hi = ((PlayerBits3e *)&pair->player1->unk_3e)->hi;
    work->formationChanging = 1;
    {
        s16 stepLimit = *(const s16 *)(data_0211b298 + 0x18);
        *(s16 *)&pair->unk_34 = stepLimit;
        *(s16 *)&pair->unk_36 = stepLimit;
    }
    if ((pair->player0->statusFlags | pair->player1->statusFlags) & 0xc10) {
        if (!(pair->player1->statusFlags & 0x810) && (pair->player0->statusFlags & 0x810)) {
            Knife_Single_SinglePlay_SetContNoDirect(work, work->contNo ^ 1);
            return;
        }
        Knife_Single_SinglePlay_SetContNoDirect(work, work->contNo);
        return;
    }
    if ((pair->player0->unk_07 & 0x80) && (pair->player1->unk_07 & 0x80)) {
        Knife_Single_SinglePlay_SetContNoDirect(work, work->contNo);
        return;
    }
    ((PalBits *)&pair->player0->paletteBits)->a = 1;
    ((PalBits *)&pair->player1->paletteBits)->a = 3;
    if (frameCounter[0x11] != 0) {
        return;
    }
    if (!((pair->unk_18 | pair->unk_1e) & 0xf0)) {
        (*(s16 *)&pair->unk_34)--;
        (*(s16 *)&pair->unk_36)--;
    }
    if (Knife_Single_SinglePlay_UpdateWarpZoneCheck(work, pair)) {
        return;
    }
    if (Knife_Single_SinglePlay_returnZero_020956ec(work, pair)) {
        return;
    }
    if (Knife_Single_SinglePlay_UpdateTruck(work, pair)) {
        return;
    }
    if (work->contNo == 0) {
        if (Knife_Single_SinglePlay_UpdateEnemyCheck(work, pair)) {
            return;
        }
    }
    if (work->contNo == 0) {
        if (Knife_Single_SinglePlay_UpdateWallCheck(work, pair)) {
            return;
        }
    }
    if (work->contNo == 0) {
        if (Knife_Single_SinglePlay_UpdateFormationMode(work, pair)) {
            return;
        }
    } else {
        if (Knife_Single_SinglePlay_UpdateFormationMode2p(work, pair)) {
            return;
        }
    }
    Knife_Single_SinglePlay_SinglePlayWork_SetTargetPos(pair);
    if (work->unk_20 != pair->player1->unk_22) {
        work->unk_05[0] = 0;
        work->unk_20 = pair->player1->unk_22;
    }
    if (Knife_Single_SinglePlay_UpdateStopWarp(work, pair)) {
        return;
    }
    if (Knife_Single_SinglePlay_returnZero_02096e40(work, pair)) {
        return;
    }
    if ((s16)pair->unk_30 < (s16)pair->unk_34 && (s16)pair->unk_32 < (s16)pair->unk_36 && !(pair->player0->hitFlags & 0x40)) {
        Knife_Single_SinglePlay_UpdateNear(work, pair);
        return;
    }
    if (pair->player0->statusFlags & 0x200) {
        return;
    }
    Knife_Single_SinglePlay_UpdateFar(work, pair);
}
