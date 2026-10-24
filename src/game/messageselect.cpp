#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::MessageSelect::init() (0x020a1838). MessageSelect::setup (0x020a1864) is parked in
//   scratch/agentE/nonmatching/func_020a1864_MessageSelect_setup.cpp

// One choice of the select list: two words
typedef struct KnifeMessageSelectItem {
    u32 value;   // 0x00 (+8 of the list)
    u32 label;   // 0x04 (+0xc of the list)
} KnifeMessageSelectItem;

// Select list state (Knife::Message::MessageSelect). Only the fields the functions matched so far use are named.
typedef struct KnifeMessageSelect {
    u8 flag0;                       // 0x00: 1 once set up
    u8 cursor;                      // 0x01
    u8 maxItems;                    // 0x02: 10 after setup
    u8 count;                       // 0x03: number of items
    u8 unk_04;
    u8 mode;                        // 0x05: third argument of setup
    u8 unk_06;
    u8 flag7;                       // 0x07: 1 after init
    KnifeMessageSelectItem items[0x10]; // 0x08
} KnifeMessageSelect;

// MessageSelect::init() (0x020a1838): clears the list
extern "C" void Knife_Message_MessageSelect_init(void *a);
ARM void Knife_Message_MessageSelect_init(void *a) {
    KnifeMessageSelect *self = (KnifeMessageSelect *)a;

    self->flag0 = 0;
    self->count = 0;
    self->mode = 0;
    self->cursor = 0;
    self->unk_04 = 0;
    self->unk_06 = 0;
    self->maxItems = 0;
    self->flag7 = 1;
}
