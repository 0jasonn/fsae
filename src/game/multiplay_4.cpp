#include "actor/object/common_a.h"

// Warp-out sequence of the multiplayer stage (multiplay_warp, 0x020483f8).
typedef struct WarpSfxList {
    u32 ids[4];
} WarpSfxList;

extern u16 data_0212c540;
extern u8 data_0216efa8[];
extern u32 data_0216efac[4]; // sound ids in the order the players are announced
extern const WarpSfxList multiplayWarpSfx;  // multiplayWarpSfx
extern const u16 multiplayWarpSfxTimes[2];  // multiplayWarpSfxTimes: timer values at which the sounds play
extern u16 playerKeys[];
extern u16 playerKeysPrev[];

void multiplay_warp(void) {
    u8 i;
    u8 j;
    u8 next;
    u16 bonus;
    WarpSfxList sfx;
    u16 timer;

    for (i = 0; i < 4; i++) {
        playerKeys[i] = 0;
        playerKeysPrev[i] = playerKeys[i];
    }
    switch (data_0212c4dc) {
    case 0:
        data_0212c540 = 1;
        frameCounter.timer = 0x3c;
        data_0212c4dc++;
        break;
    case 1:
        if (frameCounter.timer-- == 0) {
            frameCounter.timer = 0x3c;
            if (gameState.active != 0 && gameState.phaseTimer == 0) {
                data_0212c4dc = 3;
            } else {
                time_bonus();
                data_0212c4dc++;
            }
        }
        sfx = multiplayWarpSfx;
        timer = frameCounter.timer;
        if (timer == multiplayWarpSfxTimes[0]) {
            for (i = 0; i < 4; i++) {
                data_0216efac[i] = sfx.ids[i];
            }
            if (gameState.playerCount != 4) {
                for (i = 0; i < gameState.playerCount - 1; i++) {
                    j = i + (u32)Random() % (u32)(3 - i);
                    data_0216efac[i] = data_0216efac[j];
                    data_0216efac[j] = sfx.ids[i];
                }
            }
            SoundReq(*(u32 *)(data_0216efa8 + 0x10));
        } else if (timer == multiplayWarpSfxTimes[1]) {
            for (i = 0; i < gameState.playerCount - 1; i++) {
                SoundReq(data_0216efac[i]);
            }
        }
        break;
    case 2:
        if (frameCounter.timer-- == 0) {
            bonus = get_time_bonus();
            frameCounter.timer = 0x3c;
            gameState.unk_24 |= 0x80;
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                for (i = 0; i < gameState.playerCount; i++) {
                    AddRupee(playerWork[i].entity, (s16)bonus);
                }
            } else {
                AddRupee(playerWork[0].entity, (s16)bonus);
            }
            gameState.unk_24 &= 0x7f;
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                if (gameState.active != 0 && gameState.phaseFlags == 0x4f) {
                    GetSetWork(0x51, 0, 0);
                } else if (gameState.difficulty == 2 && gameState.phaseTimer < 0xb) {
                    GetSetWork(0x51, 0, 0);
                } else if (gameState.periodicFlag == 0 && gameState.active == 0 && gameState.unk_01 != 5
                           && gameState.unk_01 != 6) {
                    GetSetWork(0x51, 0, 0);
                } else if ((u8)(gameState.unk_01 + 0xfb) <= 1 && gameState.phaseTimer < 2) {
                    GetSetWork(0x51, 0, 0);
                }
            }
            data_0212c4dc++;
        }
        break;
    case 3:
        if (frameCounter.timer-- == 0) {
            gameState.unk_6e = 3;
            data_0212c4dc++;
            if (gameState.unk_01 == 5) {
                UnlockTokiWave();
            }
        }
        break;
    case 4:
        if (gameState.unk_6e == 4) {
            SoundReq(0x1a);
            for (i = 0; i < gameState.playerCount; i++) {
                if (playerWork[i].entity != NULL) {
                    playerWork[i].entity->spriteSettings.b0 = 0;
                }
            }
            data_0212c4dc++;
        }
        break;
    case 5:
        if (blendRequest.blendEnabled == 0) {
            gameState.unk_6e = 5;
            FadeSet(1, 8);
            data_0212c4dc++;
        }
        break;
    case 6:
        next = 6;
        if (blendRequest.blendEnabled == 0) {
            gameState.unk_20 += gameState.frameCount;
            if (gameState.phaseFlags == 0x80) {
                next = 5;
                Task_Chain(next);
                func_020827a8(next);
            } else if (!GameState_UpdatePhase()) {
                data_0212c500 = 1;
                data_0212c4dc = 0;
            } else {
                if (gameState.gameMode == 2 || gameState.active != 0) {
                    Task_Chain(6);
                    next = 5;
                } else if (gameState.unk_01 >= 5) {
                    if ((u8)(gameState.unk_01 + 0xfb) <= 1) {
                        ClearNewStageUpdate();
                        Task_Chain(next);
                        next = 5;
                    } else {
                        next = 5;
                        Task_Chain(next);
                    }
                } else {
                    Task_Chain(4);
                    next = 5;
                }
                func_020827a8(5);
            }
            func_020827a8(next);
            ObjWorkPoolClear();
            ObjMoveInit();
            DispCtrlClear();
            return;
        }
        break;
    }
    frameCounter.frame++;
    data_0212c564();
    ScrollMove();
    BgAnm();
    func_0208309c();
    Cockpit();
    VGroupManager();
    PlayerTrans();
    func_020830ec();
}
