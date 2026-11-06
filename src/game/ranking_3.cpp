#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Ranking screen unit 3 (module ranking). Address -> name (original names):
//   0x02055650 ranking_scroll (matches)
//   0x020554c8 ranking_init (matches)

void ranking_init(void) {
    if (blendRequest != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0 = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    VGroupInit();
    ClearWorkBuffer();
    func_02029a50(&effectState, 0x28);
    ranking_noop();
    data_0212c4f8 = 0;
    if (gameState.unk_01 == 5) {
        gameState.unk_8e = 0;
        CgLoad(2);
    }
    CgLoad(0x14);
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0 = 0x6739;
    DataLoad(1);
    DataLoad(0x23);
    DataLoad(gameState.playerCount + 0x22);
    ranking_player_set();
    make_cockpit();
    calc_result();
    CalcRanking();
    ComRequest(5);
    displayState.reg66 = 0x3f40;
    displayState.reg68 = 0x720 - 0x14;
    displayState.unk_08 = 0x54;
    displayState.unk_20 = 0x844a;
    displayState.unk_2c = 0x864b;
    displayState.unk_0a = 0;
    displayState.unk_0c = 0;
    displayState.unk_22 = 0;
    displayState.scrollX = 0x140;
    displayState.unk_2e = 0;
    displayState.unk_30 = 0x140;
    mapState.unk_20 = 0;
    mapState.cameraX = 0x140;
    displayState.displayFlags = 0x1d40;
    effectState.unk_27 = 0;
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
    cameraX = mapState.cameraX;
    if (cameraX != wanted) {
        if (cameraX < wanted) {
            wanted = cameraX + 1;
        } else {
            wanted = cameraX - 1;
        }
        mapState.cameraX = wanted;
    }
    displayState.unk_30 = mapState.cameraX;
    displayState.scrollX = displayState.unk_30;
}
