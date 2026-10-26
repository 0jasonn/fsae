#include "engine/functions.h"
#include "global.h"

// Functions in this file (no original names in the debug build, so plain C linkage; they store into the
// Knife::Message::TextRenderer object, see include/game/message_e.h for the fields):
//   Knife_Message_TextRenderer_setField50_54 (0x020a4f30), Knife_Message_TextRenderer_setField58 (0x020a4f3c),
//   Knife_Message_TextRenderer_setField64 (0x020a510c), Knife_Message_TextRenderer_setField68 (0x020a5114)

extern "C" void Knife_Message_TextRenderer_setField50_54(void *self, s32 a, s32 b);
extern "C" void Knife_Message_TextRenderer_setField58(void *self, s32 value);
extern "C" void Knife_Message_TextRenderer_setField64(void *self, s32 value);
extern "C" void Knife_Message_TextRenderer_setField68(void *self, s32 value);

// TextRenderer +0x64 (0x020a510c)
ARM void Knife_Message_TextRenderer_setField64(void *self, s32 value) {
    *(s32 *)((u8 *)self + 0x64) = value;
}

// TextRenderer +0x68 (0x020a5114)
ARM void Knife_Message_TextRenderer_setField68(void *self, s32 value) {
    *(s32 *)((u8 *)self + 0x68) = value;
}
