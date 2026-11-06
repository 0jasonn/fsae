#ifndef WIP_E_MSGTEXTRENDER_E_H
#define WIP_E_MSGTEXTRENDER_E_H

#include "engine/functions.h"
#include "engine/player.h"
// knife_message.h and text_tokenizer.h both define the Voice and Language enums; rename the first copy locally
#define Voice KnifeMessageVoice
#define Language KnifeMessageLanguage
#define VOICE_0 KM_VOICE_0
#define VOICE_1 KM_VOICE_1
#define VOICE_2 KM_VOICE_2
#define VOICE_3 KM_VOICE_3
#define LANGUAGE_0 KM_LANGUAGE_0
#define LANGUAGE_1 KM_LANGUAGE_1
#define LANGUAGE_2 KM_LANGUAGE_2
#define LANGUAGE_3 KM_LANGUAGE_3
#define LANGUAGE_4 KM_LANGUAGE_4
#define LANGUAGE_5 KM_LANGUAGE_5
#define LANGUAGE_6 KM_LANGUAGE_6
#define LANGUAGE_7 KM_LANGUAGE_7
#include "knife/message/knife_message.h"
#undef Voice
#undef Language
#undef VOICE_0
#undef VOICE_1
#undef VOICE_2
#undef VOICE_3
#undef LANGUAGE_0
#undef LANGUAGE_1
#undef LANGUAGE_2
#undef LANGUAGE_3
#undef LANGUAGE_4
#undef LANGUAGE_5
#undef LANGUAGE_6
#undef LANGUAGE_7
#include "knife/message/text_tokenizer.h"
#include "ui/message.h"

typedef struct MsgPictogramTable {
    u16 entry[0x1f];
} MsgPictogramTable;
extern const MsgPictogramTable data_020de58c;

typedef struct MsgButtonTable {
    u16 entry[14];
} MsgButtonTable;
extern const MsgButtonTable data_020de570;

extern "C" {
void Knife_Message_MessageTextRender_onReadPlainText(Knife::Message::MessageTextRender *self, const Knife::Message::Text *text);
s32 func_020c5e00(void *canvas, void *font, s32 x, s32 y, s32 palette, u16 ch);
void *KnifeApp_getField20Address(void *app);
void Knife_Message_MessageTextRender_onReadPictTag(Knife::Message::MessageTextRender *self, s32 pictogram);
void Knife_Message_MessageTextRender_onReadButtonTag(Knife::Message::MessageTextRender *self, s32 button);
void IconToCanvas(u8 *icon, const void *canvas, s32 x, s32 y);
}

#endif
