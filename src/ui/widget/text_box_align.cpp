#include "engine/functions.h"

// The explicit branches preserve the three return blocks in the original selectors.
s32 TextBox_getHorizontalAlignment(void *self) {
    u8 alignment = ((u8 *)self)[0x3a] & 0xf;

    if (alignment == 0) {
        goto zero;
    }
    if (alignment == 1) {
        goto one;
    }
    if (alignment == 2) {
        goto two;
    }
zero:
    return 0;
one:
    return 1;
two:
    return 2;
}

s32 TextBox_getVerticalAlignment(void *self) {
    u8 alignment = ((u8 *)self)[0x3a] >> 4;

    if (alignment == 0) {
        goto zero;
    }
    if (alignment == 1) {
        goto one;
    }
    if (alignment == 2) {
        goto two;
    }
zero:
    return 0;
one:
    return 1;
two:
    return 2;
}

typedef struct TextBoxAlignmentBits {
    u8 alignment : 2;
    u8 unk_02 : 6;
} TextBoxAlignmentBits;

// Resolves the alignment flag (0x020b7028). A zero flag selects the fallback.
s32 TextBox_getAlignment(void *self) {
    u32 alignment;

    alignment = ((TextBoxAlignmentBits *)((u8 *)self + 0x44))->alignment;
    switch (alignment) {
    case 0:
    default:
        return TextBox_getHorizontalAlignment(self);
    case 1:
        return 0;
    case 2:
        return 1;
    case 3:
        return 2;
    }
}
