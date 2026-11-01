#include "engine/functions.h"
#include "knife/message/knife_font.h"
#include "knife/message/textlength.h"
#include "knife/message/textlength_api.h"
#include "knife/app/knifeapp_b.h"

// knife_GetFontStrWidth (0x0204c2e0): measures the text of a message index with a TextLengthAnalyzer. flag 0 returns the
// longest line; otherwise the packed line counts are returned.
u32 knife_GetFontStrWidth_04c2e0(s32 index, u8 flag, void *tokenizer) {
    KnifeTextLengthAnalyzer analyzer;

    Knife_Message_TextLengthAnalyzer_TextLengthAnalyzer(&analyzer);
    KnifeApp_MessageRequest(KnifeApp_getInstance(), index, tokenizer, &analyzer, 0);
    if (flag == 0) {
        return analyzer.maxLength;
    }
    return analyzer.maxLength | ((analyzer.emptyLines << 24) | (analyzer.nonEmptyLines << 16));
}

// knife_GetFontStrWidth (0x0204c34c): copies the text into a 0x200-byte buffer and measures it with the text box.
s32 knife_GetFontStrWidth_04c34c(const char *text, s32 length) {
    u8 buf[0x200];
    u32 textLen;

    MI_CpuFill(buf, 0, 0x200);
    textLen = Str_Length((const u8 *)text);
    func_02005cc0(buf, text, textLen);
    return TextBox_MeasureWidth(KnifeApp_getField20Address(KnifeApp_getInstance()), length, buf);
}
