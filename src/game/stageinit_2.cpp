#include "engine/functions.h"
#include "game/scene_d.h"
#include "global.h"

// knife_native_init_0537bc -> knife_native_init_0537bc, ... knife_native_init_0538e8 -> knife_native_init_0538e8: same shape as Init_Kazan2A1
// with an entity argument: one of two lists chosen by bit 0 of Random().

ARM void knife_native_init_0537bc(u8 param) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_02111741, param);
    } else {
        RandomBlockSet(data_0211173c, param);
    }
}

ARM void knife_native_init_0537f8(u8 param) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_020d8115, param);
    } else {
        RandomBlockSet(data_020d8110, param);
    }
}

ARM void knife_native_init_053834(u8 param) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_021119e3, param);
    } else {
        RandomBlockSet(data_021119dc, param);
    }
}

ARM void knife_native_init_053870(u8 param) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_020d8121, param);
    } else {
        RandomBlockSet(data_020d811c, param);
    }
}

ARM void knife_native_init_0538ac(u8 param) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_02111c9f, param);
    } else {
        RandomBlockSet(data_02111c96, param);
    }
}

ARM void knife_native_init_0538e8(u8 param) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_020d812d, param);
    } else {
        RandomBlockSet(data_020d8128, param);
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

// Pause -> Pause
ARM void Pause(void) {
    data_0211474c[data_02134980[0]]();
}

// pause_init -> pause_init (guess)
ARM void pause_init(void) {
    u8 i;
    if (data_0212c5ac.blendEnabled != 0 || data_02134980[5] != 0) {
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            if ((data_0212c58c[i] & 0x8) != 0 && (data_0212c584[i] & 0x1000) == 0
                && (s8)data_0212ceb0[i].entity->iframes >= 0) {
                pause_req(i);
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
    pause_req(0);
}
