#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/knife_msgsys.h"

// Functions in this file (module knife_comm, the message box dispatch):
//   knife_commDispMove (0x0204b4dc)

extern "C" int isSkipAvailable(KNIFE_MSGSYS *msg);
extern "C" void knife_commDispMove(KNIFE_MSGSYS *msg);

extern u8 localPlayerIndex[];
extern u8 frameCounter[];
extern u16 data_0212c58c[];
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

// Fields of the message box that KNIFE_MSGSYS does not name yet
typedef struct MsgMoveFields {
    /* 00 */ u8 unk_00[0x0e];
    /* 0e */ u8 speedSetting : 4; // picks the step in data_020d7c18
    /* 0f */ u8 unk_0f[0xda - 0x0f];
    /* da */ s8 moveAccum;    // text move accumulator: steps are added until it is positive
} MsgMoveFields;

// Moves the message text. The accumulator moveAccum is reduced by the speed (1, 2 or 5), then the steps of the speed
// setting are added until it is positive; that many steps run, and each analyzes one part of the token list.
ARM void knife_commDispMove(KNIFE_MSGSYS *msg) {
    s16 steps;
    MsgMoveFields *fields = (MsgMoveFields *)msg;
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
        if ((data_0212c58c[playerIndex] & 1) != 0) {
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
    fields->moveAccum -= speed;
    if (fields->moveAccum > 0) {
        return;
    }
    steps = 0;
    do {
        steps = steps + 1;
        fields->moveAccum += data_020d7c18[fields->speedSetting];
    } while (fields->moveAccum <= 0);

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
        if (msg->unk_dd != 0 || msg->unk_d2[0] != 0) {
            return;
        }
        if (msg->noTelopWait != 0) {
            steps = speed;
        }
        steps = steps - 1;
    } while (steps > 0);
}
