#include "engine/functions.h"
#include "engine/player.h"
#include "game/endinglink.h"

// selectEndingLink, 0x02045874. Picks a random player index for the ending: it first steps a random number of
// players (1 to 16) forward from player 0, then keeps stepping until it lands on a player without a ranking key.
void selectEndingLink(void) {
    u8 steps = (Random() & 0xf) + 1;
    u8 index = 0;
    CalcRanking();
    while (--steps != 0) {
        index = (index + 1) % gameState.playerCount;
    }
    do {
        index = (index + 1) % gameState.playerCount;
    } while (ranking_getKey(index) != 0);
    gameState.unk_50[3] = 0;
}
