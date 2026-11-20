#include "engine/functions.h"
#include "game/bganm_api.h"
#include "game/player.h"
#include "engine/scr.h"
#include "engine/data_0212c564.h"
#include "global.h"
#include "game/multiplay_main.h"
#include "game/mathutil.h"
#include "knife/comm/commframe_sync.h"
#include "knife/comm/commupdatejoy.h"
#include "engine/data_0212c500.h"

// Per-frame main of the multiplayer game (multiplay_main, 0x02047e34).

void multiplay_main(void) {
    u8 current;
    u8 other;
    s16 distX;
    s16 distY;

    if (CommFrameSync() != 0) {
        CommUpdateJoy();
        if (frameCounter.pauseRequest != 0 || CommKeyCheck(8) != 0) {
            Pause();
            Cockpit();
            CommFrameUpdate();
            return;
        }
        if (playerKeysPrev[0] & 0x1000) {
            BindPlayer(0);
            if (playerWork[0].paletteBits.bind == 0) {
                playerWork[0].unk_30 = 0x2d;
            }
        }
        if (playerKeysPrev[1] & 0x1000) {
            BindPlayer(1);
            if (playerWork[1].paletteBits.bind == 0) {
                playerWork[1].unk_30 = 0x2d;
            }
        }
        if (playerKeysPrev[2] & 0x1000) {
            BindPlayer(2);
            if (playerWork[2].paletteBits.bind == 0) {
                playerWork[2].unk_30 = 0x2d;
            }
        }
        if (playerKeysPrev[3] & 0x1000) {
            BindPlayer(3);
            if (playerWork[3].paletteBits.bind == 0) {
                playerWork[3].unk_30 = 0x2d;
            }
        }
        if (!KnifeApp_isWirelessMode(KnifeApp_getInstance()) && frameCounter.playersBoundPrev == 0 && frameCounter.playersBound == 0) {
            playerWork[0].paletteBits.partner = 0;
            playerWork[1].paletteBits.partner = 0;
            current = *Knife_Single_SinglePlay_GetInstance();
            if (mapState.target == playerWork[current].entity) {
                distX = (s16)abs_s32(playerWork[current].entity->x.HALF.HI - mapState.scrollX - 0x80) * 2;
                distY = (s16)abs_s32(playerWork[current].entity->y.HALF.HI - mapState.scrollY - 0x60) * 2;
                if (distX >= 0x120 || distY >= 0xe0) {
                    playerKeysPrev[current] |= 0x1000;
                    BindPlayer(current);
                    playerWork[current].paletteBits.bind |= 1;
                }
            }
            if (Knife_Single_SinglePlay_GetInstance()[1] != 0) {
                other = *Knife_Single_SinglePlay_GetInstance() ^ 1;
                playerKeysPrev[other] |= 0x1000;
                playerWork[other].entity->iframes = 0xfe;
                playerWork[other].paletteBits.partner = 1;
            }
            if (playerWork[0].paletteBits.bind != 0 && (playerKeysPrev[0] & 0x1000)) {
                playerKeysPrev[0] &= 0x170c;
            }
        }
        if (cockpitState.item != 0xff && frameCounter.playersBoundPrev == 0 && frameCounter.pauseRequest == 0) {
            if (gameState.frameCount < 0x57e04) {
                gameState.frameCount++;
            }
        }
        if ((frameCounter.frame & 0xff) == 0) {
            CalcItemLevel();
        }
        gameState.unk_6f = 0;
        frameCounter.frame++;
        Encounter();
        data_0212c564();
        ShikakeMove();
        ScrollMove();
        BgAnm();
        StopBlockManager();
        func_0208309c();
        Cockpit();
        func_02083fb8();
        PlayerTrans();
        func_02062fcc();
        func_020830ec();
        VGroupManager();
        if (frameCounter.stopRequest != 0) {
            func_0202809c();
            SoundReq(0x80040000);
            SoundInit();
            data_0212c500 += 2;
            data_0212c4dc = 0;
            data_0212c4b8 = 1;
            frameCounter.timer = 0xb4;
            if (gameState.unk_01 == 5) {
                UnlockTokiWave();
            }
            return;
        }
        if (warp_check() != 0) {
            func_0202809c();
            WarpPlayer();
            Scene_SetFlag5();
            SoundReq(0x80040000);
            SoundInit();
            cockpitState.mode = 2;
            gameState.unk_6e = 2;
            data_0212c520 = 1;
            data_0212c500++;
            data_0212c4dc = 0;
        }
        Random();
        data_0212c554 = data_0212c550;
        CommFrameUpdate();
    } else {
        playerKeys[0] = playerKeys[1] = playerKeys[2] = playerKeys[3] = 0;
    }
}
