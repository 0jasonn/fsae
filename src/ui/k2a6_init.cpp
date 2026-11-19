#include "engine/functions.h"
#include "ui/k2a6.h"
#include "game/scene.h"

// k2a6_init(unsigned char) (0x020535fc): for each of four map positions picks one of three tile layouts at random and stores
// its tile indices into the two layers of the scene.
void k2a6_init(u8 unused) {
    switch (Random() % 3) {
    case 0:
        Scene_StoreTileIndices(data_02109484, 0x490, 0x485);
        break;
    case 1:
        Scene_StoreTileIndices(data_0210948c, 0x490, 0x485);
        break;
    case 2:
        Scene_StoreTileIndices(data_02109494, 0x490, 0x485);
        break;
    }
    switch (Random() % 3) {
    case 0:
        Scene_StoreTileIndices(data_0210949c, 0x485, 0x490);
        break;
    case 1:
        Scene_StoreTileIndices(data_021094a4, 0x485, 0x490);
        break;
    case 2:
        Scene_StoreTileIndices(data_021094ac, 0x485, 0x490);
        break;
    }
    switch (Random() % 3) {
    case 0:
        Scene_StoreTileIndices(data_021094b4, 0x477, 0x46e);
        break;
    case 1:
        Scene_StoreTileIndices(data_021094bc, 0x477, 0x46e);
        break;
    case 2:
        Scene_StoreTileIndices(data_021094c4, 0x477, 0x46e);
        break;
    }
    switch (Random() % 3) {
    case 0:
        Scene_StoreTileIndices(data_021094cc, 0x46e, 0x477);
        break;
    case 1:
        Scene_StoreTileIndices(data_021094d4, 0x46e, 0x477);
        break;
    case 2:
        Scene_StoreTileIndices(data_021094dc, 0x46e, 0x477);
        break;
    }
}
