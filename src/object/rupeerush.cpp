#include "engine/functions.h"
#include "global.h"

// Rupee rush dice (module rupeerush): rupeeRushState holds the dice cursor (+0) and the level (+1), rupeeRushDice is the
// 15-cell shuffled table the cursor walks through.
//   changeRupeeRushLevel (0x0207758c), initRupeeRush (0x020775c4), getRupeeRushDiceIndex (0x02077650).

typedef struct RupeeRushState {
    u8 diceIndex; // 00, cursor into rupeeRushDice, wraps at 15
    u8 level;     // 01
} RupeeRushState;

extern RupeeRushState rupeeRushState; // rupeeRushState
extern u8 rupeeRushDice[15];          // rupeeRushDice

// changeRupeeRushLevel (0x0207758c): sets the level and starts the dice at a random cursor
extern "C" void changeRupeeRushLevel(u8 level);
ARM void changeRupeeRushLevel(u8 level) {
    rupeeRushState.level = level;
    rupeeRushState.diceIndex = Random() % 15;
}

// initRupeeRush (0x020775c4): fills the dice with 0..14, then shuffles them with 128 random swaps
extern "C" void initRupeeRush(void);
ARM void initRupeeRush(void) {
    int i;
    int count;
    int a;
    int b;
    u8 tmp;

    changeRupeeRushLevel(0);
    for (i = 0; i < 15; i++) {
        rupeeRushDice[i] = i;
    }
    count = 0;
    do {
        a = Random() % 15;
        b = Random() % 15;
        if (a != b) {
            tmp = rupeeRushDice[a];
            rupeeRushDice[a] = rupeeRushDice[b];
            rupeeRushDice[b] = tmp;
        }
        count++;
    } while (count < 0x80);
}
