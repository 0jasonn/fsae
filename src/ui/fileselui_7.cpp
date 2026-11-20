#include "engine/functions.h"
#include "global.h"
#include "ui/fileselui_view.h"
#include "ui/fileselui_2_api.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_errorFileInit (0x020a88a8), fileSelUIView_getText (0x020a8d78), fileSelUIView_vfunc2 (0x020a8f7c)

extern "C" void *Knife_Message_getCESObject_021770b4(void);
extern "C" void clearSaveData(u8 index);
extern "C" void fileSelUIView_errorFileInit(void *self);
void Knife_InitialSaveFile(u8 index);
void Knife_mediaWrite(void);
#include "engine/multisio_save.h"

// fileSelUIView::errorFileInit() (0x020a88a8): the save entries in state 6 (initial file, then clear) and 8 (clear)
// are cleared to idle, then the media is written
void fileSelUIView_errorFileInit(void *self) {
    MultiSioEntry *base;
    u32 i;
    MultiSioEntry *entry;
    s8 state;

    base = data_021350b0;
    for (i = 0; i < 3; i++) {
        entry = &base[i];
        state = entry->status;
        switch (state) {
        case 6:
            Knife_InitialSaveFile((u8)i);
            /* fall through */
        case 8:
            clearSaveData((u8)i);
            entry->status = 0;
            break;
        }
    }
    Knife_mediaWrite();
}

