#include "game/scene_d.h"
#include "global.h"

// Scene_SpawnPatternA -> Scene_SpawnPatternA
// Scene_SpawnPatternB -> Scene_SpawnPatternB
// Scene_SpawnPatternC -> Scene_SpawnPatternC
// Scene_SpawnPatternD -> Scene_SpawnPatternD
// Each pattern picks one of three spawn lists at random (func_0204e690 walks a 0xff terminated list).
ARM void Scene_SpawnPatternA(Entity *e) {
    u8 roll = Random();
    if (roll < 0x55) {
        func_0204e690(data_020d80e3, e);
    } else if (roll < 0xaa) {
        func_0204e690(data_020d80e6, e);
    } else {
        func_0204e690(data_020d80e0, e);
    }
}

ARM void Scene_SpawnPatternB(Entity *e) {
    u8 roll = Random();
    if (roll < 0x55) {
        func_0204e690(data_020d80ef, e);
    } else if (roll < 0xaa) {
        func_0204e690(data_020d80f2, e);
    } else {
        func_0204e690(data_020d80ec, e);
    }
}

ARM void Scene_SpawnPatternC(Entity *e) {
    u8 roll = Random();
    if (roll < 0x55) {
        func_0204e690(data_020d80f8, e);
    } else if (roll < 0xaa) {
        func_0204e690(data_020d80fb, e);
    } else {
        func_0204e690(data_020d80fe, e);
    }
}

ARM void Scene_SpawnPatternD(void) {
    if ((Random() & 1) != 0) {
        func_0204e690(data_020d8104, (void *)1);
    } else {
        func_0204e690(data_020d8109, (void *)1);
    }
}

// Converts the two points in pos (x0, y0, x1, y1) to tile indices, offset by data_0213492c, and writes them
// to the two layers with func_02083694.
ARM void Scene_StoreTileIndices(const u16 *pos, u32 layer0, u32 layer1) {
    func_02083694(layer0, (u16)(((pos[0] + data_0213492c[2]) >> 4) | (((pos[1] + data_0213492c[3]) >> 4) << 6)), 0x4000);
    func_02083694(layer1, (u16)(((pos[2] + data_0213492c[2]) >> 4) | (((pos[3] + data_0213492c[3]) >> 4) << 6)), 0x4000);
}
