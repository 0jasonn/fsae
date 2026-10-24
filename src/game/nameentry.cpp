#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/baseduiview.h"

// Functions in this file (original names from the debug build):
//   nameEntryUIView::getText(Knife::Message::Text*, unsigned long, Knife::Message::Language) (0x020ae558),
//   nameEntryUIView::initialize() (0x020ae5bc)

extern "C" {
u32 func_0208fc6c(const void *a);
const void *Knife_Comm_selectDataTable(s32 unused, s32 flag);
}

extern u8 data_021806f0[];
extern u8 data_02125560[];

// Knife::Message::Text: a text handle, the string and its kind
typedef struct KnifeMsgText {
    u32 handle;
    const u16 *str;
    u32 kind;
} KnifeMsgText;

// Fields of the name entry view that the functions of this file use (the base view comes first)
typedef struct NameEntryUIViewCtrl {
    basedUIView base;
    u8 unk_30[0x46 - 0x30];
    u8 unk_46;
    s8 unk_47; // language flag, passed to Knife_Comm_selectDataTable
    u8 unk_48;
    u8 unk_49;
    u16 unk_4a;
} NameEntryUIViewCtrl;

// One of the 0x47 entries of data_02125560 (0x34 bytes each)
typedef struct NameEntryItem {
    u8 unk_00[8];
    void *ptr08;
    s32 index0c;
    u8 unk_10[8];
    s32 unk18;
    s32 unk1c;
    u8 unk_20[0x34 - 0x20];
} NameEntryItem;

extern "C" s32 nameEntryUIView_getText(void *self, KnifeMsgText *out, u32 index, s32 language);
extern "C" void nameEntryUIView_initialize(NameEntryUIViewCtrl *self);

// nameEntryUIView::getText (0x020ae558): ids 0x2328 to 0x232d are the name characters of the view, other ids come from the
// table of the language flag at offset 0x47
ARM s32 nameEntryUIView_getText(void *self, KnifeMsgText *out, u32 index, s32 language) {
    u8 *obj;
    s32 slot;
    u32 handle;
    const u16 *str;
    const u16 *table;

    obj = (u8 *)self;
    slot = (s32)index - 0x2328;
    if (slot >= 0 && slot < 6) {
        handle = func_0208fc6c(self);
        str = (const u16 *)(obj + 0x34) + slot;
    } else {
        table = (const u16 *)Knife_Comm_selectDataTable((s32)self, (s8)obj[0x47]);
        handle = func_0208fc6c(table);
        str = table + (slot - 6);
    }
    out->handle = handle;
    out->str = str;
    out->kind = 2;
    return 1;
}

// nameEntryUIView::initialize (0x020ae5bc): initialises the base view, the flags and the 0x47 name entries
ARM void nameEntryUIView_initialize(NameEntryUIViewCtrl *self) {
    u32 off;
    u32 i;
    u8 *el;
    u32 value;
    NameEntryItem *item;

    basedUIView_initialize((basedUIView *)self);
    self->base.unk_04 = 5;
    self->unk_49 = 0;
    self->unk_4a = 0;
    self->unk_47 = 0;
    self->unk_46 = 0;
    el = *(u8 **)(data_021806f0 + 0x6b4);
    off = 0;
    for (i = 0; i < 0x47; i++) {
        value = off + 0x240;
        item = (NameEntryItem *)(data_02125560 + i * 0x34);
        item->index0c = value;
        item->unk18 = 2;
        item->unk1c = 2;
        item->ptr08 = el + (value << 5);
        off += 4;
    }
}
