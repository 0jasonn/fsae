#include "engine/functions.h"
#include "global.h"
#include "knife/message/knife_message.h"
#include "actor/object/k_bitstream.h"

extern u8 data_0217d350[]; // message state: byte 0 is 1 while a message waits for the window to close

// Scene block of the message (MessageSceneInfo) with the bytes onTerminate uses
typedef struct KnifeMsgSceneTerm {
    u8 unk_00[0x25];
    u8 mode25;     // 0x25: 2 keeps the state as it is
    u8 unk_26[0xd1 - 0x26];
    u8 state;      // 0xd1: set to 2 or 6 at the end of the message
} KnifeMsgSceneTerm;

// MessageTextRender::onTerminate() (0x020a0edc): ends the message, a waiting message is closed in two steps
void Knife_Message_MessageTextRender_onTerminate(void *a) {
    Knife::Message::MessageTextRender *self = (Knife::Message::MessageTextRender *)a;
    KnifeMsgSceneTerm *scene = (KnifeMsgSceneTerm *)self->sceneInfo;

    if (scene->mode25 != 2 && data_0217d350[0] == 1) { scene->state = 6; data_0217d350[8] = data_0217d350[0] = 2; } else scene->state = 2;
}
