#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/texttokenize.h"

// Knife::Message::getGrammaticalNumber (0x0208fea4) and the two helpers of the number formatting that follow it
// (0x0208ff18: the group separator of a language and value, 0x0208ffb4: the digits per group, always 3). localizeValue
// (0x0208fd50) is parked in scratch/agentD/nonmatching/Knife_Message_localizeValue.cpp (register numbering of its locals).

extern "C" {
s32 Knife_Message_getGroupSeparator(s32 language, s32 value); // 0x0208ff18, below
s32 Knife_Message_getGroupSize(s32 language, s32 value);      // 0x0208ffb4, below
}

namespace Knife {
namespace Message {

// getGrammaticalNumber(Language, int) (0x0208fea4): 0 for the singular, 1 for the plural. Language 0 has no number.
ARM s32 getGrammaticalNumber(Language language, int value) {
    switch (language) {
    case 0:
        return 0;
    case 1:
    case 2:
    case 3:
    case 6:
    case 7:
    case 8:
    case 9:
        if (value == 1 || value == -1) {
            return 0;
        }
        return 1;
    case 4:
    case 5:
        if (value >= -1 && value <= 1) {
            return 0;
        }
        return 1;
    default:
        return 0;
    }
}

}
}

// Separator between digit groups for a language and value (0x0208ff18), 0 for none (unnamed in the debug build)
ARM s32 Knife_Message_getGroupSeparator(s32 language, s32 value) {
    switch (language) {
    case 0:
        return 0;
    case 1:
    case 2:
        return ',';
    case 3:
        return ' ';
    case 4:
    case 5:
        return ' ';
    case 6:
    case 7:
        if (value < 10000) {
            return 0;
        }
        return ' ';
    case 8:
        if (value < 10000) {
            return 0;
        }
        return '.';
    case 9:
        if (value < 10000) {
            return 0;
        }
        return ' ';
    default:
        return 0;
    }
}

// Digits per group (0x0208ffb4): always 3 (unnamed in the debug build)
ARM s32 Knife_Message_getGroupSize(s32 language, s32 value) {
    return 3;
}
