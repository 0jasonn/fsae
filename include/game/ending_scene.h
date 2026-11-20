#ifndef GAME_ENDING_SCENE_H
#define GAME_ENDING_SCENE_H

// Declarations for the finale/staff roll scene functions (finale_init, demo_01). The scene slot table data_02134d30 is
// declared in engine/scene_slot.h.

#include "engine/entity.h"
#include "engine/functions.h"
#include "engine/player.h"
#include "engine/blend_request.h"
#include "engine/display_state.h"
#include "engine/map_state.h"
#include "engine/effect_state.h"
#include "engine/em12_type_masks.h"
#include "engine/em2f_map_flag.h"

#include "engine/scene_slot.h"

extern u8 data_0212c4f8;
extern s32 data_02134924;
#include "engine/palette_buff.h"

void ComRequest(u8 a);
void yousei_move(void);
void subTask_staffroll_setFlagOff(void);
void subTask_staffroll_start_finale(void);

#endif
