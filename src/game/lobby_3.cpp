#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"
#include "game/subtask.h"

// Functions in this file (original names from the debug build):
//   lobby_selection_dialogUpdate (0x020b4d68)

// lobby_selection_dialogUpdate() (0x020b4d68): updates the selection dialog window, flushes its 0x600 byte screen block
// and sends it to the VBlank queue. Returns 0
extern "C" s32 lobby_selection_dialogUpdate(void);
ARM s32 lobby_selection_dialogUpdate(void) {
    Knife_Message_selectionDialog_update(pauseDialogWindow);
    DC_FlushRange(pauseDialogBuffer, 0x600);
    subTaskSendScr(0, pauseDialogBuffer, 0, 0x600);
    return 0;
}
