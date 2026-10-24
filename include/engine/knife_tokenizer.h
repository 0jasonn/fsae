#ifndef WIP_D_MESSAGE_H
#define WIP_D_MESSAGE_H

#include "types.h"

namespace Knife {
namespace Message {

// Knife::Message::Token: the token base. Slot 2 gives the number of analyzable parts, slot 5 analyzes one part.
class Token {
public:
    virtual void dtorSlot(void);
    virtual void deletingDtorSlot(void);
    virtual s32 getCount(void) const;
    virtual void slot3(void);
    virtual void slot4(void);
    virtual void analyze(void *analyzer, s32 index) const;
};

// Knife::Message::TextTokenizer: the token list starts at +0x20 and its count is at +0x24
class TextTokenizer {
public:
    u8 unk_00[0x20];
    Token **tokens;     // 0x20
    s32 tokenCount;     // 0x24
};

}
}

#endif
