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
ARM BOOL Enemy_SpawnPartPair(Entity *e) {
    Entity *a;
    Entity *b;
    if ((a = func_0204bcc8()) != NULL && (b = func_0204bd00()) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        a->unk_09 = 0x30;
        b->unk_09 = 0x30;
        a->type = 3;
        b->type = 3;
        a->type2 = 2;
        b->type2 = 3;
        a->parent = e->parent;
        b->parent = e->parent;
        a->child = e;
        b->child = e;
        b->unk_6c[4] = e->direction;
        CopyPosition(e, a);
        CopyPosition(e, b);
        func_0204c178(4, a);
        func_0204c178(4, b);
        return TRUE;
    }
    return FALSE;
}

// Enemy_SpawnPartPairWithSfx (0x02042cc8): like Enemy_SpawnPartPair with different types and directions. Stores the
// two parts in this entity's part slots and plays sound 0xa2.

ARM int Enemy_SpawnPartPairWithSfx(Entity *e) {
    Entity *a;
    Entity *b;
    if ((a = func_0204bcc8()) != NULL && (b = func_0204bd00()) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        a->unk_09 = 0x30;
        b->unk_09 = 0x30;
        a->type = 1;
        b->type = 2;
        a->parent = e->parent;
        b->parent = e->parent;
        a->child = e;
        b->child = e;
        CopyPosition(e, a);
        CopyPosition(e, b);
        func_0204c178(4, a);
        func_0204c178(4, b);
        VPARTS(e)->partA = a;
        VPARTS(e)->partB = b;
        EnqueueSFX(0xa2);
        return 1;
    }
    return 0;
}
// Enemy_SetSpriteFromTable (0x02042d7c): picks the sprite index from data_020f26c3 by the child's state and this type,
// and copies it into the second sprite index field.

ARM void Enemy_SetSpriteFromTable(Entity *e) {
    e->spriteSettings.b20 = data_020f26c3[e->child->unk_6c[7] + e->type - 1];
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

// Enemy_SpawnRandomGroup (0x02042f30): picks one of three spawn groups at random. Group 0 makes three type-2 parts
// (the two side ones are offset from this entity), group 1 makes three type-3 parts, and group 2 makes four type-1
// parts placed at this entity's position and plays sound 0x9f.
