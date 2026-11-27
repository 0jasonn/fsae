#include "engine/functions.h" // pause_dialogUpdate returns int (proposed for engine/functions.h)
#include "engine/misc.h"
#include "engine/local_player_index.h"
#include "game/scene.h"
#include "engine/telop_request.h"
#include "engine/message_request.h"
#include "engine/cockpit_state.h"


// pause_dialogUpdate() (0x02053c6c): clears the rows of both HUD tile pages under the pause window, updates the
// selection dialog and copies its rows from pauseDialogBuffer into the page being drawn. Returns 0 (functions.h
// declares it void; the ROM sets r0 = 0).
int pause_dialogUpdate(void) {
    s32 frameX;
    s32 frameY;
    s32 frameW;
    s32 frameH;
    u16 *bgA;
    u16 *bgB;
    u32 row;
    u32 col;
    Knife_Message_selectionDialog_getFrameSize(pauseDialogWindow, &frameX, &frameY, &frameW, &frameH);
    bgA = (u16 *)(data_021361a0[0] + frameY * 0x40);
    bgB = (u16 *)(data_021361a0[1] + frameY * 0x40);
    for (row = 0; row < (u32)frameH; row++) {
        for (col = 0; col < 0x20; col++) {
            bgA[row * 0x20 + col] = 0;
            bgB[row * 0x20 + col] = 0;
        }
    }
    Knife_Message_selectionDialog_update(pauseDialogWindow);
    Knife_Message_selectionDialog_getFrameSize(pauseDialogWindow, &frameX, &frameY, &frameW, &frameH);
    {
        u16 *src;
        u32 copyRow;
        u32 copyCol;
        u16 *dst;
        src = (u16 *)(pauseDialogBuffer + frameY * 0x40);
        dst = (u16 *)(data_021361a0[cockpitState.bufferIndex] + frameY * 0x40);
        for (copyRow = 0; copyRow < (u32)frameH; copyRow++) {
            for (copyCol = 0; copyCol < 0x20; copyCol++) {
                dst[copyRow * 0x20 + copyCol] = src[copyRow * 0x20 + copyCol];
            }
        }
    }
    return 0;
}

// Body of pause_start, written against a PauseState pointer: the stores go through the pointer and the dialog
// arguments are read back from the global, so mwcc reloads them (as the ROM does) and keeps 0 in a register.
static inline void PauseStart_Open(PauseState *state, u8 index) {
    frameCounter.pauseRequest = index | 0x80;
    state->count++;
    state->mode = 0x1e;
    state->resetFlag = 0;
    state->unk_0a = 0;
    if (index == localPlayerIndex) {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
            state->textId = 0x7d6;
            state->unk_0a = 0;
            state->unk_0c = 8;
        } else {
            state->textId = 0x9ca;
            state->unk_0a = 0;
            state->unk_0c = 7;
        }
        pause_dialogDisp(pauseState.textId, pauseState.unk_0c, pauseState.unk_0a);
        messageRequest.unk_01[1] = (messageRequest.unk_01[1] & ~0x30) | 0x30;
        messageRequest.unk_01[1] = (messageRequest.unk_01[1] & ~0xc0) | 0x40;
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 7;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0xa;
        messageRequest.width = 0x10;
    } else {
        TelopRequest(0x83f7);
        telopRequest.params[0] = (u16)(index + 1);
    }
    keyDisable();
}

// pause_start() (0x02053da0): pauses the game for player index. The pausing player gets the pause window (message
// 0x7d6 in wireless mode, 0x9ca otherwise); the others get telop 0x83f7 naming the player.
void pause_start(u8 index) {
    PauseStart_Open(&pauseState, index);
}
