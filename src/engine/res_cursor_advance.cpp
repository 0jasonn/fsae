#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/res_cursor_api.h"
#include "engine/g_calls.h"
#include "engine/res_cursor_advance_api.h"

// ResCursor_Advance (0x020c30e8, provisional name): steps the cursor to the next entry of its table. Modes 3 and 4
// flip the toggle at +8 and check the end first. The callback at +0x28 (armed by the flag at +0x20) runs after the
// step, and the cursor is re-initialised for modes 2 and 4. The position is clamped to the table range at the end.
void ResCursor_Advance(u8 *cursor) {
    u8 *table;
    u32 mode;
    u32 limit;
    u32 base;
    u32 current;
    void (*callback)(u32, u32);

    mode = *(u32 *)(cursor + 0x18);
    if (mode == 0) {
        mode = *(u32 *)(*(u32 *)(cursor + 0x1c) + 8);
    }
    switch (mode) {
    case 3:
    case 4:
        *(u32 *)(cursor + 8) = *(u32 *)(cursor + 8) ^ 1;
        table = *(u8 **)(cursor + 0x1c);
        limit = *(u32 *)(table + 0x0c) + ((u32)*(u16 *)(table + 2) << 3) - 8;
        if (*(u32 *)cursor <= limit) {
            if (*(u32 *)(cursor + 0x20) == 1) {
                callback = *(void (**)(u32, u32))(cursor + 0x28);
                callback(*(u32 *)(cursor + 0x24), *(u32 *)(cursor + 0x10));
            }
            mode = *(u32 *)(cursor + 0x18);
            if (mode == 0) {
                mode = *(u32 *)(*(u32 *)(cursor + 0x1c) + 8);
            }
            if (mode != 2 && mode != 4) {
                *(u32 *)(cursor + 0xc) = 0;
            } else {
                ResCursor_InitRange(cursor);
            }
        }
        break;
    default:
        if (*(u32 *)(cursor + 0x20) == 1) {
            callback = *(void (**)(u32, u32))(cursor + 0x28);
            callback(*(u32 *)(cursor + 0x24), *(u32 *)(cursor + 0x10));
        }
        mode = *(u32 *)(cursor + 0x18);
        if (mode == 0) {
            mode = *(u32 *)(*(u32 *)(cursor + 0x1c) + 8);
        }
        if (mode != 2 && mode != 4) {
            *(u32 *)(cursor + 0xc) = 0;
        } else {
            ResCursor_InitRange(cursor);
        }
    }
    table = *(u8 **)(cursor + 0x1c);
    current = *(u32 *)cursor;
    base = *(u32 *)(table + 0x0c);
    limit = base + ((u32)*(u16 *)table << 3) - 8;
    if (current > limit) {
        *(u32 *)cursor = limit;
        return;
    }
    if (current < base) {
        *(u32 *)cursor = base;
    }
}
