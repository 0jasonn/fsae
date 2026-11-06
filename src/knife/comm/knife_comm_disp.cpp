#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "actor/enemy/knife_msgsys.h"
#include "ui/message.h"

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispMove (0x0204b4dc)

extern "C" int isSkipAvailable(KNIFE_MSGSYS *msg);
extern "C" void knife_commDispMove(KNIFE_MSGSYS *msg);

extern u8 localPlayerIndex[];
extern u8 frameCounter[];
extern u16 playerKeys[];
extern const s8 data_020d7c18[]; // step table of the text speed, indexed by the low nibble of speedSetting

// Knife::Message::Token as the move function calls it: slot 2 gives the number of parts, slot 5 analyzes one part
class MsgToken {
public:
    virtual void dtorSlot(void);
    virtual void deletingDtorSlot(void);
    virtual s32 getCount(void) const;
    virtual void slot3(void);
    virtual void slot4(void);
    virtual void analyze(void *analyzer, s32 index) const;
};

// Token list of the message tokenizer (TextTokenizer: the list at +0x20, its count at +0x24)
typedef struct MsgTokenList {
    u8 unk_00[0x20];
    MsgToken **tokens; // 0x20
    s32 count;         // 0x24
} MsgTokenList;

// Moves the message text. The accumulator moveAccum is reduced by the speed (1, 2 or 5), then the steps of the speed
// setting are added until it is positive; that many steps run, and each analyzes one part of the token list.
void knife_commDispMove(KNIFE_MSGSYS *msg) {
    s16 steps;
    MsgTokenList *tokenList;
    MsgToken *token;
    void *instance;
    u8 playerIndex;
    u8 speed;
    u8 frameState;

    if (msg->unk_dd != 0) {
        msg->unk_dd--;
        return;
    }
    if (msg->unk_de != 0) {
        msg->unk_de--;
    }
    instance = KnifeApp_getInstance();
    playerIndex = localPlayerIndex[0];
    if (KnifeApp_isWirelessMode(instance) == 0) {
        playerIndex = Knife_Single_SinglePlay_GetInstance()[0];
    }
    if (msg->openMode != 2) {
        speed = 1;
        if ((playerKeys[playerIndex] & 1) != 0) {
            if (isSkipAvailable(msg) != 0) {
                msg->noTelopWait = speed;
                speed = 5;
            }
        }
    } else {
        speed = 2;
        frameState = frameCounter[0x11];
        if ((frameState & 0x80) != 0 && (frameState & 3) == localPlayerIndex[0]) {
            return;
        }
    }
    msg->moveAccum -= speed;
    if (msg->moveAccum > 0) {
        return;
    }
    steps = 0;
    do {
        steps = steps + 1;
        msg->moveAccum += data_020d7c18[msg->speedSetting];
    } while (msg->moveAccum <= 0);

    ((Knife::Message::MessageTextRender *)msg->renderer)->clearField36();
    speed = 2;
    do {
        tokenList = (MsgTokenList *)msg->tokenizer;
        if (msg->tokenIndex == tokenList->count) {
            return;
        }
        token = tokenList->tokens[msg->tokenIndex];
        if (token->getCount() != 0) {
            token->analyze(msg->renderer, msg->tokenSub);
            msg->tokenSub = msg->tokenSub + 1;
            if (msg->tokenSub == token->getCount()) {
                msg->tokenSub = 0;
                msg->tokenIndex = msg->tokenIndex + 1;
            }
        } else {
            token->analyze(msg->renderer, 0);
            msg->tokenSub = 0;
            msg->tokenIndex = msg->tokenIndex + 1;
        }
        if (((Knife::Message::MessageTextRender *)msg->renderer)->getField36() == 0) {
            return;
        }
        if (msg->unk_dd != 0 || msg->waitTimer != 0) {
            return;
        }
        if (msg->noTelopWait != 0) {
            steps = speed;
        }
        steps = steps - 1;
    } while (steps > 0);
}

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispWait (0x0204b6f4)

// Waits for the message box to be allowed to move on. While the box is closing (openMode 2) it waits for the frame
// counter flag and the telop request; otherwise it waits for the player's flag in playerKeys. Both paths end by
// setting subState to 3 (the shared block at set_sub3 keeps the code layout of the original).
void knife_commDispWait(KNIFE_MSGSYS *msg) {
    u8 playerIndex;
    u8 state;
    u8 remaining;
    void *instance;

    if (msg->openMode != 2) {
        statusUpdate((MSG_STATUS)6);
        if (msg->unk_d6 != 0) {
            return;
        }
        instance = KnifeApp_getInstance();
        playerIndex = localPlayerIndex[0];
        if (KnifeApp_isWirelessMode(instance) == 0) {
            playerIndex = Knife_Single_SinglePlay_GetInstance()[0];
        }
        if ((playerKeys[playerIndex] & 1) != 0) {
            goto set_sub3;
        }
        return;
    }
    state = frameCounter[0x11];
    if ((state & 0x80) != 0 && (state & 3) == localPlayerIndex[0]) {
        return;
    }
    if (msg->noTelopWait == 0) {
        if ((telopRequest.requestId & 0x8000) != 0) {
            msg->stepTimer = 1;
            return;
        }
    } else {
        msg->stepTimer = 0;
    }
    remaining = msg->stepTimer;
    msg->stepTimer = remaining - 1;
    if (remaining != 0) {
        return;
    }
set_sub3:
    msg->subState = 3;
}
