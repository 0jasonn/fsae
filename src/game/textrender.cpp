#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   TextRender::setup() (0x020a11fc)

// Callback object of the text renderer (at +0x18): the clear function is at +4
typedef struct KnifeTextClearHook {
    u8 unk_00[4];
    void (*clear)(void *canvas, s32 mode);
} KnifeTextClearHook;

// Text render state (Knife::Message::TextRender). Only the fields the functions matched so far use are named.
typedef struct KnifeTextRender {
    u8 unk_00[4];
    void *canvas;        // 0x04: the canvas the clear function works on
    s32 widthCells;      // 0x08
    u8 unk_0c[0x18 - 0x0c];
    KnifeTextClearHook *hook; // 0x18
    u8 unk_1c[0x30 - 0x1c];
    s16 startX;          // 0x30
    s16 unk_32;          // 0x32: set from unk_77
    s16 centerIndex;     // 0x34
    u16 centering[0x10]; // 0x36: centering values, set by setCenteringParam
    u8 unk_56[0x76 - 0x56];
    s8 unk_76;           // 0x76: step added to unk_32 at each new line
    s8 unk_77;
    u8 unk_78;
    u8 selectCount;      // 0x79: entries of selectTable in use
    u8 selectTable[8];   // 0x7a: x and y of each select entry, in cells
    u8 unk_82;
    u8 flag83;           // 0x83: set by setField83
    u8 flag84;           // 0x84
} KnifeTextRender;

// TextRender::setup() (0x020a11fc): resets the centre index and computes the start x from the centring value
extern "C" void Knife_Message_TextRender_setup(void *a);
ARM void Knife_Message_TextRender_setup(void *a) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->centerIndex = 0;
    self->flag84 = 0;
    if (self->flag83 == 0) {
        self->startX = 0;
    } else {
        self->startX = ((self->widthCells << 3) - self->centering[self->centerIndex]) / 2;
    }
    self->unk_32 = self->unk_77;
}
