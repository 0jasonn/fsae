#ifndef WIP_E_SETUPTEXT_E_H
#define WIP_E_SETUPTEXT_E_H

#include "engine/functions.h"
#include "ui/fileselui_view.h"
#include "ui/modeselui_view.h"

// One text target of a UI view (0x34 bytes): where the text is drawn in the cell buffer
typedef struct UIViewTextTarget {
    s32 msgId;       // 0x00
    u8 unk_04[4];
    u8 *cellBase;    // 0x08: cell buffer + cellIndex * 0x20
    s32 cellIndex;   // 0x0c
    s32 column;      // 0x10: first column of the text (cells)
    s32 row;         // 0x14
    s32 height;      // 0x18
    u8 unk_1c[8];
    s16 offsetX;     // 0x24: pixel offset inside the first cell
    s16 offsetY;     // 0x26
    u8 unk_28[0x0c];
} UIViewTextTarget;

extern "C" {
s32 knife_GetFontStrWidth_04c2e0(s32 msgId, u8 flag, void *work);
void Knife_Message_SetupTextRenderer(void *sceneInfo, s32 language, void *textGetter);
s32 fsFileCheck(u8 slot);
void modeSelUIView_setupTextRender(ModeSelUIView *self);
}
void Knife_Message_CleanupTextRenderer(void);

extern u8 *data_02180da4;          // cell buffer
extern UIViewTextTarget data_02124bb4[];
extern u8 data_021806f0[];
extern u8 data_02124c50[];

#endif
