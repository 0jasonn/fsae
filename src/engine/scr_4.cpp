#include "engine/functions.h"
#include "global.h"
#include "actor/object/pot.h"
#include "game/rankingsave.h"
#include "game/savemedia.h"
#include "engine/bg_buff.h"

// Scroll and map unit (module scr): FrameSet 0x0205715c, PartsSet 0x020571fc.
// Both load a map into the work buffer and copy it into the two BG layer buffers (BlockCopy).

extern u8 triangleTable[];       // map work buffer
extern u32 *data_020d7680[];     // map table indexed by frame
extern u32 *data_020d78b4[];     // parts map table
extern u16 data_020d8168[];      // (x, y) in pixels of each part

void FrameSet(u16 frame) {
    u16 *work = (u16 *)triangleTable;

    MemClearFast(work, 0x4000);
    MapLoad(data_020d7680[frame], 0);
    BlockCopy(data_02158fa0.screen, work, (u16)(mapState.limitX >> 4), (u16)((mapState.limitY >> 4) | 0x8000));
    BlockCopy(data_02163fa4.screen, work + 0x1000, (u16)(mapState.limitX >> 4), (u16)((mapState.limitY >> 4) | 0x8000));
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
    BlockCopy(data_02158fa0.screen + offset, work, x, (u16)(y | 0x8000));
    BlockCopy(data_02163fa4.screen + offset, work + 0x400, x, (u16)(y | 0x8000));
    AtariMake();
}

// Scroll and map unit 5 (module scr). Address -> name (original names):
//   0x020572b4 MultiRoomSet

extern "C" {
void MakeMapScreen(const void *src, void *dst);
}
extern u8 data_02140fa0[];
extern u8 data_02148fa0[];
extern u8 data_02135640[];
extern u8 data_02135840[];
#include "engine/em2f_map_flag.h"

void MultiRoomSet(void) {
    MIi_CpuCopy32(data_02158fa0.screen, data_02158fa0.screenSave, 0x2000);
    MIi_CpuCopy32(data_02163fa4.screen, data_02163fa4.screenSave, 0x2000);
    MakeMapScreen(data_02140fa0, &data_02158fa0);
    MakeMapScreen(data_02148fa0, &data_02163fa4);
    MIi_CpuCopyFast(data_02135640, data_02135840, 0x20);
    em2f_mapFlag |= 0x200000;
}
