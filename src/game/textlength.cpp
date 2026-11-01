#include "engine/functions.h"
#include "global.h"
#include "game/textlength_api.h"
#include "game/textlength.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::TextLengthAnalyzer::TextLengthAnalyzer() (0x020a16c4)

extern u8 data_0211ede0[]; // TextLengthAnalyzer vtable

// TextLengthAnalyzer::TextLengthAnalyzer() (0x020a16c4): sets the vtable and clears the counts
void Knife_Message_TextLengthAnalyzer_TextLengthAnalyzer(void *a) {
    KnifeTextLengthAnalyzer *self = (KnifeTextLengthAnalyzer *)a;
    s32 i;

    self->vtbl = data_0211ede0;
    self->maxLength = 0;
    for (i = 0; i < 0x20; i++) {
        self->counts[i] = 0;
    }
    self->nonEmptyLines = 0;
    self->emptyLines = 0;
    self->lineIndex = 0;
    self->charCount = 0;
}
