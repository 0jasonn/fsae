#ifndef WIP_E_GAMESTART_E_H
#define WIP_E_GAMESTART_E_H

#include "engine/functions.h"
#include "knife/subtask/subtask.h"
#include "knife/subtask/game_start.h"
#include "ui/widget/uiobject.h"
#include "engine/res_player_api.h"
#include "engine/res_chunk_b_api.h"
#include "game/eff.h"

// u8 index tables of the start screen cells
typedef struct StartCellIds {
    u8 ids[4];
} StartCellIds;

extern u8 data_0217d30c;     // start screen request state
extern s8 data_0217d30d;     // start screen mode (0 none, 1 title, 2 first run)
extern s32 data_0217d188;
extern u8 data_0217d23c[];
extern u8 data_0217a23c[];
extern u8 data_0217c23c[];
extern const StartCellIds data_020df1c4;

extern "C" {
void subtask_init_hblank_raster(s32 mode);
void GXx_SetMasterBrightness_(void *reg, s32 value);
void subTask_game_start_init_vram(s32 mode);
void subTask_init_bg3(int a, int b, int c);
void subTask_init_obj_lang(int a, int b);
void initCellAnimation(void *obj, s32 index1, s32 index2);
void *subTask_GetNewCellAnimation(void *cell);
void ResPlayer_SeekAndRefresh(void *entry, s32 value);
void subTask_game_start_init(void);
}
void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);

#endif
