#ifndef UNKNOWN_D_MISC_D_H
#define UNKNOWN_D_MISC_D_H

#include "engine/entity.h"
#include "engine/player.h"

typedef void (*VoidFunc)(void);

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

// Blend request read by title_resourceCtrlCallback and color_control
typedef struct UnkStruct_0212c5ac_D {
    /* 00 */ u8 blendEnabled;
    /* 01 */ u8 blendMode; // 0..5, selects the sign of the weight
    /* 02 */ u8 unk_2[5];
    /* 07 */ u8 blendColor;
    /* 08 */ s16 blendWeight;
    /* 0a */ u8 unk_a[2];
    /* 0c */ s32 resetValue; // set to -1 by op_demo_skip (guess)
} UnkStruct_0212c5ac_D;
extern UnkStruct_0212c5ac_D data_0212c5ac;

// Display/effect shadow block (hardware-register mirror values; field names are guesses where marked)
typedef struct UnkStruct_0212c75c {
    /* 00 */ u16 displayFlags;
    /* 02 */ u8 unk_2[6];
    /* 08 */ u16 unk_8;
    /* 0a */ u16 unk_a;
    /* 0c */ u16 unk_c;
    /* 0e */ u8 unk_e[2];
    /* 10 */ void *workBuffer; // guess
    /* 14 */ u16 unk_14;
    /* 16 */ u16 frameCounter;
    /* 18 */ u16 unk_18;
    /* 1a */ u8 unk_1a[6];
    /* 20 */ u16 unk_20;
    /* 22 */ u16 unk_22;
    /* 24 */ u16 scrollX;
    /* 26 */ u8 unk_26[6];
    /* 2c */ u16 unk_2c;
    /* 2e */ u16 unk_2e;
    /* 30 */ u16 unk_30;
    /* 32 */ u8 unk_32[0x34];
    /* 66 */ u16 reg66; // hardware value written by mist_effect
    /* 68 */ u16 reg68; // hardware value written by mist_effect
} UnkStruct_0212c75c;
extern UnkStruct_0212c75c data_0212c75c;

typedef struct UnkStruct_0212c648_D {
    /* 00 */ u8 unk_0[0x20];
    /* 20 */ u16 unk_20;
    /* 22 */ s16 cameraX; // guess
} UnkStruct_0212c648_D;
extern UnkStruct_0212c648_D data_0212c648;

// Effect state block. Kept as a byte array: a struct-typed declaration makes mwcc schedule the stores differently.
enum {
    EFFECT_STATE_SCENE = 0x00, // scene state machine of op_scene_00
    EFFECT_STATE_TIMER = 0x04, // u16 countdown used by op_scene_00
    EFFECT_STATE_STEP_TIMER = 0x09, // counts down before the step index advances
    EFFECT_STATE_STEP_INDEX = 0x0a, // index into mistStepTable, 0xff at the end
    EFFECT_STATE_ACTIVE = 0x0b,
    EFFECT_STATE_LEVEL = 0x0c,
    EFFECT_STATE_FLAG_E = 0x0e, // set to 2/3 by gufu_scene_02, cleared by its last state
};
extern u8 data_021349c0[];

// Scene/actor control byte block (messageRequest): low 7 bits of [0] are the mode, [3] and [4] hold 5-bit sub-modes
enum {
    SCENE_CTRL_MODE = 0x00,
    SCENE_CTRL_SUBMODE_3 = 0x03,
    SCENE_CTRL_SUBMODE_4 = 0x04,
};
extern u8 messageRequest[];

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
extern u16 data_0212c594;
extern VoidFunc data_0212c564;
extern const VoidFunc data_02104a40[];
extern const u16 mistStepTable[];
extern const u32 titleDialogBlock;
extern u8 frameCounter[];
extern u8 data_0212c4bc;
extern u8 data_0212c4f8;
extern u8 localPlayerIndex;
extern u8 data_0212c618[];
extern u8 data_021361a0[];
extern const u8 data_020ce4d0[];
extern s32 data_02134924;
extern s32 em2f_mapFlag;
extern const VoidFunc data_02104a24[];



#endif
