#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/record_cursor.h"

// RecordCursor_Fetch(self) (0x0200c3b4): resolves self->key to a packed record, parses the record header and
// hands the record to the context restore at its entry offset.
void RecordCursor_Fetch(RecordCursor *self) {
    RangeLookup lookup;
    const u8 *src;
    const u8 *next;
    u32 entryOffset;
    u32 valueOne;
    volatile u32 header;
    u32 valueZero;

    RangeLookup_Resolve(self->key, &lookup);
    if (lookup.data == NULL) {
        CallHook_0200c55c();
    }
    PackedRec_Parse(self, &lookup);
    if (self->cached != 0) {
        self->result = 0;
    } else {
        self->result = func_0200bf48(self, &lookup);
        if (self->result == 0) {
            CallHook_0200c55c();
        }
    }

    src = func_0200c17c(self, &lookup, &valueZero);
    header = src[1] | (src[2] << 8) | (src[3] << 16) | (src[4] << 24);
    next = func_0200b24c(src + 5, &valueOne);
    func_0200b1c8(next, &entryOffset);
    func_0200b714(self, &lookup, src);
    Node_Write(self, entryOffset, valueZero);
    Ctx_RestoreRegsJump(self, (u32)&lookup, (void (*)(void))(lookup.base + valueOne));
}
