#ifndef WIP_G_KNIFE_MANUAL_H
#define WIP_G_KNIFE_MANUAL_H

// Knife manual-mode functions (0x020c7c10 to 0x020c8104). The Knife::* functions are static (no this): they
// are written as namespace functions, which mangle to the same names.

#include "types.h"
#include "engine/functions.h"
#include "game/menu.h"

// Global object of the Knife manual mode (the menu wrapper at data_0218704c): a pointer at +0x14, three block
// pointers at +0x18 and a flag byte at +0x3c. Size 0x40 (cleared by Knife::i_postprocManual).
typedef struct KnifeManual {
    /* 00 */ u8 unk_00[0x14];
    /* 14 */ void *block14;
    /* 18 */ void *blocks[3];
    /* 24 */ u8 unk_24[0x3c - 0x24];
    /* 3c */ u8 flag3c;
} KnifeManual;

extern KnifeManual data_0218704c;
extern u8 data_02187050[];
extern u8 data_02fe0000[];

// Menu_RunFromWrapper (src/game/menu_14.cpp, original signature in original_names.tsv)
void Menu_RunFromWrapper(MenuWrapper *w);

extern "C" {
void m4aEnterManualAlias(void);
void Knife_i_restoreGfxSettings(void);
void *Knife_GetPowerManager(void);
void MI_CpuFill8(void *dst, u8 value, u32 size);
void func_020c2c48(void *heap, void *block);
void func_020bf06c(MenuWrapper *wrapper, void *arg);
}

namespace Knife {
// Calls into the rest of the manual code (defined in other units, original signatures)
s32 i_preprocManual(void);
void i_initM2dLibrary(void);
void i_postprocManual(void);
void i_deallocate(void *block);
void i_VBlankIntr_OnManual(void);
void i_restoreGfxSettings(void);
s32 runManual(void);
}

#endif
