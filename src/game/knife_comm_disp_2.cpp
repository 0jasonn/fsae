#include "engine/functions.h"
#include "game/knife_message.h"
#include "game/message.h"
#include "global.h"
#include "types.h"
#include "enemy/knife_msgsys.h"

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispRoll (0x0204b900), knife_commDispEnq (0x0204ba1c)

extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);

// Roll: scrolls the text up by one row (the cell rows and the line queue shift; the top row is cleared) when the line
// change is requested through openMode 2. Otherwise it asks for a line change and moves the scroll bars of data_0217d358.
void knife_commDispRoll(KNIFE_MSGSYS *msg) {
    if (msg->openMode == 2) {
        MIi_CpuCopy16(msg->cellRows[1], msg->cellRows[0], 0x1e);
        MIi_CpuCopy16(msg->cellRows[2], msg->cellRows[1], 0x1e);
        MIi_CpuCopy16(msg->cellRows[3], msg->cellRows[2], 0x1e);
        MIi_CpuClear16(0, msg->cellRows[3], 0x1e);
        msg->lineQueue[0] = msg->lineQueue[1];
        msg->lineQueue[1] = msg->lineQueue[2];
        msg->lineQueue[2] = msg->lineQueue[3];
        msg->lineQueue[3] = 0;
        if (msg->lineQueue[0] != 0) {
            return;
        }
        msg->renderer->canvasOps->clear(&msg->renderer->canvas, 0xf);
        ((Knife::Message::MessageTextRender *)msg->renderer)->setOffset(0, 0);
    } else {
        if (msg->lineQueue[2] == 0) {
            knife_msgLineChange((MsgWork *)msg, 2);
        }
        msg->lineChangeReq = 1;
        data_0217d358[8] -= 2;
        data_0217d358[9] -= 2;
        data_0217d358[10] -= 2;
        data_0217d358[11] -= 2;
    }
    Knife_palletChange((MsgWork *)msg, msg->palletBits | 0x40);
    msg->subState = 1;
}
