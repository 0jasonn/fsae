
#include "engine/functions.h"
#include "engine/player.h"
#include "engine/display_state.h"
#include "engine/frame_counter.h"
#include "engine/data_0212c500.h"
#include "game/multiplay.h"
#include "game/check.h"
#include "game/cockpit.h"
#include "game/jyouchuu.h"
#include "game/encnt.h"
#include "game/makemap.h"

// Functions in this file (original names from the debug build): makemap_30

// makemap_30() (0x020479d8): last step of the stage build: resets the display and the input state, finishes the
// cockpit and cell set-up and advances the scene. The key words are cleared in one chained assignment: that is what
// gives the ROM's store order.
void makemap_30(void) {
    *(u32 *)0x04000000 = ConvertDispCntToTWL(0, *(u32 *)0x04000000);
    displayState.displayFlags = 0;
    data_0212c550 = data_0212c554;
    FloorInit();
    if (gameState.unk_01 == 5) {
        LoadTokiWave();
    }
    AutoSet();
    LoadJyouchuu();
    CockpitInit();
    CheckPlsSet();
    Encnt_Reset();
    playerKeys[0] = playerKeys[1] = playerKeys[2] = playerKeys[3] = playerKeysPrev[0] = playerKeysPrev[1] =
        playerKeysPrev[2] = playerKeysPrev[3] = data_0212c514 = data_0212c510 = 0;
    frameCounter.timer = 0x1e;
    data_0212c4b8 = 1;
    data_0212c4f8 = 0;
    data_0212c520 = 1;
    SetCgColor(0, 0);
    displayState.savedFlags = displayState.displayFlags;
    displayState.displayFlags = 0;
    data_0212c4dc = 0;
    data_0212c500++;
    gameState.unk_8c = 0;
}
