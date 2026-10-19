#ifndef WIP_C_STAGESEL_H
#define WIP_C_STAGESEL_H

// Declarations used by the stage select files (src/wip/C/stagesel*.cpp) that are not in engine/functions.h yet

#include "types.h"

extern "C" {
void MI_CpuCopy(const void *src, void *dst, u32 size);
void MI_UncompressLZ16(const void *src, void *dst);
}

void stagesel_loadsel(u16 index, int mode);
void stagesel_dialogDisp(u8 index, u32 unused);
void stagesel_dialogDelete(void);
void ssel_pause_dialogDisp(u32 index, s32 unused, u8 value);
int ssel_pause_dialogUpdate(void);
void effect_char_load(u8 index, int mode);
void set_please_wait(void);
void del_please_wait(void);
void start_select(int mode);
void stagesel_scroll(void);
int stagesel_save(u8 mode);
void ZeldaFadeSet(Entity *e, u32 a);
void ComRequest(u8 request);

#endif
