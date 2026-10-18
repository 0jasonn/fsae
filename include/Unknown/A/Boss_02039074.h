#ifndef UNKNOWN_A_BOSS_02039074_H
#define UNKNOWN_A_BOSS_02039074_H

#include "Unknown/A/Boss_02038544.h"

// Fields past 0x78 for this actor; V() from Boss_02038544.h covers 0x64..0x7d
typedef struct Vars_02039074 {
    /* 00 */ u8 unk_00[0x71];
    /* 71 */ u8 unk_71;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u16 unk_74;
    /* 76 */ u16 unk_76;
    /* 78 */ u8 unk_78;
    /* 79 */ u8 unk_79[5];
    /* 7e */ u16 unk_7e;
} Vars_02039074;
#define W(e) VARS(Vars_02039074, e)

// Halfword at 0x62 of the entity referenced by unk_60
typedef struct Vars_Target {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 unk_62;
} Vars_Target;

void func_0208ae30(Entity *e);
void func_020847f8(Entity *e);
Entity *CreateProjectile(int id);
void CopyPosition(Entity *e, Entity *other);
Entity *CreateEnemy(int id);
void DeleteEntity(Entity *e);
void func_02045c20(Entity *e, Entity *a, Entity *b);
void func_02039e58(Entity *e);
void func_02039e8c(Entity *e, int a);
void func_02039ed4(Entity *e);
void func_02039f24(Entity *e);
int func_0203a07c(Entity *e);
int func_020847b0(Entity *e);
void func_02089524(Entity *e);
void func_0203a168(Entity *e);
void func_02084788(Entity *e);
void func_02085a60(Entity *e, u16 a);

extern const EntityFunc data_020d1b94[];
extern const EntityFunc data_020d1b84[];
extern const EntityFunc data_020d1c20[];
extern const EntityFunc data_020d1c7c[];
extern const EntityFunc data_020d1a64[];
extern const u8 data_020d1b8c[];
extern const u8 data_020d1bcc[];
extern const u8 data_020d1bd4[];
extern const s8 data_020d1b7c[];
extern const s8 data_020d1998[];
extern const EntityFunc data_020d1d40[];
extern const EntityFunc data_020d1d58[];
extern const EntityFunc data_020d1d2c[];
extern const u16 data_020d1ccc[];
extern const u8 data_020d1cd4[];
extern const u8 data_020d1cdc[];
extern u16 data_0212c540[];

#endif
