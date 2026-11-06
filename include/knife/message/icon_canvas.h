#ifndef WIP_E_ICON_CANVAS_E_H
#define WIP_E_ICON_CANVAS_E_H

#include "engine/functions.h"
#include "knife/message/knife_canvas.h"

extern "C" {
void *getCanvasBase(s32 *outX, s32 *outY, const NNSG2dCharCanvas *canvas, s32 x, s32 y, s32 w, s32 h);
void CopyNotZero(s32 leftCol, s32 rowOffset, u8 *srcTile, u8 *dstTile, u16 size);
void IconToCanvas(u8 *icon, const NNSG2dCharCanvas *canvas, s32 x, s32 y);
}

#endif
