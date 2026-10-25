#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   TextLengthAnalyzer::onTerminate() (0x020a1704)

// Text length analyzer (Knife::Message::TextLengthAnalyzer), same layout as in textlength.cpp
typedef struct KnifeTextLengthAnalyzer {
    void *vtbl;             // 0x00
    s16 maxLength;          // 0x04
    s16 nonEmptyLines;      // 0x06: lines with a count
    s16 emptyLines;         // 0x08: lines without a count
    s16 lineIndex;          // 0x0a: index into counts
    u16 counts[0x20];       // 0x0c: one count per line
    s16 unk_4c;
} KnifeTextLengthAnalyzer;

// TextLengthAnalyzer::onTerminate() (0x020a1704): the same count step as onReadNewLine, without the zero test
extern "C" void Knife_Message_TextLengthAnalyzer_onTerminate(void *a);
ARM void Knife_Message_TextLengthAnalyzer_onTerminate(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;

    if (self->counts[self->lineIndex] > self->maxLength) {
        self->maxLength = self->counts[self->lineIndex];
    }
    if (self->counts != 0) {
        self->nonEmptyLines++;
    } else {
        self->emptyLines++;
    }
    self->lineIndex++;
}
