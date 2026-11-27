#ifndef KNIFE_MESSAGE_ICON_CANVAS_H
#define KNIFE_MESSAGE_ICON_CANVAS_H

#include "engine/functions.h"
#include "knife/message/knife_canvas.h"

extern "C" {
void *getCanvasBase(int *outX, int *outY, const NNSG2dCharCanvas *canvas, int x, int y, int w, int h);
void CopyNotZero(int leftCol, int rowOffset, u8 *srcTile, u8 *dstTile, u16 size);
void IconToCanvas(u8 *icon, const NNSG2dCharCanvas *canvas, int x, int y);
}

#endif
