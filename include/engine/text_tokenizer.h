#ifndef WIP_D_TEXT_TOKENIZER_H
#define WIP_D_TEXT_TOKENIZER_H

#include "types.h"
#include "engine/kmsgreader.h"

// Knife::Message::TextTokenizer, Knife::Message::Text and the enums used by the tag handlers (0x0208e4e0 to 0x02094000).
// The virtual slots follow the vtable at data_0211af7c in declaration order: slot 0 is onBegin, slot 1 onEnd, and so on up
// to slot 22 (onReadError). Slots 23 and 24 are the dtors, which are not declared here (the ctor and dtors stay extern "C").
// Replaces the partial class in engine/knife_tokenizer.h once integrated.

extern "C" {
void Mem_Set(void *dst, u32 value, u32 size);  // MI_CpuFill-like fill (dsd name), zeroes the pool
void CopyBytes(void *dst, const void *src, u32 size); // memcpy (0x02005dc0)
extern char data_0211ad5c[]; // TerminateToken vtable (4-byte token: just the vtable pointer)
extern char data_021770b4[]; // default character encoding scheme object (UTF-16LE), bss
extern char data_021770b8[]; // second static character encoding scheme object, bss
extern const u16 data_020dd9d4[]; // full-width forms of the characters 0x20 to 0x7e
extern char data_0211ad7c[]; // PlainTextToken vtable
extern char data_0211ae1c[]; // NewLineToken vtable (4 bytes)
}

namespace Knife {
namespace Message {

// Language of the message text (values not known yet)
typedef enum Language { LANGUAGE_0, LANGUAGE_1, LANGUAGE_2, LANGUAGE_3, LANGUAGE_4, LANGUAGE_5, LANGUAGE_6, LANGUAGE_7 } Language;

// Voice of a speech tag (values not known yet)
typedef enum Voice { VOICE_0, VOICE_1, VOICE_2, VOICE_3 } Voice;

// Placeholders for the tag argument types (values not known yet)
typedef enum Pictogram { PICTOGRAM_UNKNOWN } Pictogram;
typedef enum Button { BUTTON_UNKNOWN } Button;
typedef enum ColorType { COLOR_TYPE_UNKNOWN } ColorType;

class IAppInfoGetter;
class ICharacterEncodingScheme;
class TextReader;
class ITokenAnalyzer;

// Knife::Message::ITokenAnalyzer: the interface the tokens analyze with. The slots the token analyze functions call are
// named by their use (15: text argument, 16 and 17: no arguments); the others are not used yet.
class ITokenAnalyzer {
public:
    virtual void slot0(void);
    virtual void slot1(void);
    virtual void slot2(void);
    virtual void slot3(void);
    virtual void slot4(void);
    virtual void slot5(void);
    virtual void slot6(void);
    virtual void slot7(void);
    virtual void slot8(void);
    virtual void slot9(void);
    virtual void slot10(void);
    virtual void slot11(void);
    virtual void slot12(void);
    virtual void slot13(void);
    virtual void slot14(void);
    virtual void slot15(const void *text);
    virtual void slot16(void);
    virtual void slot17(void);
};

// Knife::Message::Token: the token base. Slot 0 is dtorSlot (empty for the pool tokens), slot 1 the deleting dtor,
// slot 2 getCount, slots 3 and 4 further queries, slot 5 analyze.
class Token {
public:
    virtual void dtorSlot(void);
    virtual void deletingDtorSlot(void);
    virtual s32 getCount(void) const;
    virtual s32 slot3(void) const;
    virtual s32 slot4(void) const;
    virtual s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;
};

// Tokens of the tag group (one class per tag): only the members the functions so far use are declared. They derive
// from Token in the original; written here without the base and without virtual so no vtable is emitted (the vtables
// are ROM data).
class RubyEndTagToken {
public:
    void dtorSlot(void);
    s32 getCount(void) const;
    s32 slot3(void) const;
    s32 slot4(void) const;
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;
};

class RubyBeginTagToken {
public:
    void dtorSlot(void);
    s32 getCount(void) const;
    s32 slot3(void) const;
    s32 slot4(void) const;
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;
};

class TerminateToken {
public:
    void dtorSlot(void);
    s32 getCount(void) const;
    s32 slot3(void) const;
    s32 slot4(void) const;
    s32 analyze(ITokenAnalyzer *analyzer, s32 index) const;
};

// Knife::Message::TextReader (only the cancel method is used here; readData and the rest live in other units)
class TextReader {
public:
    void cancel(void);
};

// Knife::Message::ICharacterEncodingScheme: slot 0 reads the first character, slot 1 gives the length of a string
class ICharacterEncodingScheme {
public:
    virtual u32 readFirstCharacter(const void *data, u32 size, u32 *out) const;
    virtual u32 getLength(const void *data, u32 size) const;
    virtual u32 convert(void *out, u32 outSize, s32 character) const;
};

// Single-byte schemes: ISO-8859-1 (characters up to 0xff) and ASCII (up to 0x7f). Both read one byte per character.
class CES_ISO8859_1 : public ICharacterEncodingScheme {
public:
    u32 readFirstCharacter(const void *data, u32 size, u32 *out) const;
    u32 getCharCount(const void *data, u32 size) const;
    u32 convert(void *out, u32 outSize, s32 character) const;
};

class CES_ASCII : public ICharacterEncodingScheme {
public:
    u32 readFirstCharacter(const void *data, u32 size, u32 *out) const;
    u32 getCharCount(const void *data, u32 size) const;
    u32 convert(void *out, u32 outSize, s32 character) const;
};

// Four-byte little-endian scheme (one character per 32-bit word)
class CES_UTF32LE : public ICharacterEncodingScheme {
public:
    u32 readFirstCharacter(const void *data, u32 size, u32 *out) const;
    u32 convert(void *out, u32 outSize, s32 character) const;
    u32 getCharCount(const void *data, u32 size) const;
};

// Two-byte little-endian scheme (UTF-16LE: surrogate pairs for the characters from 0x10000)
class CES_UTF16LE : public ICharacterEncodingScheme {
public:
    u32 readFirstCharacter(const void *data, u32 size, u32 *out) const;
    u32 convert(void *out, u32 outSize, s32 character) const;
};

// Table of the default schemes by language (10 entries, rodata at data_0211b050)
typedef struct CESTable {
    ICharacterEncodingScheme *entries[10];
} CESTable;

const ICharacterEncodingScheme *getDefaultCES(Language language); // 0x0208fc14

// Knife::Message::Text (12 bytes): a string with its character encoding scheme, the data pointer and the size in bytes.
class Text {
public:
    // The constructor Text(const u16 *) (0x0208f9dc) is the plain function Knife_Message_Text_Text below: a real one
    // makes mwcc emit two copies (C1/C2) that our link cannot drop.
    void clear(void);       // zeroes the three fields (0x0208f9c8)
    void set(ICharacterEncodingScheme *ces, const void *data, u32 size); // 0x0208fa0c
    u32 readFirstCharacter(u32 *out) const;               // 0x0208fa14
    u32 readFirstCharacterAndStep(u32 *out);              // 0x0208fa54
    u32 getLength(void) const;                            // 0x0208fac0
    u32 convert(void *out, u32 outSize, const ICharacterEncodingScheme *dstCes) const; // 0x0208faf4

    ICharacterEncodingScheme *ces; // 0x00
    const void *data;              // 0x04
    u32 size;                      // 0x08: bytes
};

}
}
extern "C" Knife::Message::Text *Knife_Message_Text_Text(Knife::Message::Text *self, const u16 *str);
namespace Knife {
namespace Message {


// Knife::Message::TextTokenizer. The tokens are allocated from the pool at poolBase: objects grow down from the top, the
// token pointer array grows up from the bottom (tokens).
class TextTokenizer {
public:
    BOOL tokenize(u32 textId, Language language, const IAppInfoGetter *appInfo);
    BOOL tokenize(const u16 *str);
    BOOL tokenize(const Text *text);
    void changeMemoryPool(void *pool, u32 size);
    BOOL duplicateText(Text *dst, const Text *src);
    void cleanupTokens(void);

    virtual void onBegin(TextReader *reader, const Text *text);
    virtual void onEnd(bool first, bool second);
    virtual void onReadPlainText(const Text *text);
    virtual void onReadNewLine(void);
    virtual void onReadWaitTag(s32 value);
    virtual void onReadAutoTag(s32 value);
    virtual void onReadSyncTag(void);
    virtual void onReadNextTag(u32 value);
    virtual void onReadSelectTag(void);
    virtual void onReadTextSETag(Voice voice);
    virtual void onReadPictTag(Pictogram pictogram);
    virtual void onReadValueTag(s32 value);
    virtual void onReadButtonTag(Button button);
    virtual void onReadBlankTag(s32 value);
    virtual void onReadPlayerNameTag(s32 value);
    virtual void onReadSPSwitchTag(s32 value, const Text *first, const Text *second);
    virtual void onReadCenterTag(void);
    virtual void onReadRightTag(void);
    virtual void onReadSizeTag(s32 value);
    virtual void onReadColorTag(ColorType color);
    virtual void onReadRubyBeginTag(const Text *text);
    virtual void onReadRubyEndTag(void);
    virtual void onReadError(void);

    KMsgFileReader msgFile;        // 0x04: the message file (16 bytes)
    void *poolBase;                // 0x14
    u32 poolSize;                  // 0x18
    u32 poolUsed;                  // 0x1c: bytes taken from the top of the pool
    Token **tokens;                // 0x20
    s32 tokenCount;                // 0x24
    TextReader *textReader;        // 0x28: the active reader, set by onBegin and cleared at the end of onEnd. The tag
                                   // handlers cancel it when the pool overflows.
    const IAppInfoGetter *appInfo; // 0x2c
    u32 textId;                    // 0x30
    s32 language;                  // 0x34: -1 when the text is not a message file entry
    u8 overflow;                   // 0x38: set when the pool has no room left
};

}
}

extern "C" {
extern const Knife::Message::CESTable data_0211b050; // default schemes by language (rodata)
}

#endif
