#include "engine/functions.h"
#include "game/multiplay.h"
#include "global.h"

// multiplay_init (0x02047490): resets the display and the multiplay work once the blend request is idle. Copies the
// low two bits of each player record (data_0212ca44, stride 0x34) into bits 2-3 of the player flag byte, clears the
// player work, points data_0212c53c at the local player's slot and advances the state byte.
void multiplay_init(void) {
    int i;
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    MultiWorkInit();
    for (i = 0; i < 4; i++) {
        ((MultiFlagByte *)((u8 *)playerWork + i * 0x94 + 0x8b))->b2 = ((MultiFlagWord *)(data_0212ca44 + i * 0x34))->b0;
    }
    PlWorkClear();
    frameCounter.stopRequest = 0;
    data_0212c53c = &playerWork[localPlayerIndex];
    data_0212c500++;
}
