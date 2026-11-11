#include "engine/functions.h"
#include "knife/message/wstr_format.h"
#include "ui/widget/menu.h"
#include "ui/widget/ctrl_draw.h"

// Row object of the menu list: the text pointer of the label sits at +0x20
typedef struct CtrlLabelRow {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ CtrlSourcePool *pool;
    /* 20 */ const u16 *text;
} CtrlLabelRow;

extern const u16 data_02126f94[]; // L"%u" format string in .data

// Ctrl_setRowLabel (0x020bbbfc): sets the label of a row of the menu list: the number (unless it is 0xffff) is drawn in a
// 0x12 wide cell and the text of the row behind it
void Ctrl_setRowLabel(void *obj, s32 textPtr, s32 number) {
    CtrlLabelRow *self = (CtrlLabelRow *)obj;
    TclCanvas canvas;
    s16 tilePos[2];
    s16 tileSize[2];
    u16 digits[10];
    s32 x;
    const u16 *text;

    self->text = (const u16 *)textPtr;
    x = 0;
    tileSize[0] = 0x20;
    tileSize[1] = 2;
    tilePos[0] = x;
    tilePos[1] = x;
    func_020bbdd8(&canvas, 1, tilePos, tileSize, self->pool->source, 0);
    if (number != 0xffff) {
        Wstr_Snprintf(digits, 10, data_02126f94, number + 1);
        TclText_DrawBlockAligned(&canvas.drawer, 0, 0, 0x12, 0x10, 1, 0x480, digits, StepOf(&canvas));
        x = 0x16;
    }
    text = self->text;
    TclText_DrawBlock(&canvas.drawer, x, 8, 1, 0x20a, text, StepOf(&canvas));
}
