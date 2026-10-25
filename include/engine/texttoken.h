#ifndef WIP_D_TEXTTOKEN_H
#define WIP_D_TEXTTOKEN_H

#include "types.h"
#include "engine/text_tokenizer.h"

// Tag tokens of the message text (Knife::Message::*TagToken and PlainTextToken), 0x0208f434 to 0x0208f9c8.
// Each token is its vtable pointer followed by the tag value. The vtables (data_0211ad5c, data_0211ad7c, ...)
// give the slots: 0 dtorSlot, 1 the deleting dtor, 2 getCount, 3 slot3, 4 slot4, 5 analyze.
// The ruby tokens and TerminateToken are declared in engine/text_tokenizer.h.
//
// ITokenAnalyzer (text_tokenizer.h) declares its slots without the arguments the tag handlers pass, so the
// analyze functions call the analyzer through TokenAnalyzerSlots: the same slot order, with the arguments.

namespace Knife {
namespace Message {

class TokenAnalyzerSlots {
public:
    virtual void onReadPlainText(const Text *text); // slot 0
    virtual void onReadNewLine(void); // slot 1
    virtual void onReadWaitTag(s32 value); // slot 2
    virtual void onReadAutoTag(s32 value); // slot 3
    virtual void onReadSyncTag(void); // slot 4
    virtual void onReadNextTag(u32 value); // slot 5
    virtual void onReadSelectTag(void); // slot 6
    virtual void onReadTextSETag(Voice voice); // slot 7
    virtual void onReadPictTag(Pictogram pictogram); // slot 8
    virtual void onReadButtonTag(Button button); // slot 9
    virtual void onReadBlankTag(s32 value); // slot 10
    virtual void onReadCenterTag(void); // slot 11
    virtual void onReadRightTag(void); // slot 12
    virtual void onReadSizeTag(s32 value); // slot 13
    virtual void onReadColorTag(ColorType color); // slot 14
    virtual void onReadRubyBeginTag(const Text *text); // slot 15
    virtual void onReadRubyEndTag(void); // slot 16
    virtual void onReadTerminate(void); // slot 17
};

// PlainTextToken: a run of characters (the text at 0x04, the character count at 0x10)
class PlainTextToken {
public:
    BOOL getText(Text *out) const;
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00
    Text text;        // 0x04: the run (scheme, data, size in bytes)
    s32 count;        // 0x10: number of characters in the run
};

// ColorTagToken: the analyze function passes its color to the analyzer
class ColorTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    ColorType color; // 0x04
};

// SizeTagToken: the analyze function passes its size to the analyzer
class SizeTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    s32 size; // 0x04
};

// RightTagToken: the analyze function passes no value
class RightTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
};

// CenterTagToken: the analyze function passes no value
class CenterTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
};

// BlankTagToken: the analyze function passes its value to the analyzer
class BlankTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    s32 value; // 0x04
};

// ButtonTagToken: the analyze function passes its button to the analyzer
class ButtonTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    Button button; // 0x04
};

// PictTagToken: the analyze function passes its pictogram to the analyzer
class PictTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    Pictogram pictogram; // 0x04
};

// TextSETagToken: the analyze function passes its voice to the analyzer
class TextSETagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    Voice voice; // 0x04
};

// SelectTagToken: the analyze function passes no value
class SelectTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
};

// NextTagToken: the analyze function passes its value to the analyzer
class NextTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    u32 value; // 0x04
};

// SyncTagToken: the analyze function passes no value
class SyncTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
};

// AutoTagToken: the analyze function passes its value to the analyzer
class AutoTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    s32 value; // 0x04
};

// WaitTagToken: the analyze function passes its value to the analyzer
class WaitTagToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
    s32 value; // 0x04
};

// NewLineToken: the analyze function passes no value
class NewLineToken {
public:
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;

    const void *vtbl; // 0x00: the token's vtable
};

}
}

#endif
