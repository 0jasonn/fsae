#ifndef WIP_B_ENDING_B_H
#define WIP_B_ENDING_B_H

// Declarations for the ending, finale and demo functions of implementer B (0x020443a0 to 0x02048264).
// Functions missing from engine/functions.h use the original signatures from config/eur/original_names.tsv
// where listed, or the parameters the call sites pass.

#include "engine/functions.h"
#include "engine/player.h"

typedef void (*EndingVoidFunc)(void);

// Scene slot table at data_02134d30: 0x14-byte records, each with an entity pointer at 0x0c
typedef struct SceneSlot {
    /* 00 */ u8 unk_00[4];
    /* 04 */ u8 unk_04;
    /* 05 */ u8 unk_05;
    /* 06 */ u8 unk_06;
    /* 07 */ u8 unk_07[5];
    /* 0c */ Entity *entity;
    /* 10 */ u8 unk_10[4];
} SceneSlot;

// Camera state at data_0212c648: first word is the entity the camera follows
typedef struct CameraState {
    /* 00 */ Entity *target;
    /* 04 */ u8 unk_04[0x1c];
    /* 20 */ u16 unk_20;
    /* 22 */ s16 unk_22;
    /* 24 */ u8 unk_24[4];
    /* 28 */ u16 unk_28;
} CameraState;

// Display shadow at data_0212c75c (displayFlags is the first halfword)
typedef struct DisplayShadow {
    /* 00 */ u16 displayFlags;
    /* 02 */ u8 unk_02[0x1e];
    /* 20 */ u16 unk_20;
    /* 22 */ u16 unk_22;
    /* 24 */ u16 unk_24;
    /* 26 */ u8 unk_26[6];
    /* 2c */ u16 unk_2c;
    /* 2e */ u16 unk_2e;
    /* 30 */ u16 unk_30;
    /* 32 */ u8 unk_32[0x34];
    /* 66 */ u16 unk_66;
    /* 68 */ u16 unk_68;
    /* 6a */ u16 unk_6a;
} DisplayShadow;

// Result state block at data_021349c0 (0x28 bytes, cleared by ending_init)
typedef struct ResultState {
    /* 00 */ u8 phase;     // state of the scene machine in ending_scene_01
    /* 01 */ u8 subPhase; // sub-state of the demo in demo_01 and demo_00
    /* 02 */ u8 unk_02[2];
    /* 04 */ u16 timer;    // frames left in the current phase
    /* 06 */ u8 unk_06[6];
    /* 0c */ u8 fadeStep;  // 0..0x10, scaled by 0x10 for the fade buffers
    /* 0d */ u8 unk_0d[0x17];
    /* 24 */ u32 frames;   // incremented once per frame by ending_rescue
} ResultState;

// Fade work at data_0212c5ac (the original tag is FADE_WORK_). Blend request read by the palette code.
typedef struct FADE_WORK_ {
    /* 00 */ u8 blendEnabled;
    /* 01 */ u8 blendMode;       // index into fadeModeTable
    /* 02 */ u8 unk_02;
    /* 03 */ u8 blendStep;       // per-frame step of blendWeight
    /* 04 */ u8 fadeRunning;
    /* 05 */ u8 unk_05[2];
    /* 07 */ u8 blendColor;
    /* 08 */ s16 blendWeight;
    /* 0a */ u8 unk_0a[2];
    /* 0c */ s32 resetValue;     // bit mask of palette rows to fade, see MakeFadeBuff256
} FADE_WORK_;
typedef FADE_WORK_ BlendRequest;
typedef void (*FadeFunc)(BlendRequest *);
extern FadeFunc const fadeModeTable[];        // fadeModeTable
extern u32 data_02134910;
extern u16 data_02135da0[];

// Flag block at messageRequest (bits in bytes 0, 3 and 4 are read by the scene code)
typedef struct UnkStruct_0217d384 {
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01[2];
    /* 03 */ u8 unk_03;
    /* 04 */ u8 unk_04;
} UnkStruct_0217d384;

#define GAME_STATE_U8(off) (*((u8 *)&data_0212c7c8 + (off)))

extern BlendRequest data_0212c5ac;
extern u16 data_021355a0;
extern u8 data_02135840[];
extern u8 data_0216fd04[];
extern u8 objAffineSet[];
extern u8 data_0212ccb0[];
extern u8 data_0212c618;
extern u8 data_021361a0[];
extern ResultState data_021349c0;
extern u32 em12_typeMasks;
extern u32 em2f_mapFlag;
extern u8 data_0212c4dc;
extern u8 data_0212c500;
extern EndingVoidFunc data_0212c564;
extern SceneSlot data_02134d30; // first record; the others are reached with SCENE_SLOT
#define SCENE_SLOT(k) (((SceneSlot *)&data_02134d30)[k])
extern CameraState data_0212c648;
extern DisplayShadow data_0212c75c;
extern EndingVoidFunc const endingFinaleTable[];
extern EndingVoidFunc const finaleDemoTable[];
extern EndingVoidFunc const endingRescueTable[];
extern u16 data_0212c584[4];
extern u16 data_0212c594;
extern u8 data_0212c4f8;
extern s32 data_02134924;
extern UnkStruct_0217d384 messageRequest;

// Functions called from this range that are not in engine/functions.h
void ComRequest(u8 a);
int CommFrameSync(void);
void CommUpdateJoy(void);
void ScrollMove(void);
void BgAnm(void);
void CommFrameUpdate(void);
void func_0208309c(void);
void selectEndingLink(void);
void ending_link_init(void);
void yousei_move(void);
BOOL ending_msgFinishWait(void);
void subTask_staffroll_setFlagOff(void);
void CalcRanking(void);
int ranking_getKey(u8 a);
extern const u16 youseiBounds1[];
extern const u16 youseiBounds2[];
extern const u16 youseiBounds3[];
void subTask_staffroll_start_finale(void);
void subTask_staffroll_cutout(void);
s32 CommKeyCheck(u16 keys);
extern "C" {
s32 WXC_GetStateCode(void);
}

#endif
