#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "ui/message.h"

// Table of telop text ids; declared non-const on purpose: the ROM keeps each table load right before its store.
extern u32 data_021186e4[];

// PlTelopRequest (0x02054f64): requests a telop message. target 0xff asks for message 0x4b3. Otherwise message 0x4b1
// is requested with the player number (index + 1) and the table entries before and at gameState.unk_50[0] as
// the range (params[1] and params[2]).
void PlTelopRequest(u16 target, u16 index) {
    u8 slot;
    if (target == 0xff) {
        TelopRequest(0x4b3);
        return;
    }
    TelopRequest(0x4b1);
    telopRequest.params[0] = (u16)(index + 1);
    slot = gameState.unk_50[0];
    telopRequest.params[1] = (u16)data_021186e4[slot - 1];
    telopRequest.params[2] = (u16)data_021186e4[slot];
}
