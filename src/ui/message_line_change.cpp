// Needs MessageTextRender::setOffset declared (long, long): this local copy of knife/message/knife_message.h changes
// only that prototype (see the O2 report).
#include "knife/message/knife_message.h"
#include "engine/functions.h"
#include "knife/message/knife_message.h"
#include "ui/message.h"

// Functions in this file (original names from the debug build): knife_msgLineChange

// knife_msgLineChange(KNIFE_MSGSYS*, long) (0x0204b250): starts a line change of the message window: sets the line
// change flags, clears the new canvas line, queues the frame color of the two lines (unless the window is closing),
// scrolls the text by one line and refreshes the palette.
void knife_msgLineChange(KNIFE_MSGSYS *msg, s32 lines) {
    u8 frameColor;
    u8 boxWidth;

    if (lines != 0) {
        msg->unk_e1[0] = 1;
        msg->unk_df = 1;
    } else {
        msg->unk_e1[0] = 0;
    }
    ((Knife::Message::MessageTextRender *)msg->renderer)->clearCanvasLine(msg->unk_e1[0] * 2, 2, 0xf);
    frameColor = msg->unk_e1[0] == 0 ? 0x90 : 0xc8;
    boxWidth = messageRequest.width;
    if (msg->openMode != 2) {
        msg->lineQueue[lines] = frameColor;
        msg->lineQueue[lines + 1] = frameColor + boxWidth;
    }
    ((Knife::Message::MessageTextRender *)msg->renderer)
        ->setOffset(0, msg->unk_e1[0] * ((Knife::Message::MessageTextRender *)msg->renderer)->field34);
    Knife_palletChange(msg, msg->palletBits | 0x40);
}
