#ifndef WIP_E_EM00_H
#define WIP_E_EM00_H

// Tables of the em00 actor (dsd names): per-action handler table and the function table passed to the handlers.
#include "engine/functions.h"
#include "game/cockpitdata.h"

extern EntityFunc data_020cfcac[];
extern u8 data_020cfd14[];
extern u8 data_020cfc74[];
extern u8 data_020cfc6c[];
extern s8 data_020cfc7c[];
extern u8 data_020cfc70[];
extern EntityFunc data_020cfddc[];
extern u8 em2b_hitbox[];
extern s8 data_020cfdfc[];
extern EntityFunc data_020cfe10[];
extern u32 em12_typeMasks[];
extern EntityFunc data_020cfec8[];
extern EntityFunc data_020cfe94[];

extern "C" s32 func_02083d30(s16 x, s16 y, u16 layer); // dsd name (thumb label), returns a map flag
BOOL trapAttBitCheck(Entity *e); // original trapAttBitCheck(OBJ_WORK_*), defined later in the E units

extern EntityFunc data_020cfd70[];
extern EntityFunc data_020cfd5c[];
extern u8 data_0212c540[];
extern u8 data_020cfd54[];

void getmoveinfo(Entity *e);

// Callees of the em0a units (dsd names with their arguments).
int func_020847c8(Entity *e);
int func_02083e54(int a); // returns a map-cell kind (0x02083e54) // original getmoveinfo(OBJ_WORK_*), defined later in the E units

#endif
