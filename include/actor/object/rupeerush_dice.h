#ifndef WIP_K_RUPEERUSH_DICE_H
#define WIP_K_RUPEERUSH_DICE_H

#include "types.h"

extern u8 rupeeRushState;     // next index into rupeeRushDice, wraps at 15
extern u8 rupeeRushDice[];    // 15 dice values (0x02171d46)

u8 getRupeeRushDiceIndex(void); // 0x02077650 (c_decls_2.h declares it too)

#endif
