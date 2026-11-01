#ifndef WIP_E_DECLS_E_H
#define WIP_E_DECLS_E_H

// Declarations used by the implementer E units that functions.h does not name yet. Plain (C linkage) names are the
// ones in config/eur/arm9/symbols.txt. Class members with plain names take the object as the first argument.

#include "engine/functions.h"
#include "ui/message_e.h"

// Layout of Knife::Message::RenderTarget as the text drawing reads it (message_e.h names only part of it)
typedef struct RenderTargetLayout {
    void *vtbl;             // 0x00
    u8 unk_04[0x20];        // 0x04
    u8 *cellBase;           // 0x24: OAM / cell buffer
    s32 mode;               // 0x28
    s32 unk_2c;             // 0x2c
    s32 unk_30;             // 0x30
    s32 unk_34;             // 0x34
    s32 unk_38;             // 0x38
    s32 unk_3c;             // 0x3c
    s32 unk_40;             // 0x40
    s32 unk_44;             // 0x44: first cell index
    u8 flag48;              // 0x48
    u8 unk_49[3];           // 0x49
    s32 unk_4c;             // 0x4c
} RenderTargetLayout;

extern "C" {
// TextRenderer members with plain names (C linkage, self first)
s32 Knife_Message_TextRenderer_calcTextWidth(const Knife::Message::TextRenderer *self, const Knife::Message::Text *text);
s32 Knife_Message_TextRenderer_getTableValue(s32 index, s32 bgMode); // 0x020a5a44
s32 Knife_Message_TextRenderer_getScreenWidth(s32 isBg, s32 index);  // 0x020a5a58
void *Knife_Message_TextRenderer_getScreenAddress(const Knife::Message::TextRenderer *self, s32 isBg, s32 index,
                                                 s32 bgMode, s32 a, s32 b); // 0x020a590c
void *func_020a59ac(Knife::Message::TextRenderer *self, s32 isBg, s32 index);
// Draw helpers of the BG and OBJ text (0x020c6008 and up)
s32 func_020c6008(void *screen, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
s32 func_020c6550(void *cell, s32 a, s32 b, s32 c, s32 d, s32 flag, s32 e);
void OS_Terminate(void);
// KnifeApp_getField20Address (0x0208dfc0): the object at field 0x20 of the application
void *KnifeApp_getField20Address(void *app);
// 0x020c5e00: draws one character of a text at (x, y) with the palette and returns its advance
s32 func_020c5e00(void *font, void *canvas, s32 x, s32 y, s32 palette, s32 ch);
// TextReader members (plain names, C linkage, the reader first)
s32 Knife_Message_TextReader_readParam_U16(void *self);       // 0x020a29e8
void Knife_Message_TextReader_readParam_Str(void *self, void *out); // 0x020a2a2c
void Knife_Message_RenderTarget_finalize(void *self);  // 0x020a4e8c
}

#endif
