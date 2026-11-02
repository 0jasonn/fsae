#include "knife/message/icon_canvas_e.h"

// IconToCanvas (0x020a0a18), plain name from the debug build: draws a 16x16 icon (four 8x8 tiles, 0x20 bytes each, in the
// order top left, top right, bottom left, bottom right) into the canvas at (x, y), merging only the nonzero pixels
void IconToCanvas(u8 *icon, const NNSG2dCharCanvas *canvas, s32 x, s32 y) {
    s32 outX;
    s32 outY;
    u8 *base;

    base = (u8 *)getCanvasBase(&outX, &outY, canvas, x, y, 8, 0x10);
    if (base != NULL) {
        CopyNotZero(outX, outY, icon, base, 0x20);
    }
    base = (u8 *)getCanvasBase(&outX, &outY, canvas, x + 8, y, 8, 0x10);
    if (base != NULL) {
        CopyNotZero(outX, outY, icon + 0x40, base, 0x20);
    }
    base = (u8 *)getCanvasBase(&outX, &outY, canvas, x, y + 8, 8, 0x10);
    if (base != NULL) {
        CopyNotZero(outX, outY, icon + 0x20, base, 0x20);
    }
    base = (u8 *)getCanvasBase(&outX, &outY, canvas, x + 8, y + 8, 8, 0x10);
    if (base != NULL) {
        CopyNotZero(outX, outY, icon + 0x60, base, 0x20);
    }
}
