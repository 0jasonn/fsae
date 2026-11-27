#include "ui/widget/tile_file_header.h"

// Check the four-byte file tag and the following byte-order marker.
BOOL func_020b7378(void *entry, u32 tag) {
    s8 *bytes;
    s32 entryTag;

    bytes = (s8 *)entry;
    entryTag = ((s32)bytes[0] << 24) | ((s32)bytes[1] << 16) | ((s32)bytes[2] << 8) | (s32)bytes[3];
    return tag == (u32)entryTag && *(u16 *)(bytes + 4) == 0xfeff;
}
