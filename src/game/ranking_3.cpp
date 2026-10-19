#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Ranking screen unit 3 (module ranking). Address -> name (original names):
//   0x02055650 ranking_scroll (matches)
//   0x020554c8 ranking_init (matches)

ARM void ranking_init(void) {
    if (data_0212c5ac != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0 = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    VGroupInit();
    func_0202a5f4();
    func_02029a50(&data_021349c0, 0x28);
    ranking_noop();
    data_0212c4f8 = 0;
    if (data_0212c7c8.pickIndex == 5) {
        data_0212c7c8.unk_8e = 0;
        CgLoad(2);
    }
    CgLoad(0x14);
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0 = 0x6739;
    DataLoad(1);
    DataLoad(0x23);
    DataLoad(data_0212c7c8.playerCount + 0x22);
    ranking_player_set();
    make_cockpit();
    calc_result();
    CalcRanking();
    ComRequest(5);
    data_0212c75c.reg66 = 0x3f40;
    data_0212c75c.reg68 = 0x720 - 0x14;
    data_0212c75c.unk_08 = 0x54;
    data_0212c75c.unk_20 = 0x844a;
    data_0212c75c.unk_2c = 0x864b;
    data_0212c75c.unk_0a = 0;
    data_0212c75c.unk_0c = 0;
    data_0212c75c.unk_22 = 0;
    data_0212c75c.scrollX = 0x140;
    data_0212c75c.unk_2e = 0;
    data_0212c75c.unk_30 = 0x140;
    data_0212c648.unk_20 = 0;
    data_0212c648.cameraX = 0x140;
    data_0212c75c.displayFlags = 0x1d40;
    data_021349c0.unk_27 = 0;
    FadeSet(2, 4);
    data_0212c500++;
}

ARM void ranking_scroll(void) {
    s32 wanted;
    s16 cameraX;

    if (data_0212c648.target == 0) {
        return;
    }
    wanted = (s16)(data_0212c648.target->y.HALF.HI - 0x60);
    if (wanted < 0) {
        wanted = 0;
    }
    if (wanted > 0x140) {
        wanted = 0x140;
    }
    cameraX = data_0212c648.cameraX;
    if (cameraX != wanted) {
        if (cameraX < wanted) {
            wanted = cameraX + 1;
        } else {
            wanted = cameraX - 1;
        }
        data_0212c648.cameraX = wanted;
    }
    data_0212c75c.unk_30 = data_0212c648.cameraX;
    data_0212c75c.scrollX = data_0212c75c.unk_30;
}
