#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_bits: function Ctrl_setFlagBits1 (0x020bb1bc), provisional name.

// Flag byte at +0x10 of the two child records at +0x70 and +0x74 (bit 1 is the unk_bit1 flag of RectObjF)
typedef struct CtrlBitsChild {
    u8 unk_00[0x10];
    u8 frozen : 1;     // 0x10 bit 0
    u8 unk_bit1 : 1;   // 0x10 bit 1
    u8 rest : 6;       // 0x10 bits 2 to 7
} CtrlBitsChild;

// Controller record: the children at +0x70 and +0x74
typedef struct CtrlBits {
    u8 unk_00[0x70];
    CtrlBitsChild *childA;   // 0x70
    CtrlBitsChild *childB;   // 0x74
} CtrlBits;

// Ctrl_setFlagBits1(self, a, b) (0x020bb1bc, provisional name): bit 1 of the flags of child A is set when a is zero,
// and bit 1 of the flags of child B is set when b is zero (the other bits are kept)
extern "C" void Ctrl_setFlagBits1(CtrlBits *self, s32 a, s32 b);
ARM void Ctrl_setFlagBits1(CtrlBits *self, s32 a, s32 b) {
    CtrlBitsChild *child;

    child = self->childA;
    child->unk_bit1 = (a == 0);
    child = self->childB;
    child->unk_bit1 = (b == 0);
}
