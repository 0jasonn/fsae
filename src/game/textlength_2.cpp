#include "engine/functions.h"
#include "global.h"
#include "game/textlength_api.h"
#include "game/textlength.h"

// Functions in this file (original names from the debug build):
//   TextLengthAnalyzer::onTerminate() (0x020a1704)

// TextLengthAnalyzer::onTerminate() (0x020a1704): the same count step as onReadNewLine, without the zero test
void Knife_Message_TextLengthAnalyzer_onTerminate(void *a) {
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
