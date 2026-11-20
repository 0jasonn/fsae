#ifndef ACTOR_ENEMY_ENDING_H
#define ACTOR_ENEMY_ENDING_H

// Declarations for the ending, finale and demo functions of implementer B (0x020443a0 to 0x02048264).
// Functions missing from engine/functions.h use the original signatures from config/eur/original_names.tsv
// where listed, or the parameters the call sites pass.

#include "engine/entity.h"
#include "engine/functions.h"
#include "engine/player.h"


#include "engine/scene_slot.h"

#include "engine/map_state.h"
#include "engine/display_state.h"
#include "engine/effect_state.h"
#include "engine/blend_request.h"
typedef void (*FadeFunc)(BlendRequest *);
extern FadeFunc const fadeModeTable[];        // fadeModeTable
extern u32 data_02134910;
#include "engine/palette_buff.h"

#include "engine/cockpit_state.h"
#include "engine/em12_type_masks.h"
#include "engine/em2f_map_flag.h"
extern VoidFunc const endingFinaleTable[];
extern VoidFunc const finaleDemoTable[];
extern VoidFunc const endingRescueTable[];
extern u16 playerKeysPrev[4];
extern u8 data_0212c4f8;
extern s32 data_02134924;

// Functions called from this range that are not in engine/functions.h
void ComRequest(u8 a);
void selectEndingLink(void);
void ending_link_init(void);
void yousei_move(void);
BOOL ending_msgFinishWait(void);
void subTask_staffroll_setFlagOff(void);
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
