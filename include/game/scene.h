#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "engine/misc.h"
#include "game/pause_req.h"

// Pairs of u16 (x and y bounds) indexed by player or effect number
extern const u16 data_02104a30[][2];
extern const u16 fairyMoveTable[][2];

extern u32 opTitleState;
extern const VoidFunc opTitleTable[];

extern const u8 spawnList_053428_high[];
extern const u8 spawnList_053428_set[];
extern const u8 spawnList_053428_mid[];
extern const u8 spawnList_053484_high[];
extern const u8 spawnList_053484_set[];
extern const u8 spawnList_053484_mid[];
extern const u8 spawnList_0534e0_set[];
extern const u8 spawnList_0534e0_mid[];
extern const u8 spawnList_0534e0_high[];
extern const u8 spawnList_kazan2a1_set[];
extern const u8 spawnList_kazan2a1_clear[];
extern u16 data_0213492c[];
extern const u16 data_02109484[];
extern const u16 data_0210948c[];
extern const u16 data_02109494[];
extern const u16 data_0210949c[];
extern const u16 data_021094a4[];
extern const u16 data_021094ac[];
extern const u16 data_021094b4[];
extern const u16 data_021094bc[];
extern const u16 data_021094c4[];
extern const u16 data_021094cc[];
extern const u16 data_021094d4[];
extern const u16 data_021094dc[];
void OpeningTaskFinalzie(void);
void ObjMoveInit(void);

extern u8 data_020d80d8[];
#include "engine/cockpit_state.h"
#include "engine/vblank_request.h"
extern u16 data_0212c514;
#include "engine/com_work.h"
#include "engine/palette_buff.h"
extern u8 titleDialogBuffer[];
extern const u8 titleDialogData[];
extern u8 data_0216fcfc[];
extern u8 data_0216fcfd[];
extern u8 data_0216fcfe[];
extern u8 data_0216fcff[];

extern const u8 spawnList_0537bc_set[];
extern const u8 spawnList_0537bc_clear[];
extern const u8 spawnList_0537f8_set[];
extern const u8 spawnList_0537f8_clear[];
extern const u8 spawnList_053834_set[];
extern const u8 spawnList_053834_clear[];
extern const u8 spawnList_053870_set[];
extern const u8 spawnList_053870_clear[];
extern const u8 spawnList_0538ac_set[];
extern const u8 spawnList_0538ac_clear[];
extern const u8 spawnList_0538e8_set[];
extern const u8 spawnList_0538e8_clear[];
extern u8 pauseDialogWindow[];
extern const VoidFunc pauseHandlerTable[];
extern u8 pauseDialogBuffer[];
extern const u8 pauseDialogRect[];

#endif
