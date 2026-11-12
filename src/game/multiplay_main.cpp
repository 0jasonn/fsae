#include "engine/functions.h"
#include "global.h"
#include "game/multiplay_main.h"

// Per-frame main of the multiplayer game (multiplay_main, 0x02047e34).

// Player byte 0x8b (paletteBits): bits 4..6 are the bind state, bit 7 marks the partner of the single-player mode.
typedef struct PlayerBindBits {
    u8 low : 4;
    u8 bind : 3;
    u8 partner : 1;
} PlayerBindBits;
typedef struct PlayerBindView {
    u8 unk_00[0x8b];
    PlayerBindBits bits;
    u8 unk_8c[8];
} PlayerBindView;
#define BIND_BITS(i) (((PlayerBindView *)playerWork)[i].bits)

void multiplay_main(void) {
    u8 current;
    u8 other;
    s16 distX;
    s16 distY;

    if (CommFrameSync() != 0) {
        CommUpdateJoy();
        if (frameCounter[0x11] != 0 || CommKeyCheck(8) != 0) {
            Pause();
            Cockpit();
            CommFrameUpdate();
            return;
        }
        if (playerKeysPrev[0] & 0x1000) {
            BindPlayer(0);
            if (BIND_BITS(0).bind == 0) {
                playerWork[0].unk_30 = 0x2d;
            }
        }
        if (playerKeysPrev[1] & 0x1000) {
            BindPlayer(1);
            if (BIND_BITS(1).bind == 0) {
                playerWork[1].unk_30 = 0x2d;
            }
        }
        if (playerKeysPrev[2] & 0x1000) {
            BindPlayer(2);
            if (BIND_BITS(2).bind == 0) {
                playerWork[2].unk_30 = 0x2d;
            }
        }
        if (playerKeysPrev[3] & 0x1000) {
            BindPlayer(3);
            if (BIND_BITS(3).bind == 0) {
                playerWork[3].unk_30 = 0x2d;
            }
        }
        if (!KnifeApp_isWirelessMode(KnifeApp_getInstance()) && frameCounter[0x14] == 0 && frameCounter[0x13] == 0) {
            playerWork[0].paletteBits = playerWork[0].paletteBits & ~0x80u;
            playerWork[1].paletteBits = playerWork[1].paletteBits & ~0x80u;
            current = *Knife_Single_SinglePlay_GetInstance();
            if (mapState.target == playerWork[current].entity) {
                distX = (s16)abs_s32(playerWork[current].entity->x.HALF.HI - (s16)mapState.unk_20 - 0x80) * 2;
                distY = (s16)abs_s32(playerWork[current].entity->y.HALF.HI - mapState.unk_22 - 0x60) * 2;
                if (distX >= 0x120 || distY >= 0xe0) {
                    playerKeysPrev[current] |= 0x1000;
                    BindPlayer(current);
                    BIND_BITS(current).bind |= 1;
                }
            }
            if (Knife_Single_SinglePlay_GetInstance()[1] != 0) {
                other = *Knife_Single_SinglePlay_GetInstance() ^ 1;
                playerKeysPrev[other] |= 0x1000;
                playerWork[other].entity->iframes = 0xfe;
                BIND_BITS(other).partner = 1;
            }
            if (BIND_BITS(0).bind != 0 && (playerKeysPrev[0] & 0x1000)) {
                playerKeysPrev[0] &= 0x170c;
            }
        }
        if ((&cockpitState)[0xc] != 0xff && frameCounter[0x14] == 0 && frameCounter[0x11] == 0) {
            if (gameState.frameCount < 0x57e04) {
                gameState.frameCount++;
            }
        }
        if ((*(u16 *)frameCounter & 0xff) == 0) {
            CalcItemLevel();
        }
        gameState.unk_6f = 0;
        (*(u16 *)frameCounter)++;
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
        if (frameCounter[0x12] != 0) {
            func_0202809c();
            SoundReq(0x80040000);
            SoundInit();
            data_0212c500 += 2;
            data_0212c4dc = 0;
            data_0212c4b8 = 1;
            *(u16 *)(frameCounter + 2) = 0xb4;
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
            cockpitState = 2;
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
