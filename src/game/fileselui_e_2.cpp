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

typedef struct FileSelText {
    u32 handle;
    u8 *str;
    u32 kind;
} FileSelText;

// fileSelUIView::getText(Knife::Message::Text*, unsigned long, Knife::Message::Language) (0x020a8d78): fills the text
// record for the save entry textId (entries of 0x50 bytes from 9000)
ARM s32 fileSelUIView_getText(void *self, void *text, u32 textId, s32 language) {
    FileSelText *msg = (FileSelText *)text;

    msg->handle = (u32)Knife_Message_getCESObject_021770b4();
    msg->str = data_021350b0 + (textId - 9000) * 0x50 + 8;
    msg->kind = 0x10;
    return 1;
}
