#include "engine/functions.h"
#include "game/knife_font.h"

// knife_GetFontStrWidth (0x0204c34c): copies the text into a 0x200-byte buffer and measures it with the text box.
s32 knife_GetFontStrWidth_04c34c(const char *text, s32 length) {
    u8 buf[0x200];
    u32 textLen;

    MI_CpuFill(buf, 0, 0x200);
    textLen = Str_Length((const u8 *)text);
    func_02005cc0(buf, text, textLen);
    return TextBox_MeasureWidth(KnifeApp_getField20Address(KnifeApp_getInstance()), length, buf);
}

