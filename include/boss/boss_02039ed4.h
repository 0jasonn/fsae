#ifndef UNKNOWN_WIP_A_BOSS_02039ED4_H
#define UNKNOWN_WIP_A_BOSS_02039ED4_H

#include "engine/entity.h"
#include "engine/player.h"

// Boss actor fields used by src/boss/boss_02039ed4.c and its siblings. File-local overlay, not shared.
typedef struct Vars_BossDying {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u8 dying; // nonzero once the boss has started its death sequence
    /* 71 */ u8 unk_71[5];
    /* 76 */ u16 dyingTimer; // frames until Boss_Explode
} Vars_BossDying;
#define VBD(e) VARS(Vars_BossDying, e)

typedef struct Vars_BossLaunch {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ u16 launchTimer;
} Vars_BossLaunch;
#define VBL(e) VARS(Vars_BossLaunch, e)

typedef struct Vars_BossTarget {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 unk_78;
    /* 79 */ u8 unk_79[3];
    /* 7c */ u8 unk_7c;
    /* 7d */ u8 unk_7d;
    /* 7e */ u16 unk_7e;
} Vars_BossTarget;
#define VBT(e) VARS(Vars_BossTarget, e)

typedef struct Tbl3 {
    u8 v[3];
} Tbl3;

extern const EntityFunc data_020d1da4[];
extern const u8 data_020d1d90[];
extern const u8 data_020d1d8c[];
extern const u8 data_020d1d9b[];
extern const u16 data_0212c58c[];
extern Entity *data_0212c7d4[];
extern const s8 data_020d1d96[];
extern const s8 data_020d1d93[];
extern const u8 data_020d1d88[];
extern const EntityFunc data_020d1ec8[];
extern const EntityFunc data_020d1f48[];
extern const u8 data_020d1ec0[];
extern const u8 data_020d1eb0[];
extern const s8 data_020d1eac[];
extern UnkStruct_0212c7c8 data_0212c7c8;
extern const u8 data_020d1db4[];
extern const u16 data_020d1dac[];
extern const EntityFunc data_020d1e14[];
extern const EntityFunc data_020d1e2c[];
extern const s8 data_020d1cbc[];

void Boss_SetAnimation(Entity *e, int a);
void Boss_StartDying(Entity *e);
void Boss_CheckWallDeath(Entity *e);
int Boss_UpdateLaunchWait(Entity *e);
void Boss_StartAction3(Entity *e);
void Boss_UpdateContact(Entity *e);
void Boss_DispatchAction2(Entity *e);
void Boss_SyncChildToParent(Entity *e);
void Boss_UpdateTarget(Entity *e);
void Boss_SpawnChild(Entity *e);
void Boss_OnAnimLoop(Entity *e);
void Boss_AdvanceAfterLoop(Entity *e);
void Boss_RetargetTick(Entity *e);
void Boss_UpdateChildHover(Entity *e);
void Boss_SubtimerStep(Entity *e);
void Boss_InitFromParent(Entity *e);
void Boss_DeleteIfParentFree(Entity *e);
void Boss_UpdateAnimFromDirection(Entity *e);
void Boss_UpdateAnimPair(Entity *e);
void Boss_LaunchChild(Entity *e);
void Boss_LaunchChildOnAction4(Entity *e);
void Boss_RunStateTable(Entity *e);
void Boss_DispatchAction3(Entity *e);
void Boss_TargetEnterAction(Entity *e);
void Boss_SetupFromAction1(Entity *e);
void Boss_NoOp(Entity *e);
void Boss_ContinueWave(Entity *e);
void Boss_RetargetDirectionTimer(Entity *e);
void Boss_ProbeAndTurn(Entity *e);
void Boss_ProbeAndTurnAlt(Entity *e);
void Boss_FrameStep(Entity *e);
void Boss_MarkGridCell(Entity *e);
void Boss_RestoreGridCell(Entity *e);
int Boss_CheckGridBlocked(Entity *e);
void Boss_SnapDirection(Entity *e);
void Boss_EnterAction6(Entity *e);

typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;
extern UnkStruct_0212c648 data_0212c648;
int func_02056f30(int a);
extern const u16 data_020d1eb8[];
extern const EntityFunc data_020d2044[];
extern const EntityFunc data_020d205c[];
extern const u8 data_020d2000[];
void Boss_ResetIdleTimer(Entity *e);
void Boss_TurnTowardTarget(Entity *e);
void Boss_RunStateTableB(Entity *e);
void Boss_DispatchAction4(Entity *e);
void Boss_GenericKnockbackB(Entity *e);
void Boss_SetupAltHitbox(Entity *e);
void Boss_TimerThenAnim(Entity *e);
void Boss_FrameWaitThenAnim(Entity *e);
void Boss_LaunchAtNearest(Entity *e);
void Boss_AnimateUntilDone(Entity *e);
void Boss_AnimFrameThenInit(Entity *e);
void Boss_RunStateTableC(Entity *e);
void Boss_DispatchAction5(Entity *e);
void Boss_CheckContactDamage(Entity *e);
int func_020856cc(Entity *e, int a);
extern const u8 data_020d1ff4[];
extern const EntityFunc data_020d21dc[];
extern const EntityFunc data_020d215c[];

typedef struct Vars_BossCell {
    /* 00 */ u8 unk_00[0x7a];
    /* 7a */ u8 savedCell; // grid cell value saved when the boss claims its cell
} Vars_BossCell;
#define VBCELL(e) VARS(Vars_BossCell, e)

typedef struct Vars_BossPtr {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target; // player the boss aims at
} Vars_BossPtr;
#define VBP(e) VARS(Vars_BossPtr, e)

typedef struct Vars_BossHalf {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 unk_7c;
} Vars_BossHalf;
#define VBH(e) VARS(Vars_BossHalf, e)

typedef struct Vars_ParentWord {
    /* 00 */ u8 unk_00[4];
    /* 04 */ s32 unk_04;
} Vars_ParentWord;
#define VPW(e) VARS(Vars_ParentWord, e)

Entity *CreateEnemy(int id);
void func_02084788(Entity *e);
u8 func_02084fd0(Entity *e, Entity *target);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
void func_0208919c(void);
void func_020260c8(Entity *a, int b);
void PositionRelative(Entity *e, Entity *target, int a, int b);
void SoundReq(int sfx);
void DeleteEntity(Entity *e);
u8 func_02045a8c(int dir);

int func_02083c75_unk(Entity *e, int a, int b);
void func_020768d8(Entity *e);
void func_020859e0(Entity *e, int a);
void func_02084ab8(Entity *e, Entity *other);
Entity *func_020849c8(Entity *e);
u8 func_02084a30(Entity *e);

#endif
