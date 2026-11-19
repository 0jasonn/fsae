#ifndef WIP_B_ENDING_B_H
#define WIP_B_ENDING_B_H

// Declarations for the ending, finale and demo functions of implementer B (0x020443a0 to 0x02048264).
// Functions missing from engine/functions.h use the original signatures from config/eur/original_names.tsv
// where listed, or the parameters the call sites pass.

#include "engine/entity.h"
#include "engine/functions.h"
#include "engine/player.h"


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

#include "engine/map_state.h"
#include "engine/display_state.h"
#include "engine/effect_state.h"
#include "engine/blend_request.h"
typedef void (*FadeFunc)(BlendRequest *);
extern FadeFunc const fadeModeTable[];        // fadeModeTable
extern u32 data_02134910;
extern u16 data_02135da0[];

#define GAME_STATE_U8(off) (*((u8 *)&gameState + (off)))

extern u16 data_021355a0;
extern u8 data_02135840[];
extern u8 data_0216fd04[];
extern u8 objAffineSet[];
extern u8 data_0212ccb0[];
#include "engine/cockpit_state.h"
#include "engine/em12_type_masks.h"
#include "engine/em2f_map_flag.h"
extern u8 data_0212c4dc;
extern u8 data_0212c500;
extern VoidFunc data_0212c564;
extern SceneSlot data_02134d30; // first record; the others are reached with SCENE_SLOT
#define SCENE_SLOT(k) (((SceneSlot *)&data_02134d30)[k])
extern VoidFunc const endingFinaleTable[];
extern VoidFunc const finaleDemoTable[];
extern VoidFunc const endingRescueTable[];
extern u16 playerKeysPrev[4];
extern u8 data_0212c4f8;
extern s32 data_02134924;

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
