#include "engine/functions.h"
#include "game/ending_scene.h"
#include "global.h"

// demo_01 (0x020454a8): the staff roll demo, one step per countdown of effectState.timer; each step poses the player
// and the scene actors, then the last one clears the screen buffers and starts the next scene.
void demo_01(void) {
    u8 phase = effectState.subPhase;
    switch (phase) {
    case 0:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.subPhase = phase + 1;
        effectState.timer = 0xc;
        data_02134d30[0].entity->animationState = 6;
        break;
    case 1:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.subPhase = phase + 1;
        effectState.timer = 0x78;
        playerWork[0].entity->animationState = 2;
        break;
    case 2:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        data_02134d30[0].scriptArg = 2;
        effectState.subPhase = phase + 1;
        effectState.timer = 0x1e;
        data_02134d30[0].dirArg = 0x80;
        data_02134d30[0].unk_06 = 0x10;
        data_02134d30[0].entity->animationState = 4;
        data_02134d30[0].entity->speed = 0x80;
        break;
    case 3:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.subPhase = phase + 1;
        effectState.timer = 0xb4;
        playerWork[0].entity->animationState = 4;
        DemoLinkWalkSet(0, 0x40, 0);
        break;
    case 4:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.subPhase = phase + 1;
        effectState.timer = 0x28;
        yousei_move();
        break;
    case 5:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.subPhase = phase + 1;
        effectState.timer = 0x28;
        blendRequest.resetValue = ~0x100000;
        PaletteFade_ClearBufferFlag();
        FadeSet(1, 2);
        em12_typeMasks[0] |= 0x10;
        break;
    case 6:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        effectState.subPhase = phase + 1;
        effectState.timer = 0x78;
        GetSetWork(0x5a, 5, 0);
        SoundReq(0x800b01a0);
        break;
    case 7:
        effectState.timer--;
        if (effectState.timer == 0) {
            effectState.subPhase = phase + 1;
            effectState.timer = 0x12c;
        }
        break;
    case 8:
        effectState.timer--;
        if (effectState.timer != 0) {
            break;
        }
        MIi_CpuClearFast(0, data_021355a0, 0x280);
        MIi_CpuClearFast(0, &data_021355a0[0x150], 0x160);
        MIi_CpuClearFast(0, data_0216fd04, 0x400);
        blendRequest.resetValue = -1;
        PaletteFade_ClearBufferFlag();
        FadeSet(1, 2);
        subTask_staffroll_setFlagOff();
        effectState.subPhase = 0;
        effectState.phase = 0;
        data_0212c4dc++;
        break;
    }
}
