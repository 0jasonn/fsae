#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "engine/misc.h"
#include "engine/com_work.h"
#include "engine/display_state.h"
#include "engine/map_state.h"
#include "engine/effect_state.h"
#include "actor/object/crystal.h"
#include "game/b_extra.h"
#include "ui/doorsel_init.h"
void doorsel_init(void) {
    int i;
    DispReset();
    ObjWorkPoolClear();
    ObjMoveInit();
    DemoBgBuffClear();
    MIi_CpuClear16(0, &effectState, 0x28);
    gameState.unk_8e = 0;
    for (i = 0; i < 4; i++) {
        playerWork[i].paletteBits.color = comWork.recv[i].bits.b0;
    }
    CgLoad(2);
    switch (gameState.unk_01) {
    case 2:
        CgLoad(0x23);
        DataLoad(0xc);
        break;
    case 6:
        CgLoad(0x34);
        DataLoad(0x28);
        break;
    case 5:
        CgLoad(0x35);
        DataLoad(0x29);
        break;
    }
    displayState.bg[0].cnt = 0x1e40;
    displayState.bg[1].cnt = 0x1d41;
    displayState.bg[2].cnt = 0x1c42;
    displayState.bg[2].scrollY = 0;
    displayState.bg[2].scrollX = 0;
    displayState.bg[1].scrollY = 0;
    displayState.bg[1].scrollX = 0;
    displayState.bg[0].scrollY = 0;
    displayState.bg[0].scrollX = 0;
    mapState.scrollY = 0;
    mapState.scrollX = 0;
    SetTblSetWorks(data_020cfc3c);
    effectState.selection = 0;
    switch (gameState.unk_01) {
    case 2:
        effectState.entryCount = ClearKeyCheck();
        break;
    case 5: {
        int level = gameState.slotWords[0].stageProgress & 3;
        effectState.entryCount = level == 3 ? 3 : level + 1;
        break;
    }
    case 6: {
        int level = (gameState.slotWords[0].stageProgress >> 2) & 3;
        effectState.entryCount = level == 0 ? 1 : level;
        break;
    }
    }
    effectState.progress = 0;
    effectState.stepIndex = 2;
    displayState.displayFlags |= 0x1700;
    ZeldaFadeSet(NULL, 1);
    data_0212c500++;
    data_0212c4dc = 0;
}
