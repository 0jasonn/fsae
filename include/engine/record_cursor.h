#ifndef WIP_A_RECORD_CURSOR_H
#define WIP_A_RECORD_CURSOR_H

#include "types.h"
#include "engine/range_lookup.h"

// Cursor over a packed record, used by RecordCursor_Fetch (0x0200c3b4). Only the fields that code names are typed.
typedef struct RecordCursor {
    u32 cached;        // 0x00: nonzero when the record is already loaded
    u8 unk_04[8];
    u32 result;        // 0x0c: value returned by the table lookup, 0 when none
    u32 key;           // 0x10: key for the range table
} RecordCursor;

extern "C" {
void RecordCursor_Fetch(RecordCursor *self);
void PackedRec_Parse(void *self, void *src);
void Node_Write(void *self, u32 offset, u32 extra);
u32 func_0200bf48(RecordCursor *self, RangeLookup *lookup);
const u8 *func_0200c17c(RecordCursor *self, RangeLookup *lookup, u32 *out);
void func_0200b1c8(const u8 *src, u32 *out);
void func_0200b714(RecordCursor *self, RangeLookup *lookup, const u8 *src);
}

void CallHook_0200c55c(void);
void Ctx_RestoreRegsJump(void *context, unsigned long unused, void (*target)(void));

#endif
