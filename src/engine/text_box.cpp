#include "engine/functions.h"
#include "global.h"

extern "C" void func_020c6c30(u8 *obj, u8 *self);
extern "C" void TextStream_ReadU16(void);
extern "C" u32 func_020c4dc8(u8 *entry, u32 value);
extern "C" u32 data_020df104[];

// TextBox_SetKindHandler (provisional name): TextBox_Init-style call on the record, then the handler at data_020df104 indexed by the kind byte at +7 of the info record at +0.
extern "C" void TextBox_SetKindHandler(u8 *self, u8 *arg);
ARM void TextBox_SetKindHandler(u8 *self, u8 *arg) {
    func_020c6c30(arg, self);
    *(u32 *)(self + 4) = data_020df104[*(u8 *)(*(u8 **)self + 7)];
}

// TextBox_SetDefaultHandler (provisional name): the same record call, then the default handler TextStream_ReadU16 at +4.
extern "C" void TextBox_SetDefaultHandler(u8 *self, u8 *arg);
ARM void TextBox_SetDefaultHandler(u8 *self, u8 *arg) {
    func_020c6c30(arg, self);
    *(u32 *)(self + 4) = (u32)TextStream_ReadU16;
}

// TextBox_FindRange (provisional name): walks the list at +0x10 of the head record for the entry whose inclusive halfword range
// holds value and returns func_020c4dc8 on it; 0xffff when none matches.
extern "C" u32 TextBox_FindRange(u8 *self, u32 value);
ARM u32 TextBox_FindRange(u8 *self, u32 value) {
    u8 *entry;

    entry = *(u8 **)(*(u8 **)self + 0x10);
    while (entry != 0) {
        if (*(u16 *)entry <= value && value <= *(u16 *)(entry + 2)) {
            return func_020c4dc8(entry, value);
        }
        entry = *(u8 **)(entry + 8);
    }
    return 0xffff;
}

// TextBox_FindRangeEntry (provisional name): the record of the list at +0xc of the head whose inclusive range holds value,
// returned as entry + 8 + (value - low) * 3; when none matches the address of the head + 4.
extern "C" u8 *TextBox_FindRangeEntry(u8 *self, u32 value);
ARM u8 *TextBox_FindRangeEntry(u8 *self, u32 value) {
    u8 *entry;
    u8 *head;

    head = *(u8 **)self;
    entry = *(u8 **)(head + 0xc);
    while (entry != 0) {
        if (*(u16 *)entry <= value && value <= *(u16 *)(entry + 2)) {
            return entry + 8 + (value - *(u16 *)entry) * 3;
        }
        entry = *(u8 **)(entry + 4);
    }
    return head + 4;
}

// TextBox_MeasureSegment (provisional name): reads characters with the reader at +4 until a newline (0xa) or the end. Each
// character adds base plus the signed width from its range entry. outState receives the reader state on a newline and 0 at the
// end. The result is the total minus one base, or the total when it is not positive.
extern "C" s32 TextBox_MeasureSegment(u8 *self, s32 base, u32 state, u32 *outState);
ARM s32 TextBox_MeasureSegment(u8 *self, s32 base, u32 state, u32 *outState) {
    u32 localState;
    s32 total;
    u32 (*reader)(u32 *);
    u32 c;
    u32 index;
    u8 *entry;

    reader = (u32 (*)(u32 *))*(u32 **)(self + 4);
    localState = state;
    total = 0;
    c = reader(&localState);
    if (c != 0) {
        do {
            if (c == 0xa) {
                break;
            }
            index = TextBox_FindRange(self, c);
            if (index == 0xffff) {
                index = *(u16 *)(*(u8 **)self + 2);
            }
            entry = TextBox_FindRangeEntry(self, index);
            total += base + *(s8 *)(entry + 2);
            c = reader(&localState);
        } while (c != 0);
    }
    if (outState != 0) {
        *outState = (c == 0xa) ? localState : 0;
    }
    if (total > 0) {
        total -= base;
    }
    return total;
}

