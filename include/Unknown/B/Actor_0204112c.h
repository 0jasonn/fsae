#ifndef UNKNOWN_B_ACTOR_0204112C_H
#define UNKNOWN_B_ACTOR_0204112C_H

#include "Unknown/Player.h"

typedef struct Vars_0204112c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64; // target entity
    /* 68 */ u8 unk_68[0xc];
    /* 74 */ u8 unk_74;
    /* 75 */ u8 unk_75;
    /* 76 */ u8 unk_76;
    /* 77 */ u8 unk_77;
    /* 78 */ u16 unk_78;
    /* 7a */ u16 unk_7a;
} Vars_0204112c;
#define V(e) VARS(Vars_0204112c, e)

typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;
extern UnkStruct_0212c648 data_0212c648;

typedef struct UnkStruct_021348cc {
    s32 unk_0;
    s32 unk_4;
} UnkStruct_021348cc;
extern UnkStruct_021348cc data_021348cc;

#ifdef __cplusplus
extern "C" {
#endif
void UpdateAnimationSingleFrame(Entity *e);
void InitAnimationForceUpdate(Entity *e, u8 anim);
int func_020847a0(Entity *e);
int GetFacingDirection(Entity *e, Entity *target);
u8 func_02086220(s16 dx, s16 dy);
int func_02083d4c(u16 a, u16 b);
Entity *func_02084f98(Entity *e, int size, int align);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
void func_020410e4(Entity *e);
int func_020415f4(Entity *e);
int func_02041498(Entity *e, u8 dir);
#ifdef __cplusplus
}
#endif

#endif
