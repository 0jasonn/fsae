#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::TextLengthAnalyzer::TextLengthAnalyzer() (0x020a16c4)

extern u8 data_0211ede0[]; // TextLengthAnalyzer vtable

// Text length analyzer (Knife::Message::TextLengthAnalyzer). Only the fields the constructor sets are named.
typedef struct KnifeTextLengthAnalyzer {
    void *vtbl;             // 0x00
    s16 maxLength;          // 0x04
    s16 unk_06;
    s16 unk_08;
    s16 unk_0a;             // index into counts
    u16 counts[0x20];       // 0x0c: one count per line
    s16 unk_4c;
} KnifeTextLengthAnalyzer;

// TextLengthAnalyzer::TextLengthAnalyzer() (0x020a16c4): sets the vtable and clears the counts
extern "C" void Knife_Message_TextLengthAnalyzer_TextLengthAnalyzer(void *a);
ARM void Knife_Message_TextLengthAnalyzer_TextLengthAnalyzer(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;
    s32 i;

    self->vtbl = data_0211ede0;
    self->maxLength = 0;
    for (i = 0; i < 0x20; i++) {
        self->counts[i] = 0;
    }
    self->unk_06 = 0;
    self->unk_08 = 0;
    self->unk_0a = 0;
    self->unk_4c = 0;
}
