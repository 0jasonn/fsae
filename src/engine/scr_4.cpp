#include "engine/functions.h"
#include "global.h"
#include "actor/object/pot.h"

// Scroll and map unit (module scr): FrameSet 0x0205715c, PartsSet 0x020571fc.
// Both load a map into the work buffer and copy it into the two BG layer buffers (BlockCopy).

extern u8 triangleTable[];       // map work buffer
extern u8 data_02158fa4[];       // BG layer 0 cell buffer
extern u8 data_02163fa8[];       // BG layer 1 cell buffer
extern u32 *data_020d7680[];     // map table indexed by frame
extern u32 *data_020d78b4[];     // parts map table
extern u16 data_020d8168[];      // (x, y) in pixels of each part

void FrameSet(u16 frame) {
    u16 *work = (u16 *)triangleTable;

    MemClearFast(work, 0x4000);
    MapLoad(data_020d7680[frame], 0);
    BlockCopy((u16 *)data_02158fa4, work, (u16)(mapState.viewX >> 4), (u16)((mapState.viewY >> 4) | 0x8000));
    BlockCopy((u16 *)data_02163fa8, work + 0x1000, (u16)(mapState.viewX >> 4), (u16)((mapState.viewY >> 4) | 0x8000));
    AtariMake();
}

void PartsSet(u16 part, u16 cellX, u16 cellY) {
    u16 *work = (u16 *)triangleTable;
    u32 *map;
    u16 x;
    u16 y;
    int offset;

    MemClearFast(work, 0x1000);
    map = data_020d78b4[part];
    x = data_020d8168[part * 2] >> 4;
    y = data_020d8168[part * 2 + 1] >> 4;
    MapLoad(map, 1);
    offset = cellX + cellY * 0x40;
    BlockCopy((u16 *)data_02158fa4 + offset, work, x, (u16)(y | 0x8000));
    BlockCopy((u16 *)data_02163fa8 + offset, work + 0x400, x, (u16)(y | 0x8000));
    AtariMake();
}
