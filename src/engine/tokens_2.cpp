#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/text_tokenizer.h"

// Knife::Message::RubyEndTagToken and RubyBeginTagToken, 0x0208f394 to 0x0208f434. Each has the deleting dtor (slot 1,
// frees the block), dtorSlot (slot 0, empty), getCount, slot3 and slot4 (constants), and analyze (slot 5), which calls the
// analyzer's slot 16 (end) or slot 15 with the ruby text (begin).

// RubyEndTagToken::~RubyEndTagToken, deleting dtor (0x0208f394): frees the token
extern "C" void *Knife_Message_RubyEndTagToken_dtor_RubyEndTagToken(void *self);
ARM void *Knife_Message_RubyEndTagToken_dtor_RubyEndTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// RubyEndTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f3a8): calls analyzer slot 16, returns TRUE
ARM s32 RubyEndTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    analyzer->slot16();
    return 1;
}

// RubyEndTagToken::slot4 (0x0208f3c4)
ARM s32 RubyEndTagToken::slot4(void) const {
    return 0;
}

// RubyEndTagToken::slot3 (0x0208f3cc)
ARM s32 RubyEndTagToken::slot3(void) const {
    return 0;
}

// RubyEndTagToken::getCount (0x0208f3d4)
ARM s32 RubyEndTagToken::getCount(void) const {
    return 0;
}

// RubyEndTagToken::dtorSlot (0x0208f3dc): nothing to release
ARM void RubyEndTagToken::dtorSlot(void) {
}

}
}

// RubyBeginTagToken::~RubyBeginTagToken, deleting dtor (0x0208f3e0): frees the token
extern "C" void *Knife_Message_RubyBeginTagToken_dtor_RubyBeginTagToken(void *self);
ARM void *Knife_Message_RubyBeginTagToken_dtor_RubyBeginTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// RubyBeginTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f3f4): passes the ruby text (+0x04) to analyzer slot 15
ARM s32 RubyBeginTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    analyzer->slot15((const u8 *)this + 4);
    return 1;
}

// RubyBeginTagToken::getCount (0x0208f418)
ARM s32 RubyBeginTagToken::getCount(void) const {
    return 0;
}

// RubyBeginTagToken::slot3 (0x0208f420)
ARM s32 RubyBeginTagToken::slot3(void) const {
    return 0;
}

// RubyBeginTagToken::slot4 (0x0208f428)
ARM s32 RubyBeginTagToken::slot4(void) const {
    return 0;
}

// RubyBeginTagToken::dtorSlot (0x0208f430)
ARM void RubyBeginTagToken::dtorSlot(void) {
}

}
}
