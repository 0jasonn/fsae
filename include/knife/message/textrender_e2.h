#ifndef WIP_E_TEXTRENDER_E2_H
#define WIP_E_TEXTRENDER_E2_H

#include "types.h"
#include "knife/message/message_classes.h"

extern "C" {
void OS_Terminate(void);
void *Knife_Message_getCESObject_021770b4(void);
u32 Wstr_Length(const u16 *str);
void Knife_Message_TextRenderer_getPlayerName(Knife::Message::TextRenderer *self, s32 index, Knife::Message::Text *out);
}

#endif
