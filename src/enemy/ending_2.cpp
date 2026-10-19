#include "engine/functions.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: ending_init (0x020443a0), ending_link_init (0x02044530), ending_rescue (0x02044638),
// ending_msgFinishWait (0x020446b4).

ARM void ending_init(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    SoundReq(0x80010000);
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0xc0, objAffineSet, 0x800);
    MIi_CpuClearFast(0, data_0212ccb0, 0x200);
    data_0212c618 = 0;
    MIi_CpuClearFast(0, data_021361a0, 0x1000);
    func_02026774();
    ObjWorkPoolClear();
    ObjMoveInit();
    VGroupInit();
    InitObjColor();
    MessageInitialize();
    func_0204f978();
    PlWorkClear();
    MIi_CpuClear16(0, &data_021349c0, 0x28);
    DataLoad(8);
    em12_typeMasks = 0;
    GetNPC(0x5d, 1, 0);
    data_02134d30.entity->x.HALF.HI = 0x1f8;
    data_02134d30.entity->y.HALF.HI = 0x1b8;
    data_0212c648.target = data_02134d30.entity;
    data_02134d30.unk_04 = 6;
    ending_link_init();
    Entity *linked = GetSetWork(0x69, 4, 0);
    linked->x.HALF.HI = 0x1f8;
    linked->y.HALF.HI = 0x1f8;
    data_0212c500 = 1;
    data_0212c4dc = 0;
    data_0212c564();
    em2f_mapFlag = 0;
    ComRequest(5);
    data_021349c0.frames = 0;
}

ARM void ending_link_init(void) {
    u8 i;
    selectEndingLink();
    for (i = 0; i < GAME_STATE_U8(0) ; i++) {
        Entity *e = func_02072554(i);
        u8 slot = 3 - i;
        e->spriteSettings.b0 = 1;
        e->x.HALF.HI = 0x1f8 - ((GAME_STATE_U8(0) - 1) << 3) + (i << 4);
        e->y.HALF.HI = 0x1d8;
        e->animationState = 0;
        e->spriteSettings.b30 = 2;
        e->unk_2e = 3;
        e->unk_5e.b2 = 1;
        e->unk_5e.b0 = slot;
    }
    {
        Entity *selected = data_0212ceb0[GAME_STATE_U8(0x53)].entity;
        u8 prevB0 = selected->unk_5e.b0;
        selected->unk_5e.b0 = 3;
        data_0212ceb0[0].entity->unk_5e.b0 = prevB0;
    }
}

ARM void ending_rescue(void) {
    if (CommFrameSync() == 0) {
        return;
    }
    CommUpdateJoy();
    data_021349c0.frames++;
    endingRescueTable[data_0212c4dc]();
    data_0212c564();
    if (data_0212c4dc < 2) {
        ScrollMove();
        BgAnm();
        func_0208309c();
    }
    VGroupManager();
    func_020830ec();
    CommFrameUpdate();
}

ARM BOOL ending_msgFinishWait(void) {
    u8 i;
    for (i = 0; i < GAME_STATE_U8(0); i++) {
        if (data_0212c584[i] & 0x1000) {
            return TRUE;
        }
    }
    return FALSE;
}
