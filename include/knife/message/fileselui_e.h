#ifndef WIP_E_FILESELUI_E_H
#define WIP_E_FILESELUI_E_H

#include "engine/functions.h"
#include "ui/fileselui.h"
#include "ui/fileselui_view.h"
#include "ui/modeselui_e.h"
#include "ui/setuptext_e.h"
#include "knife/comm/multisio.h"
#include "game/setbg.h"

// One value drawn on a file slot: the draw function gets the cell position (x, y within the slot), the value and the
// BG screen buffer. The table data_020de7e4 has one entry per slot value (ruppies, medals, items ...)
typedef void (*FileSelDrawFunc)(s32 x, s32 y, u32 value, u8 *buf);

typedef struct FileSelDrawEntry {
    u8 x;
    u8 y;
    FileSelDrawFunc draw;
} FileSelDrawEntry;

typedef struct FileSelDrawTable {
    FileSelDrawEntry entry[10];
} FileSelDrawTable;

extern const FileSelDrawTable data_020de7e4;
extern u8 data_02124bb4_dummy;

extern "C" {
void fileSelUIView_updateFileselScreen(FileSelUIView *self);
}

#endif
