#ifndef UI_DOORSEL_H
#define UI_DOORSEL_H

#include "types.h"

// Original name ab_check() (C++ linkage); include/game/doorsel_4.h still declares it extern "C" and must drop that.
void ab_check(void);
// doorsel_appear callee (original GetTablePlNum(short*, unsigned char), mangled _Z13GetTablePlNumPsh)
s16 *GetTablePlNum(s16 *table, u8 index);
extern "C" {
void DoorSelTask(void);
void doorsel_sync(void);
}

#endif
