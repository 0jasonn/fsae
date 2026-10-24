#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   nameEntryUIView::IsDakuonConvertable(unsigned short) (0x020afa7c), nameEntryUIView::IsHandakuonConvertable(unsigned short)
//   (0x020afb4c), nameEntryUIView::DakuonConvert(unsigned short) (0x020afb94), nameEntryUIView::HandakuonConvert(unsigned short)
//   (0x020afc0c), nameEntryUIView_noop nameEntryUIView_noop (0x020afc5c)
// func_020afc60 (nameEntryUIView_getTextThunk) is parked in scratch/agentF/nonmatching/func_020afc60.cpp

extern "C" {
s32 nameEntryUIView_IsDakuon(void *self, u16 ch);
s32 nameEntryUIView_IsHanDakuon(void *self, u16 ch);
s32 nameEntryUIView_IsDakuonConvertable(void *self, u16 ch);
s32 nameEntryUIView_IsHandakuonConvertable(void *self, u16 ch);
u16 nameEntryUIView_DakuonConvert(void *self, u16 ch);
u16 nameEntryUIView_HandakuonConvert(void *self, u16 ch);
}

// nameEntryUIView::IsDakuonConvertable (0x020afa7c): TRUE for the kana that have a voiced form (ka to ho rows, the
// katakana equivalents, and 0x30a6 / 0x30f4)
ARM s32 nameEntryUIView_IsDakuonConvertable(void *self, u16 ch) {
    if ((ch >= 0x304b && ch <= 0x3062) || (ch >= 0x30ab && ch <= 0x30c2) || (ch >= 0x3064 && ch <= 0x3069) ||
        (ch >= 0x30c4 && ch <= 0x30c9) || (ch >= 0x306f && ch <= 0x307d) || (ch >= 0x30cf && ch <= 0x30dd) ||
        ch == 0x30a6 || ch == 0x30f4) {
        return 1;
    }
    return 0;
}

// nameEntryUIView::IsHandakuonConvertable (0x020afb4c): TRUE for the kana of the ha row and the range 0x306f to 0x307d
ARM s32 nameEntryUIView_IsHandakuonConvertable(void *self, u16 ch) {
    if ((ch >= 0x306f && ch <= 0x307d) || (ch >= 0x30cf && ch <= 0x30dd)) {
        return 1;
    }
    return 0;
}

// nameEntryUIView::DakuonConvert (0x020afb94): converts a kana to the voiced or the unvoiced form, by the dakuon tables
ARM u16 nameEntryUIView_DakuonConvert(void *self, u16 ch) {
    if (nameEntryUIView_IsDakuon(self, ch) != 0) {
        if (ch == 0x30f4) {
            return 0x30f4 - 0x4e;
        }
        return ch - 1;
    }
    if (nameEntryUIView_IsHanDakuon(self, ch) != 0) {
        return ch - 1;
    }
    if (ch == 0x30a6) {
        return 0x30a6 + 0x4e;
    }
    return ch + 1;
}

// nameEntryUIView::HandakuonConvert (0x020afc0c): converts a kana to the semi-voiced or the unvoiced form
ARM u16 nameEntryUIView_HandakuonConvert(void *self, u16 ch) {
    if (nameEntryUIView_IsDakuon(self, ch) != 0) {
        return ch + 1;
    }
    if (nameEntryUIView_IsHanDakuon(self, ch) != 0) {
        return ch - 2;
    }
    return ch + 2;
}

// nameEntryUIView_noop (0x020afc5c): an empty function (the entry of a virtual slot)
ARM void nameEntryUIView_noop(void *self) {
}
