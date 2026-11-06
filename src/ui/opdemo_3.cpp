#include "engine/functions.h"
#include "game/scene.h"
#include "global.h"

// fairy_set -> fairy_set
// fairy_talkset -> fairy_talkset
// opdemo_scroll -> opdemo_scroll
// op_title -> op_title
void fairy_set(u8 slot, u8 index, u8 flags) {
    ObjAnimMoveSet(fairySlots[slot].entity, fairyMoveTable[index], flags);
    fairySlots[slot].entity->action = 1;
    SoundReq(0x201);
}

void fairy_talkset(u8 slot, u16 effectId) {
    MessageRequest(effectId);
    messageRequest[SCENE_CTRL_SUBMODE_3] = (messageRequest[SCENE_CTRL_SUBMODE_3] & ~0x1f) | 1;
    messageRequest[SCENE_CTRL_SUBMODE_4] = (messageRequest[SCENE_CTRL_SUBMODE_4] & ~0x1f) | 0x10;
    effectState[EFFECT_STATE_ACTIVE_SLOT] = slot;
    fairySlots[slot].entity->action = 3;
}

// Follows the camera target (mapState) on y, clamping the camera x to 0..0xa0
void opdemo_scroll(void) {
    s32 desired;
    s32 next;
    if (*(Entity **)&mapState == NULL) {
        return;
    }
    desired = (s16)((*(Entity **)&mapState)->y.HALF.HI - 0x60);
    if (desired < 0) {
        desired = 0;
    }
    if (desired > 0xa0) {
        desired = 0xa0;
    }
    if (mapState.cameraX != desired) {
        if (mapState.cameraX < desired) {
            next = mapState.cameraX + 1;
        } else {
            next = mapState.cameraX - 1;
        }
        mapState.cameraX = next;
    }
    displayState.unk_30 = mapState.cameraX;
    displayState.scrollX = displayState.unk_30;
}

void op_title(void) {
    effectState[8] = opTitleState & 0xf;
    opTitleTable[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
}
