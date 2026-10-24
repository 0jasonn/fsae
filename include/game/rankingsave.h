#ifndef WIP_D_DECLS_H
#define WIP_D_DECLS_H

// Implementer D: declarations shared by the D files that functions.h does not have yet (the reviewer moves them).
#include "engine/functions.h"
#include "engine/entity.h"
#include "game/gamestateview_c.h"

extern "C" {
s32 FX_Sqrt(s32 x);
}

void ComRequest(u8 request);
void ClearWorkBuffer(void);
void ranking_noop(void);
void ranking_scroll(void);
void CalcRanking(void);
void set00itemSet(Entity *e);
void set0a_moveset(Entity *e);
void SetItemAdd(Entity *a, Entity *b);
void YureSet(int a, int b);
void SoundReq(u32 a);
void make_cockpit(void);
void ranking_write_rupee(u16 *cells, u32 value, u8 digits, u16 palette);
void calc_result(void);
void ranking_player_set(void);

// Data used by implementer D's files, typed where the D files need fields.
// data_0212c648: the first word is the entity whose y position the ranking camera follows.
typedef struct RankScrollState {
    /* 00 */ Entity *target;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 yureMode; // YureSet: b & 3
    /* 06 */ u8 scrollMode; // index into data_020d85b0, see ScrollMove
    /* 07 */ u8 unk_07[0xf];
    /* 16 */ u16 yureValue; // YureSet: a
    /* 18 */ u8 unk_18[8];
    /* 20 */ u16 unk_20;
    /* 22 */ s16 cameraX;
} RankScrollState;
extern RankScrollState data_0212c648;

// data_0212c75c: display/effect shadow block (same bytes as UnkStruct_0212c75c in engine/misc_d.h)
typedef struct RankDispShadow {
    /* 00 */ u16 displayFlags;
    /* 02 */ u8 unk_02[6];
    /* 08 */ u16 unk_08;
    /* 0a */ u16 unk_0a;
    /* 0c */ u16 unk_0c;
    /* 0e */ u8 unk_0e[0x12];
    /* 20 */ u16 unk_20;
    /* 22 */ u16 unk_22;
    /* 24 */ u16 scrollX;
    /* 26 */ u8 unk_26[6];
    /* 2c */ u16 unk_2c;
    /* 2e */ u16 unk_2e;
    /* 30 */ u16 unk_30;
    /* 32 */ u8 unk_32[0x34];
    /* 66 */ u16 reg66; // hardware value written by the ranking screen
    /* 68 */ u16 reg68;
} RankDispShadow;
extern RankDispShadow data_0212c75c;

extern u8 data_0212c618[];
extern u8 data_021361a0[];

// data_021349c0: effect and result state block of the ranking screen (bytes shared with other files)
typedef struct RankEffectState {
    /* 00 */ u8 unk_00[4];
    /* 04 */ u16 timer; // countdown of the result phase
    /* 06 */ u8 unk_06[6];
    /* 0c */ u32 playerFlags; // bit per player, set once that player's result is shown
    /* 10 */ u32 finishedCount; // number of players whose result was shown
    /* 14 */ u8 unk_14[0x13];
    /* 27 */ u8 unk_27;
} RankEffectState;
extern RankEffectState data_021349c0;

// data_0212ceb0: per-player slots, 0x94 bytes each (same bytes as PlayerData in engine/player.h)
typedef struct RankPlayerSlot {
    /* 00 */ u8 unk_00[0x0c];
    /* 0c */ u8 unk_0c;
    /* 0d */ u8 unk_0d[0x1b];
    /* 28 */ Entity *entity;
    /* 2c */ u8 unk_2c[0x94 - 0x2c];
} RankPlayerSlot;
extern RankPlayerSlot data_0212ceb0[4];

typedef void (*RankVoidFunc)(void);
extern RankVoidFunc data_0212c564; // per-frame handler called by ranking_calc
extern u8 data_0212c4dc; // phase of the result sequence, 0..3
extern u16 data_0212c594; // frame counter
extern const u8 data_020d851c[];
extern const u8 data_020d8524[];
extern u8 data_02171d01[];
extern const RankVoidFunc data_020d85b0[];
extern const EntityFunc data_02115398[];
extern const EntityFunc data_020d8860[];
extern u16 data_021349d8[];
extern u16 data_021355a0;
extern u8 data_0212c4f8;
extern u8 data_0212c500;
extern u8 data_0212c5ac; // blendEnabled, see misc_d.h


// Save media (backup) layer, see src/game/backup*.cpp
typedef struct SaveEepInfo {
    /* 00 */ u8 unk_00[2];
    /* 02 */ u16 unk_02; // read by DeleteSaveFile
    /* 04 */ u8 unk_04[8];
} SaveEepInfo; // 0x0c bytes, one per slot
extern const SaveEepInfo data_020d8550[];

typedef struct _SAVEHEADER _SAVEHEADER; // FAT header of a save, layout not known yet
s32 checkFatData(_SAVEHEADER *header);
void readFromSaveBuffer(u32 *buffer, u16 index, s32 size);
s32 ReadSaveBufferDword(u16 index, u16 *data);
void ProgramSaveBufferDwordEx(u16 index, u16 *data);
s32 VerifySaveBufferDword(u16 index, u16 *data);
const SaveEepInfo *getEepInfo(u8 slot);
s32 Knife_WriteToMedia(u8 slot, const u32 *data);
s32 ReadFromMedia(u8 slot, u32 *data);
void Knife_mediaWrite(void);
void func_020569cc(const void *buffer, u16 value, s32 size);

extern "C" {
s32 FS_CreateDirectoryAuto(const char *path, u32 flag);
s32 FS_GetArchiveResultCode(const char *path);
s32 FS_GetArchiveResource(const char *path, void *resource);
s32 FS_HasEnoughSpaceToCreateFile(void *resource, const char *path, s32 size);
}
extern void *data_02171d10;
extern u8 data_02163fa4[];
extern u8 data_02158fa0[];

#endif
