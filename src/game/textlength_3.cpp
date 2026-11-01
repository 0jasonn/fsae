#include "engine/functions.h"
#include "global.h"
#include "game/textlength_api.h"
#include "game/textlength.h"

// Functions in this file (original names from the debug build):
//   TextLengthAnalyzer::onReadNewLine() (0x020a17e8)

// TextLengthAnalyzer::onReadNewLine() (0x020a17e8): closes the current line and counts it as empty or not
void Knife_Message_TextLengthAnalyzer_onReadNewLine(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;

    if (self->counts[self->lineIndex] > self->maxLength) {
        self->maxLength = self->counts[self->lineIndex];
    }
    if (self->counts[self->lineIndex] != 0) {
        self->nonEmptyLines++;
    } else {
        self->emptyLines++;
    }
    self->lineIndex++;
}
