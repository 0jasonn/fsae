#include "engine/functions.h"
#include "game/scene_d.h"
#include "global.h"

// fairy_set -> fairy_set
// fairy_talkset -> fairy_talkset
// opdemo_scroll -> opdemo_scroll
// op_title -> op_title
ARM void fairy_set(u8 slot, u8 index, u8 flags) {
    ObjAnimMoveSet(data_02134d3c[slot].entity, data_02104ab0[index], flags);
    data_02134d3c[slot].entity->action = 1;
    SoundReq(0x201);
}

ARM void fairy_talkset(u8 slot, u16 effectId) {
    MessageRequest(effectId);
    data_0217d384[SCENE_CTRL_SUBMODE_3] = (data_0217d384[SCENE_CTRL_SUBMODE_3] & ~0x1f) | 1;
    data_0217d384[SCENE_CTRL_SUBMODE_4] = (data_0217d384[SCENE_CTRL_SUBMODE_4] & ~0x1f) | 0x10;
    data_021349c0[EFFECT_STATE_ACTIVE_SLOT] = slot;
    data_02134d3c[slot].entity->action = 3;
}

// Follows the camera target (data_0212c648) on y, clamping the camera x to 0..0xa0
ARM void opdemo_scroll(void) {
    s32 desired;
    s32 next;
    if (*(Entity **)&data_0212c648 == NULL) {
        return;
    }
    desired = (s16)((*(Entity **)&data_0212c648)->y.HALF.HI - 0x60);
    if (desired < 0) {
        desired = 0;
    }
    if (desired > 0xa0) {
        desired = 0xa0;
    }
    if (data_0212c648.cameraX != desired) {
        if (data_0212c648.cameraX < desired) {
            next = data_0212c648.cameraX + 1;
        } else {
            next = data_0212c648.cameraX - 1;
        }
        data_0212c648.cameraX = next;
    }
    data_0212c75c.unk_30 = data_0212c648.cameraX;
    data_0212c75c.scrollX = data_0212c75c.unk_30;
}

ARM void op_title(void) {
    data_021349c0[8] = data_0212c530 & 0xf;
    data_02104a90[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
}
