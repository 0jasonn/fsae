#ifndef UNKNOWN_B_ACTOR_0204001C_H
#define UNKNOWN_B_ACTOR_0204001C_H

#include "Unknown/Entity.h"

typedef struct Vars_0204001c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64; // child object, allocated by func_02084f98 (0x58 bytes)
    /* 68 */ u8 unk_68[0x14];
    /* 7c */ u16 unk_7c;
    /* 7e */ u16 unk_7e;
} Vars_0204001c;
#define V(e) VARS(Vars_0204001c, e)

extern const void *data_020d310c[];
extern const s8 data_020d2e64[];
extern const s8 data_020d2e3c[];
extern const EntityFunc data_020d2fb4[];
extern const EntityFunc data_020d2fe4[];

#ifdef __cplusplus
extern "C" {
#endif
Entity *func_02084f98(Entity *e, int size, int align);
u32 func_02084ae8(Entity *e, int a, Entity *target);
int func_02084ac0(Entity *e, int a, Entity *target);
void func_020852f8(Entity *e, s32 dist, u8 speed);
u8 func_02084fd0(Entity *e, Entity *target);
void func_0205031c(Entity *e, Entity *other);
void func_02050390(Entity *e, Entity *other, s32 a, s32 b);
Entity *func_0204bdb8(int id);
u8 func_02086080(s16 x, s16 y, s16 tx, s16 ty);

void func_0204007c(Entity *e);
void func_020400b4(Entity *e);
void func_0204017c(Entity *e);
void func_020401b4(Entity *e);
void func_020401f4(Entity *e);
void func_02040254(Entity *e, u8 a);
void func_020402e0(Entity *e);
void func_02040304(Entity *e);
void func_02040334(Entity *e);
BOOL func_02040368(Entity *e);
void func_0204042c(Entity *e);
void func_0204048c(Entity *e);
void func_020404a0(Entity *e);
void func_020404bc(Entity *e);
void func_020404f4(Entity *e);
void func_02040548(Entity *e);
void func_02040674(Entity *e);
BOOL func_02040708(Entity *e);
void func_02040744(Entity *e);
void func_02040790(Entity *e);
#ifdef __cplusplus
}
#endif

#endif
