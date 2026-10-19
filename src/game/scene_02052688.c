#include "game/scene_d.h"
#include "global.h"

// Scene_StartSlotEntity -> Scene_StartSlotEntity
// Scene_StartSlotEffect -> Scene_StartSlotEffect
// Scene_FollowCameraTarget -> Scene_FollowCameraTarget
// Scene_UpdateStep -> Scene_UpdateStep
ARM void Scene_StartSlotEntity(s32 slot, s32 index, s32 flags) {
    func_0205069c(data_02134d3c[slot].entity, data_02104ab0[index], flags);
    data_02134d3c[slot].entity->action = 1;
    SoundReq(0x201);
}

ARM void Scene_StartSlotEffect(s32 slot, s32 effectId) {
    Status_ResetWithValue(effectId);
    data_0217d384[SCENE_CTRL_SUBMODE_3] = (data_0217d384[SCENE_CTRL_SUBMODE_3] & ~0x1f) | 1;
    data_0217d384[SCENE_CTRL_SUBMODE_4] = (data_0217d384[SCENE_CTRL_SUBMODE_4] & ~0x1f) | 0x10;
    data_021349c0[EFFECT_STATE_ACTIVE_SLOT] = slot;
    data_02134d3c[slot].entity->action = 3;
}

// Follows the camera target (data_0212c648) on y, clamping the camera x to 0..0xa0
ARM void Scene_FollowCameraTarget(void) {
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

ARM void Scene_UpdateStep(void) {
    data_021349c0[8] = data_0212c530 & 0xf;
    data_02104a90[data_0212c4dc]();
    data_0212c564();
    func_020830ec();
}
