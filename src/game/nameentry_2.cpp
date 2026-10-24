#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   nameEntryUIView::IsDakuon(unsigned short) (0x020afa1c), nameEntryUIView::IsHanDakuon(unsigned short) (0x020afa4c)

extern "C" {
s32 nameEntryUIView_IsDakuon(void *self, u16 ch);
s32 nameEntryUIView_IsHanDakuon(void *self, u16 ch);
}

extern const u16 data_020debc8[];
extern const u16 data_020deb90[];

// nameEntryUIView::IsDakuon (0x020afa1c): TRUE for the voiced kana 0x304c and for the characters in data_020debc8
ARM s32 nameEntryUIView_IsDakuon(void *self, u16 ch) {
    const u16 *p;
    u16 cur;

    p = data_020debc8;
    cur = 0x304c;
    while (1) {
        if (cur == ch) {
            return 1;
        }
        cur = *(++p);
        if (cur == 0) {
            return 0;
        }
    }
}

// nameEntryUIView::IsHanDakuon (0x020afa4c): TRUE for the semi-voiced kana 0x3071 and for the characters in data_020deb90
ARM s32 nameEntryUIView_IsHanDakuon(void *self, u16 ch) {
    const u16 *p;
    u16 cur;

    p = data_020deb90;
    cur = 0x3071;
    while (1) {
        if (cur == ch) {
            return 1;
        }
        cur = *(++p);
        if (cur == 0) {
            return 0;
        }
    }
}
