#ifndef WIP_E_FILESELUI_E_H
#define WIP_E_FILESELUI_E_H

// fileSelUIView: the file select screen (the view that owns the file list). Layout of the fields the functions use is
// named as they are matched; the view derives from basedUIView, so +0x0c is viewStack (the objects) and +0x2c the
// stack index (the focus index in the notes).

#include "types.h"
#include "game/baseduiview.h"

// Layout of the fields used by serialize and deserialize (0x30 and 0x44 are not named yet)
typedef struct FileSelUIView {
    /* 00 */ basedUIView base;
    /* 30 */ u8 unk_30[0x34 - 0x30];
    /* 34 */ basedUIView *objA; // child views, serialized through vtable slot 5 (deserialize: slot 6)
    /* 38 */ basedUIView *objB;
    /* 3c */ basedUIView *objC;
    /* 40 */ u8 flag40;
    /* 41 */ u8 flag41;
    /* 42 */ u8 flag42;
    /* 43 */ u8 flag43;
    /* 44 */ u8 unk_44[0x48 - 0x44];
    /* 48 */ u32 value48;
    /* 4c */ u8 block4c[0x20];
} FileSelUIView;

extern "C" {
void fileSelUIView_errorFileInit(void *self);
void fileSelUIView_serialize(FileSelUIView *self, u8 **buf);
void fileSelUIView_deserialize(FileSelUIView *self, u8 **buf);
void fileSelUIView_vfunc2(void *self);
s32 fileSelUIView_getText(void *self, void *text, u32 textId, s32 language);
}

extern "C" {
void subTaskSendBgChar(s16 index, void *data, u32 offset, u32 size);
void fileSelUIView_viewWillApper(FileSelUIView *self);
void fileSelUIView_setupTextRender(FileSelUIView *self);
}

#endif
