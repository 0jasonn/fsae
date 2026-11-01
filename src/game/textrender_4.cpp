#include "engine/functions.h"
#include "global.h"
#include "game/textrender_api.h"
#include "game/textrender.h"

// Functions in this file (original names from the debug build, or invented where marked):
//   TextRender::setCenteringParam (0x020a1614), setField83 (0x020a1644, name invented), clearCanvas(int) (0x020a164c)

// TextRender::setCenteringParam(long, unsigned short const*) (0x020a1614): copies count centring values
void Knife_Message_TextRender_setCenteringParam(void *a, s32 count, const u16 *values) {
    KnifeTextRender *self = (KnifeTextRender *)a;
    s32 i;

    for (i = 0; i < count; i++) {
        self->centering[i] = values[i];
    }
}

// Sets flag83 (0x020a1644, name invented)
void Knife_Message_TextRender_setField83(void *a, u8 value) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->flag83 = value;
}

// TextRender::clearCanvas(int) (0x020a164c): clears the canvas with the low four bits of mode through the hook
void Knife_Message_TextRender_clearCanvas(void *a, s32 mode) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->hook->clear((void *)&self->canvas, mode & 0xf);
}
