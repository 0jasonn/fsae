#ifndef ENGINE_MISC_H
#define ENGINE_MISC_H

#include "engine/entity.h"
#include "engine/player.h"


// Node of the intrusive entity lists whose heads are data_0212c6b0[]; the links sit at the start of Entity
typedef struct EntityNode {
    struct EntityNode *prev;
    struct EntityNode *next;
} EntityNode;

// Palette fade state (guessed from use)
typedef struct UnkStruct_0216fcf8 {
    /* 00 */ u8 fadeActive;
    /* 01 */ u8 unk_1;
    /* 02 */ u16 fadeLevel; // multiple of 8, 0..0xc0
    /* 04 */ s32 unk_4;
    /* 08 */ s32 bufferSelect; // nonzero: data_0216fd04 is uploaded, zero: data_02170104
} UnkStruct_0216fcf8;
extern UnkStruct_0216fcf8 paletteFade;

#include "engine/blend_request.h"

#include "engine/display_state.h"

typedef struct UnkStruct_0212c648_D {
    /* 00 */ u8 unk_0[0x20];
    /* 20 */ u16 unk_20;
    /* 22 */ s16 cameraX; // guess
} UnkStruct_0212c648_D;
extern UnkStruct_0212c648_D mapState;

#include "engine/effect_state.h"

// Scene control block (data_02134d30)
typedef struct UnkStruct_02134d30 {
    /* 00 */ u8 unk_0[2];
    /* 02 */ u8 unk_2;
    /* 03 */ u8 unk_3;
    /* 04 */ u8 unk_4;
    /* 05 */ u8 unk_5;
    /* 06 */ u8 unk_6;
    /* 07 */ u8 unk_7[5];
    /* 0c */ Entity *entity;
} UnkStruct_02134d30;
extern UnkStruct_02134d30 data_02134d30;
extern const u8 data_02104a74[];

extern EntityNode data_0212c6b0[];
extern EntityNode data_0212c6f0[];
extern u16 data_0216fd04[];
extern u16 data_02170104[];
extern u8 data_0212c500;
extern u8 data_0212c4dc;
extern VoidFunc data_0212c564;
extern const VoidFunc data_02104a40[];
extern const u16 mistStepTable[];
extern const u32 titleDialogBlock;
extern u8 frameCounter[0x20];
extern u8 data_0212c4bc;
extern u8 data_0212c4f8;
extern u8 localPlayerIndex;
#include "engine/cockpit_state.h"
extern u8 data_021361a0[];
extern const u8 data_020ce4d0[];
extern s32 data_02134924;
extern s32 em2f_mapFlag;
extern const VoidFunc data_02104a24[];



#endif
