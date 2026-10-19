#ifndef UNKNOWN_BOSS_02036CA4_H
#define UNKNOWN_BOSS_02036CA4_H

#include "engine/player.h"

typedef struct Vars_02036ca4 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 unk_70;
    /* 71 */ u8 unk_71;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ const u16 *unk_74; // path
    /* 78 */ u16 unk_78; // target x
    /* 7a */ u16 unk_7a; // target y
    /* 7c */ u8 unk_7c; // attack history
    /* 7d */ s8 unk_7d;
    /* 7e */ u8 unk_7e;
} Vars_02036ca4;
#define V(e) VARS(Vars_02036ca4, e)

typedef struct UnkStruct_0212c5ac {
    /* 00 */ u8 unk_00[7];
    /* 07 */ u8 unk_7;
    /* 08 */ u8 unk_8[4];
    /* 0c */ s32 unk_c;
} UnkStruct_0212c5ac;
extern UnkStruct_0212c5ac data_0212c5ac;
extern Entity *data_0212c648;
extern u8 data_0217d384;
extern const EntityFunc data_020d177c[];
extern const u8 data_020d1438[];
extern const u8 data_020d1428[];
extern const u8 data_020d70c8[];
extern s32 data_02134914;
extern u8 data_0212c504;
extern u8 data_0212c618;
extern const u16 data_020d142c[];
extern const u32 data_020cf9b8[];
extern const s16 data_020d7e58[];
extern const u8 data_020d1440[];
extern u16 data_0212c5bc;
extern const u8 data_020f26a8[][8];
extern const u16 *const data_020d1464[];
extern const u8 data_020d1450[];
extern const u8 data_020d1458[];
extern const u16 *const data_020d1448[];
extern const u16 *const data_020d1474[];
extern const u8 data_020d1432[][2];

#ifdef __cplusplus
extern "C" {
#endif
void BindPlayers(void);
void func_0208ae30(Entity *e);
void SoundReq(int sfx);
void *KnifeApp_getInstance(void);
int KnifeApp_isWirelessMode(void *a);
void BikkuriSet(Entity *e, int a, int b);
void MakeFadeBuff256(int a);
void GufuFuyusnd(Entity *e);
void MessageRequest(int a);
void Status_ArmIfEnabled(void);
void MapLoad(const void *a, int b);
void FadeSet(int a, int b);
Entity *GetTamaWork(int id);
void ObjPosCopy(Entity *e, Entity *other);
u8 CalculateDirectionTo(s16 x, s16 y, s16 tx, s16 ty);
u8 *Knife_Single_SinglePlay_GetInstance(void);
void Scene_ClearFlag5(void);
void CockpitOn(void);
void MoveDir(Entity *e);
void nextSet(Entity *e);
BOOL setTsubomi(Entity *e);
void tsubomiCloseWaitSet(Entity *e);
int gufuVitalCheck(Entity *e);
void getTsubomiMoveInfo(Entity *e);
int tblMove(Entity *e);
void stormGetTama(Entity *e);
void stormMove(Entity *e);
void getStormMoveInfo(Entity *e);
void SetDisp(Entity *e, int a, int b, int c);
void getFiveMoveInfo(Entity *e);
void Scene_SetFlag5(void);
void func_020899e4(Entity *e);
void gufuBindPls(void);
void CockpitOff(void);
Entity *GetObjWork(void);
Entity *GetObjWork2(void);
void RegistObjWork(int list, Entity *e);
void func_02086200(Entity *e, int a);
BOOL func_02084670(const u8 *bits, int index);
#ifdef __cplusplus
}
#endif

#endif
