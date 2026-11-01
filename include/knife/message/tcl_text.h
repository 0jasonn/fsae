#ifndef WIP_F_TCL_TEXT_H
#define WIP_F_TCL_TEXT_H

// Text run state and helpers of the TCL text layer (0x020b68c8 - 0x020b6b3c). Names are provisional.

#include "engine/functions.h"

// Character source: +0x00 data, +0x04 read function (takes the cursor, returns the next code unit).
typedef struct TclTextSource {
    void *data;
    s32 (*readChar)(const u16 **cursor);
} TclTextSource;

// Run state used by TclText_RunLine. Offsets follow the original layout.
typedef struct TclText {
    void *renderer;             // +0x00
    TclTextSource *source;      // +0x04
    s32 advance;                // +0x08
    u32 unk_0c;                 // +0x0c
    const u16 *cursor;          // +0x10
    s32 penX;                   // +0x14
    s32 penY;                   // +0x18
    void *extra;                // +0x1c
    u32 unk_20;                 // +0x20
    u8 pendingAdvance;          // +0x24
} TclText;

extern "C" {
void TclText_RunLine(TclText *self, const u16 *end, void *ctx);
void TclText_DispatchTag(void *ctx, s32 code, TclText *self);
s8 TclText_DrawChar(void *renderer, TclTextSource *source, s32 penX, s32 penY, void *extra, s32 ch);
}

#endif
