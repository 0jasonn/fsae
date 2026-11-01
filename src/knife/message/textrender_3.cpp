#include "engine/functions.h"
#include "global.h"
#include "knife/message/textrender_api.h"
#include "knife/message/textrender.h"

// Functions in this file (original names from the debug build, or invented where marked):
//   TextRender::onReadBlankTag(int) (0x020a15e0), setFlag83On (0x020a15f4, name invented)

// TextRender::onReadBlankTag(int) (0x020a15e0): moves the start x by the (signed 16-bit) value
void Knife_Message_TextRender_onReadBlankTag(void *a, s32 value) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->startX = self->startX + (s16)value;
}

// Sets flag83 to 1 (0x020a15f4, name invented)
void Knife_Message_TextRender_setFlag83On(void *a) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->flag83 = 1;
}
