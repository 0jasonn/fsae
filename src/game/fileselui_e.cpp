#include "engine/functions.h"
#include "global.h"
#include "game/fileselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_errorFileInit (0x020a88a8), fileSelUIView_getText (0x020a8d78), fileSelUIView_vfunc2 (0x020a8f7c)

extern "C" void *Knife_Message_getCESObject_021770b4(void);
extern "C" void clearSaveData(u8 index);
extern "C" void fileSelUIView_errorFileInit(void *self);
void Knife_InitialSaveFile(u8 index);
void Knife_mediaWrite(void);
extern u8 data_021350b0[];

// fileSelUIView::errorFileInit() (0x020a88a8): the save entries in state 6 (initial file, then clear) and 8 (clear)
// are cleared to idle, then the media is written
ARM void fileSelUIView_errorFileInit(void *self) {
    u8 *base;
    u32 i;
    u8 *entry;
    s8 state;

    base = data_021350b0;
    for (i = 0; i < 3; i++) {
        entry = base + i * 0x50;
        state = (s8)entry[0x47];
        switch (state) {
        case 6:
            Knife_InitialSaveFile((u8)i);
            /* fall through */
        case 8:
            clearSaveData((u8)i);
            entry[0x47] = 0;
            break;
        }
    }
    Knife_mediaWrite();
}

// Text record written by getText (the layout of Knife::Message::Text used by the file list)
typedef struct FileSelText {
    u32 handle;
    u8 *str;
    u32 kind;
} FileSelText;
