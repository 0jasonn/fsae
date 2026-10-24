#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   nameEntryUIView::jpMojiCheck(unsigned short) (0x020af978)
// nameEntryUIView::loadScreen (0x020af8c8) is parked in scratch/agentF/nonmatching/nameEntryUIView_loadScreen.cpp

extern "C" {
s32 nameEntryUIView_IsDakuonConvertable(void *self, u16 ch);
s32 nameEntryUIView_IsHandakuonConvertable(void *self, u16 ch);
u16 nameEntryUIView_DakuonConvert(void *self, u16 ch);
u16 nameEntryUIView_HandakuonConvert(void *self, u16 ch);
}

// nameEntryUIView::jpMojiCheck (0x020af978): when the character is the voiced (0x309b) or semi-voiced (0x309c) sound
// mark, combines it with the last character of the name; other characters are returned unchanged
ARM u16 nameEntryUIView_jpMojiCheck(void *self, u16 ch) {
    u8 *obj;
    u16 last;
    u16 result;

    obj = (u8 *)self;
    if (ch != 0x309b && ch != 0x309c) {
        return ch;
    }
    if ((s8)obj[0x42] == 0) {
        return 0;
    }
    last = *(u16 *)(obj + 0x34 + ((s8)obj[0x42] - 1) * 2);
    if (ch == 0x309c) {
        if (nameEntryUIView_IsHandakuonConvertable(self, last) == 0) {
            return 0;
        }
        result = nameEntryUIView_HandakuonConvert(self, last);
    } else {
        if (nameEntryUIView_IsDakuonConvertable(self, last) == 0) {
            return 0;
        }
        result = nameEntryUIView_DakuonConvert(self, last);
    }
    obj[0x42] = (u8)((s8)obj[0x42] - 1);
    return result;
}
