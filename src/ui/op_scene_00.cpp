#include "engine/functions.h"
#include "engine/misc.h"
#include "engine/effect_state.h"
#include "engine/message_request.h"
#include "engine/blend_request.h"
#include "engine/scene_slot.h"

// scene_00() (0x0205114c, op_scene_00): the opening's first scene: the fairy and Link enter, the dialog lines are
// requested one after the other (each waits for the message window and arms the status display), then the NPC script runs
// and the scene fades out.
void op_scene_00(void) {
    Entity *e;

    switch (effectState.phase) {
    case 0:
        GX_DispOn();
        if (blendRequest.blendEnabled != 0) {
            return;
        }
        e = func_02072554(0);
        e->spriteSettings.b0 = 1;
        e->x.HALF.HI = 0x70;
        e->y.HALF.HI = 0x1a0;
        e->animationState = 0;
        e->spriteSettings.b30 = 2;
        e->unk_2e = 3;
        e->unk_5e.b2 = 1;
        GetNPC(0x5d, 0, 0);
        e = data_02134d30[0].entity;
        e->x.HALF.HI = 0x90;
        e->y.HALF.HI = 0x198;
        effectState.phase++;
        return;
    case 1:
        if (effectState.stepTimer != 0) {
            return;
        }
        DemoLinkWalkSet(0, 0x68, 0);
        data_02134d30[0].scriptArg = 2;
        data_02134d30[0].dirArg = 0xe0;
        data_02134d30[0].unk_06 = 0;
        data_02134d30[0].entity->animationState = 0;
        data_02134d30[0].entity->speed = 0x80;
        effectState.phase++;
        return;
    case 2:
        if (data_02134d30[0].waitFlag == 0) {
            effectState.timer = 0x3c;
            effectState.phase++;
        }
        return;
    case 3:
        if (effectState.fadeActive == 0) {
            return;
        }
        if (effectState.timer == 8) {
            data_02134d30[0].entity->animationState = 6;
        }
        effectState.timer--;
        if (effectState.timer != 0) {
            return;
        }
        MessageRequest(1);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
        data_02134d30[0].entity->animationState = 4;
        effectState.phase++;
        return;
    case 4:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        DemoLinkWalkSet(0, 0x10, 0);
        effectState.timer = 0x10;
        return;
    case 5:
        effectState.timer--;
        if (effectState.timer == 0) {
            effectState.phase++;
        }
        return;
    case 6:
        effectState.timer = 0x3c;
        effectState.phase++;
        data_02134d30[0].entity->animationState = 6;
        playerWork[0].entity->animationState = 2;
        MessageRequest(2);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
        return;
    case 7:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        effectState.timer = 0x10;
        return;
    case 8:
        effectState.timer--;
        if (effectState.timer != 0) {
            return;
        }
        MessageRequest(3);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0x10;
        SoundReq(0x80040008);
        effectState.phase++;
        return;
    case 9:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        DemoLinkWalkSet(0, 0x10, 0);
        playerWork[0].state = 8;
        playerWork[0].entity->animationState = 0;
        ScriptJump(&data_02134d30[0], data_02104a74);
        return;
    case 10:
        if (ScriptMove(&data_02134d30[0]) == 0) {
            return;
        }
        effectState.phase = 0;
        data_0212c4dc++;
        blendRequest.blendColor = 0;
        blendRequest.resetValue = 0x20fff0;
        PaletteFade_ClearBufferFlag();
        return;
    }
}
