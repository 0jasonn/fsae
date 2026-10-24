#ifndef WIP_E_SUBTASK_H
#define WIP_E_SUBTASK_H

#include "types.h"

// OAM attribute entry as written by the subtask draw functions (8 bytes, stride 8 in an OAM buffer).
typedef struct GXOamAttr {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 affine;
} GXOamAttr;

// Cell animation object (NNSG2dCellAnimation); only the field read by the OAM link code is named.
typedef struct NNSG2dCellAnimation {
    u8 unk_00[0x30];
    s32 cellRef; // 0x30
} NNSG2dCellAnimation;

typedef enum GXOamShape { GXOamShape_DUMMY } GXOamShape; // values not known yet, passed as raw bits
typedef enum GXOamEffect { GXOamEffect_DUMMY } GXOamEffect; // values not known yet, ORed into attr0/attr1

// Subtask player status block (SUBTASK_PLAYER_WORK, passed to subtask_draw_player_status). Only the used fields are named.
typedef struct SUBTASK_PLAYER_WORK {
    u32 itemFlags;  // 0x00: item and key bits, read as (flags << n) >> 31 or >> 30
    u32 unk_04;
    u32 medalValue; // 0x08
    u32 ruppyValue; // 0x0c
} SUBTASK_PLAYER_WORK;

// Object info block (OBJInfo, passed to subTask_free_objinfo). Only the pointer slots are named.
typedef struct OBJInfo {
    void *block00;
    u32 unk_04;
    void *block08;
    u32 unk_0c;
    void *block10;
    u32 unk_14;
    void *block18;
    u32 unk_1c;
    void *block20;
} OBJInfo;

// Transfer request queued for the VBlank DMA (12 bytes): size, VRAM offset and source buffer.
typedef struct SubtaskSendEntry {
    u32 size;
    u32 offset;
    void *data;
} SubtaskSendEntry;

// Per-index queue of up to three transfer requests (36 bytes per index).
typedef struct SubtaskSendQueue {
    SubtaskSendEntry entry[3];
} SubtaskSendQueue;

// Calls into the rest of the ARM9 image that engine/functions.h does not declare yet (original C++ signatures).
void set_bg_char_8_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_char_16_16(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_char_8_8(u8 *buf, s32 x, s32 y, u16 palette, u16 charSize);
void set_bg_pal_xywh(u8 *buf, s32 x, s32 y, s32 w, s32 h, u16 palette);
void subtask_draw_total_ruppy(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_medal(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_daikaitengiri(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_mastersword(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_kazenosinden(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_tokinoshinden(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_shuurenjo(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_mori_key(s32 a, s32 b, u32 mode, u8 *buf);
void subtask_draw_status_wallpaper(s32 a, s32 b);
extern "C" void DC_FlushRange(const void *base, u32 size);
extern "C" void Knife_Message_RedrawText(s32 index, const s32 *args);
void subTask_free_objinfo(OBJInfo *info);
void subTask_free_slot(s32 index);
void subTask_setupBuffer(u32 mode);
BOOL subtask_draw_oam(s32 x, s32 y, s32 charNo, s32 palette, GXOamShape shape, GXOamAttr *attr);
void subTaskSendStop(void);
void Knife_Message_CleanupTextRenderer(void);

// Not named yet (dsd names, plain C linkage).
extern "C" void func_0209bee4(void);
extern "C" s32 func_020c40a4(void *oam, s32 a1, s32 a2, s32 a3, s32 *pos, s32 a5, s32 a6);
extern "C" void func_020c4064(void *anim, s32 c);

#endif
