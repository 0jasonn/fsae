#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Ranking screen unit 3 (module ranking). Address -> name (original names):
//   0x02055650 ranking_scroll (matches)
//   0x020554c8 ranking_init (matches)

void ranking_init(void) {
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0[0] = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    VGroupInit();
    ClearWorkBuffer();
    MemClearFast(&effectState, 0x28);
    ranking_noop();
    data_0212c4f8 = 0;
    if (gameState.unk_01 == 5) {
        gameState.unk_8e = 0;
        CgLoad(2);
    }
    CgLoad(0x14);
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0[0] = 0x6739;
    DataLoad(1);
    DataLoad(0x23);
    DataLoad(gameState.playerCount + 0x22);
    ranking_player_set();
    make_cockpit();
    calc_result();
    CalcRanking();
    ComRequest(5);
    displayState.blendCnt = 0x3f40;
    displayState.blendAlpha = 0x720 - 0x14;
    displayState.bg[0].cnt = 0x54;
    displayState.bg[2].cnt = 0x844a;
    displayState.bg[3].cnt = 0x864b;
    displayState.bg[0].scrollX = 0;
    displayState.bg[0].scrollY = 0;
    displayState.bg[2].scrollX = 0;
    displayState.bg[2].scrollY = 0x140;
    displayState.bg[3].scrollX = 0;
    displayState.bg[3].scrollY = 0x140;
    mapState.scrollX = 0;
    mapState.scrollY = 0x140;
    displayState.displayFlags = 0x1d40;
    effectState.removeFlag = 0;
    FadeSet(2, 4);
    data_0212c500++;
}

void ranking_scroll(void) {
    s32 wanted;
    s16 cameraX;

    if (mapState.target == 0) {
        return;
    }
    wanted = (s16)(mapState.target->y.HALF.HI - 0x60);
    if (wanted < 0) {
        wanted = 0;
    }
    if (wanted > 0x140) {
        wanted = 0x140;
    }
    cameraX = mapState.scrollY;
    if (cameraX != wanted) {
        if (cameraX < wanted) {
            wanted = cameraX + 1;
        } else {
            wanted = cameraX - 1;
        }
        mapState.scrollY = wanted;
    }
    displayState.bg[3].scrollY = mapState.scrollY;
    displayState.bg[2].scrollY = displayState.bg[3].scrollY;
}
