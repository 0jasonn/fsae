#ifndef WIP_E_TCL_LAYOUT_E_H
#define WIP_E_TCL_LAYOUT_E_H

#include "types.h"
#include "knife/message/tcl_text.h"

// Layout flags of the TCL text layer (TclText_DrawBlock / DrawBlockAligned / DrawLines)
#define TCL_ALIGN_BOX_V_CENTER 0x80
#define TCL_ALIGN_BOX_V_END    0x100
#define TCL_ALIGN_H_CENTER     0x10
#define TCL_ALIGN_H_END        0x20
#define TCL_ALIGN_V_CENTER     0x02
#define TCL_ALIGN_V_END        0x04
#define TCL_ALIGN_LINE_END     0x800
#define TCL_ALIGN_LINE_CENTER  0x400

// Drawer of the TCL layout layer: the character source and the spacing added between characters and lines.
typedef struct TclLayoutDrawer {
    void *renderer;            // 0x00
    TclTextSource *source;     // 0x04
    s32 charSpacing;           // 0x08
    s32 lineSpacing;           // 0x0c
} TclLayoutDrawer;

// Direction in which text advances (-1, 0 or 1 per axis); passed by value
typedef struct TclLayoutStep {
    s8 dx;
    s8 dy;
} TclLayoutStep;

typedef struct TclTextSize {
    s32 width;
    s32 height;
} TclTextSize;

extern "C" {
s32 TextBox_MeasureSegment(TclTextSource *source, s32 charSpacing, const u16 *text, const u16 **next);
TclTextSize TextBox_MeasureBlock(TclTextSource *source, s32 charSpacing, s32 lineSpacing, const u16 *text);
s32 TextBox_MeasureHeight(TclTextSource *source, s32 lineSpacing, const u16 *text);
void func_020c6828(TclLayoutDrawer *self, s32 x, s32 y, s32 palette, const u16 *text, const u16 **next, TclLayoutStep step);
void TclText_DrawLines(TclLayoutDrawer *self, s32 x, s32 y, s32 width, s32 palette, u32 flags, const u16 *text, TclLayoutStep step);
void TclText_DrawBlock(TclLayoutDrawer *self, s32 x, s32 y, s32 palette, u32 flags, const u16 *text, TclLayoutStep step);
void TclText_DrawBlockAligned(TclLayoutDrawer *self, s32 x, s32 y, s32 width, s32 height, s32 palette, u32 flags, const u16 *text, TclLayoutStep step);
}

#endif
