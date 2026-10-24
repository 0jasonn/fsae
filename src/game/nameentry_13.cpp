#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/subtask.h"

// Functions in this file (provisional name for a func_ address):
//   nameEntryUIView_cleanupText nameEntryUIView_cleanupText (0x020ae824): tail call to Knife_Message_CleanupTextRenderer (0x020a2d30)

// nameEntryUIView_cleanupText (0x020ae824): jumps to the cleanup of the text renderer
ARM void nameEntryUIView_cleanupText(void) {
    Knife_Message_CleanupTextRenderer();
}
