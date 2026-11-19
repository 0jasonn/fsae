// ClearNut (0x020295a4): PlayerData +0x3e is a byte of four 2-bit counters (nutBits); ClearNut clears b0/b2/b4 of player 1 and copies player 1's b0 into player 0's b4/b2/b0.
#include "engine/functions.h"
#include "engine/player.h"

extern "C" {
void ClearNut(void);
}

void ClearNut(void) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) return;
    playerWork[1].nutBits.b4 = 0;
    playerWork[1].nutBits.b2 = playerWork[1].nutBits.b4;
    playerWork[1].nutBits.b0 = playerWork[1].nutBits.b2;
    playerWork[0].nutBits.b4 = playerWork[1].nutBits.b0;
    playerWork[0].nutBits.b2 = playerWork[0].nutBits.b4;
    playerWork[0].nutBits.b0 = playerWork[0].nutBits.b2;
}
