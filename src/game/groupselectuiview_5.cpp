#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"
#include "game/uiobject.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   groupSelectUIView::viewDidDisapper (0x020b11a0)

// groupSelectUIView::viewDidDisapper (0x020b11a0): leaves the text renderer and the title dialog, and clears the
// text buffer of the view
ARM void groupSelectUIView::viewDidDisapper(void) {
    Knife_Message_CleanupTextRenderer();
    knife_title_dialogDelete();
    subTaskSendObjChar(*(void **)(*(u8 **)(data_021806f0 + 0x554) + 0x14), 0, 0x2000);
}
