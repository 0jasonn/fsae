#ifndef WIP_C3_SUBTASK_RASTER_H
#define WIP_C3_SUBTASK_RASTER_H

#include "types.h"

// Work block of the subtask screens (pointer at data_0217d348) as the HBlank raster setup uses it: one s32 scroll offset
// per scanline (256 of them) at 0x534.
typedef struct SubtaskRasterWork {
    u8 unk_000[0x534];
    s32 rasterOffset[256]; // 0x534
} SubtaskRasterWork;

extern SubtaskRasterWork *data_0217d348;
extern s32 data_0217d178; // raster offset of the first line group
extern s32 data_0217d17c;
extern s32 data_0217d180;
extern s32 data_0217d184;

void OS_SetIrqFunction(u32 mask, void (*func)(void)); // _Z17OS_SetIrqFunctionmPFvvE

extern "C" {
void subtask_make_lobby_raster(void);
void subtask_init_hblank_raster(s32 mode);
void GX_HBlankIntr(s32 enable);
void OS_DisableIrqMask(u32 mask);
}

#endif
