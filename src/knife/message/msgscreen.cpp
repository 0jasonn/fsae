#include "knife/comm/msgscrn.h"

// knife_MakeMsgScreen(unsigned short, Knife::Message::KNIFE_MSGSCRN const*) (0x0204c4bc): builds the frame and the text of a
// message dialog from a message screen description. With a frame the frame graphics are copied, the text is measured and
// the frame and its fill are written into the tile map; the text is then requested for the message index (or drawn from
// the dialog text when the index is 0). Returns the size in cells (columns << 16 | rows) of a framed dialog.
u32 knife_MakeMsgScreen(u16 msgId, const void *src) {
    KnifeMsgScrn scrn;
    s32 rows;
    u8 *app;
    s32 j;
    s32 w;
    s32 resSize;
    u16 count;
    u16 *row;
    u16 *dst;
    u16 attr;
    s32 cols;
    u8 lines;
    s32 textCols;
    u8 *res;

    MIi_CpuCopy32(src, &scrn, 0x38);
    rows = cols = 0;
    if (scrn.styleFlags & 1) {
        res = (u8 *)KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &resSize, 0x1b6);
        MIi_CpuCopyFast(res + ((u32)((scrn.styleFlags & 0xe) * resSize) >> 1), scrn.charBase, 0xa0);
        MI_CpuFill(scrn.charBase + 0xa0, (u8)msgFramePalette[scrn.paletteSel], 0x20);
        scrn.charBase += 0xc0;
        w = knife_GetFontStrWidth_04c2e0(msgId, 1, scrn.appWork);
        lines = w >> 16;
        textCols = scrn.textCols;
        rows = (w >> 24) * scrn.lineHeight + (lines << 1);
        if (textCols == 0) {
            textCols = (u16)w;
        }
        scrn.heightCells = rows;
        if (scrn.widthPx < textCols) {
            textCols = scrn.widthPx;
        }
        cols = (textCols + 7) / 8;
        if (!(scrn.layoutFlags & 8)) {
            if (scrn.layoutFlags & 0x10) {
                scrn.screenBuffer += 0x180 - (((rows + 2) / 2) << 5);
            } else if (scrn.layoutFlags & 0x20) {
                scrn.screenBuffer += 0x300 - ((rows + 2) << 5);
            }
        }
        dst = scrn.screenBuffer;
        if (!(scrn.layoutFlags & 1)) {
            scrn.screenBuffer = dst + 1;
        } else {
            cols = (cols + 1) & 0xfe;
            row = dst - (cols / 2 + 1);
            dst = row + 0x10;
            scrn.screenBuffer += 0x10;
        }
        attr = (scrn.charInfo & 0x3ff) | ((scrn.styleFlags & 0xf0) << 8);
        scrn.screenBuffer += 0x20;
        MessageFrameDisp(dst, cols, rows, attr);
        dst += 1;
        count = rows;
        while (count-- != 0) {
            dst += 0x20;
            row = dst;
            j = cols;
            while (j-- > 0) {
                *row++ = attr + 5;
            }
        }
        scrn.charInfo += 6;
    }
    if (msgId != 0) {
        if (scrn.layoutFlags & 1) {
            knife_GetFontStrWidth_04c2e0(msgId, 0, scrn.appWork);
            scrn.screenBuffer -= cols / 2;
            scrn.widthPx = cols << 3;
        }
        app = (u8 *)KnifeApp_getInstance();
        func_020a1100(app + 0x80, 2);
        app = (u8 *)KnifeApp_getInstance();
        func_020a1108(app + 0x80, 0x10);
        Knife_Message_TextRender_setupCanvas((KnifeTextRender *)((u8 *)KnifeApp_getInstance() + 0x80), (const TextRenderMsgScrn *)&scrn, msgId);
        {
            u32 pal = msgFramePalette[scrn.paletteSel] & 0xf;
            KnifeTextRender *render = (KnifeTextRender *)((u8 *)KnifeApp_getInstance() + 0x80);
            render->hook->clear(&render->canvas, pal);
        }
        app = (u8 *)KnifeApp_getInstance();
        KnifeApp_MessageRequest(KnifeApp_getInstance(), msgId, scrn.appWork, app + 0x80, scrn.requestFlags);
    } else {
        if (scrn.layoutFlags & 1) {
            s16 chars = (knife_GetFontStrWidth_04c34c(dialogText, 1) + 7) / 8;
            scrn.screenBuffer -= (chars + 1) / 2;
            scrn.widthPx = chars << 3;
            scrn.heightCells = (scrn.lineHeight + 1) << 1;
        }
        Knife_Message_TextRender_setupFromMsgScrn((KnifeTextRender *)((u8 *)KnifeApp_getInstance() + 0x80), (const TextRenderMsgScrn *)&scrn);
        Knife_Message_TextRender_drawText((KnifeTextRender *)((u8 *)KnifeApp_getInstance() + 0x80), dialogText, ((const u8 *)src)[0x13] & 1);
    }
    if (scrn.styleFlags & 1) {
        return ((u32)(u16)cols << 16) | (u16)rows;
    }
    return 0;
}
