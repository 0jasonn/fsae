#include "engine/functions.h"
#include "global.h"
#include "actor/object/rupeerush_dice.h"

// 0x02077650 getRupeeRushDiceIndex (original name): next value of the rupee rush dice sequence (15 entries).

u8 getRupeeRushDiceIndex(void) {
    u8 *dice = rupeeRushDice;
    u8 index = rupeeRushState++;
    u8 result = dice[index];
    if (rupeeRushState >= 0xf) {
        rupeeRushState = 0;
    }
    return result;
}
