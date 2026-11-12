#include "engine/functions.h"
#include "actor/enemy/ending.h"
#include "actor/enemy/ending_scene_00.h"
#include "global.h"

// ending_scene_00 (0x02044700): the first ending scene. Waits for the rescue flag, shows the three ending messages
// with a surprise mark before each, places the two scene actors and finally hands over to the next task.
void ending_scene_00(void) {
    u8 phase = effectState.phase;
    u8 i;
    Entity *actor;

    switch (phase) {
    case 0:
        if (em12_typeMasks & 1) {
            effectState.phase = phase + 1;
            effectState.timer = 0x1e;
        }
        break;
    case 1:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        effectState.timer = 0x78;
        em12_typeMasks |= 2;
        break;
    case 2:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        MessageRequest(0x1f6);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = messageRequest.unk_04 & ~0x1f;
        break;
    case 3:
        if ((messageRequest.unk_00 & 0x7f) != 6) {
            break;
        }
        SoundReq(0x800b01b9);
        Status_ArmIfEnabled();
        effectState.phase++;
        break;
    case 4:
        if (ending_msgFinishWait() != 0) {
            break;
        }
        data_02134d30.unk_04 = 7;
        effectState.phase++;
        break;
    case 5:
        if (data_02134d30.unk_00[2] == 0) {
            effectState.phase = phase + 1;
            effectState.timer = 0x1e;
        }
        break;
    case 6:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        effectState.timer = 0x3c;
        bikkuri();
        break;
    case 7:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        MessageRequest(0x1f8);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = messageRequest.unk_04 & ~0x1f;
        break;
    case 8:
        if ((messageRequest.unk_00 & 0x7f) != 6) {
            break;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        break;
    case 9:
        if (ending_msgFinishWait() != 0) {
            break;
        }
        effectState.timer = 0x3c;
        effectState.phase++;
        break;
    case 10:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        effectState.timer = 0x3c;
        bikkuri();
        break;
    case 11:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        MessageRequest(0x1fa);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = messageRequest.unk_04 & ~0x1f;
        messageRequest.unk_08 = gameState.playerCount;
        break;
    case 12:
        if ((messageRequest.unk_00 & 0x7f) != 6) {
            break;
        }
        Status_ArmIfEnabled();
        effectState.phase++;
        break;
    case 13:
        if (ending_msgFinishWait() != 0) {
            break;
        }
        effectState.timer = 0x3c;
        effectState.phase++;
        break;
    case 14:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        actor = GetSetWork(0x68, 3, 0);
        actor->x.HALF.HI = 0x1f8;
        actor->y.HALF.HI = 0x1ee;
        actor = GetSetWork(0x68, 3, 4);
        actor->x.HALF.HI = 0x1f8;
        actor->y.HALF.HI = 0x1ee;
        effectState.phase++;
        effectState.timer = 0x3c;
        SoundReq(0x80040000);
        break;
    case 15:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.phase = phase + 1;
        effectState.timer = 0x78;
        bikkuri();
        for (i = 0; i < gameState.playerCount; i++) {
            playerWork[i].entity->animationState = 4;
        }
        break;
    case 16:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        data_0212c4dc++;
        effectState.phase = 0;
        em12_typeMasks |= 4;
        break;
    }
}
