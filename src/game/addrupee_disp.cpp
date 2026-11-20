// addrupee_disp (0x020274d0): draws the rupee gain/loss counters next to the rupee count (cockpitState +0x14..+0x23).
#include "engine/functions.h"
#include "engine/local_player_index.h"
#include "engine/cockpit_state.h"
#include "engine/frame_counter.h"
#include "game/cockpit_9.h"
#include "knife/message/selectiondialog.h"


void addrupee_disp(void) {
    s32 frame[4];
    s32 value;
    u16 flags;
    u32 digits;
    u16 *page;
    u16 *p;
    u16 i;

    if (frameCounter.pauseRequest != 0 && (frameCounter.pauseRequest & 3) == localPlayerIndex &&
        Knife_Message_selectionDialog_isModal(pauseDialogWindow) != 0) {
        Knife_Message_selectionDialog_getFrameSize(pauseDialogWindow, &frame[3], &frame[2], &frame[1], &frame[0]);
        if (frame[2] + frame[0] >= 0x14) {
            return;
        }
    }
    p = (u16 *)data_021361a0[cockpitState.bufferIndex] + 0x29a;
    for (i = 0; i < 6; i++, p++) {
        p[0] = 0;
        p[0x20] = 0;
    }
    value = cockpitState.rupeeShown;
    if (value == 0) {
        return;
    }
    flags = value >= 0 ? 0x1000 : 0;
    if (value < 0) {
        value = -value;
    }
    if (value > 9999) {
        value = 9999;
    }
    if (value < 10) {
        digits = 1;
    } else if (value < 100) {
        digits = 2;
    } else {
        digits = 3;
        if (value >= 1000) {
            digits = 4;
        }
    }
    cockpit_write_rupee((u16 *)data_021361a0[cockpitState.bufferIndex] + 0x29e, value, digits, flags);
    page = (u16 *)data_021361a0[cockpitState.bufferIndex] + (0x1e - digits) + 0x280;
    if (cockpitState.rupeeShown > 0) {
        page[0] = 0x1030;
        page[0x20] = 0x1050;
    } else {
        page[0] = 0x31;
        page[0x20] = 0x51;
    }
}
