#ifndef GAME_TEXTLENGTH_API_H
#define GAME_TEXTLENGTH_API_H

// Functions defined in src/game/textlength*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Message_TextLengthAnalyzer_TextLengthAnalyzer(void *a);
void Knife_Message_TextLengthAnalyzer_onReadNewLine(void *a);
void Knife_Message_TextLengthAnalyzer_onTerminate(void *a);
}

#endif
