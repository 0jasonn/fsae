#ifndef UNKNOWN_B_ACTOR_020407C8_H
#define UNKNOWN_B_ACTOR_020407C8_H

#include "engine/entity.h"
#include "engine/player.h"

typedef struct Vars_020407c8 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ u16 unk_70;
    /* 72 */ u16 unk_72;
    /* 74 */ u16 unk_74;
    /* 76 */ u16 unk_76;
    /* 78 */ u16 unk_78;
    /* 7a */ u16 unk_7a;
    /* 7c */ u16 unk_7c;
    /* 7e */ u16 unk_7e;
} Vars_020407c8;
#define V(e) VARS(Vars_020407c8, e)

extern const EntityFunc data_020d31b8[];
extern const EntityFunc data_020d31a8[];
extern const u8 data_020d31a0[];
extern const EntityFunc data_020d322c[];
extern const EntityFunc data_020d321c[];
extern const u8 data_020d3224[];
extern const EntityFunc data_020d3334[];
extern const u8 data_020d32d4[];

typedef struct UnkStruct_021348cc {
    s32 unk_0;
    s32 unk_4;
} UnkStruct_021348cc;
extern UnkStruct_021348cc data_021348cc;

#ifdef __cplusplus
extern "C" {
#endif
Entity *func_020849c8(Entity *e);
void func_02084ab8(Entity *e, Entity *other);
u8 func_02084a30(Entity *e);
Entity *GetEnemyWork(int id);
Entity *GetObjWork(void);
Entity *GetObjWork2(void);
void PutObjWork(Entity *e);
void EmDie(Entity *e);
void EmPalamCopy(void);
void RegistObjWork(int list, Entity *e);
void KemuriSet(void);
void BubbleReset(Entity *e);
void childInit(Entity *e, Entity *other);
void func_02084700(Entity *e);
u8 func_02084a30(Entity *e);
void func_0208ae30(Entity *e);
void GenericKnockback(Entity *e, const void *funcs);
void jumpInit(Entity *e);
void ObjPosCopy(Entity *e, Entity *other);
Entity *GetSetWork(int id, int a, int b);

void Em26(Entity *e);
void em26_normal(Entity *e);
void em26_damage(Entity *e);
void em26_die(Entity *e);
void em26_move(Entity *e);
void em26_div(Entity *e);
void BubbleReset(Entity *e);
void childInit(Entity *e, Entity *other);
void Em27(Entity *e);
void em27_normal(Entity *e);
void func_02040e18(Entity *e);
void em27_die(Entity *e);
void em27_init(Entity *e);
void em27_move(Entity *e);
void cbubbleReset(Entity *e);
void func_02040f20(Entity *e);
void em28_damage(Entity *e);
void em28_init(Entity *e);
void em28_getdir(Entity *e);
Entity *GetTamaWork2(int id);
u32 Random(void);
void *KnifeApp_getInstance(void);
int KnifeApp_isWirelessMode(void *a);
u8 *Knife_Single_SinglePlay_GetInstance(void);
int func_020847dc(Entity *e);
void InitAnimationForceUpdate(Entity *e, u8 anim);
#ifdef __cplusplus
}
#endif

#endif
