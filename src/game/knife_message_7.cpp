#include "engine/functions.h"
#include "global.h"
#include "game/knife_message.h"
#include "game/knife_message_layout.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::MessageTextRender::onReadColorTag (0x020a0dcc). changePalette (0x020a0dfc) is parked in scratch/agentE/nonmatching.
// The method is not declared in game/knife_message.h yet, so it is written with C linkage taking the object first.

using Knife::Message::MessageTextRender;

extern "C" void Knife_Message_MessageTextRender_changePalette(MessageTextRender *self, u8 palette);

// MessageTextRender::onReadColorTag(ColorType) (0x020a0dcc): clears the colour reset flag and sets the palette of the
// colour given by the two tables
extern "C" void Knife_Message_MessageTextRender_onReadColorTag(MessageTextRender *self, s32 colorType);
ARM void Knife_Message_MessageTextRender_onReadColorTag(MessageTextRender *self, s32 colorType) {
    u8 index;
    u8 palette;

    index = data_020de45c[colorType];
    palette = data_020de470[index];
    ((KnifeMsgSceneLayout *)self->sceneInfo)->colorReset = 0;
    Knife_Message_MessageTextRender_changePalette(self, palette);
}
