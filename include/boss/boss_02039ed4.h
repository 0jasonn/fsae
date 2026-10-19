#ifndef UNKNOWN_WIP_A_BOSS_02039ED4_H
#define UNKNOWN_WIP_A_BOSS_02039ED4_H

#include "engine/entity.h"
#include "engine/player.h"

// Boss actor fields used by src/boss/boss_02039ed4.c and its siblings. File-local overlay, not shared.
typedef struct Vars_BossDying {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u8 dying; // nonzero once the boss has started its death sequence
    /* 71 */ u8 unk_71[5];
    /* 76 */ u16 dyingTimer; // frames until explodeSet
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

void em08_seqSet(Entity *e, int a);
void tenka(Entity *e);
void searchCandle(Entity *e);
int purupuru(Entity *e);
void piyoriSet(Entity *e);
void Em09(Entity *e);
void em09_normal(Entity *e);
void type2Move(Entity *e);
void em09_damage(Entity *e);
void em09_init(Entity *e);
void em09_wait(Entity *e);
void em09_appear(Entity *e);
void em09_move(Entity *e);
void em09_kuttsuki(Entity *e);
void em09_wait2(Entity *e);
void em09_type2_init(Entity *e);
void em09_type2_move(Entity *e);
void em09_seqSet(Entity *e);
void seqMove(Entity *e);
void kuttsukiReset(Entity *e);
void em09_kuttsuki_reset(Entity *e);
void Boss_RunStateTable(Entity *e);
void em10_normal(Entity *e);
void em10_damage(Entity *e);
void em10_init(Entity *e);
void Boss_NoOp(Entity *e);
void em10_awake(Entity *e);
void em10_move(Entity *e);
void em10_endmove0(Entity *e);
void em10_endmove1(Entity *e);
void em10_sleep(Entity *e);
void attset(Entity *e);
void attreset(Entity *e);
int poscheck(Entity *e);
void nextendmoveset(Entity *e);
void sleepSet(Entity *e);

typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;
extern UnkStruct_0212c648 data_0212c648;
int GetBgBuffAdrs(int a);
extern const u16 data_020d1eb8[];
extern const EntityFunc data_020d2044[];
extern const EntityFunc data_020d205c[];
extern const u8 data_020d2000[];
void em11_waitSet(Entity *e);
void dirSet(Entity *e);
void Boss_RunStateTableB(Entity *e);
void em11_normal(Entity *e);
void Boss_GenericKnockbackB(Entity *e);
void em11_init(Entity *e);
void em11_wait(Entity *e);
void em11_look(Entity *e);
void em11_tame(Entity *e);
void em11_jump(Entity *e);
void em11_land(Entity *e);
void Boss_RunStateTableC(Entity *e);
void em12_normal(Entity *e);
void em12_damage(Entity *e);
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

Entity *GetEnemyWork(int id);
void func_02084788(Entity *e);
u8 func_02084fd0(Entity *e, Entity *target);
void *KnifeApp_getInstance(void);
int KnifeApp_isWirelessMode(void *a);
u8 *Knife_Single_SinglePlay_GetInstance(void);
void func_0208919c(void);
void AddRupee(Entity *a, int b);
void ObjPosCopyOfs32(Entity *e, Entity *target, int a, int b);
void SoundReq(int sfx);
void PutObjWork(Entity *e);
u8 EmCharDir2(int dir);

int func_02083c75_unk(Entity *e, int a, int b);
void KemuriSet(Entity *e);
void func_020859e0(Entity *e, int a);
void func_02084ab8(Entity *e, Entity *other);
Entity *func_020849c8(Entity *e);
u8 func_02084a30(Entity *e);

#endif
