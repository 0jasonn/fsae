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
Entity *CreateEnemy(int id);
Entity *func_0204bcc8(void);
Entity *func_0204bd00(void);
void DeleteEntity(Entity *e);
void func_02045ac0(Entity *e);
void func_02045b74(void);
void func_0204c178(int list, Entity *e);
void func_020768d8(void);
void func_02040d00(Entity *e);
void func_02040d60(Entity *e, Entity *other);
void func_02084700(Entity *e);
u8 func_02084a30(Entity *e);
void func_0208ae30(Entity *e);
void GenericKnockback(Entity *e, const void *funcs);
void func_02040be0(Entity *e);
void CopyPosition(Entity *e, Entity *other);
Entity *CreateFx(int id, int a, int b);

void func_020407c8(Entity *e);
void func_02040834(Entity *e);
void func_02040850(Entity *e);
void func_02040880(Entity *e);
void func_02040ad8(Entity *e);
void func_02040b3c(Entity *e);
void func_02040d00(Entity *e);
void func_02040d60(Entity *e, Entity *other);
void func_02040dcc(Entity *e);
void func_02040dfc(Entity *e);
void func_02040e18(Entity *e);
void func_02040e2c(Entity *e);
void func_02040e44(Entity *e);
void func_02040e94(Entity *e);
void func_02040f00(Entity *e);
void func_02040f20(Entity *e);
void func_02040ff8(Entity *e);
void func_02041064(Entity *e);
void func_020410e4(Entity *e);
Entity *func_0204bdf0(int id);
u32 Random(void);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
int func_020847dc(Entity *e);
void InitAnimationForceUpdate(Entity *e, u8 anim);
#ifdef __cplusplus
}
#endif

#endif
