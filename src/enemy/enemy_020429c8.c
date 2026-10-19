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
ARM void Enemy_UpdateWithChildSfx(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->hitbox = data_020d34d2;
        InitAnimationForceUpdate(e, 2);
        Enemy_SetSpriteFromTable(e);
    }
    PositionRelative(e->child, e, 0, 1);
    if (e->frame & 2) {
        if (e->unk_6c[4] != 0) {
            return;
        }
        e->unk_6c[4] = 1;
        EnqueueSFX(0x9c);
    } else {
        e->unk_6c[4] = 0;
    }
}

// Enemy_InitAndUpdateChild (0x02042a5c): on the first action starts action 1 with animation 3 and sets up with
// Enemy_SetSpriteFromTable. Every frame updates the child through PositionRelative.

ARM void Enemy_InitAndUpdateChild(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->hitbox = data_020d34ca;
        InitAnimationForceUpdate(e, 3);
        Enemy_SetSpriteFromTable(e);
    }
    PositionRelative(e->child, e, 0, 1);
}
// Enemy_SpawnPartPair (0x02042c18): allocates two parts, links both to this entity's parent and to this entity, copies
// this entity's position into each, and registers both. Returns FALSE when either allocation fails.
