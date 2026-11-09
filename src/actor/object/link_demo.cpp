#include "engine/functions.h"
#include "engine/player.h"

// 0x020725d0 (original name DemoLinkWalkSet, mangled). Switches a player slot to the demo walk state with the
// given timer values.
void DemoLinkWalkSet(u8 a, u8 b, u8 c) {
    playerWork[a].state = 3;
    playerWork[a].stateTimer = b;
    playerWork[a].unk_39 = c;
}
