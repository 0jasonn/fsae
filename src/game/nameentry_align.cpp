#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/nameentry_align.h"

// nameentry_align: function nameEntryUIView_alignCenter (0x020ae7a8).

// Render target of an entry: the position (halfwords) at +0x5c and +0x5e
typedef struct NameEntryTarget {
    u8 unk_00[0x5c];
    s16 posX;          // 0x5c
    s16 posY;          // 0x5e
} NameEntryTarget;

// nameEntryUIView::alignCenter(index, width) (0x020ae7a8): centres the render target of the entry index horizontally in
// width, using the first two bytes of the text range entry found for the entry's text id (the first is the left offset
// and the second the width)
ARM void nameEntryUIView_alignCenter(void *self, s32 index, s32 width) {
    u16 textId;
    NameEntryTarget *target;
    u8 *box;
    u32 range;
    u8 *entry;
    s16 savedY;

    textId = nameEntryUIView_getTextFromIndex(self, index);
    target = (NameEntryTarget *)Knife_Message_GetRenderTarget(index);
    box = (u8 *)KnifeApp_getField20Address(KnifeApp_getInstance());
    range = TextBox_FindRange(box, textId);
    if (range == 0xffff) {
        range = *(u16 *)(*(u8 **)box + 2);
    }
    entry = TextBox_FindRangeEntry(box, range);
    savedY = target->posY;
    target->posX = -(s8)entry[0] + (width - entry[1]) / 2;
    target->posY = savedY;
}
