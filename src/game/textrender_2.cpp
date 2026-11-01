#include "engine/functions.h"
#include "global.h"
#include "game/textrender_api.h"
#include "game/textrender.h"

// Functions in this file (original names from the debug build):
//   TextRender::onReadSelectTag() (0x020a1340)

// TextRender::onReadSelectTag() (0x020a1340): records the position of the next select entry, in cells
void Knife_Message_TextRender_onReadSelectTag(void *a) {
    KnifeTextRender *self = (KnifeTextRender *)a;

    self->selectTable[self->selectCount * 2] = self->startX / 8;
    self->selectTable[self->selectCount * 2 + 1] = self->unk_32 / 8;
    self->selectCount = self->selectCount + 1;
}

// Functions in this file (invented name, the debug build has none):
//   TextRender::onReadNop (0x020a1390): an empty tag handler

// TextRender::onReadNop() (0x020a1390): an empty tag handler
void Knife_Message_TextRender_onReadNop(void *a) {
}
