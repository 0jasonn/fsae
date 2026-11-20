#ifndef GAME_COMERROR_H
#define GAME_COMERROR_H

#include "engine/functions.h"

// Data used by the communication error screen (not in engine/functions.h or engine/misc.h yet)
#include "engine/vblank_request.h"
extern u8 data_0212c4c4;
extern u8 data_0212c4d8;
extern u16 data_0212c510;
extern u8 data_020f25a8[];
extern u8 data_020f25b4[];
#include "engine/effect_state.h"
#include "engine/palette_buff.h"

// Declared where functions.h has no prototype yet (plain symbols, extern "C")
extern "C" {
void comerror_init(void);  // 0x02028c44
void comerror_move(void);  // 0x02028e70
}

#endif
