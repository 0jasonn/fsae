#include "engine/functions.h"
#include "engine/bg_buff.h"
#include "engine/vblank_request.h"
#include "engine/a_decls.h"

// RewCellOne (0x02021a94): rewrites one map cell with the cell of a source index. The tile entry and the attribute come
// from the layer's BG buffer (the cell index of source and the attribute table data_02171e0c), and the 2x2 tiles are
// copied from the buffer's tile data into the map screen of that layer (layer bits 14-15: 2 = the second layer).
// A source of 0x800 or more restores the cell instead (RewCellBack). Requests the scroll update for the current frame.
void RewCellOne(u16 source, u16 dest, u16 layer) {
    BG_BUFF_ *buffer;
    u16 tile;
    u16 *map;
    u16 *tileSource;
    int index;

    if (source < 0x800) {
        buffer = (BG_BUFF_ *)GetBgBuffAdrs(layer);
        tile = buffer->cellIndex[source];
        buffer->screen[dest] = tile;
        buffer->attr[dest] = data_02171e0c[source];
        index = ((dest & 0x3f) << 1) + ((dest & 0xfc0) << 2);
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
    } else {
        RewCellBack(dest, layer);
    }
}
