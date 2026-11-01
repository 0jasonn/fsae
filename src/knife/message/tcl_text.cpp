#include "engine/functions.h"
#include "knife/message/tcl_text.h"

// TclText_RunLine (0x020b6b3c): reads code units until the end pointer or a 0 / newline unit.
// Control codes (< 0x20) go to TclText_DispatchTag; other units are drawn by TclText_DrawChar.
void TclText_RunLine(TclText *self, const u16 *end, void *ctx) {
    s32 (*readChar)(const u16 **cursor) = self->source->readChar;
    s32 c;
    while (self->cursor < end) {
        c = readChar(&self->cursor);
        if (c == 0 || c == 0x0a) {
            return;
        }
        if (c < 0x20) {
            TclText_DispatchTag(ctx, c, self);
        } else {
            if (self->pendingAdvance) {
                self->penX += self->advance;
                self->pendingAdvance = 0;
            }
            s8 width = TclText_DrawChar(self->renderer, self->source, self->penX, self->penY, self->extra, c);
            self->penX += width;
            self->pendingAdvance = 1;
        }
    }
}
