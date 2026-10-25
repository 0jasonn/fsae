#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Functions in this file (plain names from the debug build, C linkage):
//   draw_radar_goal_pos (0x020a6cc0)

// Work block at data_0217d348 (the subtask screen work): the radar OAM buffer at +0x3e0 and its entry count at +0x460.
typedef struct RadarWork {
    u8 unk_000[0x3e0];
    u8 oamBuf[0x80];   // 0x3e0: attribute entries written by subtask_draw_oam
    s32 oamCount;      // 0x460: number of entries written so far
} RadarWork;

extern u8 *data_0217d348;
extern u8 data_0217a23c[];
extern const u16 data_020df054[][4];   // sprite widths, [size][shape]
extern const u16 data_020df03c[][4];   // sprite heights, [size][shape]
extern "C" void func_020c36fc(void *obj, const void *attrs, u16 count);

// draw_radar_goal_pos(long, long) (0x020a6cc0): the goal marker, one OAM entry centred on (x + 0x38, y + 0x10)
extern "C" void draw_radar_goal_pos(s32 x, s32 y);
ARM void draw_radar_goal_pos(s32 x, s32 y) {
    GXOamShape shape = (GXOamShape)0;
    u16 width;
    u16 height;
    s32 count;

    width = data_020df054[(shape & 0xc000) >> 14][(shape & 0xc0000000) >> 30];
    height = data_020df03c[(shape & 0xc000) >> 14][(shape & 0xc0000000) >> 30];
    count = subtask_draw_oam(x + 0x38 - ((u32)width >> 1), y + 0x10 - ((u32)height >> 1), 0x24, shape, shape,
                             (GXOamAttr *)(data_0217d348 + 0x3e0));
    func_020c36fc(data_0217a23c, data_0217d348 + 0x3e0, (u16)count);
    ((RadarWork *)data_0217d348)->oamCount += count;
}
