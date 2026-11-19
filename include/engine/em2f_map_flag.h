#ifndef ENGINE_EM2F_MAP_FLAG_H
#define ENGINE_EM2F_MAP_FLAG_H

#include "types.h"

// Palette dirty mask (em2f_mapFlag, 4 bytes): one bit per 16-colour palette row that has to be uploaded to the screen.
// SetCgColor/CgPalletSet set the row's bit, MultiRoomSet sets bit 21, FadeClear sets all bits (0xffffffff), FadeSet
// and the scene setups clear it.
extern u32 em2f_mapFlag; // 0x02134914

#endif
