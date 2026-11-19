#include "engine/functions.h"
#include "ui/message.h"
#include "ui/msgwin.h"
#include "global.h"
#include "types.h"

// MessageFrameClear (0x0204ae7c): fills the border of a width x height message frame (top and bottom rows, then the
// left and right columns) with one tile attribute.
void MessageFrameClear(u16 *tiles, s16 width, s16 height, u16 attr) {
    s32 rowOffset;
    u16 *bottom;
    u16 *top;
    u16 *bottomCursor;

    rowOffset = height * 32;
    bottom = tiles + 32 + rowOffset;
    tiles[0] = attr;
    tiles[rowOffset + 32] = attr;
    top = tiles + 1;
    bottomCursor = bottom + 1;
    if (width > 0) {
        width -= 2;
        tiles[1] = attr;
        bottom[1] = attr;
        top = tiles + 2;
        bottomCursor = bottom + 2;
        while (width-- > 0) {
            *top++ = attr;
            *bottomCursor++ = attr;
        }
        *top++ = attr;
        *bottomCursor++ = attr;
    }
    *top = attr;
    *bottomCursor = attr;
    if (height <= 0) {
        return;
    }
    height -= 2;
    tiles[32] = attr;
    top[32] = attr;
    tiles += 64;
    top += 64;
    while (height-- > 0) {
        *top = attr;
        top += 32;
        *tiles = attr;
        tiles += 32;
    }
    *tiles = attr;
    *top = attr;
}
