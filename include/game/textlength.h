#ifndef GAME_TEXTLENGTH_H
#define GAME_TEXTLENGTH_H

#include "engine/entity.h"

typedef struct KnifeTextLengthAnalyzer {
    void *vtbl;        // 0x00
    s16 maxLength;     // 0x04
    s16 nonEmptyLines; // 0x06: lines with a count
    s16 emptyLines;    // 0x08: lines without a count
    s16 lineIndex;     // 0x0a: index into counts
    u16 counts[0x20];  // 0x0c: one count per line
    u16 charCount;     // 0x4c
} KnifeTextLengthAnalyzer;

#endif
