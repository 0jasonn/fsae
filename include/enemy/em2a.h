#ifndef UNKNOWN_BOSS_02030A14_H
#define UNKNOWN_BOSS_02030A14_H

#include "engine/player.h"

typedef struct Vars_Boss {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ Entity *unk_60;
    /* 64 */ PlayerData *unk_64;
    /* 68 */ u8 unk_68[8];
    /* 70 */ u16 unk_70;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74;
    /* 75 */ u8 unk_75;
    /* 76 */ u8 unk_76[2];
    /* 78 */ u8 unk_78;
    /* 79 */ u8 unk_79;
    /* 7a */ u8 unk_7a[2];
    /* 7c */ s32 unk_7c;
} Vars_Boss;
#define V(e) VARS(Vars_Boss, e)

// Hand-like child entity of the boss
typedef struct Vars_BossHand {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ s16 unk_74;
    /* 76 */ u16 unk_76;
} Vars_BossHand;
#define VH(e) VARS(Vars_BossHand, e)

typedef struct Vars_Counter {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 unk_62;
} Vars_Counter;

extern Entity *data_0212c648;
extern const u8 data_020d0a62[];
extern const EntityFunc data_020d0a7c[];
extern const EntityFunc data_020d0dc0[];
extern const u8 data_020d0a42[];
extern const u8 data_020d0a52[];
extern const u8 data_020d0a72[];
extern const u8 data_020d0a4a[];
extern const u16 data_020d0a5a[];
extern const s8 data_020d0ab2[];

#ifdef __cplusplus
extern "C" {
#endif
Entity *GetEnemyWork(int id);
void PutObjWork(Entity *e);
void MoveDir(Entity *e);
void CockpitOn(void);
void CockpitOff(void);
void BindPlayers(void);
void EmDie(Entity *e);
void EmDivPosSet(Entity *e, Entity *a, Entity *b);
void YureSet(int a, int b);
void em2a_core(Entity *e);
void jumpefectSet(Entity *e);
void bigjumpinit(Entity *e);
void lifeset(Entity *e);
void em2a_ruppyset(Entity *e);
void coreSync(Entity *e);
void coreSet(Entity *e);
void move3Init(Entity *e);
u8 em2a_areaCheck(Entity *e);
u8 move3search(Entity *e);
void flashcheck(Entity *e);
void PutObjColor(int a);
u32 GetObjColor(int a);
void GetVGroup(Entity *e, int a);
void PutVGroup(Entity *e);
void func_02030ae4(int index);
void efectset(Entity *e);
void SoundReq(int sfx);
u8 CalculateDirectionTo(s16 x, s16 y, s16 tx, s16 ty);
u8 func_02086078(Entity *target, Entity *e);
void nearplcheck(Entity *e);
void shadowmoveset(Entity *e);
#ifdef __cplusplus
}
#endif

#endif
