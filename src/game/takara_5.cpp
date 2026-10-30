#include "engine/functions.h"
#include "global.h"
#include "enemy/loader_decls.h"

typedef struct TakaraEntry {
    u16 id;
    u8 handlerIndex;
    u8 flags;
} TakaraEntry;

extern TakaraEntry data_02134c30[32];
extern "C" void takara_set(u8 *records, FRAME_INFO_ *frame, u8 kind);

ARM void takara_set(u8 *records, FRAME_INFO_ *frame, u8 kind) {
    TakaraEntry *entry;
    u8 i;
    u8 *frameOffsets;
    s32 kindBits;
    u16 x;
    u16 y;

    frameOffsets = (u8 *)frame + (kind - 1) * 2;
    kindBits = (kind << 5) & 0xe0;
    entry = data_02134c30;
    for (i = 0; i < 0x20 && records[0] != 0xff; i++, entry++) {
        if (entry->id == 0xffff) {
            x = records[0];
            y = records[1];
            if (kind != 0) {
                x = (u16)(x + frameOffsets[4]);
                y = (u16)(y + frameOffsets[5]);
            }
            entry->id = (u16)(x | (y << 6));
            entry->handlerIndex = (records[2] & 0x1f) | kindBits;
            entry->flags = records[3];
            records += 4;
        }
    }
}
