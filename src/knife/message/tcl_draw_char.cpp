#include "knife/message/tcl_text.h"

struct NNSG2dGlyphWidth {
    s8 bearing;
    u8 width;
    s8 advance;
};

struct NNSG2dFontBitmap {
    u8 cellWidth;
    u8 cellHeight;
    u16 cellSize;
    u8 format[3];
    u8 orientation;
};

struct NNSG2dFontResource {
    u16 unknown;
    u16 defaultGlyph;
    NNSG2dGlyphWidth defaultEntry;
    NNSG2dFontBitmap *bitmap;
};

struct NNSG2dGlyph {
    const NNSG2dGlyphWidth *width;
    const u8 *bitmap;
};

// The text-box range helpers accept a view of the font as raw bytes.
extern "C" u32 TextBox_FindRange(u8 *self, u32 value);
extern "C" u8 *TextBox_FindRangeEntry(u8 *self, u32 value);

static const u32 rangeNotFound = 0x0000ffff;

extern "C" s8 TclText_DrawChar(const NNSG2dCharCanvas *self, const TclTextSource *token, int x, int y, int color, u16 ch) {
    u32 range = TextBox_FindRange((u8 *)token, ch);
    const NNSG2dFontResource *font;
    NNSG2dGlyph info;
    const NNSG2dGlyphWidth *glyph;
    s32 kind;

    if (range == rangeNotFound) {
        font = (const NNSG2dFontResource *)token->data;
        range = font->defaultGlyph;
    }

    glyph = (const NNSG2dGlyphWidth *)TextBox_FindRangeEntry((u8 *)token, range);
    font = (const NNSG2dFontResource *)token->data;
    info.width = glyph;
    const NNSG2dFontBitmap *descriptor = font->bitmap;
    info.bitmap = (const u8 *)(descriptor + 1) + range * descriptor->cellSize;
    descriptor = font->bitmap;
    kind = descriptor->orientation;

    switch (kind) {
    case 0:
    case 7:
        x += info.width->bearing;
        break;
    case 1:
    case 2:
        x -= descriptor->cellWidth;
        y += info.width->bearing;
        break;
    case 3:
    case 4:
        x -= info.width->bearing + info.width->width;
        y -= descriptor->cellHeight;
        break;
    case 5:
    case 6:
        y -= info.width->bearing + descriptor->cellHeight;
        break;
    }

    const NNSG2dCharCanvasOps *callback = self->operations;
    callback->draw(self, token, x, y, color, &info);
    return info.width->advance;
}
