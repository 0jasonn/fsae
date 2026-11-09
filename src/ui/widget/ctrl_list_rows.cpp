#include "engine/functions.h"
#include "knife/message/wstr_format.h"
#include "ui/widget/ctrl_draw_e.h"
#include "ui/widget/rect_slot3_api.h"

#define SOURCE(slider) (((CtrlSourcePool *)*(void **)((u8 *)(slider) + 0x1c))->source)

extern const u16 data_02126ef4[]; // L"%u" format string in .data

// Ctrl_drawListRow (0x020b98f8): shows one entry in a row of a list pane: draws the entry number and the entry text into two
// canvases laid out by the row, sets the flag of the row, selects it and records which item the row holds
void Ctrl_drawListRow(CtrlPanel *slider, const CtrlItemEntry &entry, s32 index) {
    s32 slot;
    s16 y;
    const u16 *text;
    s16 numberPos[2];
    s16 numberSize[2];
    s16 textPos[2];
    TclCanvas numberCanvas;
    s16 textSize[2];
    u16 number[10];
    TclCanvas textCanvas;

    slot = index % (u16)(slider->rowCount + 1);
    y = slot * 3;
    numberSize[0] = 4;
    numberSize[1] = 4;
    numberPos[0] = 0;
    numberPos[1] = y;
    func_020bbdd8(&numberCanvas, 0, numberPos, numberSize, SOURCE(slider), 0);
    Wstr_Snprintf(number, 10, data_02126ef4, index + 1);
    TclText_DrawBlockAligned(&numberCanvas.drawer, 0, 0, 0x20, 0x20, 1, 0x480, number, StepOf(&numberCanvas));
    textSize[0] = 0x14;
    textSize[1] = 4;
    textPos[0] = 0x10;
    textPos[1] = y;
    func_020bbdd8(&textCanvas, 0, textPos, textSize, SOURCE(slider), 0);
    text = (const u16 *)entry.obj;
    TclText_DrawBlock(&textCanvas.drawer, 0, 0x10, 1, 0x20a, text, StepOf(&textCanvas));
    RectSlot2_setFlag(slider->rows[slot], entry.flag);
    slider->rows[slot]->setSelected(1);
    slider->rowItem[slot] = index;
}

// Ctrl_drawListRows (0x020b9b58): shows count entries, starting at item number start, in the rows of a list pane: every row
// that has an entry is drawn like Ctrl_drawListRow (without the number), the rows behind the last entry are deselected
void Ctrl_drawListRows(CtrlPanel *slider, const CtrlItemEntry *entries, s32 count, s16 start) {
    TclCanvas canvas;
    s16 textPos[2];
    s16 textSize[2];
    s32 i;
    s32 slot;
    s16 index;
    const u16 *text;

    // the ROM reads the row count again at each use: the casts keep mwcc from sharing the loads
    if (*(u16 *)((u8 *)slider + 0x24) <= (u32)count) {
        count = *(u16 *)((u8 *)slider + 0x24);
    }
    for (i = 0; i < (u16)(slider->rowCount + 1); i++) {
        index = start + i;
        slot = index % (u16)(*(u16 *)((u8 *)slider + 0x24) + 1);
        if (i < count) {
            textSize[0] = 0x18;
            textSize[1] = 4;
            textPos[0] = 0;
            textPos[1] = slot * 3 + 0x12;
            func_020bbdd8(&canvas, 0, textPos, textSize, SOURCE(slider), 0);
            text = (const u16 *)entries[i].obj;
            TclText_DrawBlock(&canvas.drawer, 0, 0x10, 1, 0x20a, text, StepOf(&canvas));
            RectSlot2_setFlag(slider->rows[slot], entries[i].flag);
            slider->rows[slot]->setSelected(1);
            slider->rowItem[slot] = index;
        } else {
            slider->rows[slot]->setSelected(0);
        }
    }
}
