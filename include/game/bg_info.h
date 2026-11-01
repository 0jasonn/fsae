#ifndef GAME_BG_INFO_H
#define GAME_BG_INFO_H

#include "types.h"

// Declarations used by the implementer E files in src/wip/E (not yet in engine/functions.h).

// Background layer block (BGInfo): palette, character and screen buffers, each with its resource chunk
typedef struct BGInfo {
    void *palBuf;    // 0x00: palette data (initBgWithLoadVram)
    void *palChunk;  // 0x04: ResChunkTTLP
    void *charBuf;   // 0x08: character data (initBgCharWithLoadVram)
    void *charChunk; // 0x0c: ResChunkRACH
    void *scrBuf;    // 0x10: screen data (initScrWithLoad)
    void *scrChunk;  // 0x14: ResChunkTTLP
} BGInfo;

// Chunk opened by ResChunk_OpenRACH / ResChunk_OpenRACH2: size at 0x10, data at 0x14
typedef struct ResChunkRACH {
    u8 unk_00[0x10];
    u32 size;
    void *data;
} ResChunkRACH;

// Chunk opened by ResChunk_OpenTTLP / ResChunk_GetNRCS: size at 0x08, data at 0x0c
typedef struct ResChunkTTLP {
    u8 unk_00[0x08];
    u32 size;
    void *data;
} ResChunkTTLP;

// Object block (OBJInfo) of the object loaders: buffer and chunk pairs at 0x00, 0x08, 0x10, 0x18, 0x20
typedef struct ObjLoadBlock {
    void *buf0;   // 0x00: TTLP chunk at 0x04 (initObjWithLoadVram, palette)
    void *chunk0; // 0x04
    void *buf1;   // 0x08: RACH chunk at 0x0c (initObjWithLoadVram, character)
    void *chunk1; // 0x0c
} ObjLoadBlock;

extern "C" void DC_FlushRange(void *base, u32 size);            // TwlSDK, 0x020184b8
extern "C" void MI_CpuCopy8(const void *src, void *dst, u32 size);    // TwlSDK, 0x02015d0c
void subTaskSendScr(s16 index, void *data, u32 offset, u32 size); // 0x0209da7c, C++ linkage

extern "C" void subtask_dialogDelete(void);                     // 0x020ac308
extern "C" u32 getResourceSize(u32 index, u8 kind);             // 0x020ac40c
extern "C" void *getResourceData(u32 index, u8 kind);           // 0x020ac3d0
extern "C" s32 ResChunk_GetNRCS(void *entry, void *owner);      // 0x020c3028
extern "C" void ResChunk_OpenRACH2(void *entry, void *chunk);  // 0x020c2f90
extern "C" void ResChunk_OpenRACH(void *entry, void *chunk);   // 0x020c2f44
extern "C" void ResChunk_OpenTTLP(void *entry, void *chunk);   // 0x020c2fdc
extern "C" s32 ResChunk_OpenKBEC(void *entry, void *owner);    // 0x020c2e44
extern "C" s32 Menu_ForwardC2cb4(void *entry, void *owner);    // 0x020c2cb4

extern "C" void subTaskSendBgChar(s16 index, void *data, u32 offset, u32 size); // 0x0209daa0 (parked)
extern "C" void subTaskSendBgPlt(void *data, u32 offset, u32 size);  // 0x0209db38 (parked)
extern "C" void subTaskSendObjChar(void *data, u32 offset, u32 size); // 0x0209daf0 (parked)
extern "C" void subTaskSendObjPlt(void *data, u32 offset, u32 size); // 0x0209db80 (parked)
void func_0208e188(void *block);                                // 0x0208e188, C++ linkage
extern "C" void initBgCharWithLoadVram(BGInfo *bg, u32 layer, s32 index, u32 offset, u32 freeFlag);

extern "C" s32 Knife_Message_i_IsExText(u32 textId);             // 0x020a3134
extern void *data_02124970;   // pointer to the message system block (+0x450: 0x34-byte records, first word = text id)
extern u8 data_0217d56c[];    // redraw state (bss): +0x04 text object, +0x08 language, +0x0c render targets (0x68 each)
extern u8 data_0217d594[];    // text renderer of the redraw (bss), +0x50 four arguments

extern u8 data_0217e604[]; // dialog clear block (bss), see subtask_dialog.cpp
extern u8 data_02117e60[]; // word written by subtask_dialogDelete

#endif
