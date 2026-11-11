#ifndef WIP_E_SNDWAVEARC_E_H
#define WIP_E_SNDWAVEARC_E_H

#include "engine/functions.h"

// Wave archive image as it is read from the sound table: a 0x3c byte header whose word at +0x38 counts the entries,
// followed by the entry words (and a second block of the same size that is filled by the copy).
typedef struct SndWaveArc {
    u8 unk_00[0x38];
    s32 count;        // 0x38
    u8 data[1];       // 0x3c
} SndWaveArc;

extern s32 data_021848b4[]; // header of the archive being read (0x3c bytes)
typedef struct SndWaveHdrBuf { s32 pad; s32 hdr[0xf]; } SndWaveHdrBuf;
extern SndWaveHdrBuf data_021848b0;

extern "C" {
s32 SndTable_ReadBlock(s32 index, void *payload, s32 size, s32 offset);
void *func_020c0b20(void *record, u32 size, void *callback, void *data, s32 index2);
u32 SndTable_GetWord14(s32 index);
void SndTable_SetWord14(s32 index, u32 value);
void *func_020c05dc(void);
void DC_StoreRange(void *start, u32 size);
void SndBank_ReleaseWaveArc(void *obj, s32 unused, void *data, s32 index);
void *SndBank_AcquireWaveArc(s32 index, void *record, s32 flag);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void MI_CpuFill8(void *dst, u8 value, u32 size);
}

#endif
