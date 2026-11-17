#ifndef WIP_ENDINGLINK_H
#define WIP_ENDINGLINK_H

#include "engine/functions.h"

// Not in engine/functions.h yet (original CalcRanking() 0x02055f18, ranking_getKey(unsigned char) 0x0205610c).
void CalcRanking(void);
u32 ranking_getKey(u8 index);

#endif
