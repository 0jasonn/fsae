#ifndef WIP_A_EFF_H
#define WIP_A_EFF_H

#include "engine/functions.h"

// Effect work entry (16 bytes). The table is data_0217d190 with the count in data_0217d18c.
typedef struct EffWork {
    s32 kind;    // 0x00: 2 cut in, 3 fade out, 4 fade in, 6 white out, 7 white in
    s32 level;   // 0x04: 16.16 fixed point progress
    s32 unk_08;
    s32 speed;   // 0x0c: added to level every frame
} EffWork;

// Fixed point level word stored by the fade effects (level >> 12) and the state word in data_0217d23c + 0xf8.
extern s32 data_0217d18c;
extern u8 data_0217d190[];
extern u8 data_0217c23c[];
extern u8 data_0217d23c[];
extern s32 data_0217d334;

extern "C" void MI_CpuFill8(void *dst, u8 value, u32 size);
extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);

EffWork *effwk_add(void);
void effwk_del(void *work, s32 index);
int eff_cut_out(void *work, s32 index);
void eff_cut_in_init(void);
int eff_cut_in(void *work, s32 index);
void eff_fade_out_init(s32 speed);
int eff_fade_out(void *work, s32 index);
void eff_fade_in_init(s32 speed);
int eff_fade_in(void *work, s32 index);
int eff_fade_in2(void *work, s32 index);
void eff_white_out_init(s32 speed);
int eff_white_out(void *work, s32 index);
void eff_white_in_init(s32 speed);
int eff_white_in(void *work, s32 index);

#endif
