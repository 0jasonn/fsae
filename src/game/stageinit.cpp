#include "engine/functions.h"
#include "game/scene_d.h"
#include "global.h"

// knife_native_init_053428 -> knife_native_init_053428
// knife_native_init_053484 -> knife_native_init_053484
// knife_native_init_0534e0 -> knife_native_init_0534e0
// Init_Kazan2A1 -> Init_Kazan2A1
// Each pattern picks one of three spawn lists at random (RandomBlockSet walks a 0xff terminated list).
ARM void knife_native_init_053428(u8 param) {
    u8 roll = Random();
    if (roll < 0x55) {
        RandomBlockSet(data_020d80e3, param);
    } else if (roll < 0xaa) {
        RandomBlockSet(data_020d80e6, param);
    } else {
        RandomBlockSet(data_020d80e0, param);
    }
}

ARM void knife_native_init_053484(u8 param) {
    u8 roll = Random();
    if (roll < 0x55) {
        RandomBlockSet(data_020d80ef, param);
    } else if (roll < 0xaa) {
        RandomBlockSet(data_020d80f2, param);
    } else {
        RandomBlockSet(data_020d80ec, param);
    }
}

ARM void knife_native_init_0534e0(u8 param) {
    u8 roll = Random();
    if (roll < 0x55) {
        RandomBlockSet(data_020d80f8, param);
    } else if (roll < 0xaa) {
        RandomBlockSet(data_020d80fb, param);
    } else {
        RandomBlockSet(data_020d80fe, param);
    }
}

ARM void Init_Kazan2A1(void) {
    if ((Random() & 1) != 0) {
        RandomBlockSet(data_020d8104, 1);
    } else {
        RandomBlockSet(data_020d8109, 1);
    }
}

// Converts the two points in pos (x0, y0, x1, y1) to tile indices, offset by data_0213492c, and writes them
// to the two layers with func_02083694.
ARM void Scene_StoreTileIndices(const u16 *pos, u32 layer0, u32 layer1) {
    func_02083694(layer0, (u16)(((pos[0] + data_0213492c[2]) >> 4) | (((pos[1] + data_0213492c[3]) >> 4) << 6)), 0x4000);
    func_02083694(layer1, (u16)(((pos[2] + data_0213492c[2]) >> 4) | (((pos[3] + data_0213492c[3]) >> 4) << 6)), 0x4000);
}
