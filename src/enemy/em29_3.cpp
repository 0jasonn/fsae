#include "engine/functions.h"
// Implementer B, round 3: functions of 0x020417e8 to 0x02048264 (matched, all 0 differ, 0 size mismatches).
// Address -> name (also in scratch/agentB/renames.txt):
//   Em29 Em29    em29_init em29_init
//   em29_move em29_move          em29_vacuumInit em29_vacuumInit
//   em29_vacuum em29_vacuum        em29_vacuumEnd em29_vacuumEnd
//   em29_die em29_die       breakSekichu breakSekichu
//   movecheck movecheck               hikiyoseSet hikiyoseSet
//   em30_type0_init em30_type0_init               em30_type0_wait em30_type0_wait
//   type0_attackBlossom type0_attackBlossom           em30_type1 em30_type1
//   em30_type2 em30_type2         setUde setUde
//   setFlower setFlower       Enemy_SetSpriteFromTable Enemy_SetSpriteFromTable
//   flowerTamaSet flowerTamaSet           Em30CheckAttack Em30CheckAttack
//   Em30GetRightColor Em30GetRightColor           Enemy_RunHandlerTable Enemy_RunHandlerTable
//   em31_normal em31_normal             em31_damage em31_damage
//   em31_move em31_move          Enemy_StartScript Enemy_StartScript
//   Enemy_ArmSharedState Enemy_ArmSharedState             Encounter Encounter
//   plback plback                plfront plfront
// Not matched (kept in scratch/agentB/nonmatching): plhikiyose, type0_kamae, em30_type3, damageCheck,
// em31_init, honyaMove, honyaGetInfo, func_0204363c.

#include "enemy/em29.h"
#include "global.h"

extern const EntityFunc em29_stateTable[];
extern const u16 em29_scrollLimitsIn[];
extern const s8 em29_restZ[];
extern const s8 em29_sinkZ[];
extern const u16 em29_scrollLimitsOut[];
extern u8 encntSharedState[];
extern const u8 em31_typeFx[];
extern const u8 em31_randomFx[];
extern const EntityFunc em31_stateTable[];
extern const EntityFunc em31_handlerTable[];
extern const u8 em30_type0Hitbox[];

// Em29 (0x020417e8): a follower whose parent raises trigger bit 0 restarts in action 6.
// Then runs the action handler and, for type 2, the two helpers below and a 0x1e-frame cycle that plays sound 0x59.
ARM void em29_move(Entity *e) {
    Entity *parent = e->parent;
    if (VARS(Vars_Parent, parent)->state == 1) {
        e->action = 3;
        return;
    }
    u16 oldX = e->x.HALF.HI;
    u16 oldY = e->y.HALF.HI;
    if (e->type2 != 0) {
        e->x.HALF.HI = parent->x.HALF.HI;
        e->y.HALF.HI = parent->y.HALF.HI;
    } else {
        u8 *offsets = W(e)->orbitOffsets;
        u8 index = (data_0212c5bc + 1) & 7;
        e->x.HALF.HI += (offsets[index] & 0xf) - 8;
        e->y.HALF.HI += ((offsets[index] & 0xf0) >> 4) - 8;
    }
    if (e->child != NULL) {
        int dx = e->x.HALF.HI - oldX;
        int dy = e->y.HALF.HI - oldY;
        W(e->child)->orbitOffsets[data_0212c5bc & 7] = ((dx + 8) & 0xf) | (((dy + 8) & 0xf) << 4);
    }
    UpdateAnimationSingleFrame(e);
}

// em29_vacuumInit (0x02041b18): steps the scroll position by +8 in x and -8 in y, clamps each to its limit,
// and sinks z. When both limits are reached and z has reached its limit, goes to action 4 after one frame.

ARM void em29_vacuumInit(Entity *e) {
    W(e)->subPosX += 8;
    W(e)->subPosY -= 8;
    u16 limitX = em29_scrollLimitsIn[e->type * 2];
    u8 reached = 0;
    if (W(e)->subPosX >= limitX) {
        W(e)->subPosX = limitX;
        reached++;
    }
    u16 limitY = em29_scrollLimitsIn[e->type * 2 + 1];
    if (W(e)->subPosY <= limitY) {
        W(e)->subPosY = limitY;
        reached++;
    }
    e->z.WORD -= 0x8000;
    s16 limitZ = em29_sinkZ[e->type];
    if (limitZ >= e->z.HALF.HI) {
        e->z.HALF.HI = limitZ;
        if (reached == 2) {
            e->action = 4;
            e->timer = 1;
        }
    }
    scrollArgs[0] = W(e)->subPosX;
    scrollArgs[1] = W(e)->subPosY;
    scrollArgs[2] = 0;
    ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
    UpdateAnimationSingleFrame(e);
}

// em29_vacuum (0x02041c00): with the parent's state at 0 this sets action 5 and stops. Otherwise it
// counts the timer down and, when it reaches 0, resets it and adds 0x30 to the speed.

ARM void em29_vacuum(Entity *e) {
    if (VARS(Vars_Parent, e->parent)->state == 0) {
        e->action = 5;
        e->speed = 0;
    } else {
        e->timer--;
        if (e->timer == 0) {
            e->timer = 0x1e;
            e->speed += 0x30;
        }
    }
    UpdateAnimationSingleFrame(e);
}

// em29_vacuumEnd (0x02041c50): the mirror of em29_vacuumInit: steps -8 in x and +8 in y, sinks z the
// other way, and goes to action 2 when both limits are reached and z has reached its limit.

ARM void em29_vacuumEnd(Entity *e) {
    W(e)->subPosX -= 8;
    W(e)->subPosY += 8;
    u16 limitX = em29_scrollLimitsOut[e->type * 2];
    u8 reached = 0;
    if (W(e)->subPosX <= limitX) {
        W(e)->subPosX = limitX;
        reached++;
    }
    u16 limitY = em29_scrollLimitsOut[e->type * 2 + 1];
    if (W(e)->subPosY >= limitY) {
        W(e)->subPosY = limitY;
        reached++;
    }
    e->z.WORD += 0x8000;
    s8 limitZ = em29_restZ[e->type];
    if (limitZ <= e->z.HALF.HI) {
        e->z.HALF.HI = limitZ;
        if (reached == 2) {
            e->action = 2;
        }
    }
    scrollArgs[0] = W(e)->subPosX;
    scrollArgs[1] = W(e)->subPosY;
    scrollArgs[2] = 0;
    ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
    UpdateAnimationSingleFrame(e);
}
// em29_die (0x02041d30): clears the child's offset slot for this frame. While the timer runs, the
// entity moves up and right on the scroll position. When it ends, the child takes this entity's place under the
// parent, copies the parent's position, and the entity is removed.

ARM void em29_die(Entity *e) {
    if (e->child != NULL) {
        W(e->child)->orbitOffsets[data_0212c5bc & 7] = 0x88;
    }
    e->timer--;
    if (e->timer != 0) {
        W(e)->subPosX -= 4;
        W(e)->subPosY += 8;
        scrollArgs[0] = W(e)->subPosX;
        scrollArgs[1] = W(e)->subPosY;
        scrollArgs[2] = 0;
        ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
        UpdateAnimationSingleFrame(e);
        return;
    }
    if (e->child != NULL) {
        e->parent->parent = e->child;
        e->child->type2 = 1;
        e->child->x.HALF.HI = e->parent->x.HALF.HI;
        e->child->y.HALF.HI = e->parent->y.HALF.HI;
        moveInit(e->child);
        if (e->child->child != NULL) {
            e->child->child->x.HALF.HI = e->parent->x.HALF.HI;
            e->child->child->y.HALF.HI = e->parent->y.HALF.HI;
            moveInit(e->child->child);
        }
    }
    func_02085d34(e);
    PutObjWork(e);
}

// breakSekichu (0x02041e58): converts the position into a 64-column cell index relative to
// data_0212c648. When the cell check returns 0x138, spawns effect 0xf on this entity and reports the cell.

ARM void breakSekichu(Entity *e) {
    u16 cell = ((e->x.HALF.HI - data_0212c648.unk_18) >> 4) | (((e->y.HALF.HI - data_0212c648.unk_1a) >> 4) << 6);
    if (func_02083ca8(cell, e->unk_50) != 0x138) {
        return;
    }
    Entity *fx = GetSetWork(0xf, 0xf, 0);
    if (fx == NULL) {
        return;
    }
    ObjPosCopy(e, fx);
    RewCell(0x2f, cell, e->unk_50);
}

// movecheck (0x02041edc): true when the entity is active, its player slot has no blocking flags, and the
// entity is not in action 6.

ARM BOOL movecheck(Entity *e) {
    if (func_020860dc(e) != 0) {
        if (data_0212ceb0[e->type].unk_36 & 0x100) {
            return FALSE;
        }
        if (data_0212ceb0[e->type].unk_03[2] == 1) {
            return FALSE;
        }
        return e->action != 6;
    }
    return FALSE;
}

// hikiyoseSet (0x02041f48): when the leader is close enough and free, creates a new segment between the
// leader and this segment and returns TRUE. Otherwise nudges the leader with func_020852f8 and returns FALSE.

ARM BOOL hikiyoseSet(Entity *segment, Entity *leader, u16 speed) {
    if (leader->child != NULL) {
        if (leader->child->unk_08 == 4 && leader->child->unk_09 == 2) {
            return FALSE;
        }
    }
    if ((s32)(u16)(leader->x.HALF.HI - segment->x.HALF.HI + 6) <= 12) {
        if ((s32)(u16)(leader->y.HALF.HI - segment->y.HALF.HI + 6) <= 12) {
            if (leader->action != 2 || leader->subAction > 1) {
                if (func_020860dc(leader) != 0) {
                    Entity *inserted = EmGetTama(segment, 2, 0);
                    if (inserted != NULL) {
                        inserted->z.HALF.HI = leader->z.HALF.HI;
                        inserted->parent = segment->parent;
                        inserted->child = segment;
                        W(inserted)->target = leader;
                        leader->child = inserted;
                        return TRUE;
                    }
                }
            }
        }
    }
    func_020852f8(leader, speed, GetFacingDirection(leader, segment));
    return FALSE;
}

// em30_type0_init (0x02042318): sets up a follower entity when setUde accepts it.
