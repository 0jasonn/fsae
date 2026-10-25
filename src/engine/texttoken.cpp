#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/texttoken.h"

// Knife::Message tag tokens, 0x0208f434 to 0x0208f9c8: each class has the deleting dtor (a plain function),
// analyze (passes its value to the analyzer), getCount, slot3, slot4 and dtorSlot. PlainTextToken (0x0208f8a4 to
// 0x0208f978) also has getText. The functions are in address order.

extern "C" void *Knife_Message_ColorTagToken_dtor_ColorTagToken(void *self);
ARM void *Knife_Message_ColorTagToken_dtor_ColorTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// ColorTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f448)
ARM s32 ColorTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadColorTag(color);
    return 1;
}

}
}

extern "C" s32 Knife_Message_ColorTagToken_slot4(void *self);
ARM s32 Knife_Message_ColorTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_ColorTagToken_slot3(void *self);
ARM s32 Knife_Message_ColorTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_ColorTagToken_getCount(void *self);
ARM s32 Knife_Message_ColorTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_ColorTagToken_dtorSlot(void *self);
ARM void Knife_Message_ColorTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_SizeTagToken_dtor_SizeTagToken(void *self);
ARM void *Knife_Message_SizeTagToken_dtor_SizeTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// SizeTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f49c)
ARM s32 SizeTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadSizeTag(size);
    return 1;
}

}
}

extern "C" s32 Knife_Message_SizeTagToken_slot4(void *self);
ARM s32 Knife_Message_SizeTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_SizeTagToken_slot3(void *self);
ARM s32 Knife_Message_SizeTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_SizeTagToken_getCount(void *self);
ARM s32 Knife_Message_SizeTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_SizeTagToken_dtorSlot(void *self);
ARM void Knife_Message_SizeTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_RightTagToken_dtor_RightTagToken(void *self);
ARM void *Knife_Message_RightTagToken_dtor_RightTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// RightTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f4f0)
ARM s32 RightTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadRightTag();
    return 1;
}

}
}

extern "C" s32 Knife_Message_RightTagToken_slot4(void *self);
ARM s32 Knife_Message_RightTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_RightTagToken_slot3(void *self);
ARM s32 Knife_Message_RightTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_RightTagToken_getCount(void *self);
ARM s32 Knife_Message_RightTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_RightTagToken_dtorSlot(void *self);
ARM void Knife_Message_RightTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_CenterTagToken_dtor_CenterTagToken(void *self);
ARM void *Knife_Message_CenterTagToken_dtor_CenterTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// CenterTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f53c)
ARM s32 CenterTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadCenterTag();
    return 1;
}

}
}

extern "C" s32 Knife_Message_CenterTagToken_slot4(void *self);
ARM s32 Knife_Message_CenterTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_CenterTagToken_slot3(void *self);
ARM s32 Knife_Message_CenterTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_CenterTagToken_getCount(void *self);
ARM s32 Knife_Message_CenterTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_CenterTagToken_dtorSlot(void *self);
ARM void Knife_Message_CenterTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_BlankTagToken_dtor_BlankTagToken(void *self);
ARM void *Knife_Message_BlankTagToken_dtor_BlankTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// BlankTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f588)
ARM s32 BlankTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadBlankTag(value);
    return 1;
}

}
}

extern "C" s32 Knife_Message_BlankTagToken_slot4(void *self);
ARM s32 Knife_Message_BlankTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_BlankTagToken_slot3(void *self);
ARM s32 Knife_Message_BlankTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_BlankTagToken_getCount(void *self);
ARM s32 Knife_Message_BlankTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_BlankTagToken_dtorSlot(void *self);
ARM void Knife_Message_BlankTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_ButtonTagToken_dtor_ButtonTagToken(void *self);
ARM void *Knife_Message_ButtonTagToken_dtor_ButtonTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// ButtonTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f5dc)
ARM s32 ButtonTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadButtonTag(button);
    return 1;
}

}
}

extern "C" s32 Knife_Message_ButtonTagToken_slot4(void *self);
ARM s32 Knife_Message_ButtonTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_ButtonTagToken_slot3(void *self);
ARM s32 Knife_Message_ButtonTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_ButtonTagToken_getCount(void *self);
ARM s32 Knife_Message_ButtonTagToken_getCount(void *self) {
    return 1;
}

extern "C" void Knife_Message_ButtonTagToken_dtorSlot(void *self);
ARM void Knife_Message_ButtonTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_PictTagToken_dtor_PictTagToken(void *self);
ARM void *Knife_Message_PictTagToken_dtor_PictTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// PictTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f630)
ARM s32 PictTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadPictTag(pictogram);
    return 1;
}

}
}

extern "C" s32 Knife_Message_PictTagToken_slot4(void *self);
ARM s32 Knife_Message_PictTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_PictTagToken_slot3(void *self);
ARM s32 Knife_Message_PictTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_PictTagToken_getCount(void *self);
ARM s32 Knife_Message_PictTagToken_getCount(void *self) {
    return 1;
}

extern "C" void Knife_Message_PictTagToken_dtorSlot(void *self);
ARM void Knife_Message_PictTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_TextSETagToken_dtor_TextSETagToken(void *self);
ARM void *Knife_Message_TextSETagToken_dtor_TextSETagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// TextSETagToken::analyze(ITokenAnalyzer*, int) const (0x0208f684)
ARM s32 TextSETagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadTextSETag(voice);
    return 1;
}

}
}

extern "C" s32 Knife_Message_TextSETagToken_slot4(void *self);
ARM s32 Knife_Message_TextSETagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_TextSETagToken_slot3(void *self);
ARM s32 Knife_Message_TextSETagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_TextSETagToken_getCount(void *self);
ARM s32 Knife_Message_TextSETagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_TextSETagToken_dtorSlot(void *self);
ARM void Knife_Message_TextSETagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_SelectTagToken_dtor_SelectTagToken(void *self);
ARM void *Knife_Message_SelectTagToken_dtor_SelectTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// SelectTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f6d8)
ARM s32 SelectTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadSelectTag();
    return 1;
}

}
}

extern "C" s32 Knife_Message_SelectTagToken_slot4(void *self);
ARM s32 Knife_Message_SelectTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_SelectTagToken_slot3(void *self);
ARM s32 Knife_Message_SelectTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_SelectTagToken_getCount(void *self);
ARM s32 Knife_Message_SelectTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_SelectTagToken_dtorSlot(void *self);
ARM void Knife_Message_SelectTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_NextTagToken_dtor_NextTagToken(void *self);
ARM void *Knife_Message_NextTagToken_dtor_NextTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// NextTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f724)
ARM s32 NextTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadNextTag(value);
    return 1;
}

}
}

extern "C" s32 Knife_Message_NextTagToken_slot4(void *self);
ARM s32 Knife_Message_NextTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_NextTagToken_slot3(void *self);
ARM s32 Knife_Message_NextTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_NextTagToken_getCount(void *self);
ARM s32 Knife_Message_NextTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_NextTagToken_dtorSlot(void *self);
ARM void Knife_Message_NextTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_SyncTagToken_dtor_SyncTagToken(void *self);
ARM void *Knife_Message_SyncTagToken_dtor_SyncTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// SyncTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f778)
ARM s32 SyncTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadSyncTag();
    return 1;
}

}
}

extern "C" s32 Knife_Message_SyncTagToken_slot4(void *self);
ARM s32 Knife_Message_SyncTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_SyncTagToken_slot3(void *self);
ARM s32 Knife_Message_SyncTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_SyncTagToken_getCount(void *self);
ARM s32 Knife_Message_SyncTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_SyncTagToken_dtorSlot(void *self);
ARM void Knife_Message_SyncTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_AutoTagToken_dtor_AutoTagToken(void *self);
ARM void *Knife_Message_AutoTagToken_dtor_AutoTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// AutoTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f7c4)
ARM s32 AutoTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadAutoTag(value);
    return 1;
}

}
}

extern "C" s32 Knife_Message_AutoTagToken_slot4(void *self);
ARM s32 Knife_Message_AutoTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_AutoTagToken_slot3(void *self);
ARM s32 Knife_Message_AutoTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_AutoTagToken_getCount(void *self);
ARM s32 Knife_Message_AutoTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_AutoTagToken_dtorSlot(void *self);
ARM void Knife_Message_AutoTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_WaitTagToken_dtor_WaitTagToken(void *self);
ARM void *Knife_Message_WaitTagToken_dtor_WaitTagToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// WaitTagToken::analyze(ITokenAnalyzer*, int) const (0x0208f818)
ARM s32 WaitTagToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadWaitTag(value);
    return 1;
}

}
}

extern "C" s32 Knife_Message_WaitTagToken_slot4(void *self);
ARM s32 Knife_Message_WaitTagToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_WaitTagToken_slot3(void *self);
ARM s32 Knife_Message_WaitTagToken_slot3(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_WaitTagToken_getCount(void *self);
ARM s32 Knife_Message_WaitTagToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_WaitTagToken_dtorSlot(void *self);
ARM void Knife_Message_WaitTagToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_NewLineToken_dtor_NewLineToken(void *self);
ARM void *Knife_Message_NewLineToken_dtor_NewLineToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// NewLineToken::analyze(ITokenAnalyzer*, int) const (0x0208f86c)
ARM s32 NewLineToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadNewLine();
    return 1;
}

}
}

extern "C" s32 Knife_Message_NewLineToken_slot4(void *self);
ARM s32 Knife_Message_NewLineToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_NewLineToken_slot3(void *self);
ARM s32 Knife_Message_NewLineToken_slot3(void *self) {
    return 1;
}

extern "C" s32 Knife_Message_NewLineToken_getCount(void *self);
ARM s32 Knife_Message_NewLineToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_NewLineToken_dtorSlot(void *self);
ARM void Knife_Message_NewLineToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_PlainTextToken_dtor_PlainTextToken(void *self);
ARM void *Knife_Message_PlainTextToken_dtor_PlainTextToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// PlainTextToken::analyze(ITokenAnalyzer*, int) const (0x0208f8b8): steps the run past the characters before
// the index, then passes the rest of the run to the analyzer. An index outside the run gives FALSE.
ARM s32 Knife::Message::PlainTextToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    Text run;
    s32 i;

    run.ces = text.ces;
    run.data = text.data;
    run.size = text.size;
    if (index < 0 || index >= count) {
        return 0;
    }
    for (i = 0; i < index; i++) {
        run.readFirstCharacterAndStep(NULL);
    }
    ((TokenAnalyzerSlots *)analyzer)->onReadPlainText(&run);
    return 1;
}

// PlainTextToken::getText(Text*) const (0x0208f948): copies the run out, always TRUE
ARM BOOL Knife::Message::PlainTextToken::getText(Text *out) const {
    out->ces = text.ces;
    out->data = text.data;
    out->size = text.size;
    return 1;
}

}
}

extern "C" s32 Knife_Message_PlainTextToken_getCount(void *self);
// the character count (count at 0x10)
ARM s32 Knife_Message_PlainTextToken_getCount(void *self) {
    return ((Knife::Message::PlainTextToken *)self)->count;
}

extern "C" s32 Knife_Message_PlainTextToken_slot3(void *self);
ARM s32 Knife_Message_PlainTextToken_slot3(void *self) {
    return 0;
}

extern "C" void Knife_Message_PlainTextToken_dtorSlot(void *self);
ARM void Knife_Message_PlainTextToken_dtorSlot(void *self) {
}

extern "C" void *Knife_Message_TerminateToken_dtor_TerminateToken(void *self);
ARM void *Knife_Message_TerminateToken_dtor_TerminateToken(void *self) {
    operator delete(self);
    return self;
}

namespace Knife {
namespace Message {

// TerminateToken::analyze(ITokenAnalyzer*, int) const (0x0208f990)
ARM s32 TerminateToken::analyze(ITokenAnalyzer *analyzer, s32 index) const {
    ((TokenAnalyzerSlots *)analyzer)->onReadTerminate();
    return 1;
}

}
}

extern "C" s32 Knife_Message_TerminateToken_slot4(void *self);
ARM s32 Knife_Message_TerminateToken_slot4(void *self) {
    return 0;
}

extern "C" s32 Knife_Message_TerminateToken_slot3(void *self);
ARM s32 Knife_Message_TerminateToken_slot3(void *self) {
    return 1;
}

extern "C" s32 Knife_Message_TerminateToken_getCount(void *self);
ARM s32 Knife_Message_TerminateToken_getCount(void *self) {
    return 0;
}

extern "C" void Knife_Message_TerminateToken_dtorSlot(void *self);
ARM void Knife_Message_TerminateToken_dtorSlot(void *self) {
}

