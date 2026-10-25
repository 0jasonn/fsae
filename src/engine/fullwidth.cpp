#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::convertToFullWidth, 0x0208fc84 to 0x0208fcf8: maps the printable ASCII characters to their full-width
// forms through a rodata table. Characters outside 0x20 to 0x7e are returned unchanged. The second overload converts a
// whole text with that mapping (the loop of Text::convert with the mapping in front of the destination scheme).

namespace Knife {
namespace Message {

// convertToFullWidth(int) (0x0208fc84)
ARM s32 convertToFullWidth(s32 character) {
    u32 index;

    if (character >= 0x7f) {
        return character;
    }
    if (character >= 0x20) {
        index = character - 0x20;
        return data_020dd9d4[index];
    }
    return character;
}

}
}
