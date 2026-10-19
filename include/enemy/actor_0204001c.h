#ifndef UNKNOWN_B_ACTOR_0204001C_H
#define UNKNOWN_B_ACTOR_0204001C_H

#include "engine/entity.h"

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
void ObjPosCopy(Entity *e, Entity *other);
void ObjPosCopyOfs32(Entity *e, Entity *other, s32 a, s32 b);
Entity *GetTamaWork(int id);
u8 CalculateDirectionTo(s16 x, s16 y, s16 tx, s16 ty);

void em24_aimInit(Entity *e);
void em24_aimMove(Entity *e);
void em24_attackInit(Entity *e);
void em24_attack(Entity *e);
void swordset(Entity *e);
void charset(Entity *e, u8 a);
void em24_waitSet(Entity *e);
void moveSet(Entity *e);
void aimSet(Entity *e);
BOOL em24_crossCheck(Entity *e);
void em24_kemuriSet(Entity *e);
void func_0204048c(Entity *e);
void em25_normal(Entity *e);
void em25_damage(Entity *e);
void em25_aimInit(Entity *e);
void em25_aimMove(Entity *e);
void getAimPos(Entity *e);
BOOL crossCheck2(Entity *e);
void arrowSet(Entity *e);
void arrowPosSet(Entity *e);
#ifdef __cplusplus
}
#endif

#endif
