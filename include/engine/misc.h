#ifndef ENGINE_MISC_H
#define ENGINE_MISC_H

#include "engine/entity.h"
#include "engine/player.h"


#include "engine/obj_list.h"

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

#include "engine/map_state.h"

#include "engine/effect_state.h"

#include "engine/scene_slot.h"
extern const u8 data_02104a74[];

#include "engine/palette_buff.h"
extern u16 data_02170104[];
extern u8 data_0212c500;
extern u8 data_0212c4dc;
extern VoidFunc data_0212c564;
extern const VoidFunc data_02104a40[];
extern const u16 mistStepTable[];
extern const u32 titleDialogBlock;
#include "engine/frame_counter.h"
extern u8 data_0212c4bc;
extern u8 data_0212c4f8;
extern u8 localPlayerIndex;
#include "engine/cockpit_state.h"
extern const u8 data_020ce4d0[];
extern s32 data_02134924;
#include "engine/em2f_map_flag.h"
extern const VoidFunc data_02104a24[];



#endif
