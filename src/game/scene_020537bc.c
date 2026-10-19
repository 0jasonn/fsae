#include "game/scene_d.h"
#include "global.h"

// Scene_SpawnPatternE -> Scene_SpawnPatternE, ... Scene_SpawnPatternJ -> Scene_SpawnPatternJ: same shape as Scene_SpawnPatternD
// with an entity argument: one of two lists chosen by bit 0 of Random().

ARM void Scene_SpawnPatternE(Entity *e) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_02111741, e);
    } else {
        func_0204e690(data_0211173c, e);
    }
}

ARM void Scene_SpawnPatternF(Entity *e) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_020d8115, e);
    } else {
        func_0204e690(data_020d8110, e);
    }
}

ARM void Scene_SpawnPatternG(Entity *e) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_021119e3, e);
    } else {
        func_0204e690(data_021119dc, e);
    }
}

ARM void Scene_SpawnPatternH(Entity *e) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_020d8121, e);
    } else {
        func_0204e690(data_020d811c, e);
    }
}

ARM void Scene_SpawnPatternI(Entity *e) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_02111c9f, e);
    } else {
        func_0204e690(data_02111c96, e);
    }
}

ARM void Scene_SpawnPatternJ(Entity *e) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_020d812d, e);
    } else {
        func_0204e690(data_020d8128, e);
    }
}

// Scene_ResetOverlayState -> Scene_ResetOverlayState
ARM void Scene_ResetOverlayState(void) {
    func_02029a50(data_02134980, 0x20);
    func_020a1a1c(data_02171c84);
    data_0212c5bc[0x11] = 0;
}

// Scene_SetFlag5 -> Scene_SetFlag5, Scene_ClearFlag5 -> Scene_ClearFlag5
ARM void Scene_SetFlag5(void) {
    data_02134980[5] = 1;
}

ARM void Scene_ClearFlag5(void) {
    data_02134980[5] = 0;
}

// Scene_CallStateHandler -> Scene_CallStateHandler
ARM void Scene_CallStateHandler(void) {
    data_0211474c[data_02134980[0]]();
}

// Scene_UpdatePlayerSelect -> Scene_UpdatePlayerSelect (guess)
ARM void Scene_UpdatePlayerSelect(void) {
    u8 i;
    if (data_0212c5ac.blendEnabled != 0 || data_02134980[5] != 0) {
        return;
    }
    if (func_0208de54(func_0208da4c()) != 0) {
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            if ((data_0212c58c[i] & 0x8) != 0 && (data_0212c584[i] & 0x1000) == 0
                && (s8)data_0212ceb0[i].entity->iframes >= 0) {
                Scene_QueueSelect(i);
            }
        }
        return;
    }
    if ((data_0212c58c[0] & 0x8) == 0) {
        return;
    }
    if ((data_0212c584[0] & 0x1000) != 0 && (data_0212c584[1] & 0x1000) != 0) {
        return;
    }
    if ((s8)data_0212ceb0[0].entity->iframes < 0 && (s8)data_0212ceb0[1].entity->iframes < 0) {
        return;
    }
    Scene_QueueSelect(0);
}
