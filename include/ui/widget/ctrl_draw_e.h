#ifndef WIP_E_CTRL_DRAW_E_H
#define WIP_E_CTRL_DRAW_E_H

#include "engine/functions.h"
#include "knife/message/tcl_layout_e.h"
#include "ui/ctrl_scroll.h"

// Text canvas that the Ctrl rows draw into: a record (made by Record_InitShape) with a vtable at +0x14 and the text drawer
// embedded at +0x18; the drawer's renderer points back at the canvas.
typedef struct TclCanvas {
    /* 00 */ u8 unk_00[0x14];
    /* 14 */ void *vtable;
    /* 18 */ TclLayoutDrawer drawer;
} TclCanvas;

// Font data behind TclTextSource.data: the info record at +8 tells which way the text advances
typedef struct TclFontInfo {
    u8 unk_00[7];
    u8 direction;   // 0x07: 0 and 7 left to right, 1 and 2 downwards, 3 and 4 right to left, 5 and 6 upwards
} TclFontInfo;

typedef struct TclFontRef {
    u8 unk_00[8];
    TclFontInfo *info;
} TclFontRef;

// Pool at +0x1c of the Ctrl panels: the character source of the rows is at +4
typedef struct CtrlSourcePool {
    void *unk_00;
    TclTextSource *source;
} CtrlSourcePool;

extern "C" {
// Builds a canvas over a tile map area in main (second = 0) or sub VRAM: tile position, tile size, character source
// and character spacing
void Ctrl_drawListRows(CtrlPanel *slider, const CtrlItemEntry *entries, s32 count, s16 start);
TclCanvas *func_020bbdd8(TclCanvas *self, s32 second, const s16 *tilePos, const s16 *tileSize, TclTextSource *source, s16 spacing);
}

// Step of the text for the writing direction of the font (0 and 7: right, 1 and 2: down, 3 and 4: left, 5 and 6: up)
static inline TclLayoutStep StepOf(const TclCanvas *canvas) {
    TclLayoutStep step = {0, 0};
    switch (((TclFontRef *)canvas->drawer.source->data)->info->direction) {
    case 0:
    case 7:
        step.dx = 1;
        break;
    case 1:
    case 2:
        step.dy = 1;
        break;
    case 3:
    case 4:
        step.dx = -1;
        break;
    case 5:
    case 6:
        step.dy = -1;
        break;
    }
    return step;
}

#endif
