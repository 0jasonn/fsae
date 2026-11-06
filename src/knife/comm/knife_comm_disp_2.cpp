#include "engine/functions.h"
#include "knife/message/knife_message.h"
#include "ui/message.h"
#include "global.h"
#include "types.h"
#include "actor/enemy/knife_msgsys.h"

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
            knife_msgLineChange(msg, 2);
        }
        msg->lineChangeReq = 1;
        data_0217d358[8] -= 2;
        data_0217d358[9] -= 2;
        data_0217d358[10] -= 2;
        data_0217d358[11] -= 2;
    }
    Knife_palletChange(msg, msg->palletBits | 0x40);
    msg->subState = 1;
}

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispEnq (0x0204ba1c)

extern u8 localPlayerIndex[];
extern u16 playerKeys[];
extern u8 data_0217d350[];           // saved state, written by the choice dispatch
extern u8 data_0217d358[];           // choice block of the message box, cleared by MemClearFast
extern u8 knifeChoiceMsgIds[];       // message id low byte for each choice state (knifeChoiceMsgIds)
extern u8 *const knifeChoiceRows[];  // rows of direction states for each entry count (knifeChoiceRows)

// Choice block of the message box (data_0217d358): the entry count, the current state, and the entry values
typedef struct KnifeChoiceBlock {
    u8 unk_00[2];
    s8 count;     // 0x02: number of entries
    s8 state;     // 0x03: current choice, index of knifeChoiceMsgIds
    u8 unk_04[4];
    u8 values[4]; // 0x08: values of the entries, compared to find the run from the first one
} KnifeChoiceBlock;

// Enqueues the choice of the message box: the A or B keys select the message of the current state, the direction keys
// move to the next state of the row table. The block is saved and cleared when the choice is taken.
void knife_commDispEnq(KNIFE_MSGSYS *msg) {
    KnifeChoiceBlock *choice = (KnifeChoiceBlock *)data_0217d358;
    void *instance;
    u8 playerIndex;
    u16 keys;
    u8 msgIdLow;
    u16 newMsgId;
    s8 count;
    u16 run;
    u8 first;
    u8 *row;
    u8 packed;
    u8 dirKeys;
    u16 bit;
    u8 newState;

    instance = KnifeApp_getInstance();
    playerIndex = localPlayerIndex[0];
    if (KnifeApp_isWirelessMode(instance) == 0) {
        playerIndex = Knife_Single_SinglePlay_GetInstance()[0];
    }
    keys = playerKeys[playerIndex];
    if ((keys & 9) != 0) {
        msgIdLow = knifeChoiceMsgIds[choice->state];
        if (msgIdLow == 0xff) {
            msg->subState = 3;
            msg->stepTimer = 1;
        } else {
            newMsgId = (u16)((msg->msgId & 0xff00) | msgIdLow);
            msg->msgId = newMsgId;
            Knife_MsgReadPtrFromID((u8 *)msg + 0x24, newMsgId);
            msg->subState = 1;
            msg->unk_df = 3;
        }
        data_0217d350[1] = ((KnifeChoiceBlock *)data_0217d358)->state;
        data_0217d350[0] = 3;
        MemClearFast(data_0217d358, 0x14);
        return;
    }

    dirKeys = (keys & 0xf0) >> 4;
    if (dirKeys == 0 || choice->count <= 1) {
        return;
    }
    count = choice->count;
    run = 1;
    if (count > 1) {
        first = choice->values[0];
        do {
            if (choice->values[run] != first) {
                break;
            }
            run = run + 1;
        } while (count > run);
    }
    row = knifeChoiceRows[count - 1] + count * (run - 1);
    packed = row[choice->state];
    bit = 0;
    do {
        if ((dirKeys & 1) != 0) {
            break;
        }
        dirKeys = dirKeys >> 1;
        bit = bit + 2;
    } while (bit < 8);
    newState = (packed >> bit) & 3;
    if (newState == choice->state) {
        return;
    }
    choice->state = newState;
    SoundReq(0x3d);
}
