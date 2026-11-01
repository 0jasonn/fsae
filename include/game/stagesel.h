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

// Parameter block of the stage select message dialog (data_02116720). Only the fields used here are named.
typedef struct SselDialogParams {
    /* 00 */ u8 unk_00[0x34];
    /* 34 */ u32 bgVramBase; // 0x06000000
    /* 38 */ u8 unk_38[0xc];
    /* 44 */ u16 unk_44;
    /* 46 */ u8 unk_46[0x22];
    /* 68 */ void *msgScrn; // KnifeApp work + 0x1bc
    /* 6c */ void *dialogBuffer;
    /* 70 */ u8 unk_70[8];
    /* 78 */ u32 unk_78;
    /* 7c */ u16 unk_7c;
    /* 7e */ u8 unk_7e;
    /* 7f */ u8 unk_7f[0x21];
    /* a0 */ void *msgScrnPause;
} SselDialogParams;

// One 6-byte row of the stage select dialog table: layout key, message index and sound effect
typedef struct SselDialogRow {
    u16 layout;
    u16 msgIndex;
    u16 sfxId;
} SselDialogRow;

#endif
