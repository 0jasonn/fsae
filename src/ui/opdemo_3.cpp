#include "engine/functions.h"
#include "game/scene.h"
#include "global.h"
#include "engine/message_request.h"

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
    messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
    messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
    effectState.activeSlot = slot;
    fairySlots[slot].entity->action = 3;
}

// Follows the camera target (mapState) on y, clamping the camera x to 0..0xa0
void opdemo_scroll(void) {
    s32 desired;
    s32 next;
    if (mapState.target == NULL) {
        return;
    }
    desired = (s16)(mapState.target->y.HALF.HI - 0x60);
    if (desired < 0) {
        desired = 0;
    }
    if (desired > 0xa0) {
        desired = 0xa0;
    }
    if (mapState.scrollY != desired) {
        if (mapState.scrollY < desired) {
            next = mapState.scrollY + 1;
        } else {
            next = mapState.scrollY - 1;
        }
        mapState.scrollY = next;
    }
    displayState.bg[3].scrollY = mapState.scrollY;
    displayState.bg[2].scrollY = displayState.bg[3].scrollY;
}

void op_title(void) {
    effectState.progress = opTitleState & 0xf;
    opTitleTable[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
}
