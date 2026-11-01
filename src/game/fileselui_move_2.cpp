#include "engine/functions.h"
#include "game/fileselui_move.h"

// Wrappers of fileSelUIView::move (0x020a7a60) for the mode 0, 1 and 3 move kinds: 0x020a8138, 0x020a8148, 0x020a8168.
// The mode 2 wrapper at 0x020a8158 is matched in symbols.txt as CARD_LockBackup and is not defined here.

// fileSelUIView::move(3) (0x020a8168)
void fileSelUIView_moveOutReturn(void *self) {
    fileSelUIView_move(self, 3);
}
