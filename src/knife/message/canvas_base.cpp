#include "knife/message/icon_canvas.h"

// Return the first character cell touched by the clipped icon rectangle.
// Negative pixel offsets are preserved for CopyNotZero to clip within that cell.
extern "C" void *getCanvasBase(int *outX, int *outY, const NNSG2dCharCanvas *canvas, int x, int y, int w, int h) {
    const int charBytes = Knife_CharBytes(canvas);
    int width = w & 0xff;
    int height = h & 0xff;
    u32 canvasWidth = canvas->width;
    u32 canvasHeight = canvas->height;
    u8 *bits = (u8 *)canvas->pBits;

    if (width == 0) {
        return NULL;
    }

    if (x + width < 0 || y + height < 0) {
        return NULL;
    }

    int right = x + width;
    int bottom = y + height;
    width = 0;
    if (x > 0) {
        width = (u32)x >> 3;
    }
    height = 0;
    if (y > 0) {
        height = (u32)y >> 3;
    }
    right = (u32)(right + 7) >> 3;
    if (canvasWidth <= (u32)right) {
        right = canvasWidth;
    }
    bottom = (u32)(bottom + 7) >> 3;
    if (canvasHeight <= (u32)bottom) {
        bottom = canvasHeight;
    }

    canvasHeight = bottom - height;
    canvasWidth = right - width;
    if ((s32)canvasWidth < 0 || (s32)canvasHeight < 0) {
        return NULL;
    }

    u8 *base = bits + charBytes * (canvas->rowStride * height + width);
    *outX = x >= 0 ? x & 7 : x;
    *outY = y >= 0 ? y & 7 : y;
    return base;
}
