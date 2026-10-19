// Implementer B, round 3: functions of 0x020417e8 to 0x02048264 (matched, all 0 differ, 0 size mismatches).
// Address -> name (also in scratch/agentB/renames.txt):
//   Enemy_UpdateWithParentTrigger Enemy_UpdateWithParentTrigger    Enemy_InitAtSpawn Enemy_InitAtSpawn
//   Enemy_FollowOrbitOffset Enemy_FollowOrbitOffset          Enemy_StepLimitsUp Enemy_StepLimitsUp
//   Enemy_RampSpeedFromParent Enemy_RampSpeedFromParent        Enemy_StepLimitsDown Enemy_StepLimitsDown
//   Enemy_CountdownThenHandOff Enemy_CountdownThenHandOff       Enemy_CheckTileThenSpawnFx Enemy_CheckTileThenSpawnFx
//   Enemy_IsTargetable Enemy_IsTargetable               Enemy_InsertSegment Enemy_InsertSegment
//   Enemy_InitFollower Enemy_InitFollower               Enemy_TimedTurnDirection Enemy_TimedTurnDirection
//   Enemy_RunPartsTimeline Enemy_RunPartsTimeline           Enemy_UpdateWithChildSfx Enemy_UpdateWithChildSfx
//   Enemy_InitAndUpdateChild Enemy_InitAndUpdateChild         Enemy_SpawnPartPair Enemy_SpawnPartPair
//   Enemy_SpawnPartPairWithSfx Enemy_SpawnPartPairWithSfx       Enemy_SetSpriteFromTable Enemy_SetSpriteFromTable
//   Enemy_SpawnRandomGroup Enemy_SpawnRandomGroup           Enemy_IsPartInSequence Enemy_IsPartInSequence
//   Enemy_PartBSpriteIndex Enemy_PartBSpriteIndex           Enemy_RunHandlerTable Enemy_RunHandlerTable
//   Enemy_DispatchAction Enemy_DispatchAction             Enemy_ReactToContact Enemy_ReactToContact
//   Enemy_RemoveIfOffscreen Enemy_RemoveIfOffscreen          Enemy_StartScript Enemy_StartScript
//   Enemy_ArmSharedState Enemy_ArmSharedState             Enemy_RunGlobalHandler Enemy_RunGlobalHandler
//   Enemy_UpdateSlotA Enemy_UpdateSlotA                Enemy_UpdateSlotB Enemy_UpdateSlotB
// Not matched (kept in scratch/agentB/nonmatching): func_02042044, func_020426e0, func_02042abc, func_02042dc8,
// func_020432dc, func_02043428, Enemy_RunScriptCommand, func_0204363c.

#include "enemy/enemy_020417e8.h"
#include "global.h"

extern const EntityFunc data_020d34a4[];
extern const u16 data_020d3486[];
extern const s8 data_020d346c[];
extern const s8 data_020d346f[];
extern const u16 data_020d347a[];
extern u8 data_021348ec[];
extern const u8 data_020d35e0[];
extern const u8 data_020d35fc[];
extern const EntityFunc data_020d35e4[];
extern const EntityFunc data_020d360c[];
extern const u8 data_020d34e2[];

// Enemy_UpdateWithParentTrigger (0x020417e8): a follower whose parent raises trigger bit 0 restarts in action 6.
// Then runs the action handler and, for type 2, the two helpers below and a 0x1e-frame cycle that plays sound 0x59.
ARM void Enemy_UpdateWithParentTrigger(Entity *e) {
    if (e->type2 != 0) {
        Vars_Parent *parent = VARS(Vars_Parent, e->parent);
        if (parent->triggerFlags & 1) {
            e->action = 6;
            e->timer = 0x1e;
            SPRITE_VIEW(e)->b8 |= 2;
            W(e)->subPosX = 0xf0;
            W(e)->subPosY = 0x120;
            parent->triggerFlags &= 0xfe;
        }
    }
    data_020d34a4[e->action](e);
    if (e->type != 2) {
        return;
    }
    func_02042044(e);
    Enemy_CheckTileThenSpawnFx(e);
    W(e)->cycleTimer--;
    if (W(e)->cycleTimer != 0) {
        return;
    }
    W(e)->cycleTimer = 0x1e;
    func_02085f98(e, 0x59);
}

// Enemy_InitAtSpawn (0x020418bc): sets the start action and offsets from the type, resets the cycle timer, then
// centres the scroll position at (0x800, 0x600) and refreshes the scroll arguments.

ARM void Enemy_InitAtSpawn(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->y.HALF.LO = 2 - e->type;
    e->z.HALF.HI = data_020d346c[e->type];
    W(e)->cycleTimer = 0x1e;
    if (e->type != 0) {
        if (e->type == 1) {
            e->unk_5e.b0 = 3;
        }
    } else {
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 1;
    }
    Enemy_SetDefaultAuxBytes(e);
    InitAnimationForceUpdate(e, 0);
    func_02085cf8(e);
    W(e)->subPosX = 0x800;
    W(e)->subPosY = 0x600;
    data_0212c574[0] = W(e)->subPosX;
    data_0212c574[1] = W(e)->subPosY;
    data_0212c574[2] = 0;
    func_0205063c(data_0212c574, e);
}

// Enemy_FollowOrbitOffset (0x02041a3c): when the parent is in state 1 this switches to action 3. Otherwise a
// follower copies the parent's position, while the first type nudges itself by the packed offset for this frame.
// A child records the offset it has just moved by, in its own table.
