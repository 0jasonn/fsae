#ifndef UNKNOWN_ENEMY_020347DC_H
#define UNKNOWN_ENEMY_020347DC_H

#include "engine/player.h"

typedef struct Vars_020347dc {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[6];
    /* 6e */ u16 unk_6e;
    /* 70 */ Entity *unk_70;
    /* 74 */ Entity **unk_74; // slot in the parent's segment list
    /* 78 */ u8 unk_78[4];
    /* 7c */ u16 unk_7c;
    /* 7e */ u8 unk_7e;
    /* 7f */ u8 unk_7f;
} Vars_020347dc;
#define V(e) VARS(Vars_020347dc, e)

typedef struct Vars_Event {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 unk_7d;
} Vars_Event;
#define VE(e) VARS(Vars_Event, e)

typedef struct Vars_Controller {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 unk_7c;
} Vars_Controller;
#define VCT(e) VARS(Vars_Controller, e)

typedef struct UnkStruct_021348c0 {
    s32 unk_0;
    s32 unk_4;
} UnkStruct_021348c0;
extern UnkStruct_021348c0 data_021348c0;

extern const EntityFunc data_020d11e0[];
extern const EntityFunc data_020d11c0[];
extern const u8 data_020f266e[];
extern const u8 data_020f266b[];
extern const u8 data_020f2668[];
extern const u16 data_020f267a[];
extern const u16 data_020f2680[];
extern const s8 data_020f2675[];
extern const s8 data_020f2671[];
extern const u8 data_020d11ac[];
extern const u8 data_020d11a4[];
extern const u8 data_020d119f[][3];
extern const s8 data_020f2686[];
extern const u8 data_020d11d0[];

typedef struct Vars_SegmentList {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ Entity *unk_70;
    /* 74 */ Entity *unk_74;
    /* 78 */ Entity *unk_78;
} Vars_SegmentList;
#define VS(e) VARS(Vars_SegmentList, e)
extern const u8 data_020d119c[];
extern const s16 data_020d7e58[];
extern const u32 data_020cf9b8[];

#ifdef __cplusplus
extern "C" {
#endif
void *KnifeApp_getInstance(void);
int KnifeApp_isWirelessMode(void *a);
u8 *Knife_Single_SinglePlay_GetInstance(void);
int kukiSet(Entity *e);
void ObjPosCopy(Entity *e, Entity *other);
void ObjPosCopyOfs32(Entity *e, Entity *other, s32 a, s32 b);
void cercleMoveC2(Entity *e);
void openInit(Entity *e);
void cercleMove2(Entity *e);
void openEndSet(Entity *e);
BOOL damagecheck(Entity *e);
void flowerDie(Entity *e);
void closeInit(Entity *e);
void closeEndSet(Entity *e);
Entity *EmGetAimPl(void);
u8 func_02084fd0(Entity *e, Entity *target);
void MoveDir(Entity *e);
void seedSet(Entity *e);
void differentColSet(Entity *e);
void cercleMoveC(Entity *e);
Entity *GetObjWork(void);
Entity *GetObjWork2(void);
void RegistObjWork(int list, Entity *e);
void testiRupeeSet(Entity *e);
void PutObjWork(Entity *e);
void SoundReq(int sfx);
Entity *GetTamaWork(int id);

#ifdef __cplusplus
}
#endif

#endif
