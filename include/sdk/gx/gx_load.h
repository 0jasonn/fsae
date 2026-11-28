#ifndef SDK_GX_GX_LOAD_H
#define SDK_GX_GX_LOAD_H

// TwlSDK GX loads into palette RAM, OAM and VRAM (GX_ engine A, GXS_ engine B), by DMA when OamRing_dmaNo holds a
// channel. The extended palettes and textures sit in banks that are not CPU-visible: the Begin call maps the banks to
// the LCDC and records their address, the Load calls copy into them, the End call waits for the copy and maps the banks
// back.
#include "types.h"

// Extended palette load state (data_02129828, 0x1c bytes).
typedef struct GxExtPlttState {
    /* 00 */ u32 subBgBanks;     // banks of the sub BG extended palette
    /* 04 */ u32 mainObjAddr;    // LCDC address of the main OBJ extended palette
    /* 08 */ u32 mainObjBanks;
    /* 0c */ u32 mainBgOffset;   // subtracted from the offset passed to GX_LoadBGExtPltt
    /* 10 */ u32 mainBgAddr;     // LCDC address of the main BG extended palette
    /* 14 */ u32 mainBgBanks;
    /* 18 */ u32 subObjBanks;
} GxExtPlttState;

// Texture load state (data_02129844, 0x20 bytes).
typedef struct GxTexState {
    /* 00 */ u32 unk_00;
    /* 04 */ u32 texAddr;        // LCDC address of the first run of texture banks
    /* 08 */ u32 texPlttAddr;    // LCDC address of the texture palette banks
    /* 0c */ u32 texPlttBanks;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 texBanks;
    /* 18 */ u32 texAddr2;       // second run when the banks are not contiguous, 0 otherwise
    /* 1c */ u32 texSplitSize;   // size of the first run
} GxTexState;

extern GxExtPlttState data_02129828;
extern GxTexState data_02129844;
extern u16 data_020cd1fc[];      // LCDC address >> 12 of the texture palette banks, by bank mask >> 4
extern u16 data_020cd20c[];      // texture bank address tables (GX_BeginLoadTex)
extern u16 data_020cd20e[];
extern u16 data_020cd210[];

extern "C" {
void GX_LoadBGPltt(void *src, s32 offset, s32 size);
void GXS_LoadBGPltt(void *src, s32 offset, s32 size);
void GX_LoadOBJPltt(void *src, s32 offset, s32 size);
void GXS_LoadOBJPltt(void *src, s32 offset, s32 size);
void GX_LoadOAM(const void *src, u32 offset, u32 size);
void GXS_LoadOAM(const void *src, u32 offset, u32 size);
void GX_LoadOBJ(void *src, s32 offset, s32 size);
void GXS_LoadOBJ(void *src, s32 offset, s32 size);

void GX_BeginLoadBGExtPltt(void);
void GX_LoadBGExtPltt(void *src, u32 offset, u32 size);
void GX_EndLoadBGExtPltt(void);
void GX_BeginLoadOBJExtPltt(void);
void GX_LoadOBJExtPltt(void *src, u32 offset, u32 size);
void GX_EndLoadOBJExtPltt(void);
void GXS_BeginLoadBGExtPltt(void);
void GXS_LoadBGExtPltt(void *src, u32 offset, u32 size);
void GXS_EndLoadBGExtPltt(void);
void GXS_BeginLoadOBJExtPltt(void);
void GXS_LoadOBJExtPltt(void *src, u32 offset, u32 size);
void GXS_EndLoadOBJExtPltt(void);

void GX_BeginLoadTex(void); // not decompiled yet
void GX_LoadTex(void *src, u32 offset, u32 size);
void GX_EndLoadTex(void);
void GX_BeginLoadTexPltt(void);
void GX_LoadTexPltt(void *src, u32 offset, u32 size);
void GX_EndLoadTexPltt(void);
}

#endif
