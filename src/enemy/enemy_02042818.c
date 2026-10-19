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
ARM void Enemy_RunPartsTimeline(Entity *e) {
    UpdateAnimationSingleFrame(e);
    W(e)->phaseTimer--;
    if (W(e)->phaseTimer > 0x5a) {
        func_02042dc8(e);
        if (VPARTS(e)->partA->frame != 0) {
            VPARTS(e)->partA->unk_3c |= 0x80;
        } else {
            UpdateAnimationSingleFrame(VPARTS(e)->partA);
        }
        if (VPARTS(e)->partB->frame != 0) {
            VPARTS(e)->partB->unk_3c |= 0x80;
            return;
        }
        UpdateAnimationSingleFrame(VPARTS(e)->partB);
        return;
    }
    if (W(e)->phaseTimer > 0x1e) {
        VPARTS(e)->partA->unk_3c &= 0x7f;
        VPARTS(e)->partB->unk_3c &= 0x7f;
        UpdateAnimationSingleFrame(VPARTS(e)->partA);
        UpdateAnimationSingleFrame(VPARTS(e)->partB);
        return;
    }
    if (W(e)->phaseTimer == 0x1e) {
        Enemy_SpawnRandomGroup(e);
        VPARTS(e)->partA->unk_3c |= 0x80;
        VPARTS(e)->partB->unk_3c |= 0x80;
        return;
    }
    if (W(e)->phaseTimer != 0) {
        return;
    }
    e->action = 0xc;
    VPARTS(e)->partA->unk_3c &= 0x7f;
    VPARTS(e)->partB->unk_3c &= 0x7f;
    InitAnimationForceUpdate(e, 1);
    InitAnimationForceUpdate(VPARTS(e)->partA, 4);
    InitAnimationForceUpdate(VPARTS(e)->partB, 5);
}
// Enemy_UpdateWithChildSfx (0x020429c8): on the first action starts action 1 with animation 2 and sets up with
// Enemy_SetSpriteFromTable. Every frame updates the child through PositionRelative. While the frame bit 2 is set, plays sound 0x9c
// once, using the flag byte at 0x70 to remember it.
