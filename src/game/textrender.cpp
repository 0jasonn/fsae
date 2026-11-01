#include "engine/functions.h"
#include "global.h"
#include "game/textrender_api.h"
#include "game/textrender.h"

// Functions in this file (original names from the debug build):
//   TextRender::setup() (0x020a11fc)

// TextRender::setup() (0x020a11fc): resets the centre index and computes the start x from the centring value
void Knife_Message_TextRender_setup(void *a) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->centerIndex = 0;
    self->flag84 = 0;
    if (self->flag83 == 0) {
        self->startX = 0;
    } else {
        self->startX = ((self->widthCells << 3) - self->centering[self->centerIndex]) / 2;
    }
    self->unk_32 = self->unk_77;
}
