#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/res_chunk_b_api.h"
#include "engine/res_chunk_c_api.h"
#include "engine/res_table_reloc_api.h"

// ResTable_RelocateKbec (0x020c2ea8, provisional name): turns the offsets of a KBEC body into pointers. Entries get
// the table end added at +4, the sub-table at +0x0c and the trailing table at +0x14 are relocated, and the trailing
// table is looked up through ResTable_LookupFrom8. Called by ResChunk_OpenKBEC.
void ResTable_RelocateKbec(u8 *body) {
    u8 *end;
    u8 *entry;
    u8 *sub;
    u8 *tailPtr;
    u32 tail;
    u16 i;

    *(u32 *)(body + 4) += (u32)body;
    end = ResTable_GetEnd(body);
    for (i = 0; i < *(u16 *)body; i++) {
        entry = ResTable_GetEntryAt(body, i);
        *(u32 *)(entry + 4) += (u32)end;
    }
    if (*(u32 *)(body + 0x0c) != 0) {
        sub = (u8 *)(*(u32 *)(body + 0x0c) + (u32)body);
        *(u8 **)(body + 0x0c) = sub;
        *(u32 *)(sub + 4) += (u32)sub;
        *(u8 **)(body + 0x0c) = sub;
    }
    tail = *(u32 *)(body + 0x14);
    if (tail == 0) {
        return;
    }
    tailPtr = (u8 *)(tail + (u32)body);
    *(u8 **)(body + 0x14) = tailPtr;
    ResTable_LookupFrom8(tailPtr);
}
