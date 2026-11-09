#ifndef WIP_C_MESSAGE_H
#define WIP_C_MESSAGE_H

#include "engine/entity.h"
#include "types.h"

// Per-state function of the message box (messageStates) and the telop box (telopStates).
// A state returns 0 when it is finished for this frame.
typedef int (*MsgStateFunc)(void);

// Telop request block (telopRequest, 0x18 bytes)
typedef struct TelopDrawBits {
    u8 pos : 5;
    u8 rest : 3;
} TelopDrawBits;
typedef struct TelopWork {
    /* 00 */ u8 active;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 flags; // low nibble = 3 while a request is active, bits 4-5 = bank of (id - 1000) / 100
    /* 03 */ u8 unk_03[3];
    /* 06 */ u16 requestId; // bit 15 is set while the telop is busy
} TelopWork;

// One window slot (8 bytes): the telop and message boxes each have a primary and a secondary array of two
typedef struct WindowSlot {
    /* 00 */ u8 unk_00;
    /* 01 */ u8 active;
    /* 02 */ u8 unk_02;
    /* 03 */ u8 unk_03;
    /* 04 */ u8 tileX;
    /* 05 */ u8 tileY;
    /* 06 */ u8 width;
    /* 07 */ u8 height;
} WindowSlot;

// Message box (messageBox) and telop box (telopBox), both 0xe8 bytes with the same layout
// Original name Knife::Message::KNIFE_MSGSYS. The renderer and tokenizer types are defined in enemy/knife_msgsys.h.
struct MsgRendererView;
namespace Knife {
namespace Message {
class TextTokenizer;

typedef struct KNIFE_MSGSYS {
    /* 00 */ struct MsgRendererView *renderer;
    /* 04 */ TextTokenizer *tokenizer;
    /* 08 */ const void *appInfo; // IAppInfoGetter passed to the tokenizer
    /* 0c */ u8 windowPhase; // window opening progress, compared with 1 and 6 in Message (guess)
    /* 0d */ u8 unk_0d;
    /* 0e */ union {
        u8 layoutFlags; // 1 after msgInit/tlpInit
        struct {
            u8 speedSetting : 4; // text speed, indexes the step table data_020d7c18
            u8 frameBank : 2;    // bank passed to Knife_msgFrameDma
            u8 slotBank : 2;     // window slot bank
        };
    };
    /* 0f */ u8 originBits; // low 5 bits: tile origin x of the window
    /* 10 */ union {
        u8 drawFlags; // low 5 bits set to 0x18 by tlpInit
        TelopDrawBits draw;
    };
    /* 11 */ u8 sizeBits;   // low 5 bits: width step, bits 5-7: height step
    /* 12 */ u16 msgId;     // text id of the message
    /* 14 */ u8 unk_14[0x25 - 0x14];
    /* 25 */ u8 openMode; // 2 while the message box is closing
    /* 26 */ u8 unk_26[0x2a - 0x26];
    /* 2a */ u8 unk_2a; // set to 0xa0 by tlpInit
    /* 2b */ u8 unk_2b[0x30 - 0x2b];
    /* 30 */ s16 tokenIndex;
    /* 32 */ s16 tokenSub;
    /* 34 */ u8 cellRows[4][0x1e]; // attribute cells of four text rows, 30 bytes each; shifted up by the roll
    /* ac */ u8 lineQueue[4];      // line changes waiting to run; cleared when the window starts closing
    /* b0 */ u8 unk_b0[0xd0 - 0xb0];
    /* d0 */ u8 state;     // index into the state table
    /* d1 */ u8 subState;  // index into the move table msgMoveTable
    /* d2 */ u8 waitTimer; // frames to wait before the state table runs again
    /* d3 */ u8 unk_d3[0xd6 - 0xd3];
    /* d6 */ u8 unk_d6;     // nonzero makes the wait state return early
    /* d7 */ u8 palletBits; // palette bits passed to Knife_palletChange with 0x40
    /* d8 */ u8 unk_d8[0xda - 0xd8];
    /* da */ s8 moveAccum; // text move accumulator: steps are added until it is positive
    /* db */ u8 unk_db;
    /* dc */ u8 stepTimer; // frames left in the wait state / until the line feed is finished
    /* dd */ u8 unk_dd;
    /* de */ s8 unk_de;
    /* df */ u8 unk_df;
    /* e0 */ u8 lineChangeReq; // set when the line change has to run (knife_msgLineChange)
    /* e1 */ u8 unk_e1[2];
    /* e3 */ u8 windowMode;  // 1 while the window opens, 3 while it closes
    /* e4 */ u8 cursorState; // frames the line feed arrow has been shown; bit 4: cursor drawn (dispCursor)
    /* e5 */ s8 sizeStep;    // window size progress 0..8: msgOpen adds 1, msgClose subtracts 1
    /* e6 */ u8 unk_e6;
    /* e7 */ u8 noTelopWait; // nonzero: the wait does not depend on the telop request
} KNIFE_MSGSYS;
} // namespace Message
} // namespace Knife
typedef Knife::Message::KNIFE_MSGSYS KNIFE_MSGSYS;

extern TelopWork telopRequest;
extern KNIFE_MSGSYS messageBox;
extern KNIFE_MSGSYS telopBox;
extern u8 data_0216efbc[];
extern u8 messageRequest[];
extern u8 data_0217d3c0[];
extern u8 data_0217d4a8[];
extern u8 data_0217d358[];
extern u8 data_0217d3a8[];
extern u8 data_0217d490[];
extern u8 data_0216efc8[];
extern u8 data_0216efd4[];
extern u8 data_0211ed80[];
extern u8 data_021371a0[];
extern u8 data_021361a0[];
extern MsgStateFunc messageStates[];
extern MsgStateFunc telopStates[];
extern VoidFunc msgMoveTable[];
extern WindowSlot telopWindowSlots[];
extern WindowSlot data_0216f010[];
extern WindowSlot data_0216efe0[];
extern WindowSlot data_0216eff0[];
extern u8 cockpitState[];

extern void knife_msgLineChange(KNIFE_MSGSYS *msg, s32 lines);
extern void Knife_msgFrameDma(KNIFE_MSGSYS *msg, u32 bank);
extern void Knife_palletChange(KNIFE_MSGSYS *msg, u8 pallet);

#endif
