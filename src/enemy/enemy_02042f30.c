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

// FAKE MATCH: Random takes no argument, but these call sites only match when a value is in r0 at the call.
// Revisit once the real source shape is known (see docs/nonmatching/fake_random_arg.md).
#define RANDOM_WITH_ARG(x) (((u32 (*)(u32))Random)((u32)(x)))

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
ARM void Enemy_SpawnRandomGroup(Entity *e) {
    Entity *spawned;
    switch (RANDOM_WITH_ARG((u32)e) % 3) {
    case 0:
        spawned = CreateProjectile(5);
        if (spawned != NULL) {
            spawned->type = 2;
            spawned->type2 = 1;
            spawned->direction = 0x10;
            spawned->parent = e;
            CopyPosition(e, spawned);
        }
        spawned = CreateProjectile(5);
        if (spawned != NULL) {
            spawned->type = 2;
            spawned->type2 = 1;
            spawned->direction = 0x10;
            spawned->parent = e;
            PositionRelative(e, spawned, -0xc0000, 0);
        }
        spawned = CreateProjectile(5);
        if (spawned != NULL) {
            spawned->type = 2;
            spawned->type2 = 1;
            spawned->direction = 0x10;
            spawned->parent = e;
            PositionRelative(e, spawned, 0xc0000, 0);
        }
        break;
    case 1:
        spawned = CreateProjectile(5);
        if (spawned != NULL) {
            spawned->type = 3;
            spawned->type2 = 1;
            spawned->direction = 0x10;
            spawned->parent = e;
            CopyPosition(e, spawned);
        }
        spawned = CreateProjectile(5);
        if (spawned != NULL) {
            spawned->type = 3;
            spawned->type2 = 1;
            spawned->direction = 0xd;
            spawned->parent = e;
            CopyPosition(e, spawned);
        }
        spawned = CreateProjectile(5);
        if (spawned != NULL) {
            spawned->type = 3;
            spawned->type2 = 1;
            spawned->direction = 0x13;
            spawned->parent = e;
            CopyPosition(e, spawned);
        }
        break;
    case 2:
        spawned = CreateProjectile(0xb);
        if (spawned != NULL) {
            spawned->type = 1;
            spawned->direction = 0x14;
            CopyPosition(e, spawned);
        }
        spawned = CreateProjectile(0xb);
        if (spawned != NULL) {
            spawned->type = 1;
            spawned->direction = 0x12;
            CopyPosition(e, spawned);
        }
        spawned = CreateProjectile(0xb);
        if (spawned != NULL) {
            spawned->type = 1;
            spawned->direction = 0xe;
            CopyPosition(e, spawned);
        }
        spawned = CreateProjectile(0xb);
        if (spawned != NULL) {
            spawned->type = 1;
            spawned->direction = 0xc;
            CopyPosition(e, spawned);
        }
        EnqueueSFX(0x9f);
        break;
    }
}
// Enemy_IsPartInSequence (0x02043148): true for a part (tags 3/0x30, type 0, action 0xb) whose phase timer is past 0x5a.

ARM BOOL Enemy_IsPartInSequence(Entity *e) {
    if (e->unk_08 == 3 && e->unk_09 == 0x30 && e->type == 0 && e->action == 0xb) {
        if (W(e)->phaseTimer > 0x5a) {
            return TRUE;
        }
    }
    return FALSE;
}

// Enemy_PartBSpriteIndex (0x02043184): the sprite index of part B for a part with tags 3/0x30, or 0xff otherwise.

ARM u8 Enemy_PartBSpriteIndex(Entity *e) {
    if (e->unk_08 != 3 || e->unk_09 != 0x30) {
        return 0xff;
    }
    return VPARTS(e)->partB->spriteSettings.b20 - 7;
}

// Enemy_RunHandlerTable (0x020431b8): runs this entity's handler from data_020d360c.

ARM void Enemy_RunHandlerTable(Entity *e) {
    EnemyFunctionHandler(e, data_020d360c);
}

// Enemy_DispatchAction (0x020431cc): runs the handler for this entity's action from data_020d35e4.

ARM void Enemy_DispatchAction(Entity *e) {
    data_020d35e4[e->action](e);
}

// Enemy_ReactToContact (0x020431e8): a contact byte from 0x84 up to 0x22 (wrapping past 0xff) sets the direction from
// unk_3e, may flip bit 2 of the sprite settings, and spawns an effect at this entity. Contact 0x80 turns this entity by
// two steps. Then the generic knockback handler runs.

ARM void Enemy_ReactToContact(Entity *e) {
    u8 contact = e->contactFlags;
    u8 offset = contact - 0x84;
    if (offset <= 0x9e) {
        e->direction = e->unk_3e;
        if (e->unk_3e & 0xf) {
            SPRITE_BIT2(e)->bit2 = ((e->unk_3e >> 4) ^ 1) & 1;
        }
        e->speed = 0x480;
        u8 value;
        if (e->type != 0) {
            value = data_020d35e0[e->type - 1];
        } else {
            value = data_020d35fc[RANDOM_WITH_ARG(e->speed) & 0xf];
        }
        Entity *fx = CreateFx(0, value, 1);
        if (fx != NULL) {
            fx->direction = (e->direction ^ 0x10) | 0x80;
            CopyPosition(e, fx);
        }
    } else if (contact == 0x80) {
        int step = (RANDOM_WITH_ARG(offset) & 1) ? 2 : -2;
        u8 turned = e->direction + (u8)step;
        e->direction = turned & 0x1f;
    }
    GenericKnockback(e, data_020d360c);
}

// Enemy_RemoveIfOffscreen (0x020433dc): animates, runs func_02043428, and removes the entity when it is outside the
// box around (0x168, 0x190) of size (0x120, 0xd0).
