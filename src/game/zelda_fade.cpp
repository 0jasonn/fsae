#include "engine/functions.h"
#include "game/multiplay.h"
#include "game/multiplay_main.h"
#include "engine/frame_counter.h"
#include "engine/local_player_index.h"
#include "engine/data_0212c500.h"
#include "engine/data_0212c564.h"
#include "engine/com_work.h"
#include "game/trianglewin.h"
#include "game/player.h"
#include "knife/comm/commframe_sync.h"
#include "engine/scr.h"
#include "game/bganm_api.h"
#include "game/zelda_fade.h"
#include "game/keyclear_api.h"

// Functions in this file (original names from the debug build): zelda_fade

// zelda_fade() (0x02047c9c): the triangle wipe at the start of a multiplayer stage. Once the frame sync is complete it
// clears the keys, grows the triangle window (frameCounter.wipeSize, by 3 up to 0x8c, then by 4) until it covers the
// screen, then starts the stage BGM, resets the scene step and the message/telop systems, and runs the common per-frame
// tasks. `zero` is set from the loop counter (the ROM copies the 0 from it), and the two packet tags are cleared in
// one chained assignment (the ROM masks the second one).
void zelda_fade(void) {
    u8 i;
    int zero;

    if (CommFrameSync() == 0) {
        return;
    }
    for (zero = i = 0; i < 4; i++) {
        playerKeys[i] = zero;
        playerKeysPrev[i] = playerKeys[i];
    }
    data_0212c510 = zero;
    data_0212c514 = zero;
    ((u16 *)(data_02134cb0 + localPlayerIndex * 0x20))[data_0212c538 & 0xf] = zero;
    data_0212c550 = data_0212c554;
    if (frameCounter.wipeSize < 0x118) {
        MakeTriangleWindow(0x80, 0x60, (s16)frameCounter.wipeSize, (u8)(frameCounter.frame * 5));
        if (frameCounter.wipeSize < 0x8c) {
            frameCounter.wipeSize += 3;
        } else {
            frameCounter.wipeSize += 4;
        }
        frameCounter.frame++;
    } else {
        gameState.unk_50[1] = zero;
        BgmSet();
        StopEffectWindow();
        data_0212c500++;
        data_0212c4dc = zero;
        frameCounter.frame = zero;
        gameState.periodicFlag &= 0x7f;
        comWork.send.tag = comWork.next.tag = zero;
        MessageInitialize();
        TelopInitialize();
    }
    data_0212c564();
    ScrollMove();
    BgAnm();
    func_0208309c();
    Cockpit();
    PlayerTrans();
    func_020830ec();
    VGroupManager();
    CommFrameUpdate();
}
