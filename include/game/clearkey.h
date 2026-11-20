#ifndef GAME_CLEARKEY_H
#define GAME_CLEARKEY_H

#include "engine/entity.h"

extern "C" {
void ClearKeyUpdate(u8 level); // 0x02048fa0, original ClearKeyUpdate(unsigned char)
}

// C++ linkage (_Z9key_checkhh), defined at 0x02048ea8
s32 key_check(u8 keys, u8 threshold);

#endif
