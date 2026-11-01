#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/knife_msgsys.h"

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispEnq (0x0204ba1c)

extern u8 localPlayerIndex[];
extern u16 data_0212c58c[];
extern u8 data_0217d350[];           // saved state, written by the choice dispatch
extern u8 data_0217d358[];           // choice block of the message box, cleared by func_02029a50
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
ARM void knife_commDispEnq(KNIFE_MSGSYS *msg) {
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
    keys = data_0212c58c[playerIndex];
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
        func_02029a50(data_0217d358, 0x14);
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
