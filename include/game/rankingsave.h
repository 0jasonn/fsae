#ifndef GAME_RANKINGSAVE_H
#define GAME_RANKINGSAVE_H

// Implementer D: declarations shared by the D files that functions.h does not have yet (the reviewer moves them).
#include "engine/functions.h"
#include "engine/entity.h"
#include "game/player_flags.h"
#include "engine/player.h"

extern "C" {
s32 FX_Sqrt(s32 x);
}

void ComRequest(u8 request);
void ranking_noop(void);
void ranking_scroll(void);
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
#include "engine/map_state.h"

#include "engine/display_state.h"

#include "engine/cockpit_state.h"

#include "engine/effect_state.h"

extern const u8 data_020d851c[];
extern const u8 data_020d8524[];
extern u8 data_02171d01[];
extern const VoidFunc data_020d85b0[];
extern const EntityFunc data_02115398[];
extern const EntityFunc data_020d8860[];
#include "engine/palette_buff.h"
extern u8 data_0212c4f8;
#include "engine/blend_request.h"


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
s32 Knife_mediaWrite(void); // returns the FSResult
void writeToSaveBuffer(const void *buffer, u16 value, s32 size);

extern "C" {
s32 FS_CreateDirectoryAuto(const char *path, u32 flag);
s32 FS_GetArchiveResultCode(const char *path);
s32 FS_GetArchiveResource(const char *path, void *resource);
s32 FS_HasEnoughSpaceToCreateFile(void *resource, const char *path, s32 size);
}
extern void *data_02171d10;

#endif
