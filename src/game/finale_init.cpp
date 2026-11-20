#include "engine/functions.h"
#include "game/ending_scene.h"
#include "engine/disp_reset.h"
#include "global.h"

// finale_init (0x020450e4): sets up the staff roll scene (palette/cg resources, the BG registers, the scene actors and
// the player's stand-in), then starts the final link wait.
void finale_init(void) {
    Entity *player;
    Entity *npc;
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    data_0212c4f8 = 0;
    SoundReq(0x80040000);
    DispReset();
    initializeVirtualScreenData();
    setupVirtualScreenCallback();
    ObjMoveInit();
    ObjWorkPoolClear();
    VGroupInit();
    InitObjColor();
    data_02134924 = 0;
    MessageInitialize();
    func_0204f978();
    MIi_CpuClear16(0, &effectState, 0x28);
    PlWorkClear();
    CgLoad(0x17);
    DataLoad(2);
    displayState.bg[2].cnt = 0x841a;
    displayState.bg[3].cnt = 0x687;
    displayState.blendCnt = 0x3c66;
    displayState.blendAlpha = 0x808;
    displayState.bg[2].scrollX = 0;
    displayState.bg[2].scrollY = 0x10;
    displayState.bg[3].scrollX = 0;
    displayState.bg[3].scrollY = 0x10;
    mapState.scrollX = 0;
    mapState.scrollY = 0x10;
    npc = GetSetWork(0x5a, 2, 0);
    npc->x.HALF.HI = 0x80;
    npc->y.HALF.HI = 0xf0;
    data_02134d30[1].entity = GetSetWork(0x5a, 3, 0);
    data_02134d30[2].entity = GetSetWork(0x5a, 3, 1);
    data_02134d30[3].entity = GetSetWork(0x5a, 3, 2);
    player = func_02072554(0);
    player->spriteSettings.b0 = 1;
    player->x.HALF.HI = 0x70;
    player->y.HALF.HI = 0x110;
    player->animationState = 0;
    player->spriteSettings.b30 = 2;
    player->unk_2e = 3;
    player->unk_5e.b2 = 1;
    player->spriteSettings.b16 = gameState.unk_50[3] + 7;
    player->spriteSettings.b20 = player->spriteSettings.b16;
    GetNPC(0x5d, 0, 0);
    npc = data_02134d30[0].entity;
    npc->x.HALF.HI = 0x90;
    npc->y.HALF.HI = 0x110;
    em2f_mapFlag = 0;
    data_0212c4dc++;
    subTask_staffroll_start_finale();
    ComRequest(4);
}
