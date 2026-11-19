#include "engine/functions.h"
#include "engine/bg_buff.h"
#include "engine/vblank_request.h"
#include "engine/a_decls.h"

// RewCellBack (0x02021df4): restores a map cell from the saved screen of its layer: the tile entry comes back from
// screenSave, the attribute is looked up from the cell map and the 2x2 tiles are copied again into the map screen.
void RewCellBack(int cell, int layer) {
    BG_BUFF_ *buffer = (BG_BUFF_ *)GetBgBuffAdrs(layer);
    u16 tile = buffer->screenSave[cell];
    u16 *map;
    u16 *tileSource;
    int index;

    buffer->screen[cell] = tile;
    buffer->attr[cell] = data_02171e0c[buffer->cellMap[tile]];
    index = ((cell & 0x3f) << 1) + ((cell & 0xfc0) << 2);
    if ((layer >> 14) != 2) {
        map = data_02140fa0 + index;
    } else {
        map = data_02148fa0 + index;
    }
    tileSource = (u16 *)buffer->unk_7004 + tile * 4;
    map[0] = tileSource[0];
    map[1] = tileSource[1];
    map[0x80] = tileSource[2];
    map[0x81] = tileSource[3];
    data_021348f4[data_0212c4c8] = 1;
}
